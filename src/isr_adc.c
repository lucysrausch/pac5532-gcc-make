/****************************************************************************
 * @file     isr_adc.c
 * @brief    ADC Interrupt Support
 * @date     13 February 2015
 *
 * @note
 * Copyright (C) 2015 Active Semiconductor. All rights reserved.
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
 * @brief ADC Interrupt Handler routine
 */
APP_RAMFUNC void ADC_IRQHandler(void)
{
	
	single_shunt_current = PAC55XX_ADC->DTSERES2.VAL + PAC55XX_ADC->DTSERES4.VAL + PAC55XX_ADC->DTSERES6.VAL;
	//
#if IREG

	if (!sine_mode)
		{
		ADC_Counter++;
		if (ADC_Counter >= ADC_SKIP)
			{
			ADC_Counter = 0;
			tmp_pi_debug_index = 0;
			pid_run(&iq_pid, fix16_sub(iq_ref, (single_shunt_current << 16)));
			pwm_duty = iq_pid.PI_sat >> 16;
				
			if (pwm_duty == 0) pwm_duty++;
			
			PAC55XX_TIMERA->CCTR4.CTR = pwm_duty;				//Configure U Phase Duty Cycle
			PAC55XX_TIMERA->CCTR5.CTR = pwm_duty;				//Configure V Phase Duty Cycle
			PAC55XX_TIMERA->CCTR6.CTR = pwm_duty;				//Configure W Phase Duty Cycle
			}
		}
#endif
	PAC55XX_ADC->ADCINT.ADCIRQ0IF = 1;
}
