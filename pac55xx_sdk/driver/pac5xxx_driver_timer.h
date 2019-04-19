/**************************************************************************//**
 * @file     pac5xxx_driver_timer.h
 * @brief    Firmware driver for the PAC5XXX timer and DTG units
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
 
#ifndef PAC5XXX_DRIVER_TIMER_H
#define PAC5XXX_DRIVER_TIMER_H

/*------------- Analog to Digital Converter (ADC) ----------------------*/
/** @addtogroup PAC5XXX_Driver_Timer PAC5XXX Analog Timer and DTG Driver
  @{
*/

#include "pac5xxx.h"
#include "pac5xxx_driver_config.h"

#ifdef PAC5XXX_DRIVER_TIMER_RAM
#define RAMFUNC_TIMER	PAC5XXX_RAMFUNC
#else 
#define RAMFUNC_TIMER
#endif

/** Timer Instance for Timer Driver Configuration */
typedef enum { 
    TimerA,
    TimerB,
    TimerC,
    TimerD
} TimerInstance; 

/**
 * @brief  This function clears Timer A
 *
 * @return none
 * @note   This function will set the timer clear bit, which will clear the timer counter, as well as hold the timer in
 *         reset until this bit is cleared. It will also assert the clear output signal to other timers that need to be
 *         synchronized if their timer SYNC bit is set.
 */
RAMFUNC_TIMER static inline  void pac5xxx_timer_a_clear_assert(void) { PAC55XX_TIMERA->CTL.CLR = 1; }

/**
 * @brief  This function releases the clear for Timer A
 *
 * @return none
 * @note   This function will clear the timer clear bit, which will release the timer from reset (if the mode is set to 
 *         up or up/down modes, as well as de-assert the timer clear signal to other timers that need to be synchronzied
 *         if their timer SYNC bit is set.
 */
RAMFUNC_TIMER static inline void pac5xxx_timer_a_clear_deassert(void) { PAC55XX_TIMERA->CTL.CLR = 0; }

/**
 * @brief  This function sets the compare value for the given timer and capture unit
 *
 * @param  value 16b compare value
 * @return None
 */
RAMFUNC_TIMER static inline void pac5xxx_timer_a_ccctr0_value_set(uint16_t value) { PAC55XX_TIMERA->CCTR0.CTR = value; }

/**
 * @brief  This function sets the compare value for the given timer and capture unit
 *
 * @param  value 16b compare value
 * @return None
 */
RAMFUNC_TIMER static inline void pac5xxx_timer_a_ccctr1_value_set(uint16_t value) { PAC55XX_TIMERA->CCTR1.CTR = value; }


/**
 * @brief  This function configures the base timer period, mode and single-use mode
 *         for the given timer
 *
 * @param  timer Timer Instance
 * @param  period Timer Period in clock ticks
 * @param  single_shot Set to 1 for single-use timer mode, 0 for auto-reload
 * @param  mode Timer Mode (up, up/down, etc.)
 * @param  sync Timer slave synchronize (set for slave sync) if set to 1
 * @return none
 *
 */
RAMFUNC_TIMER void pac5xxx_timer_base_config(TimerInstance timer, uint16_t period, int single_shot, TXCTRL_MODE_Type mode, int sync);

/**
 * @brief  This function configures and enables the given Dead-Time Generator (DTG)
 *
 * @param  p_dtg DTG Instance
 * @param  red Risigin Edge Delay
 * @param  fed Trailing Edge Delay
 * @return none
 *
 */
RAMFUNC_TIMER void pac5xxx_dtg_config2(DTGCTL_TYPEDEF *p_dtg, uint16_t red, uint16_t fed);

/**
 * @brief  This function configures the clock source and pre-scaler for the given timer
 *
 * @param  timer Timer Instance
 * @param  source Timer clock input source
 * @param  prescale Timer pre-scaler
 * @return none
 *
 */
RAMFUNC_TIMER void pac5xxx_timer_clock_config(TimerInstance timer, TXCTRL_CLKIN_Type source, TXCTRL_PS_Type prescale);


/**
 * @brief  This function sets the compare value for the given timer and capture unit
 *
 * @param  value 16b compare value
 * @return None
 */
RAMFUNC_TIMER static inline void pac5xxx_timer_b_ccctr0_value_set(uint16_t value) { PAC55XX_TIMERB->CCTR0.CTR = value; }

/**
 * @brief  This function sets the compare value for the given timer and capture unit
 *
 * @param  value 16b compare value
 * @return None
 */
RAMFUNC_TIMER static inline void pac5xxx_timer_b_ccctr1_value_set(uint16_t value) { PAC55XX_TIMERB->CCTR1.CTR = value; }

/**
 * @brief  This function sets the compare value for the given timer and capture unit
 *
 * @param  value 16b compare value
 * @return None
 */
RAMFUNC_TIMER static inline void pac5xxx_timer_b_ccctr2_value_set(uint16_t value) { PAC55XX_TIMERB->CCTR2.CTR = value; }

/*@}*/ /* end of group PAC5XXX_Driver_Timer */

#endif // PAC5XXX_DRIVER_TIMER_H

