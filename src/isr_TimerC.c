/****************************************************************************
 * @file     isr_TimerC.c
 * @brief    Timer C Interrupt Service Routine
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
 * @brief  This is the interrupt handler for Timer C. This interrupt handler will execute at a 50 KHz rate.
 *         It is in charge of sampling the comparator output and determining whether the BEMF crossing has been
 *         detected. If so, a new commutation point is computed and scheduled.
 *
 * @return none
 *
 */
APP_RAMFUNC void TimerC_IRQHandler(void)
{
if (PAC55XX_TIMERC->INT.CCR0IF)
	{
	// Stall detection is a function of determining when the application gets stuck in the TimerC_getslcomp_samples state
	// If the application can't find the BEMF transition, it won't be able to commutate. As a result, a lack of commutation
	// is to be considered a stall condition. When enabled, the stall detection engine will disable the motor once TIMERC ISR
	// is called too many times without successfully detecting the BEMF transition.

#if STALL_DETECT
	stall_counter++;
	if (stall_counter >= STALL_DETECT_DEF)
		{
		motor_pwm_disable();
		stall_counter = 0;
		app_status |= status_motor_stalled;
		}
#endif

	sample = (PAC55XX_GPIOA->IN.w & NIRQ2_PIN_MASK);	// Sample sensorless comparator output on nIRQ2

	switch(getslcomp_state)
	{
		case TimerC_getslcomp_first_sample:
			if (sample == slcomp_cross_polarity[sl_current_state])
				{
			    timer_d_latch_in = PAC55XX_TIMERD->CTR.w;
			    ++samplecounter;			// Increment sample counter
				last_sample_stored = sample;	// Store good comm state
				getslcomp_state = TimerC_getslcomp_samples;
				}
		break;

		case TimerC_getslcomp_samples:
            if (last_sample_stored == sample)
                ++samplecounter;			// Increment sample counter
            else
            	{
            	samplecounter = 0;
            	getslcomp_state = TimerC_getslcomp_first_sample;
            	}
            if (samplecounter >= good_samples)
            	{
            	motorspeed = timer_d_latch_in + timer_d_offset;															// Determine motor speed to calculate 30 degree delay
            	avg_speed_index++;
            	if (avg_speed_index >= AVG_SMP_CNT)
            		avg_speed_index = 0;
            	avg_speed_array[avg_speed_index] = motorspeed;

            	int i;
            	avg_speed = 0;
            	for (i=0;i<AVG_SMP_CNT;i++)
            	{
            		avg_speed += avg_speed_array[i];
            	}
            	avg_speed = fix16_mul_new_16_16(avg_speed, AVRG_DIV);

#define ANGLE_ADVANCE 1
#define	DUAL_AA 1

#if ANGLE_ADVANCE

            	// Use to calculate commutation advanced delay
            	// GUI sends a number from 0 to 60 which corresponds to 0 to 30 degrees in 0.5 degrees increment (GUI# / 2)
            	// Commutation Advance Delay = motorspeed * half_degree_adv_delay_factor * GUI#
            	// half_degree_adv_delay_factor = 0.00833333 = 1/2 * 1/60

            	fix16_t comm_advanced_delay;

#if DUAL_AA
            	if (slcomp_cross_polarity[sl_current_state])			//Polarity is HI (1)
            		{
            		comm_advanced_delay = fix16_mul_new_16_16(avg_speed << 16, commutation_advanced_rise) >> 16;
            		}
            	else
            		{
            		comm_advanced_delay = fix16_mul_new_16_16(avg_speed << 16, commutation_advanced_fall) >> 16;
            		}

#else
           		comm_advanced_delay = fix16_mul_new_16_16(avg_speed << 16, commutation_advanced_rise) >> 16;
#endif
            	timer_d_offset = PAC55XX_TIMERD->CTR.w - timer_d_latch_in;
            	commutation_time = comm_advanced_delay - timer_d_offset + 3;

#else
            	timer_d_offset = PAC55XX_TIMERD->CTR.w - timer_d_latch_in;
            	commutation_time = (avg_speed >> 1) - timer_d_offset + 3;
#endif

            	__disable_irq();
				PAC55XX_TIMERD->CTR.w = 0;
            	PAC55XX_TIMERD->CCTR0.CTR = commutation_time;			//Initialize Timer D CCTR0 Register
            	PAC55XX_TIMERD->INT.CCR0IF = 1; 					//write 1 to clear interrupt flag
            	PAC55XX_TIMERD->CCTL0.CCINTEN = 1;					//Enable Timer C CCR0 Interrupt
            	__enable_irq();

            	samplecounter = 0;
            	tmp_blanking_cycles = blanking_cycles;
	        	PAC55XX_TIMERD->INT.BASEIF = 1;
	    		PAC55XX_TIMERC->CCTL0.CCINTEN = 0;
	    		stall_counter = 0;
            }

        break;

		case TimerC_getslcomp_blanking_cycles:
			tmp_blanking_cycles--;
			if (tmp_blanking_cycles <= 0)
			{
			getslcomp_state = TimerC_getslcomp_first_sample;
			}
		break;
		}
	PAC55XX_TIMERC->INT.CCR0IF = 1;
	}
}
