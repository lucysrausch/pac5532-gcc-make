/**************************************************************************//**
 * @file     pac5xxx_driver_timer.c
 * @brief    Firmware driver for the PAC5XXX timer
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
 *
 ******************************************************************************/
 
#include "pac5xxx_driver_timer.h"

RAMFUNC_TIMER void pac5xxx_dtg_config2(DTGCTL_TYPEDEF *p_dtg, uint16_t red, uint16_t fed)
{
    p_dtg->RED = red;
    p_dtg->FED = fed;
    p_dtg->DTEN = 1;
}

RAMFUNC_TIMER void pac5xxx_timer_clock_config(TimerInstance timer, TXCTRL_CLKIN_Type source, TXCTRL_PS_Type prescale)
{
    PAC55XX_TIMER_TYPEDEF * p_timer;
    
    switch (timer)
    {
        case TimerA:
            p_timer = PAC55XX_TIMERA;
            break;
        case TimerB:
            p_timer = PAC55XX_TIMERB;
            break;
        case TimerC:
            p_timer = PAC55XX_TIMERC;
            break;
        case TimerD:
            p_timer = PAC55XX_TIMERD;
            break;
    }
    
    p_timer->CTL.CLKSRC = source;
    p_timer->CTL.CLKDIV = prescale;
}

RAMFUNC_TIMER void pac5xxx_timer_base_config(TimerInstance timer, uint16_t period, int single_shot, TXCTRL_MODE_Type mode, int slave_sync)
{
    PAC55XX_TIMER_TYPEDEF * p_timer;
    
    switch (timer)
    {
        case TimerA:
            p_timer = PAC55XX_TIMERA;
            break;
        case TimerB:
            p_timer = PAC55XX_TIMERB;
            break;
        case TimerC:
            p_timer = PAC55XX_TIMERC;
            break;
        case TimerD:
            p_timer = PAC55XX_TIMERD;
            break;
    }
        
    p_timer->CTL.SSYNC = slave_sync; // Be sure to set sync bit first
    p_timer->PRD.w = period;
    p_timer->CTL.MODE = mode;
    p_timer->CTL.SINGLE = single_shot;
 
}
 
RAMFUNC_TIMER volatile CCTL_TYPEDEF* timer_ccr_to_handle2(TimerInstance timer, int cc_num)
{
  volatile CCTL_TYPEDEF* pCC;
  
  switch (timer)
  {
  case TimerA:
      switch (cc_num)
      {
      case 0:
          pCC = &PAC55XX_TIMERA->CCTL0;
		  PAC55XX_TIMERA->INT.CCR0IF = 1;    // write to clear
          break;
      case 1:
          pCC = &PAC55XX_TIMERA->CCTL1;
		  PAC55XX_TIMERA->INT.CCR1IF = 1;    // write to clear
          break;
      case 2:
          pCC = &PAC55XX_TIMERA->CCTL2;
		  PAC55XX_TIMERA->INT.CCR2IF = 1;    // write to clear
          break;
      case 3:
          pCC = &PAC55XX_TIMERA->CCTL3;
		  PAC55XX_TIMERA->INT.CCR3IF = 1;    // write to clear
          break;
      case 4:
          pCC = &PAC55XX_TIMERA->CCTL4;
	  	  PAC55XX_TIMERA->INT.CCR4IF = 1;    // write to clear
          break;
      case 5:
          pCC = &PAC55XX_TIMERA->CCTL5;
		  PAC55XX_TIMERA->INT.CCR5IF = 1;    // write to clear
          break;
      case 6:
          pCC = &PAC55XX_TIMERA->CCTL6;
		  PAC55XX_TIMERA->INT.CCR6IF = 1;    // write to clear
          break;
      case 7:
          pCC = &PAC55XX_TIMERA->CCTL7;
		  PAC55XX_TIMERA->INT.CCR7IF = 1;    // write to clear
          break;
    }
    break;
    
  case TimerB:
    switch (cc_num)
    {
    case 0:
        pCC = &PAC55XX_TIMERB->CCTL0;
		PAC55XX_TIMERB->INT.CCR0IF = 1;    // write to clear
        break;
    case 1:
        pCC = &PAC55XX_TIMERB->CCTL1;
		PAC55XX_TIMERB->INT.CCR1IF = 1;    // write to clear
        break;
    case 2:
        pCC = &PAC55XX_TIMERB->CCTL2;
		PAC55XX_TIMERB->INT.CCR2IF = 1;    // write to clear
        break;
    case 3:
        pCC = &PAC55XX_TIMERB->CCTL3;
		PAC55XX_TIMERB->INT.CCR3IF = 1;    // write to clear
        break;
    }
    break;
    
  case TimerC:
    switch (cc_num)
    {
    case 0:
        pCC = &PAC55XX_TIMERC->CCTL0;
		PAC55XX_TIMERC->INT.CCR0IF = 1;    // write to clear
        break;
    case 1:
        pCC = &PAC55XX_TIMERC->CCTL1;
		PAC55XX_TIMERC->INT.CCR1IF = 1;    // write to clear
        break;
    }
    break;

  case TimerD:
    switch (cc_num)
    {
    case 0:
        pCC = &PAC55XX_TIMERD->CCTL0;
		PAC55XX_TIMERD->INT.CCR0IF = 1;    // write to clear
        break;
    case 1:
        pCC = &PAC55XX_TIMERD->CCTL1;
		PAC55XX_TIMERD->INT.CCR1IF = 1;   // write to clear
        break;
    }
    break;
  } 
  
  return pCC;
}
