//=============================================================================
// @file    startup_pac55xx_gcc.c
// @brief   GCC Device Startup File for the PAC55XX Device Family
//
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
#include "pac5xxx.h"

//===== Stack Configuration ======================================================
#define STACK_SIZE      0x000000C0                  //Stack size (in Words)
__attribute__ ((section(".co_stack")))
unsigned long pulStack[STACK_SIZE];      

#define WEAK __attribute__ ((weak))           

//=============================================================================
// Declaration of the default fault handlers
//=============================================================================
void WEAK  Reset_Handler(void);
void WEAK  NMI_Handler(void);
void WEAK  HardFault_Handler(void);
void WEAK  MemManageFault_Handler(void);               // MemManage fault Handler
void WEAK  BusFault_Handler(void);                     // BusFault Handler
void WEAK  UsageFault_Handler(void);                   // Usage Fault Handler
void WEAK  SVC_Handler(void);
void WEAK  PendSV_Handler(void);
void WEAK  SysTick_Handler(void);
void WEAK  MemCtl_IRQHandler(void);
void WEAK  Wdt_IRQHandler(void);
void WEAK  RTC_IRQHandler(void);
void WEAK  ADC_IRQHandler(void);
void WEAK  ADC1_IRQHandler(void);
void WEAK  ADC2_IRQHandler(void);
void WEAK  ADC3_IRQHandler(void);
void WEAK  TimerA_IRQHandler(void);
void WEAK  TimerB_IRQHandler(void);
void WEAK  TimerC_IRQHandler(void);
void WEAK  TimerD_IRQHandler(void);
void WEAK  QEPA_IRQHandler(void);
void WEAK  QEPB_IRQHandler(void);
void WEAK  QEPC_IRQHandler(void);
void WEAK  QEPD_IRQHandler(void);
void WEAK  GpioA_IRQHandler(void);
void WEAK  GpioB_IRQHandler(void);
void WEAK  GpioC_IRQHandler(void);
void WEAK  GpioD_IRQHandler(void);
void WEAK  GpioE_IRQHandler(void);
void WEAK  GpioF_IRQHandler(void);
void WEAK  GpioG_IRQHandler(void);
void WEAK  I2C_IRQHandler(void);
void WEAK  USARTA_IRQHandler(void);
void WEAK  USARTB_IRQHandler(void);
void WEAK  USARTC_IRQHandler(void);
void WEAK  USARTD_IRQHandler(void);
void WEAK  CAN_IRQHandler(void);
void WEAK  GPTimerA_IRQHandler(void);
void WEAK  GPTimerB_IRQHandler(void);
void WEAK  SYSCTRL_IRQHandler(void);

//=============================================================================
// Symbols defined in linker script
//=============================================================================
extern unsigned long _sidata;           // Start address for the initialization
                                        //     values of the .data section.
extern unsigned long _sdata;            // Start address for the .data section
extern unsigned long _edata;            // End address for the .data section
extern unsigned long _sbss;             // Start address for the .bss section
extern unsigned long _ebss;             // End address for the .bss section
extern void _eram;                      // End address for ram

extern uint32_t fault_mask;

//=============================================================================
// Function prototypes
//=============================================================================
extern int main(void);                  // The entry point for the application
void Default_Reset_Handler(void);       // Default reset handler
static void Default_Handler(void);      // Default exception handler

//=============================================================================
// @brief   The minimal vector table for a Cortex M0.  Note that the proper
//          constructs must be placed on this to ensure that it ends up at
//          physical address 0x00000000.  
//=============================================================================
__attribute__ ((section(".isr_vector")))
void (* const g_pfnVectors[])(void) =
{
    //=========================================================================
    // Core Exceptions
    //=========================================================================
    (void *)&pulStack[STACK_SIZE],      // Initial stack pointer
    Reset_Handler,                      // Reset handler
    NMI_Handler,                        // NMI handler
    HardFault_Handler,                  // Hard Fault handler
    MemManageFault_Handler,             // MemManage fault Handler
    BusFault_Handler,                   // BusFault Handler
    UsageFault_Handler,                 // Usage Fault Handler
    0,0,0,0,                            // Reserved
    SVC_Handler,                        // SVCall handler
    0, 0,                               // Reserved
    PendSV_Handler,                     // PendSV handler
    SysTick_Handler,                    // SysTick handler

    //=========================================================================
    // External Exceptions
    //=========================================================================
    //0-2
    MemCtl_IRQHandler,
    Wdt_IRQHandler,
    RTC_IRQHandler,

    //3-6
    ADC_IRQHandler,
    ADC1_IRQHandler,
    ADC2_IRQHandler,
    ADC3_IRQHandler,

    //7-10
    TimerA_IRQHandler,
    TimerB_IRQHandler,
    TimerC_IRQHandler,
    TimerD_IRQHandler,

    //11-14
    QEPA_IRQHandler,
    QEPB_IRQHandler,
    QEPC_IRQHandler,
    QEPD_IRQHandler,

    //15-21
    GpioA_IRQHandler,
    GpioB_IRQHandler,
    GpioC_IRQHandler,
    GpioD_IRQHandler,
    GpioE_IRQHandler,
    GpioF_IRQHandler,
    GpioG_IRQHandler,

    //22-27
    I2C_IRQHandler,
    USARTA_IRQHandler,
    USARTB_IRQHandler,
    USARTC_IRQHandler,
    USARTD_IRQHandler,
    CAN_IRQHandler,

    //28-31
    GPTimerA_IRQHandler,
    GPTimerB_IRQHandler,
    SYSCTRL_IRQHandler
};

//=============================================================================
// @brief  This is the code that gets called when the processor first
//         starts execution following a reset event. Only the absolutely
//         necessary set is performed, after which the application
//         supplied main() routine is called. 
// @param  None
// @retval None
//=============================================================================
void Default_Reset_Handler(void)
{
    // Initialize data and bss
    unsigned long *pulSrc, *pulDest;

    // Copy the data segment initializers from flash to SRAM
    pulSrc = &_sidata;

    for(pulDest = &_sdata; pulDest < &_edata; )
    {
        *(pulDest++) = *(pulSrc++);
    }

    // Zero fill the bss segment
    for(pulDest = &_sbss; pulDest < &_ebss; )
    {
        *(pulDest++) = 0;
    }

    // enable FPU 
    SCB->CPACR |= ((3UL << 10*2) |         // set CP10 Full Access
                  (3UL << 11*2)  );        // set CP11 Full Access
  
    // Call the application's entry point.
    main();
}


extern uint32_t __StackTop;     // __StackTop is set to end of RAM by linker
//=============================================================================
// @brief Provide weak aliases for each Exception handler to the
//        Default_Handler.  As they are weak aliases, any function with the
//        same name will override this definition.
//=============================================================================
#pragma weak Reset_Handler = Default_Reset_Handler
#pragma weak NMI_Handler = Default_NMI_Handler
#pragma weak HardFault_Handler = Default_HardFault_Handler
#pragma weak MemManageFault_Handler = Default_MemManageFault_Handler
#pragma weak BusFault_Handler = Default_BusFault_Handler
#pragma weak UsageFault_Handler = Default_UsageFault_Handler
#pragma weak SVC_Handler = Default_SVC_Handler
#pragma weak PendSV_Handler = Default_PendSV_Handler
#pragma weak SysTick_Handler = Default_Handler

//0-2
#pragma weak MemCtl_IRQHandler = Default_Handler
#pragma weak Wdt_IRQHandler = Default_Handler
#pragma weak RTC_IRQHandler = Default_Handler  

//3-6
#pragma weak ADC_IRQHandler = Default_Handler
#pragma weak ADC1_IRQHandler = Default_Handler
#pragma weak ADC2_IRQHandler = Default_Handler
#pragma weak ADC3_IRQHandler = Default_Handler

//7-10
#pragma weak TimerA_IRQHandler = Default_Handler
#pragma weak TimerB_IRQHandler = Default_Handler
#pragma weak TimerC_IRQHandler = Default_Handler
#pragma weak TimerD_IRQHandler = Default_Handler

//11-14
#pragma weak QEPA_IRQHandler = Default_Handler
#pragma weak QEPB_IRQHandler = Default_Handler
#pragma weak QEPC_IRQHandler = Default_Handler
#pragma weak QEPD_IRQHandler = Default_Handler

//15-21
#pragma weak GpioA_IRQHandler = Default_Handler
#pragma weak GpioB_IRQHandler = Default_Handler
#pragma weak GpioC_IRQHandler = Default_Handler
#pragma weak GpioD_IRQHandler = Default_Handler
#pragma weak GpioE_IRQHandler = Default_Handler
#pragma weak GpioF_IRQHandler = Default_Handler
#pragma weak GpioG_IRQHandler = Default_Handler

//22-27
#pragma weak I2C_IRQHandler = Default_Handler
#pragma weak USARTA_IRQHandler = Default_Handler
#pragma weak USARTB_IRQHandler = Default_Handler
#pragma weak USARTC_IRQHandler = Default_Handler
#pragma weak USARTD_IRQHandler = Default_Handler
#pragma weak CAN_IRQHandler = Default_Handler

//28-31
#pragma weak GPTimerA_IRQHandler = Default_Handler
#pragma weak GPTimerB_IRQHandler = Default_Handler
#pragma weak SYSCTRL_IRQHandler = Default_Handler


//=============================================================================
// @brief  This is the code that gets called when the processor receives an 
//         unexpected interrupt.  This simply enters an infinite loop, 
//         preserving the system state for examination by a debugger.
// @param  None
// @retval None  
//=============================================================================
#pragma weak Default_IRQHandler = Default_Handler

static void Default_Handler(void) 
{
	while (1);
}

static void Default_NMI_Handler(void)
{
	while (1);
}
static void Default_HardFault_Handler(void)
{
	while (1);
}
static void Default_MemManageFault_Handler(void)
{
	while (1);
}
static void Default_BusFault_Handler(void)
{
	while (1);
}
static void Default_UsageFault_Handler(void)
{
	while (1);
}
static void Default_SVC_Handler(void)
{
	while (1);
}
static void Default_PendSV_Handler(void)
{
	while (1);
}
