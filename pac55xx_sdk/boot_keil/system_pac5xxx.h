//=============================================================================
// @file     system_pac55xx.h
// @brief    CMSIS Cortex-M4 Device Peripheral Access Layer Header File
//           for the Active Semiconductor PAC55XX Device Series
// @note
// Copyright (C) 2017, Active-Semi International
//
// THIS SOFTWARE IS SUBJECT TO A SOURCE CODE LICENSE AGREEMENT WHICH PROVIDES,
// AMONG OTHER THINGS:  (i) THAT IT CAN BE USED ONLY TO ADAPT THE LICENSEE'S
// APPLICATION TO PAC PROCESSORS SUPPLIED BY ACTIVE-SEMI INTERNATIONAL;
// (ii) THAT  IT IS PROVIDED "AS IS" WITHOUT WARRANTY;  (iii) THAT
// ACTIVE-SEMICONDUCTOR IS NOT LIABLE FOR ANY INDIRECT DAMAGES OR FOR DIRECT
// DAMAGES EXCEEDING US$1,500;  AND (iv) THAT IT CAN BE DISCLOSED TO AND USED
// ONLY BY CERTAIN AUTHORIZED PERSONS.
//=============================================================================

#ifndef SYSTEM_PAC55XX_H
#define SYSTEM_PAC55XX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

extern uint32_t SystemCoreClock;        //System Clock Frequency (Core Clock)
extern uint32_t SystemExternalClock;    //System External Clock Frequency (External Clock)

//=============================================================================
// Initialize the system
//
// @return  void
//
// @brief   This function configures the oscillator (PLL) that is part of the
//          microcontroller device. For systems with a variable clock speed,
//          it updates the variable SystemCoreClock. SystemInit is called from
//          the file startup_device. 
//=============================================================================
extern void SystemInit (void);

//=============================================================================
// Updates the variable SystemCoreClock
//
// @return  void
//
// @brief   This function evaluates the clock register settings and calculates
//          the current core clock and must be called whenever the core clock
//          is changed during program execution.
//=============================================================================
extern void SystemCoreClockUpdate (void);

//=============================================================================
// Updates the external clock source frequency
//
// @return  void
//
// @brief   This function updates the external clock source frequency.
//=============================================================================
extern void SystemExternalClockUpdate (uint32_t);

#ifdef __cplusplus
}
#endif

#endif  //SYSTEM_PAC55XX_H
