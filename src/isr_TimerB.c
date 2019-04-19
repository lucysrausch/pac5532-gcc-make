/****************************************************************************
 * @file     isr_TimerB.c
 * @brief    Timer B Interrupt Service Routine
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
 * @brief  This is the interrupt handler for Timer B
 *
 * @return none
 *
 */
APP_RAMFUNC void TimerB_IRQHandler(void)
{
	if (PAC55XX_TIMERB->INT.BASEIF)
		{
		PAC55XX_TIMERB->INT.BASEIF = 1;
		}
	if (PAC55XX_TIMERB->INT.CCR0IF)
		{
		PAC55XX_TIMERB->INT.CCR0IF = 1;
		}
	if (PAC55XX_TIMERB->INT.CCR1IF)
		{
		PAC55XX_TIMERB->INT.CCR1IF = 1;
		}
	if (PAC55XX_TIMERB->INT.CCR2IF)
		{
		PAC55XX_TIMERB->INT.CCR2IF = 1;
		}
	if (PAC55XX_TIMERB->INT.CCR3IF)
		{
		PAC55XX_TIMERB->INT.CCR3IF = 1;
		}
	if (PAC55XX_TIMERB->INT.CCR4IF)
		{
		PAC55XX_TIMERB->INT.CCR4IF = 1;
		}
	if (PAC55XX_TIMERB->INT.CCR5IF)
		{
		PAC55XX_TIMERB->INT.CCR5IF = 1;
		}
	if (PAC55XX_TIMERB->INT.CCR6IF)
		{
		PAC55XX_TIMERB->INT.CCR6IF = 1;
		}
	if (PAC55XX_TIMERB->INT.CCR7IF)
		{
		PAC55XX_TIMERB->INT.CCR7IF = 1;
		}
}
