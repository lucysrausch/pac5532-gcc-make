//=============================================================================
// @file     system_pac55xx.c
// @brief    CMSIS Cortex-M4 Device Peripheral Access Layer Source File
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

#include "system_pac55xx.h"
#include "PAC55XX_device.h"

#define CCSCTL	        (*((volatile unsigned long *) 0x400D0400))
#define CCSPLLCTL       (*((volatile unsigned long *) 0x400D0404))

#define __SYS_CLKREF_CLK    (4000000UL)         // Internal oscillator frequency
#define __SYS_ROSC_CLK      (16000000UL)        // Internal oscillator frequency
#define __SYS_DEFAULT_CLK   (__SYS_ROSC_CLK)    // System clock uses ROSC

uint32_t SystemCoreClock = __SYS_DEFAULT_CLK;   // Set System Clock Frequency
uint32_t SystemExternalClock = 0;

void SystemInit (void)
{
    SystemCoreClock = __SYS_DEFAULT_CLK;        // Default to ROSC on startup

#if (__FPU_USED == 1)                           // Keil
    // enable FPU if available and used
    SCB->CPACR |= ( (3UL << 10*2)               // set CP10 Full Access
                  | (3UL << 11*2) );            // set CP11 Full Access
#endif
}

void SystemCoreClockUpdate (void)
{
    uint32_t CCSCTL_reg = CCSCTL;
    uint32_t CCSPLLCTL_reg = CCSPLLCTL;
    
    uint32_t FRCLK_MUX_sel = (CCSCTL_reg & 0x00000003);
    uint32_t SCLK_MUX_sel = (CCSCTL_reg & 0x00000010) >> 4;

    uint32_t HCLK_div = ((CCSCTL_reg & 0x0F000000) >> 24) + 1;
    uint32_t PLL_FB_div = (CCSPLLCTL_reg & 0x003FFF00) >> 8;
    uint32_t PLL_IN_div = (CCSPLLCTL_reg & 0x000000F0) >> 4;
    uint32_t PLL_OUT_div = ((CCSPLLCTL_reg & 0x00000006) >> 2) + 1;

    uint32_t frclk_freq = 0;
    
    switch (FRCLK_MUX_sel)
    {
        case 0:     // ROSC
            frclk_freq = __SYS_ROSC_CLK;
            break;
        case 1:     // CLKREF
            frclk_freq = __SYS_CLKREF_CLK;
            break;
        case 2:     // XTALCLK
        case 3:     // EXTCLK
            frclk_freq = SystemExternalClock;
            break;
    }

    switch (SCLK_MUX_sel)
    {
        case 0:     // FRCLK
            SystemCoreClock = frclk_freq / HCLK_div;
            break;
        case 1:     // PLLCLK
            SystemCoreClock = frclk_freq * PLL_FB_div / PLL_OUT_div / PLL_IN_div / HCLK_div;
            break;
    }
}

void SystemExternalClockUpdate (uint32_t external_clock_freq)
{
    SystemExternalClock = external_clock_freq;
}
