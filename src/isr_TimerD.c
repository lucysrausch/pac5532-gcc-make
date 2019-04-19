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
 * @brief	This is the interrupt handler for Timer D, which gets serviced 30 degrees after zero crossing.
 *			When this interrupt is serviced, it will set the current state to the next state.  The current
 *			state needs to change to the next state 30 degrees after the zero crossing has been detected.
 *
 * @return none
 *
 */
APP_RAMFUNC void TimerD_IRQHandler(void)
{
	if (PAC55XX_TIMERD->INT.CCR0IF)
		{	
		PAC55XX_TIMERD->CCTL0.CCINTEN = 0;
		PAC55XX_GPIOB->OUT.w = c_pwm_io_state[sl_current_state];
		PAC55XX_SCC->PBMUXSEL.w = psel_mask[sl_current_state];	        // Set peripheral select state

		// Switch mux to the sensorlesss comparator that needs to be monitored during the next state
		pac5xxx_tile_register_write(ADDR_CFGAIO9, slcomp_mux[sl_current_state]);

		sl_current_state++;
		if (sl_current_state > 5)
			sl_current_state = 0;

		open_loop = 0;
		getslcomp_state = TimerC_getslcomp_blanking_cycles;
		PAC55XX_TIMERC->INT.CCR0IF = 1;
		PAC55XX_TIMERC->CCTL0.CCINTEN = 1;
		PAC55XX_TIMERD->INT.CCR0IF = 1;
		}

	if (PAC55XX_TIMERD->INT.BASEIF)
		{	
		if (sine_mode)
			{				
#if BLDC_DIRECTION
			sine_index += 1;
			if (sine_index >= 360)
				sine_index = 0;

#else
			sine_index -= 1;
			if (sine_index >= 0xFFFE)
				sine_index = 359;
#endif

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

			sl_current_state = fix16_mul_new_16_16(sine_index, ONEDIV60);
						
			}
		else
			{
			PAC55XX_GPIOB->OUT.w = c_pwm_io_state[sl_current_state];
			PAC55XX_SCC->PBMUXSEL.w = psel_mask[sl_current_state];	        // Set peripheral select state

			// Switch mux to the sensorlesss comparator that needs to be monitored during the next state
			pac5xxx_tile_register_write(ADDR_CFGAIO9, slcomp_mux[sl_current_state]);

			sl_current_state++;
			if (sl_current_state > 5)
				sl_current_state = 0;
			getslcomp_state = TimerC_getslcomp_blanking_cycles;
			}	
			
		PAC55XX_TIMERD->INT.BASEIF = 1;
		}
}
