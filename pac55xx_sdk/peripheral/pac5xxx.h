//==============================================================================
/// @file     pac5xxx.h
///
/// @brief    CMSIS Cortex-M4 Peripheral Access Layer Header File for
///           for the Active Semiconductor PAC55XX Device Family
///
/// @note
/// Copyright (C) 2017, Active-Semi International
///
/// THIS SOFTWARE IS SUBJECT TO A SOURCE CODE LICENSE AGREEMENT WHICH PROVIDES,
/// AMONG OTHER THINGS:  (i) THAT IT CAN BE USED ONLY TO ADAPT THE LICENSEE'S
/// APPLICATION TO PAC PROCESSORS SUPPLIED BY ACTIVE-SEMI INTERNATIONAL;
/// (ii) THAT  IT IS PROVIDED "AS IS" WITHOUT WARRANTY;  (iii) THAT
/// ACTIVE-SEMICONDUCTOR IS NOT LIABLE FOR ANY INDIRECT DAMAGES OR FOR DIRECT
/// DAMAGES EXCEEDING US$1,500;  AND (iv) THAT IT CAN BE DISCLOSED TO AND USED
/// ONLY BY CERTAIN AUTHORIZED PERSONS.
///
//==============================================================================
#ifndef PAC5XXX_H
#define PAC5XXX_H

#ifdef __cplusplus
extern "C" {
#endif

// Compiler Specific Definitions
#ifdef __ICCARM__           // IAR C Compiler
#define PAC5XXX_RAMFUNC             __ramfunc
#define PAC5XXX_OPTIMIZE_SPEED_ON   _Pragma("optimize=high speed")
#define PAC5XXX_OPTIMIZE_SPEED_OFF  // IAR doesn't need optimize off; it's only on for one function
#define UNUSED_PARAM
#elif defined __GNUC__      // GNU C Compiler
#define PAC5XXX_RAMFUNC             __attribute__((__long_call__))
#define PAC5XXX_OPTIMIZE_SPEED_ON   __attribute__((optimize("O3")))
#define PAC5XXX_OPTIMIZE_SPEED_OFF  // GCC doesn't need optimize off; it's only on for one function
#define UNUSED_PARAM                __attribute__((unused))
#elif defined __CC_ARM      // Keil RealView C Compiler
#define PAC5XXX_RAMFUNC             __attribute__((section("ramfunc")))
#define PAC5XXX_OPTIMIZE_SPEED_ON   _Pragma("push") _Pragma("Otime")
#define PAC5XXX_OPTIMIZE_SPEED_OFF  _Pragma("pop")
#define UNUSED_PARAM
#else
#define PAC5XXX_RAMFUNC
#define PAC5XXX_OPTIMIZE_SPEED_ON
#define PAC5XXX_OPTIMIZE_SPEED_OFF
#define UNUSED_PARAM
#endif

// version release state
#define  PAC55XX_RELEASED       0
#define  PAC55XX_RC             1
#define  PAC55XX_BETA           2
#define  PAC55XX_ALPHA          3
#define  PAC55XX_IN_DEVELOPMENT 4
#define  PAC5XXX_RELEASED       PAC55XX_RELEASED
#define  PAC5XXX_RC             PAC55XX_RC
#define  PAC5XXX_BETA           PAC55XX_BETA
#define  PAC5XXX_ALPHA          PAC55XX_ALPHA
#define  PAC5XXX_IN_DEVELOPMENT PAC55XX_IN_DEVELOPMENT

//==============================================================================
//--------------- Interrupt Number Definition ----------------------------------
//==============================================================================
typedef enum IRQn
{
//-------------------  Cortex-M4 Processor Exceptions Numbers  ---------------------------------
  Reset_IRQn                    = -15,      // Reset Vector, invoked on Power up and warm reset
  NonMaskableInt_IRQn           = -14,      // Non Maskable Interrupt
  HardFault_IRQn                = -13,      // Hard Fault Interrupt
  MemManageFault_IRQn           = -12,      // MemManage fault Handler
  BusFault_IRQn                 = -11,      // BusFault Handler
  UsageFault_IRQn               = -10,      // Usage Fault Handler
  SVCall_IRQn                   = -5,       // SV Call Interrupt
  PendSV_IRQn                   = -2,       // Pend SV Interrupt
  SysTick_IRQn                  = -1,       // System Tick Interrupt

//---------------------  PAC55XX Specific Interrupt Numbers  -----------------------------------
  MemCtl_IRQn                   = 0,        // Memory Controller Interrupt
  Wdt_IRQn                      = 1,        // Watchdog Timer Interrupt
  RTC_IRQn                      = 2,        // Real-Time Clock Timer Interrupt
  ADC0_IRQn                     = 3,        // ADC 0 Interrupt
  ADC1_IRQn                     = 4,        // ADC 1 Interrupt
  ADC2_IRQn                     = 5,        // ADC 2 Interrupt
  ADC3_IRQn                     = 6,        // ADC 3 Interrupt
  TimerA_IRQn                   = 7,        // Timer A Interrupt
  TimerB_IRQn                   = 8,        // Timer B Interrupt
  TimerC_IRQn                   = 9,        // Timer C Interrupt
  TimerD_IRQn                   = 10,       // Timer D Interrupt
  TimerA_Qep_IRQn               = 11,       // Timer A QEP Interrupt
  TimerB_Qep_IRQn               = 12,       // Timer B QEP Interrupt
  TimerC_Qep_IRQn               = 13,       // Timer C QEP Interrupt
  TimerD_Qep_IRQn               = 14,       // Timer D QEP Interrupt
  GpioA_IRQn                    = 15,       // GPIO Port A Interrupt
  GpioB_IRQn                    = 16,       // GPIO Port B Interrupt
  GpioC_IRQn                    = 17,       // GPIO Port C Interrupt
  GpioD_IRQn                    = 18,       // GPIO Port D Interrupt
  GpioE_IRQn                    = 19,       // GPIO Port E Interrupt
  GpioF_IRQn                    = 20,       // GPIO Port F Interrupt
  GpioG_IRQn                    = 21,       // GPIO Port F Interrupt
  I2C_IRQn                      = 22,       // I2C Interrupt
  USARTA_IRQn                   = 23,       // USART A Interrupt
  USARTB_IRQn                   = 24,       // USART B Interrupt
  USARTC_IRQn                   = 25,       // USART C Interrupt
  USARTD_IRQn                   = 26,       // USART D Interrupt
  CAN_IRQn                      = 27,       // CAN Interrupt
  GPTimerA_IRQn                 = 28,       // GP Timer A Interrupt
  GPTimerB_IRQn                 = 29,       // GP Timer B Interrupt
  SCC_IRQn                        = 30        // System Clock Control Interrupt
} IRQn_Type;


//==============================================================================
//================      Processor and Core Peripheral Section     ==============
//==============================================================================
//TODO: verify these values
// Configuration of the Cortex-M4 Processor and Core Peripherals
#define __CM4_REV                 0x0001    // Core Revision r0p1
#define __NVIC_PRIO_BITS          4         // Number of Bits used for Priority Levels
#define __Vendor_SysTickConfig    0         // Set to 1 if different SysTick Config is used
#define __MPU_PRESENT             1         // MPU present or not
#define __FPU_PRESENT             1         // FPU present or not

#include <core_cm4.h>                       // Cortex-M# processor and core peripherals


//-------------------  Start of section using anonymous unions  ------------------
#if defined(__CC_ARM)        // Keil Compiler
    //#pragma push          //TODO: put back and figure out why it gives error
    #pragma anon_unions
#elif defined(__ICCARM__)    // IAR Compiler
    #pragma language=extended
#elif defined(__GNUC__)        // GCC Compiler
    // anonymous unions are enabled by default */
#else
    #warning Compiler type not supported
#endif

#include "pac5xxx_adc.h"                      	// PAC55XX ADC include file
#include "pac5xxx_can.h"                      	// PAC55XX CAN include file
#include "pac5xxx_crc.h"                      	// PAC55XX CRC include file
#include "pac5xxx_gpio.h"                     	// PAC55XX GPIO include file
#include "pac5xxx_i2c.h"                      	// PAC55XX I2C include file
#include "pac5xxx_memory.h"                   	// PAC55XX Memory Controller include file
#include "pac5xxx_rtc.h"                    	// PAC55XX RTC include file
#include "pac5xxx_scc.h"                      	// PAC55XX System and Clock Control include file
#include "pac5xxx_timers.h"                     // PAC55XX Timer include file
#include "pac5xxx_gp_timers.h"                  // PAC55XX GP Timer include file
#include "pac5xxx_uart.h"                     	// PAC55XX UART include file
#include "pac5xxx_ssp.h"                     	// PAC55XX SSP include file
#include "pac5xxx_wwdt.h"                      	// PAC55XX Watchdog Timer include file

//==============================================================================
//                         Peripheral memory map
//==============================================================================
// Peripheral and SRAM base address
#define PAC55XX_FLASH_BASE          (0x00000000UL)                      // FLASH Base Address
#define PAC55XX_FLASH_SEG0_BASE     (0x00000000UL)                      // FLASH segment 0 Base Address
#define PAC55XX_FLASH_SEG1_BASE     (0x00000400UL)                      // FLASH segment 1 Base Address
#define PAC55XX_FLASH_SEG2_BASE     (0x00000800UL)                      // FLASH segment 2 Base Address
#define PAC55XX_FLASH_SEG3_BASE     (0x00000C00UL)                      // FLASH segment 3 Base Address
#define PAC55XX_FLASH_SEG4_BASE     (0x00001000UL)                      // FLASH segment 4 Base Address
#define PAC55XX_FLASH_SEG5_BASE     (0x00001400UL)                      // FLASH segment 5 Base Address
#define PAC55XX_FLASH_SEG6_BASE     (0x00001800UL)                      // FLASH segment 6 Base Address
#define PAC55XX_FLASH_SEG7_BASE     (0x00001C00UL)                      // FLASH segment 7 Base Address
#define PAC55XX_FLASH_SEG8_BASE     (0x00002000UL)                      // FLASH segment 8 Base Address
#define PAC55XX_FLASH_SEG9_BASE     (0x00002400UL)                      // FLASH segment 9 Base Address
#define PAC55XX_FLASH_SEG10_BASE    (0x00002800UL)                      // FLASH segment 10 Base Address
#define PAC55XX_FLASH_SEG11_BASE    (0x00002C00UL)                      // FLASH segment 11 Base Address
#define PAC55XX_FLASH_SEG12_BASE    (0x00003000UL)                      // FLASH segment 12 Base Address
#define PAC55XX_FLASH_SEG13_BASE    (0x00003400UL)                      // FLASH segment 13 Base Address
#define PAC55XX_FLASH_SEG14_BASE    (0x00003800UL)                      // FLASH segment 14 Base Address
#define PAC55XX_FLASH_SEG15_BASE    (0x00003C00UL)                      // FLASH segment 15 Base Address
#define PAC55XX_FLASH_SEG16_BASE    (0x00004000UL)                      // FLASH segment 16 Base Address
#define PAC55XX_FLASH_SEG17_BASE    (0x00004400UL)                      // FLASH segment 17 Base Address
#define PAC55XX_FLASH_SEG18_BASE    (0x00004800UL)                      // FLASH segment 18 Base Address
#define PAC55XX_FLASH_SEG19_BASE    (0x00004C00UL)                      // FLASH segment 19 Base Address
#define PAC55XX_FLASH_SEG20_BASE    (0x00005000UL)                      // FLASH segment 20 Base Address
#define PAC55XX_FLASH_SEG21_BASE    (0x00005400UL)                      // FLASH segment 21 Base Address
#define PAC55XX_FLASH_SEG22_BASE    (0x00005800UL)                      // FLASH segment 22 Base Address
#define PAC55XX_FLASH_SEG23_BASE    (0x00005C00UL)                      // FLASH segment 23 Base Address
#define PAC55XX_FLASH_SEG24_BASE    (0x00006000UL)                      // FLASH segment 24 Base Address
#define PAC55XX_FLASH_SEG25_BASE    (0x00006400UL)                      // FLASH segment 25 Base Address
#define PAC55XX_FLASH_SEG26_BASE    (0x00006800UL)                      // FLASH segment 26 Base Address
#define PAC55XX_FLASH_SEG27_BASE    (0x00006C00UL)                      // FLASH segment 27 Base Address
#define PAC55XX_FLASH_SEG28_BASE    (0x00007000UL)                      // FLASH segment 28 Base Address
#define PAC55XX_FLASH_SEG29_BASE    (0x00007400UL)                      // FLASH segment 29 Base Address
#define PAC55XX_FLASH_SEG30_BASE    (0x00007800UL)                      // FLASH segment 30 Base Address
#define PAC55XX_FLASH_SEG31_BASE    (0x00007C00UL)                      // FLASH segment 31 Base Address

#define PAC55XX_FLASH_SEG32_BASE    (0x00008000UL)                      // FLASH segment 32 Base Address
#define PAC55XX_FLASH_SEG33_BASE    (0x00008400UL)                      // FLASH segment 33 Base Address
#define PAC55XX_FLASH_SEG34_BASE    (0x00008800UL)                      // FLASH segment 34 Base Address
#define PAC55XX_FLASH_SEG35_BASE    (0x00008C00UL)                      // FLASH segment 35 Base Address
#define PAC55XX_FLASH_SEG36_BASE    (0x00009000UL)                      // FLASH segment 36 Base Address
#define PAC55XX_FLASH_SEG37_BASE    (0x00009400UL)                      // FLASH segment 37 Base Address
#define PAC55XX_FLASH_SEG38_BASE    (0x00009800UL)                      // FLASH segment 38 Base Address
#define PAC55XX_FLASH_SEG39_BASE    (0x00009C00UL)                      // FLASH segment 39 Base Address
#define PAC55XX_FLASH_SEG40_BASE    (0x0000A000UL)                      // FLASH segment 40 Base Address
#define PAC55XX_FLASH_SEG41_BASE    (0x0000A400UL)                      // FLASH segment 41 Base Address
#define PAC55XX_FLASH_SEG42_BASE    (0x0000A800UL)                      // FLASH segment 42 Base Address
#define PAC55XX_FLASH_SEG43_BASE    (0x0000AC00UL)                      // FLASH segment 43 Base Address
#define PAC55XX_FLASH_SEG44_BASE    (0x0000B000UL)                      // FLASH segment 44 Base Address
#define PAC55XX_FLASH_SEG45_BASE    (0x0000B400UL)                      // FLASH segment 45 Base Address
#define PAC55XX_FLASH_SEG46_BASE    (0x0000B800UL)                      // FLASH segment 46 Base Address
#define PAC55XX_FLASH_SEG47_BASE    (0x0000BC00UL)                      // FLASH segment 47 Base Address
#define PAC55XX_FLASH_SEG48_BASE    (0x0000C000UL)                      // FLASH segment 48 Base Address
#define PAC55XX_FLASH_SEG49_BASE    (0x0000C400UL)                      // FLASH segment 49 Base Address
#define PAC55XX_FLASH_SEG50_BASE    (0x0000C800UL)                      // FLASH segment 50 Base Address
#define PAC55XX_FLASH_SEG51_BASE    (0x0000CC00UL)                      // FLASH segment 51 Base Address
#define PAC55XX_FLASH_SEG52_BASE    (0x0000D000UL)                      // FLASH segment 52 Base Address
#define PAC55XX_FLASH_SEG53_BASE    (0x0000D400UL)                      // FLASH segment 53 Base Address
#define PAC55XX_FLASH_SEG54_BASE    (0x0000D800UL)                      // FLASH segment 54 Base Address
#define PAC55XX_FLASH_SEG55_BASE    (0x0000DC00UL)                      // FLASH segment 55 Base Address
#define PAC55XX_FLASH_SEG56_BASE    (0x0000E000UL)                      // FLASH segment 56 Base Address
#define PAC55XX_FLASH_SEG57_BASE    (0x0000E400UL)                      // FLASH segment 57 Base Address
#define PAC55XX_FLASH_SEG58_BASE    (0x0000E800UL)                      // FLASH segment 58 Base Address
#define PAC55XX_FLASH_SEG59_BASE    (0x0000EC00UL)                      // FLASH segment 59 Base Address
#define PAC55XX_FLASH_SEG60_BASE    (0x0000F000UL)                      // FLASH segment 60 Base Address
#define PAC55XX_FLASH_SEG61_BASE    (0x0000F400UL)                      // FLASH segment 61 Base Address
#define PAC55XX_FLASH_SEG62_BASE    (0x0000F800UL)                      // FLASH segment 62 Base Address
#define PAC55XX_FLASH_SEG63_BASE    (0x0000FC00UL)                      // FLASH segment 63 Base Address

#define PAC55XX_FLASH_SEG64_BASE    (0x00010000UL)                      // FLASH segment 64 Base Address
#define PAC55XX_FLASH_SEG65_BASE    (0x00010400UL)                      // FLASH segment 65 Base Address
#define PAC55XX_FLASH_SEG66_BASE    (0x00010800UL)                      // FLASH segment 66 Base Address
#define PAC55XX_FLASH_SEG67_BASE    (0x00010C00UL)                      // FLASH segment 67 Base Address
#define PAC55XX_FLASH_SEG68_BASE    (0x00011000UL)                      // FLASH segment 68 Base Address
#define PAC55XX_FLASH_SEG69_BASE    (0x00011400UL)                      // FLASH segment 69 Base Address
#define PAC55XX_FLASH_SEG70_BASE    (0x00011800UL)                      // FLASH segment 70 Base Address
#define PAC55XX_FLASH_SEG71_BASE    (0x00011C00UL)                      // FLASH segment 71 Base Address
#define PAC55XX_FLASH_SEG72_BASE    (0x00012000UL)                      // FLASH segment 72 Base Address
#define PAC55XX_FLASH_SEG73_BASE    (0x00012400UL)                      // FLASH segment 73 Base Address
#define PAC55XX_FLASH_SEG74_BASE    (0x00012800UL)                      // FLASH segment 74 Base Address
#define PAC55XX_FLASH_SEG75_BASE    (0x00012C00UL)                      // FLASH segment 75 Base Address
#define PAC55XX_FLASH_SEG76_BASE    (0x00013000UL)                      // FLASH segment 76 Base Address
#define PAC55XX_FLASH_SEG77_BASE    (0x00013400UL)                      // FLASH segment 77 Base Address
#define PAC55XX_FLASH_SEG78_BASE    (0x00013800UL)                      // FLASH segment 78 Base Address
#define PAC55XX_FLASH_SEG79_BASE    (0x00013C00UL)                      // FLASH segment 79 Base Address
#define PAC55XX_FLASH_SEG80_BASE    (0x00014000UL)                      // FLASH segment 80 Base Address
#define PAC55XX_FLASH_SEG81_BASE    (0x00014400UL)                      // FLASH segment 81 Base Address
#define PAC55XX_FLASH_SEG82_BASE    (0x00014800UL)                      // FLASH segment 82 Base Address
#define PAC55XX_FLASH_SEG83_BASE    (0x00014C00UL)                      // FLASH segment 83 Base Address
#define PAC55XX_FLASH_SEG84_BASE    (0x00015000UL)                      // FLASH segment 84 Base Address
#define PAC55XX_FLASH_SEG85_BASE    (0x00015400UL)                      // FLASH segment 85 Base Address
#define PAC55XX_FLASH_SEG86_BASE    (0x00015800UL)                      // FLASH segment 86 Base Address
#define PAC55XX_FLASH_SEG87_BASE    (0x00015C00UL)                      // FLASH segment 87 Base Address
#define PAC55XX_FLASH_SEG88_BASE    (0x00016000UL)                      // FLASH segment 88 Base Address
#define PAC55XX_FLASH_SEG89_BASE    (0x00016400UL)                      // FLASH segment 89 Base Address
#define PAC55XX_FLASH_SEG90_BASE    (0x00016800UL)                      // FLASH segment 90 Base Address
#define PAC55XX_FLASH_SEG91_BASE    (0x00016C00UL)                      // FLASH segment 91 Base Address
#define PAC55XX_FLASH_SEG92_BASE    (0x00017000UL)                      // FLASH segment 92 Base Address
#define PAC55XX_FLASH_SEG93_BASE    (0x00017400UL)                      // FLASH segment 93 Base Address
#define PAC55XX_FLASH_SEG94_BASE    (0x00017800UL)                      // FLASH segment 94 Base Address
#define PAC55XX_FLASH_SEG95_BASE    (0x00017C00UL)                      // FLASH segment 95 Base Address

#define PAC55XX_FLASH_SEG96_BASE    (0x00018000UL)                      // FLASH segment 96 Base Address
#define PAC55XX_FLASH_SEG97_BASE    (0x00018400UL)                      // FLASH segment 97 Base Address
#define PAC55XX_FLASH_SEG98_BASE    (0x00018800UL)                      // FLASH segment 98 Base Address
#define PAC55XX_FLASH_SEG99_BASE    (0x00018C00UL)                      // FLASH segment 99 Base Address
#define PAC55XX_FLASH_SEG100_BASE   (0x00019000UL)                      // FLASH segment 100 Base Address
#define PAC55XX_FLASH_SEG101_BASE   (0x00019400UL)                      // FLASH segment 101 Base Address
#define PAC55XX_FLASH_SEG102_BASE   (0x00019800UL)                      // FLASH segment 102 Base Address
#define PAC55XX_FLASH_SEG103_BASE   (0x00019C00UL)                      // FLASH segment 103 Base Address
#define PAC55XX_FLASH_SEG104_BASE   (0x0001A000UL)                      // FLASH segment 104 Base Address
#define PAC55XX_FLASH_SEG105_BASE   (0x0001A400UL)                      // FLASH segment 105 Base Address
#define PAC55XX_FLASH_SEG106_BASE   (0x0001A800UL)                      // FLASH segment 106 Base Address
#define PAC55XX_FLASH_SEG107_BASE   (0x0001AC00UL)                      // FLASH segment 107 Base Address
#define PAC55XX_FLASH_SEG108_BASE   (0x0001B000UL)                      // FLASH segment 108 Base Address
#define PAC55XX_FLASH_SEG109_BASE   (0x0001B400UL)                      // FLASH segment 109 Base Address
#define PAC55XX_FLASH_SEG110_BASE   (0x0001B800UL)                      // FLASH segment 110 Base Address
#define PAC55XX_FLASH_SEG111_BASE   (0x0001BC00UL)                      // FLASH segment 111 Base Address
#define PAC55XX_FLASH_SEG112_BASE   (0x0001C000UL)                      // FLASH segment 112 Base Address
#define PAC55XX_FLASH_SEG113_BASE   (0x0001C400UL)                      // FLASH segment 113 Base Address
#define PAC55XX_FLASH_SEG114_BASE   (0x0001C800UL)                      // FLASH segment 114 Base Address
#define PAC55XX_FLASH_SEG115_BASE   (0x0001CC00UL)                      // FLASH segment 115 Base Address
#define PAC55XX_FLASH_SEG116_BASE   (0x0001D000UL)                      // FLASH segment 116 Base Address
#define PAC55XX_FLASH_SEG117_BASE   (0x0001D400UL)                      // FLASH segment 117 Base Address
#define PAC55XX_FLASH_SEG118_BASE   (0x0001D800UL)                      // FLASH segment 118 Base Address
#define PAC55XX_FLASH_SEG119_BASE   (0x0001DC00UL)                      // FLASH segment 119 Base Address
#define PAC55XX_FLASH_SEG120_BASE   (0x0001E000UL)                      // FLASH segment 120 Base Address
#define PAC55XX_FLASH_SEG121_BASE   (0x0001E400UL)                      // FLASH segment 121 Base Address
#define PAC55XX_FLASH_SEG122_BASE   (0x0001E800UL)                      // FLASH segment 122 Base Address
#define PAC55XX_FLASH_SEG123_BASE   (0x0001EC00UL)                      // FLASH segment 123 Base Address
#define PAC55XX_FLASH_SEG124_BASE   (0x0001F000UL)                      // FLASH segment 124 Base Address
#define PAC55XX_FLASH_SEG125_BASE   (0x0001F400UL)                      // FLASH segment 125 Base Address
#define PAC55XX_FLASH_SEG126_BASE   (0x0001F800UL)                      // FLASH segment 126 Base Address
#define PAC55XX_FLASH_SEG127_BASE   (0x0001FC00UL)                      // FLASH segment 127 Base Address

#define PAC55XX_INFO1_FLASH_BASE    (0x00100000UL)                      // INFO 1 FLash Base Address
#define PAC55XX_INFO2_FLASH_BASE    (0x00100400UL)                      // INFO 2 FLash Base Address
#define PAC55XX_INFO3_FLASH_BASE    (0x00100800UL)                      // INFO 3 FLash Base Address

#define PAC55XX_SRAM_BASE           (0x20000000UL)                      // SRAM         Base Address
#define PAC55XX_PERIPH_BASE         (0x40000000UL)                      // Peripheral   Base Address

// Peripheral memory map
#define PAC55XX_ADC_BASE            (PAC55XX_PERIPH_BASE + 0x00000)     // ADC                     Base Address
#define PAC55XX_I2C_BASE            (PAC55XX_PERIPH_BASE + 0x10000)     // I2C                     Base Address
#define PAC55XX_USARTA_BASE         (PAC55XX_PERIPH_BASE + 0x20000)     // USARTA                  Base Address
#define PAC55XX_USARTB_BASE         (PAC55XX_PERIPH_BASE + 0x30000)     // USARTB                  Base Address
#define PAC55XX_USARTC_BASE         (PAC55XX_PERIPH_BASE + 0x40000)     // USARTC                  Base Address
#define PAC55XX_USARTD_BASE         (PAC55XX_PERIPH_BASE + 0x50000)     // USARTD                  Base Address
#define PAC55XX_TIMERA_BASE         (PAC55XX_PERIPH_BASE + 0x60000)     // Timer A/DTGA[0:3]       Base Address
#define PAC55XX_TIMERB_BASE         (PAC55XX_PERIPH_BASE + 0x70000)     // Timer B/DTGB            Base Address
#define PAC55XX_TIMERC_BASE         (PAC55XX_PERIPH_BASE + 0x80000)     // Timer C/DTGC            Base Address
#define PAC55XX_TIMERD_BASE         (PAC55XX_PERIPH_BASE + 0x90000)     // Timer D/DTGD            Base Address
#define PAC55XX_CAN_BASE            (PAC55XX_PERIPH_BASE + 0xA0000)     // CAN                     Base Address
#define PAC55XX_GPTIMERA_BASE       (PAC55XX_PERIPH_BASE + 0xB0000)     // GP Timer A              Base Address
#define PAC55XX_GPTIMERB_BASE       (PAC55XX_PERIPH_BASE + 0xC0000)     // GP Timer B              Base Address
#define PAC55XX_SYS_PERIPH_BASE     (PAC55XX_PERIPH_BASE + 0xD0000)     // System Peripheral       Base Address
#define PAC55XX_MEMCTL_BASE         (PAC55XX_SYS_PERIPH_BASE + 0x0000)  // FLASH Memory Controller Base Address
#define PAC55XX_SCC_BASE            (PAC55XX_SYS_PERIPH_BASE + 0x0400)  // System/Clock Control    Base Address
#define PAC55XX_WWDT_BASE           (PAC55XX_SYS_PERIPH_BASE + 0x0800)  // Watchdog Timer          Base Address
#define PAC55XX_RTC_BASE            (PAC55XX_SYS_PERIPH_BASE + 0x0C00)  // RTC                     Base Address
#define PAC55XX_CRC_BASE            (PAC55XX_SYS_PERIPH_BASE + 0x1000)  // CRC16                   Base Address
#define PAC55XX_GPIOA_BASE          (PAC55XX_SYS_PERIPH_BASE + 0x1400)  // GPIO A                  Base Address
#define PAC55XX_GPIOB_BASE          (PAC55XX_SYS_PERIPH_BASE + 0x1800)  // GPIO B                  Base Address
#define PAC55XX_GPIOC_BASE          (PAC55XX_SYS_PERIPH_BASE + 0x1C00)  // GPIO C                  Base Address
#define PAC55XX_GPIOD_BASE          (PAC55XX_SYS_PERIPH_BASE + 0x2000)  // GPIO D                  Base Address
#define PAC55XX_GPIOE_BASE          (PAC55XX_SYS_PERIPH_BASE + 0x2400)  // GPIO E                  Base Address
#define PAC55XX_GPIOF_BASE          (PAC55XX_SYS_PERIPH_BASE + 0x2800)  // GPIO F                  Base Address
#define PAC55XX_GPIOG_BASE          (PAC55XX_SYS_PERIPH_BASE + 0x2C00)  // GPIO G                  Base Address


//==============================================================================
//                         Peripheral declaration
//==============================================================================
#define PAC55XX_ADC                 ((PAC55XX_ADC_TYPEDEF *) PAC55XX_ADC_BASE)
#define PAC55XX_I2C                 ((PAC55XX_I2C_TYPEDEF *) PAC55XX_I2C_BASE)
#define PAC55XX_UARTA               ((PAC55XX_UART_TYPEDEF *) PAC55XX_USARTA_BASE)
#define PAC55XX_SSPA                ((PAC55XX_SSP_TYPEDEF *) PAC55XX_USARTA_BASE)
#define PAC55XX_UARTB               ((PAC55XX_UART_TYPEDEF *) PAC55XX_USARTB_BASE)
#define PAC55XX_SSPB                ((PAC55XX_SSP_TYPEDEF *) PAC55XX_USARTB_BASE)
#define PAC55XX_UARTC               ((PAC55XX_UART_TYPEDEF *) PAC55XX_USARTC_BASE)
#define PAC55XX_SSPC                ((PAC55XX_SSP_TYPEDEF *) PAC55XX_USARTC_BASE)
#define PAC55XX_UARTD               ((PAC55XX_UART_TYPEDEF *) PAC55XX_USARTD_BASE)
#define PAC55XX_SSPD                ((PAC55XX_SSP_TYPEDEF *) PAC55XX_USARTD_BASE)
#define PAC55XX_TIMERA              ((PAC55XX_TIMER_TYPEDEF *) PAC55XX_TIMERA_BASE)
#define PAC55XX_TIMERB              ((PAC55XX_TIMER_TYPEDEF *) PAC55XX_TIMERB_BASE)
#define PAC55XX_TIMERC              ((PAC55XX_TIMER_TYPEDEF *) PAC55XX_TIMERC_BASE)
#define PAC55XX_TIMERD              ((PAC55XX_TIMER_TYPEDEF *) PAC55XX_TIMERD_BASE)
#define PAC55XX_CAN                 ((PAC55XX_CAN_TYPEDEF *) PAC55XX_CAN_BASE)
#define PAC55XX_GPTIMERA            ((PAC55XX_GPTTIMER_TYPEDEF *) PAC55XX_GPTIMERA_BASE)
#define PAC55XX_GPTIMERB            ((PAC55XX_GPTTIMER_TYPEDEF *) PAC55XX_GPTIMERB_BASE)
#define PAC55XX_MEMCTL              ((PAC55XX_MEMCTL_TYPEDEF *) PAC55XX_MEMCTL_BASE)
#define PAC55XX_SCC                 ((PAC55XX_SCC_TYPEDEF *) PAC55XX_SCC_BASE)
#define PAC55XX_WWDT                ((PAC55XX_WWDT_TYPEDEF *) PAC55XX_WWDT_BASE)
#define PAC55XX_RTC                 ((PAC55XX_RTC_TYPEDEF *) PAC55XX_RTC_BASE)
#define PAC55XX_CRC                 ((PAC55XX_CRC_TYPEDEF *) PAC55XX_CRC_BASE)
#define PAC55XX_GPIOA               ((PAC55XX_GPIO_TYPEDEF *) PAC55XX_GPIOA_BASE)
#define PAC55XX_GPIOB               ((PAC55XX_GPIO_TYPEDEF *) PAC55XX_GPIOB_BASE)
#define PAC55XX_GPIOC               ((PAC55XX_GPIO_TYPEDEF *) PAC55XX_GPIOC_BASE)
#define PAC55XX_GPIOD               ((PAC55XX_GPIO_TYPEDEF *) PAC55XX_GPIOD_BASE)
#define PAC55XX_GPIOE               ((PAC55XX_GPIO_TYPEDEF *) PAC55XX_GPIOE_BASE)
#define PAC55XX_GPIOF               ((PAC55XX_GPIO_TYPEDEF *) PAC55XX_GPIOF_BASE)
#define PAC55XX_GPIOG               ((PAC55XX_GPIO_TYPEDEF *) PAC55XX_GPIOG_BASE)
#define PAC55XX_INFO3               ((PAC55XX_INFO3_TYPEDEF *) PAC55XX_INFO3_FLASH_BASE)

#ifdef __cplusplus
}
#endif

#endif  // PAC55XX_H
