/****************************************************************************
 * @file     sl_functions.h
 * @brief    Sensorless App Specific Functions
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
 * @brief	This function disables all high and low-side PWMs by driving them low.
 * @return none
 *
 */
void motor_pwm_disable(void)
{
	__disable_irq();

	NVIC_DisableIRQ(TimerD_IRQn);
	NVIC_DisableIRQ(TimerC_IRQn);

	PAC55XX_TIMERD->CTL.BASEIE = 0;

	PAC55XX_GPIOB->OUT.w = 0;			//PORTB OUT GPIO = 0;
	PAC55XX_SCC->PBMUXSEL.w = 0;		//PORTB PSEL is ALL GPIO's
	
	app_status &= ~(status_motor_enabled + status_closed_loop);
	SMS_State = SMS_Idle;
	open_loop = 1;
	sine_mode = 1;

	__enable_irq();
}

/**
 * @brief	This function executes the Speed PI Loop
 *
 * @return 	NONE
 *
 */
APP_RAMFUNC void speed_control_loop(void)
{
	
	tmp_cl_accel++;
	if ((tmp_cl_accel >= cl_accel_period) && (speed_ref_hz != speed_ref_command_hz))
		{
		if (speed_ref_hz < speed_ref_command_hz)
			{
			speed_ref_hz += cl_accel_increase;
			if (speed_ref_hz > speed_ref_command_hz)
				{
				speed_ref_hz = speed_ref_command_hz;
				}
			}
		else if (speed_ref_hz > speed_ref_command_hz)
			{
			speed_ref_hz -= cl_accel_increase;
			if (speed_ref_hz < speed_ref_command)
				{
				speed_ref_hz = speed_ref_command_hz;
				}
			}
		speed_ref_ticks = HertzToTicks((speed_ref_hz << 16), (TIMER_D_FREQ_F16 >> timer_d_div));
		tmp_cl_accel = 0;
		}

	//__disable_irq();						//ONLY DURING DEBUG - WILL IMPACT COMMUTATION
	//tmp_pi_debug_index = 1;					//ONLY DURING DEBUG
	pid_run(&speed_pid, fix16_sub((avg_speed << 16), speed_ref_ticks));
	//__enable_irq();							//ONLY DURING DEBUG - WILL IMPACT COMMUTATION
		
#if IREG
	if (enable_speed_pi)
	{
		iq_ref = speed_pid.PI_sat;
	}

#else
	pwm_duty = speed_pid.PI_sat >> 16;
	
	PAC55XX_TIMERA->CCTR4.CTR = pwm_duty;
	PAC55XX_TIMERA->CCTR5.CTR = pwm_duty;
	PAC55XX_TIMERA->CCTR6.CTR = pwm_duty;
#endif	
}

/**
 * @brief	This function fills the debug table. It is executed every 1 ms.
 *
 * @return none
 *
 */
APP_RAMFUNC void UpdateDebug(void)
{
	debug_array[0] = good_samples << 16;
	debug_array[1] = pwm_duty << 16;
	debug_array[2] = pwm_period_ticks << 16;
	debug_array[3] = app_pwm_period << 16;
	debug_array[4] = motorspeed << 16;
	debug_array[5] = blanking_cycles << 16;
	debug_array[6] = app_status << 16;
	debug_array[7] = hp_over_current_limit << 16;
	debug_array[8] = lp_over_current_limit << 16;
	debug_array[9] = dt_leading_ticks << 16;
	debug_array[10] = dt_trailing_ticks << 16;
	debug_array[11] = sample_delay << 16;
	debug_array[12] = timer_d_div << 16;
	debug_array[13] = TIMER_D_FREQ_F16 >> timer_d_div;
	debug_array[14] = avg_speed << 16;
	debug_array[15] = vin_volts;
	debug_array[16] = 0;
	debug_array[17] = single_shunt_current << 16;
	debug_array[18] = pi_debug_index;
	debug_array[19] = iq_pid.Kp;
	debug_array[20] = iq_pid.Ki;
	debug_array[21] = iq_pid.Td;
	debug_array[22] = iq_pid.min_value;
	debug_array[23] = iq_pid.max_value;
	debug_array[24] = iq_ref;
	debug_array[25] = speed_pid.Kp;
	debug_array[26] = speed_pid.Ki;
	debug_array[27] = speed_pid.Td;
	debug_array[28] = speed_pid.min_value;
	debug_array[29] = speed_pid.max_value;
	debug_array[30] = speed_ref_command;
	debug_array[31] = speed_ref_ticks;
	debug_array[32] = speed_ref_command_hz << 16;
	debug_array[33] = speed_ref_hz << 16;
	debug_array[34] = ol_accel_period << 16;
	debug_array[35] = ol_accel_increase << 16;
	debug_array[36] = stall_counter;
	debug_array[37] = commutation_advanced_rise;
	debug_array[38] = commutation_advanced_fall;
	debug_array[39] = SMS_State << 16;
	debug_array[40] = start_iq_ref << 16;;
	debug_array[41] = align_time_ms << 16;
	debug_array[42] = ol_start_hz << 16;
	debug_array[43] = ol_switchover_hz << 16;
	debug_array[44] = cl_accel_period << 16;
	debug_array[45] = cl_accel_increase << 16;
	debug_array[46] = enable_speed_pi;
	debug_array[47] = 0;
	debug_array[48] = beep_freq_hz;
	debug_array[50] = sine_scale;
	debug_array[51] = sine_scale_increase;
	debug_array[52] = sine_scale_max;
	debug_array[53] = oc_flags;
	debug_array[54] = PAC55XX_ADC->DTSERES3.VAL << 16;
	debug_array[55] = PAC55XX_ADC->DTSERES4.VAL << 16;
	debug_array[56] = PAC55XX_ADC->DTSERES5.VAL << 16;
	debug_array[57] = PAC55XX_ADC->DTSERES6.VAL << 16;
}
