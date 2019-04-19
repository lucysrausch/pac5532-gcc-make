/****************************************************************************
 * @file     isr_TimerD.c
 * @brief    Timer D Interrupt Service Routine
 * @date     22 September 2015
 *
 * @note
 * Copyright (C) 2015, Active-Semi International
 *
 * THIS SOFTWARE IS SUBJECT TO A SOURCE CODE LICENSE AGREEMENT WHICH PROVIDES,
 * AMONG OTHER THINGS:  (i) THAT IT CAN BE USED ONLY TO ADAPT THE LICENSEE'S
 * APPLICATION TO PAC PROCESSORS SUPPLIED BY ACTIVE-SEMI INTERNATIONAL;
 * (ii) THAT  IT IS PROVIDED "AS IS" WITHOUT WARRANTY;  (iii) THAT
 * ACTIVE-SEMICONDUCTOR IS NOT LIABLE FOR ANY INDIRECT DAMAGES OR FOR DIRECT
 * DAMAGES EXCEEDING US$1,500;  AND (iv) THAT IT CAN BE DISCLOSED TO AND USED
 * ONLY BY CERTAIN AUTHORIZED PERSONS.
 ******************************************************************************/
#define INCLUDE_EXTERNS
#include "bldc_common.h"

/**
 * @brief  The state machine is in charge of coordination motor operation. Interval is 1 ms.
 *
 * @return none
 *
 */
void state_machine(void)
{
	switch (SMS_State)
				{
				case SMS_Idle:
				//do nothing
				break;

				case SMS_Align:
								
				app_status &= ~status_motor_stalled;
				PAC55XX_SCC->PBMUXSEL.w =  MOTOR_OUT_PORTB_ALL_PWMS;
				
	#if BLDC_DIRECTION
				sine_index = 0;
	#else
				sine_index = 359;
	#endif
				
				sine_scale_increase = fix16_mul_new_16_16(pwm_period_ticks << 16, sine_scale_max);
				sine_scale_increase = fix16_div(sine_scale_increase, align_time_ms << 16) >> 16;
				sine_scale = 0;

				fix16_t temp0, temp1, temp2;
				
				temp0 = fix16_mul_new_16_16(sine_wave_3phase[sine_index][0], sine_scale);
				temp1 = fix16_mul_new_16_16(sine_wave_3phase[sine_index][1], sine_scale);
				temp2 = fix16_mul_new_16_16(sine_wave_3phase[sine_index][2], sine_scale);

				if (temp0 == 0) temp0++;
				if (temp1 == 0) temp1++;
				if (temp2 == 0) temp2++;

				PAC55XX_TIMERA->CCTR4.CTR = temp0;
				PAC55XX_TIMERA->CCTR5.CTR = temp1;
				PAC55XX_TIMERA->CCTR6.CTR = temp2;
				
				blanking_cycles = START_BLANKING_CYCLES;
				good_samples = START_GOOD_SAMPLES;

				SMS_Counter = 0;
				SMS_State = SMS_Align_Wait;
				app_status |= status_motor_enabled;
				open_loop = 1;
				sine_mode = 1;
				
				PAC55XX_TIMERD->CTL.MODE = 0;
				
				break;

				case SMS_Align_Wait:
					
				SMS_Counter ++;
				if (SMS_Counter > align_time_ms)
					{
					SMS_Counter = 0;
					SMS_State = SMS_Start_Motor;
					}
				else
					{
					sine_scale += sine_scale_increase;

					fix16_t temp0, temp1, temp2;

					temp0 = fix16_mul_new_16_16(sine_wave_3phase[sine_index][0], sine_scale);
					temp1 = fix16_mul_new_16_16(sine_wave_3phase[sine_index][1], sine_scale);
					temp2 = fix16_mul_new_16_16(sine_wave_3phase[sine_index][2], sine_scale);
						
					temp0++;
					temp1++;
					temp2++;

					PAC55XX_TIMERA->CCTR4.CTR = temp0;
					PAC55XX_TIMERA->CCTR5.CTR = temp1;
					PAC55XX_TIMERA->CCTR6.CTR = temp2;
					}
				break;

				case SMS_Align_Hold:
				SMS_Counter++;
				if (SMS_Counter > 10)
					{
					SMS_State = SMS_Start_Motor;
					}
				break;

				case SMS_Start_Motor:

				speed_ref_hz = ol_start_hz;
				speed_ref_ticks = HertzToTicksSine((speed_ref_hz << 16), (TIMER_D_FREQ_F16 >> timer_d_div));

				PAC55XX_TIMERD->PRD.w = speed_ref_ticks >> 16;
				PAC55XX_TIMERD->CTL.BASEIE = 1;										// Enable Timer D Base Interrupt
				PAC55XX_TIMERD->INT.BASEIF = 1;
				PAC55XX_TIMERD->CTL.MODE = TxCTL_MODE_UP;

				NVIC_EnableIRQ(TimerD_IRQn);
				SMS_State = SMS_Accel_Motor;
				SMS_Counter = 0;
				avg_speed_index = 0;
				break;

				case SMS_Accel_Motor:
				
				SMS_Counter++;
				if (SMS_Counter >= ol_accel_period)
					{
					SMS_Counter = 0;
					speed_ref_hz += ol_accel_increase;
						
					if (speed_ref_hz < ol_switchover_hz)
						{
						speed_ref_ticks = HertzToTicksSine(speed_ref_hz << 16, (TIMER_D_FREQ_F16 >> timer_d_div));
						pac5xxx_timer_base_config(TimerD, (speed_ref_ticks >> 16), 0, TxCTL_MODE_UP, 0);
						motorspeed = HertzToTicks(speed_ref_hz << 16, (TIMER_D_FREQ_F16 >> timer_d_div)) >> 16;	
						}					
					
					else if ((speed_ref_hz >= ol_switchover_hz) & switchover)
						{
						speed_ref_hz = ol_switchover_hz;
						PAC55XX_TIMERD->CTL.BASEIE = 0;	
						sine_mode = 0;
						PAC55XX_GPIOB->OUT.w = c_pwm_io_state[sl_current_state];
						PAC55XX_SCC->PBMUXSEL.w = psel_mask[sl_current_state];	        // Set peripheral select state
						sl_current_state++;				
	#if IREG
						iq_ref = start_iq_ref << 16;
						iq_pid.PI_sat = iq_pid.min_value;
						iq_pid.I_prev = iq_pid.min_value;

						speed_pid.PI_sat = iq_ref;
						speed_pid.I_prev = iq_ref;
	#else
						speed_pid.PI_sat = iq_pid.min_value;
						speed_pid.I_prev = iq_pid.min_value;
	#endif
						
						//motorspeed = HertzToTicks(speed_ref_hz << 16, (TIMER_D_FREQ_F16 >> timer_d_div)) >> 16;
			        	PAC55XX_TIMERD->CCTR0.CTR = motorspeed >> 1;
						PAC55XX_TIMERD->PRD.w = 0xFFFF;
						PAC55XX_TIMERD->CTR.w = 0;

			        	tmp_blanking_cycles = blanking_cycles;
						PAC55XX_TIMERC->CCTL0.CCINTEN = 0;					//Disable TIMER C CCR0 ISR
						PAC55XX_TIMERC->INT.CCR0IF = 1;						//Clear TIMER C CCR0 Flag
						PAC55XX_TIMERD->INT.CCR0IF = 1;						//Clear TIMER D CCR0 Flag
						PAC55XX_TIMERD->CCTL0.CCINTEN = 1;					//Enable TIMER D CCR0 Interrupt (to cause commutation at required time)

						NVIC_EnableIRQ(TimerC_IRQn);

						char i;
			        	avg_speed = 0;
			        	for (i=0;i<=5;i++)
			        		{
			        		avg_speed_array[i] = motorspeed;
			        		}
						avg_speed = motorspeed;
						open_loop = 0;
							
						app_status |= status_closed_loop;
						SMS_State = SMS_StartUp;
						}
					else
						{
						speed_ref_hz = ol_switchover_hz;
						speed_ref_ticks = HertzToTicksSine(speed_ref_hz << 16, (TIMER_D_FREQ_F16 >> timer_d_div));
						pac5xxx_timer_base_config(TimerD, (speed_ref_ticks >> 16), 0, TxCTL_MODE_UP, 0);
						}
					}
					
				break;

				case SMS_StartUp:
				SMS_Counter++;
				if (SMS_Counter > OL_CL_TRANSITION_MS)
					{
					SMS_State = SMS_Idle;
					blanking_cycles = RUN_BLANKING_CYCLES;
					good_samples = RUN_GOOD_SAMPLES;
					}
				break;

				case SMS_Beep_ON:
					app_status &= ~status_motor_stalled;

					PAC55XX_TIMERA->CCTR4.CTR = beep_pwm_dc;
					PAC55XX_TIMERA->CCTR5.CTR = beep_pwm_dc;
					PAC55XX_TIMERA->CCTR6.CTR = beep_pwm_dc;

					sl_current_state = 0;

					PAC55XX_GPIOB->OUT.w = c_pwm_io_state[sl_current_state];
					PAC55XX_SCC->PBMUXSEL.w = psel_mask[sl_current_state];	        // Set peripheral select state

					sl_current_state++;

					app_status |= status_motor_enabled;
					open_loop = 1;
					sine_mode = 0;

					speed_ref_hz = beep_freq_hz;
					speed_ref_ticks = HertzToTicks((speed_ref_hz << 16), (TIMER_D_FREQ_F16 >> timer_d_div));
					pac5xxx_timer_base_config(TimerD, (speed_ref_ticks >> 16), 0, TxCTL_MODE_UP, 0);
					PAC55XX_TIMERD->CTL.BASEIE = 1;										// Enable Timer D Base Interrupt
					NVIC_EnableIRQ(TimerD_IRQn);
					SMS_State = SMS_Idle;
					break;
				case SMS_Beep_OFF:
					PAC55XX_GPIOB->OUT.w = 0;			//PORTB OUT GPIO = 0;
					PAC55XX_SCC->PBMUXSEL.w = 0;		//PORTB PSEL is ALL GPIO's					app_status &= ~status_motor_enabled;
					PAC55XX_TIMERD->CTL.BASEIE = 0;									// Disable Timer D Base Interrupt
					NVIC_DisableIRQ(TimerD_IRQn);
					SMS_State = SMS_Idle;
					break;
				case SMS_Diag_Init:
					diag_note_offset = 0;
					SMS_Counter = 50;
					SMS_State = SMS_Diag_On_Wait;
					beep_on(diag_tunes[diag_message_offset][diag_note_offset]);
					break;
				case SMS_Diag_On_Wait:
					SMS_Counter--;
					if (SMS_Counter == 0)
						{
						beep_off();
						SMS_Counter = 10;
						SMS_State = SMS_Diag_Off_Wait;
						}
					break;
				case SMS_Diag_Off_Wait:
					SMS_Counter--;
					if (SMS_Counter == 0)
						{
						diag_note_offset++;
						if (diag_note_offset <= 3)
							{
							SMS_Counter = 50;
							SMS_State = SMS_Diag_On_Wait;
							beep_on(diag_tunes[diag_message_offset][diag_note_offset]);
							}
						else
							{
							SMS_State = SMS_Idle;
							}
						}
					break;
						
			}
}

