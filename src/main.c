/****************************************************************************
 * @file     main.c
 * @brief    Firmware for PAC BLDC controller BEMF sensorless motor
 * @date     13 February 2015
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
#include "bldc_common.h"
/**
 * @brief  Main program that performs PAC configuration and handles real time task management
 *
 * @return none
 *
 */

int dummy = 0;

int main(void)
{
	__disable_irq();
	peripheral_init();
	app_init();
	cafe_init();
	UART_init();
	adc_init();
	pi_init();
	__enable_irq();

	while(1)
		{
		while (!millisecond);
		millisecond = 0;
		check_adc();
		state_machine();
		if (app_status & status_closed_loop)
			{
			speed_control_loop();
			}

		#if CHECK_VBAT
			check_vbat();
		#endif

		#if UPDATE_DEBUG
			UpdateDebug();
		#endif

	}
}
