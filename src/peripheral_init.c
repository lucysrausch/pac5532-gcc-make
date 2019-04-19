/****************************************************************************
 * @file     hs_peripheral_init.h
 * @brief    Peripheral Initialization for the Hall Sensor Based BLDC Application
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
 * @brief  This function configures the PAC peripherals for this application
 *
 * @return none
 *
 */
void peripheral_init(void)
{

	// Set Flash Lock to allow write access to MEMCTL register for configuring clocks
    PAC55XX_MEMCTL->FLASHLOCK = FLASH_LOCK_ALLOW_WRITE_MEMCTL;      

    // Turn on Flache Cache
    PAC55XX_MEMCTL->MEMCTL.w &= ~(1 << 21);

    // Select 4 MHz CLKREF for Free Running Clock FRCLK
    PAC55XX_SCC->CCSCTL.FRCLKMUXSEL = CCSCTL_CLKIN_CLKREF;
 	pac5xxx_sys_pll_config_enable(4, 300, 0);                   // PLLCLK = 300 MHz = (4/4 * 300) /1
	
    // Configure SCLK=PLLCLK=300 MHz, HCLK=150 MHz, PCLK=50 MHz, ACLK=100 MHz and WaitStates;
    PAC55XX_SCC->CCSCTL.HCLKDIV = CCSCTL_HCLKDIV_DIV2;          // HCLK = 150 MHz = SCLK/2; when SCLK = PLLCLK
    PAC55XX_SCC->CCSCTL.ACLKDIV = CCSCTL_ACLKDIV_DIV3;          // ACLK = 100 MHz = SCLK/3; when SCLK = PLLCLK
	PAC55XX_SCC->CCSCTL.PCLKDIV = CCSCTL_PCLKDIV_DIV3;			// PCLK = 50 MHz = HCLK/3; when SCLK = PLLCLK
  	PAC55XX_MEMCTL->MEMCTL.WSTATE = 6 + 1;                      // Flash = 150/(5 + 1 Extra WS + 1) = 25 MHz + extra WS,   TODO: The 1 Extra WS might be able to be removed after testing
    PAC55XX_SCC->CCSCTL.SCLKMUXSEL = CCSCTL_SCLK_PLLCLK;        // SCLK = PLLCLK
    
    // Set MCLK for Flash write & erase in addition to read
    PAC55XX_MEMCTL->MEMCTL.MCLKDIV = MEMCTL_MCLK_DIV5;          // MCLK will = HCLK/5 when MCLKSEL = MEMCTL_MCLK_HCLKDIV
    PAC55XX_MEMCTL->MEMCTL.MCLKSEL = MEMCTL_MCLK_HCLKDIV;       // MCLK = HCLK/5 = 30 MHz; allows reading and writing of Flash  
    
    PAC55XX_MEMCTL->FLASHLOCK = 0;                              // Disallow write access to MEMCTL
    PAC55XX_MEMCTL->MEMCTL.CACHEDIS = 0;                        // MEMCTL.CACHEDIS, enable Flash CACHE

	// Configure Timer A parameters. Timer A runs at PLL Frequency (selected above).
	pac5xxx_timer_clock_config(TimerA, TXCTL_CS_ACLK, TXCTL_PS_DIV1);      // Configure timer clock input for ACLK, /1 divider
	app_pwm_period = PWM_SWITCH_FREQ;														// Number of KHz
	pwm_period_ticks = TIMER_A_FREQ_CNV / (app_pwm_period);									// 50,000 / # KHz
	pac5xxx_timer_base_config(TimerA, pwm_period_ticks, 0, TxCTL_MODE_UP, 0);			// Configure Timer

	//Configure PWM Outputs
	PAC55XX_TIMERA->CCTR4.CTR = pwm_period_ticks >> 1;
	PAC55XX_TIMERA->CCTR5.CTR = pwm_period_ticks >> 1;
	PAC55XX_TIMERA->CCTR6.CTR = pwm_period_ticks >> 1;

	// Configure Hardware Dead Time Generator
	dt_leading_ticks = DT_LED_TICKS;
	dt_trailing_ticks = DT_TED_TICKS;
	Set_Dead_Time();

	//To Drive the Motor PWM's and the Outputs
	// Write to the MODE only needs to be done once. They are always PUSH/PULL
	// Write to the PBMUXSEL to change who is a PWM and who is a GPIO.
	// Write to the OUT to enable/disable low sides.

	PAC55XX_GPIOB->OUT.w = 0;			//PORTB OUT GPIO = 0;
	PAC55XX_SCC->PBMUXSEL.w = 0;		//PORTB PSEL is ALL GPIO's
	//Configure PORTB Outputs to Push Pull
	PAC55XX_GPIOB->MODE.w = MOTOR_OUTPUTS_PUSH_PULL;

	// Configure nIRQ1 interrupt input signals and enable interrupts
	PAC55XX_GPIOA->MODE.P7 = 3;               // Input for over current interrupt
	PAC55XX_GPIOA->INTTYPE.P7 = 0;            // Edge trigger
	PAC55XX_GPIOA->INTCFG.P7 = 0;           // Falling edge
	PAC55XX_GPIOA->INTEDGEBOTH.P7 = 0;        // Only one edge
	PAC55XX_GPIOA->INTCLEAR.P7 = 1;           // Clear any pending PA7 interrupt
	PAC55XX_GPIOA->INTEN.P7 = 1;              // Enable Interrupt
	NVIC_EnableIRQ(GpioA_IRQn);								// Enable interrupts in NVIC

	//Configure PC7 for Debug Output
	PAC55XX_GPIOC->MODE.P7 = IO_PUSH_PULL_OUTPUT;               //FOR DEBUG
	PAC55XX_GPIOC->MODE.P6 = IO_PUSH_PULL_OUTPUT;               //FOR DEBUG
	PAC55XX_GPIOC->MODE.P5 = IO_PUSH_PULL_OUTPUT;               //FOR DEBUG
	PAC55XX_GPIOC->MODE.P4 = IO_PUSH_PULL_OUTPUT;               //FOR DEBUG
	
	// Configure CCR0 with interrupt enable(for reading new comparator value form float phase comparator)
	pac5xxx_timer_clock_config(TimerC, TXCTL_CS_ACLK, TXCTL_PS_DIV1);      // Configure timer clock input for ACLK, /1 divider
	pac5xxx_timer_base_config(TimerC, TIMERC_PERIOD, 0, TxCTL_MODE_UP, 0);			// Configure Timer
	PAC55XX_TIMERC->CCTR0.CTR = TIMERC_PERIOD >> 1;
	NVIC_SetPriority(TimerC_IRQn, 1);

	// Configure timer for 30-degree calculation
	// On PAC52xx TIMERD Defaults to running at 50 MHz / 16
	// On PAC55xx, 
	timer_d_div = 4;
	pac5xxx_timer_clock_config(TimerD, TXCTL_CS_PCLK, TXCTL_PS_DIV16);      // Configure timer clock input for PCLK /16 = 3.125 MHz
	pac5xxx_timer_base_config(TimerD, 0xFFFF, 0, TxCTL_MODE_UP, 0);			// Configure Timer
	PAC55XX_TIMERD->CTL.PRDLATCH = TXCTL_PRDLATCH_TXCTR_IM;
	PAC55XX_TIMERD->CCTL0.CCMODE = TXCCTL_CCMODE_COMPARE;
	PAC55XX_TIMERD->CCTL0.CCINTEDGE = TXCCTL_CCINT_FALLING_EDGE;
	NVIC_SetPriority(TimerD_IRQn, 1);												// Set Priority; Enablement will occur after Open Loop ends; Disablement will occur when motor is disabled

	//Configure SysTick Timer
    SysTick->LOAD = 150000;
    SysTick->VAL = 0;
    SysTick->CTRL |= (SysTick_CTRL_ENABLE_Msk +  SysTick_CTRL_CLKSOURCE_Msk + SysTick_CTRL_TICKINT_Msk);
	NVIC_SetPriority(SysTick_IRQn, 3);
}
