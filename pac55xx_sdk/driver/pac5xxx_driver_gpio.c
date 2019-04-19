/**************************************************************************//**
 * @file     pac5xxx_driver_gpio.c
 * @brief    Firmware driver for the PAC5XXX GPIOs
 *
 * @note
 * Copyright (C) 2015-2017, Active-Semi International
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

#include "pac5xxx_driver_gpio.h"

RAMFUNC_GPIO void pac5xxx_gpio_configure_interrupt_a(uint8_t port_mask, uint8_t active_high_mask)
{
    if ((port_mask & 0x01) == 0x01)
    {
        PAC55XX_GPIOA->MODE.P0 = 3;             // High-Z Input
        PAC55XX_GPIOA->INTTYPE.P0 = 0;          // Edge trigger
        PAC55XX_GPIOA->INTEDGEBOTH.P0 = 0;      // Only one edge
        if ((active_high_mask & 0x01) == 0x01)
            PAC55XX_GPIOA->INTCFG.P0 = 1;       // Rising edge
        else
            PAC55XX_GPIOA->INTCFG.P0 = 0;       // Falling edge
        PAC55XX_GPIOA->INTEN.P0 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x02) == 0x02)
    {
        PAC55XX_GPIOA->MODE.P1 = 3;             // High-Z Input
        PAC55XX_GPIOA->INTTYPE.P1 = 0;          // Edge trigger
        PAC55XX_GPIOA->INTEDGEBOTH.P1 = 0;      // Only one edge
        if ((active_high_mask & 0x02) == 0x02)
            PAC55XX_GPIOA->INTCFG.P1 = 1;       // Rising edge
        else
            PAC55XX_GPIOA->INTCFG.P1 = 0;       // Falling edge
        PAC55XX_GPIOA->INTEN.P1 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x04) == 0x04)
    {
        PAC55XX_GPIOA->MODE.P2 = 3;             // High-Z Input
        PAC55XX_GPIOA->INTTYPE.P2 = 0;          // Edge trigger
        PAC55XX_GPIOA->INTEDGEBOTH.P2 = 0;      // Only one edge
        if ((active_high_mask & 0x04) == 0x04)
            PAC55XX_GPIOA->INTCFG.P2 = 1;       // Rising edge
        else
            PAC55XX_GPIOA->INTCFG.P2 = 0;       // Falling edge
        PAC55XX_GPIOA->INTEN.P2 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x08) == 0x08)
    {
        PAC55XX_GPIOA->MODE.P3 = 3;             // High-Z Input
        PAC55XX_GPIOA->INTTYPE.P3 = 0;          // Edge trigger
        PAC55XX_GPIOA->INTEDGEBOTH.P3 = 0;      // Only one edge
        if ((active_high_mask & 0x08) == 0x08)
            PAC55XX_GPIOA->INTCFG.P3 = 1;       // Rising edge
        else
            PAC55XX_GPIOA->INTCFG.P3 = 0;       // Falling edge
        PAC55XX_GPIOA->INTEN.P3 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x10) == 0x10)
    {
        PAC55XX_GPIOA->MODE.P4 = 3;             // High-Z Input
        PAC55XX_GPIOA->INTTYPE.P4 = 0;          // Edge trigger
        PAC55XX_GPIOA->INTEDGEBOTH.P4 = 0;      // Only one edge
        if ((active_high_mask & 0x10) == 0x10)
            PAC55XX_GPIOA->INTCFG.P4 = 1;       // Rising edge
        else
            PAC55XX_GPIOA->INTCFG.P4 = 0;       // Falling edge
        PAC55XX_GPIOA->INTEN.P4 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x20) == 0x20)
    {
        PAC55XX_GPIOA->MODE.P5 = 3;             // High-Z Input
        PAC55XX_GPIOA->INTTYPE.P5 = 0;          // Edge trigger
        PAC55XX_GPIOA->INTEDGEBOTH.P5 = 0;      // Only one edge
        if ((active_high_mask & 0x20) == 0x20)
            PAC55XX_GPIOA->INTCFG.P5 = 1;       // Rising edge
        else
            PAC55XX_GPIOA->INTCFG.P5 = 0;       // Falling edge
        PAC55XX_GPIOA->INTEN.P5 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x40) == 0x40)
    {
        PAC55XX_GPIOA->MODE.P6 = 3;             // High-Z Input
        PAC55XX_GPIOA->INTTYPE.P6 = 0;          // Edge trigger
        PAC55XX_GPIOA->INTEDGEBOTH.P6 = 0;      // Only one edge
        if ((active_high_mask & 0x40) == 0x40)
            PAC55XX_GPIOA->INTCFG.P6 = 1;       // Rising edge
        else
            PAC55XX_GPIOA->INTCFG.P6 = 0;       // Falling edge
        PAC55XX_GPIOA->INTEN.P6 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x80) == 0x80)
    {
        PAC55XX_GPIOA->MODE.P7 = 3;             // High-Z Input
        PAC55XX_GPIOA->INTTYPE.P7 = 0;          // Edge trigger
        PAC55XX_GPIOA->INTEDGEBOTH.P7 = 0;      // Only one edge
        if ((active_high_mask & 0x80) == 0x80)
            PAC55XX_GPIOA->INTCFG.P7 = 1;       // Rising edge
        else
            PAC55XX_GPIOA->INTCFG.P7 = 0;       // Falling edge
        PAC55XX_GPIOA->INTEN.P7 = 1;            // Enable Interrupt
    }
    
    if (port_mask != 0x00)
    {
        PAC55XX_GPIOA->INTCLEAR.w = 0xFF;           // Clear any pending interrupts
        NVIC_EnableIRQ(GpioA_IRQn);	                // Enable interrupts in NVIC
    }
}

RAMFUNC_GPIO void pac5xxx_gpio_configure_interrupt_b(uint8_t port_mask, uint8_t active_high_mask)
{
    if ((port_mask & 0x01) == 0x01)
    {
        PAC55XX_GPIOB->MODE.P0 = 3;             // High-Z Input
        PAC55XX_GPIOB->INTTYPE.P0 = 0;          // Edge trigger
        PAC55XX_GPIOB->INTEDGEBOTH.P0 = 0;      // Only one edge
        if ((active_high_mask & 0x01) == 0x01)
            PAC55XX_GPIOB->INTCFG.P0 = 1;       // Rising edge
        else
            PAC55XX_GPIOB->INTCFG.P0 = 0;       // Falling edge
        PAC55XX_GPIOB->INTEN.P0 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x02) == 0x02)
    {
        PAC55XX_GPIOB->MODE.P1 = 3;             // High-Z Input
        PAC55XX_GPIOB->INTTYPE.P1 = 0;          // Edge trigger
        PAC55XX_GPIOB->INTEDGEBOTH.P1 = 0;      // Only one edge
        if ((active_high_mask & 0x02) == 0x02)
            PAC55XX_GPIOB->INTCFG.P1 = 1;       // Rising edge
        else
            PAC55XX_GPIOB->INTCFG.P1 = 0;       // Falling edge
        PAC55XX_GPIOB->INTEN.P1 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x04) == 0x04)
    {
        PAC55XX_GPIOB->MODE.P2 = 3;             // High-Z Input
        PAC55XX_GPIOB->INTTYPE.P2 = 0;          // Edge trigger
        PAC55XX_GPIOB->INTEDGEBOTH.P2 = 0;      // Only one edge
        if ((active_high_mask & 0x04) == 0x04)
            PAC55XX_GPIOB->INTCFG.P2 = 1;       // Rising edge
        else
            PAC55XX_GPIOB->INTCFG.P2 = 0;       // Falling edge
        PAC55XX_GPIOB->INTEN.P2 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x08) == 0x08)
    {
        PAC55XX_GPIOB->MODE.P3 = 3;             // High-Z Input
        PAC55XX_GPIOB->INTTYPE.P3 = 0;          // Edge trigger
        PAC55XX_GPIOB->INTEDGEBOTH.P3 = 0;      // Only one edge
        if ((active_high_mask & 0x08) == 0x08)
            PAC55XX_GPIOB->INTCFG.P3 = 1;       // Rising edge
        else
            PAC55XX_GPIOB->INTCFG.P3 = 0;       // Falling edge
        PAC55XX_GPIOB->INTEN.P3 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x10) == 0x10)
    {
        PAC55XX_GPIOB->MODE.P4 = 3;             // High-Z Input
        PAC55XX_GPIOB->INTTYPE.P4 = 0;          // Edge trigger
        PAC55XX_GPIOB->INTEDGEBOTH.P4 = 0;      // Only one edge
        if ((active_high_mask & 0x10) == 0x10)
            PAC55XX_GPIOB->INTCFG.P4 = 1;       // Rising edge
        else
            PAC55XX_GPIOB->INTCFG.P4 = 0;       // Falling edge
        PAC55XX_GPIOB->INTEN.P4 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x20) == 0x20)
    {
        PAC55XX_GPIOB->MODE.P5 = 3;             // High-Z Input
        PAC55XX_GPIOB->INTTYPE.P5 = 0;          // Edge trigger
        PAC55XX_GPIOB->INTEDGEBOTH.P5 = 0;      // Only one edge
        if ((active_high_mask & 0x20) == 0x20)
            PAC55XX_GPIOB->INTCFG.P5 = 1;       // Rising edge
        else
            PAC55XX_GPIOB->INTCFG.P5 = 0;       // Falling edge
        PAC55XX_GPIOB->INTEN.P5 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x40) == 0x40)
    {
        PAC55XX_GPIOB->MODE.P6 = 3;             // High-Z Input
        PAC55XX_GPIOB->INTTYPE.P6 = 0;          // Edge trigger
        PAC55XX_GPIOB->INTEDGEBOTH.P6 = 0;      // Only one edge
        if ((active_high_mask & 0x40) == 0x40)
            PAC55XX_GPIOB->INTCFG.P6 = 1;       // Rising edge
        else
            PAC55XX_GPIOB->INTCFG.P6 = 0;       // Falling edge
        PAC55XX_GPIOB->INTEN.P6 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x80) == 0x80)
    {
        PAC55XX_GPIOB->MODE.P7 = 3;             // High-Z Input
        PAC55XX_GPIOB->INTTYPE.P7 = 0;          // Edge trigger
        PAC55XX_GPIOB->INTEDGEBOTH.P7 = 0;      // Only one edge
        if ((active_high_mask & 0x80) == 0x80)
            PAC55XX_GPIOB->INTCFG.P7 = 1;       // Rising edge
        else
            PAC55XX_GPIOB->INTCFG.P7 = 0;       // Falling edge
        PAC55XX_GPIOB->INTEN.P7 = 1;            // Enable Interrupt
    }
    
    if (port_mask != 0x00)
    {
        PAC55XX_GPIOB->INTCLEAR.w = 0xFF;           // Clear any pending interrupts
        NVIC_EnableIRQ(GpioB_IRQn);	                // Enable interrupts in NVIC
    }
}

RAMFUNC_GPIO void pac5xxx_gpio_configure_interrupt_c(uint8_t port_mask, uint8_t active_high_mask)
{
    if ((port_mask & 0x01) == 0x01)
    {
        PAC55XX_GPIOC->MODE.P0 = 3;             // High-Z Input
        PAC55XX_GPIOC->INTTYPE.P0 = 0;          // Edge trigger
        PAC55XX_GPIOC->INTEDGEBOTH.P0 = 0;      // Only one edge
        if ((active_high_mask & 0x01) == 0x01)
            PAC55XX_GPIOC->INTCFG.P0 = 1;       // Rising edge
        else
            PAC55XX_GPIOC->INTCFG.P0 = 0;       // Falling edge
        PAC55XX_GPIOC->INTEN.P0 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x02) == 0x02)
    {
        PAC55XX_GPIOC->MODE.P1 = 3;             // High-Z Input
        PAC55XX_GPIOC->INTTYPE.P1 = 0;          // Edge trigger
        PAC55XX_GPIOC->INTEDGEBOTH.P1 = 0;      // Only one edge
        if ((active_high_mask & 0x02) == 0x02)
            PAC55XX_GPIOC->INTCFG.P1 = 1;       // Rising edge
        else
            PAC55XX_GPIOC->INTCFG.P1 = 0;       // Falling edge
        PAC55XX_GPIOC->INTEN.P1 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x04) == 0x04)
    {
        PAC55XX_GPIOC->MODE.P2 = 3;             // High-Z Input
        PAC55XX_GPIOC->INTTYPE.P2 = 0;          // Edge trigger
        PAC55XX_GPIOC->INTEDGEBOTH.P2 = 0;      // Only one edge
        if ((active_high_mask & 0x04) == 0x04)
            PAC55XX_GPIOC->INTCFG.P2 = 1;       // Rising edge
        else
            PAC55XX_GPIOC->INTCFG.P2 = 0;       // Falling edge
        PAC55XX_GPIOC->INTEN.P2 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x08) == 0x08)
    {
        PAC55XX_GPIOC->MODE.P3 = 3;             // High-Z Input
        PAC55XX_GPIOC->INTTYPE.P3 = 0;          // Edge trigger
        PAC55XX_GPIOC->INTEDGEBOTH.P3 = 0;      // Only one edge
        if ((active_high_mask & 0x08) == 0x08)
            PAC55XX_GPIOC->INTCFG.P3 = 1;       // Rising edge
        else
            PAC55XX_GPIOC->INTCFG.P3 = 0;       // Falling edge
        PAC55XX_GPIOC->INTEN.P3 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x10) == 0x10)
    {
        PAC55XX_GPIOC->MODE.P4 = 3;             // High-Z Input
        PAC55XX_GPIOC->INTTYPE.P4 = 0;          // Edge trigger
        PAC55XX_GPIOC->INTEDGEBOTH.P4 = 0;      // Only one edge
        if ((active_high_mask & 0x10) == 0x10)
            PAC55XX_GPIOC->INTCFG.P4 = 1;       // Rising edge
        else
            PAC55XX_GPIOC->INTCFG.P4 = 0;       // Falling edge
        PAC55XX_GPIOC->INTEN.P4 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x20) == 0x20)
    {
        PAC55XX_GPIOC->MODE.P5 = 3;             // High-Z Input
        PAC55XX_GPIOC->INTTYPE.P5 = 0;          // Edge trigger
        PAC55XX_GPIOC->INTEDGEBOTH.P5 = 0;      // Only one edge
        if ((active_high_mask & 0x20) == 0x20)
            PAC55XX_GPIOC->INTCFG.P5 = 1;       // Rising edge
        else
            PAC55XX_GPIOC->INTCFG.P5 = 0;       // Falling edge
        PAC55XX_GPIOC->INTEN.P5 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x40) == 0x40)
    {
        PAC55XX_GPIOC->MODE.P6 = 3;             // High-Z Input
        PAC55XX_GPIOC->INTTYPE.P6 = 0;          // Edge trigger
        PAC55XX_GPIOC->INTEDGEBOTH.P6 = 0;      // Only one edge
        if ((active_high_mask & 0x40) == 0x40)
            PAC55XX_GPIOC->INTCFG.P6 = 1;       // Rising edge
        else
            PAC55XX_GPIOC->INTCFG.P6 = 0;       // Falling edge
        PAC55XX_GPIOC->INTEN.P6 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x80) == 0x80)
    {
        PAC55XX_GPIOC->MODE.P7 = 3;             // High-Z Input
        PAC55XX_GPIOC->INTTYPE.P7 = 0;          // Edge trigger
        PAC55XX_GPIOC->INTEDGEBOTH.P7 = 0;      // Only one edge
        if ((active_high_mask & 0x80) == 0x80)
            PAC55XX_GPIOC->INTCFG.P7 = 1;       // Rising edge
        else
            PAC55XX_GPIOC->INTCFG.P7 = 0;       // Falling edge
        PAC55XX_GPIOC->INTEN.P7 = 1;            // Enable Interrupt
    }
    
    if (port_mask != 0x00)
    {
        PAC55XX_GPIOC->INTCLEAR.w = 0xFF;           // Clear any pending interrupts
        NVIC_EnableIRQ(GpioC_IRQn);	                // Enable interrupts in NVIC
    }
}

RAMFUNC_GPIO void pac5xxx_gpio_configure_interrupt_d(uint8_t port_mask, uint8_t active_high_mask)
{
    if ((port_mask & 0x01) == 0x01)
    {
        PAC55XX_GPIOD->MODE.P0 = 3;             // High-Z Input
        PAC55XX_GPIOD->INTTYPE.P0 = 0;          // Edge trigger
        PAC55XX_GPIOD->INTEDGEBOTH.P0 = 0;      // Only one edge
        if ((active_high_mask & 0x01) == 0x01)
            PAC55XX_GPIOD->INTCFG.P0 = 1;       // Rising edge
        else
            PAC55XX_GPIOD->INTCFG.P0 = 0;       // Falling edge
        PAC55XX_GPIOD->INTEN.P0 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x02) == 0x02)
    {
        PAC55XX_GPIOD->MODE.P1 = 3;             // High-Z Input
        PAC55XX_GPIOD->INTTYPE.P1 = 0;          // Edge trigger
        PAC55XX_GPIOD->INTEDGEBOTH.P1 = 0;      // Only one edge
        if ((active_high_mask & 0x02) == 0x02)
            PAC55XX_GPIOD->INTCFG.P1 = 1;       // Rising edge
        else
            PAC55XX_GPIOD->INTCFG.P1 = 0;       // Falling edge
        PAC55XX_GPIOD->INTEN.P1 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x04) == 0x04)
    {
        PAC55XX_GPIOD->MODE.P2 = 3;             // High-Z Input
        PAC55XX_GPIOD->INTTYPE.P2 = 0;          // Edge trigger
        PAC55XX_GPIOD->INTEDGEBOTH.P2 = 0;      // Only one edge
        if ((active_high_mask & 0x04) == 0x04)
            PAC55XX_GPIOD->INTCFG.P2 = 1;       // Rising edge
        else
            PAC55XX_GPIOD->INTCFG.P2 = 0;       // Falling edge
        PAC55XX_GPIOD->INTEN.P2 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x08) == 0x08)
    {
        PAC55XX_GPIOD->MODE.P3 = 3;             // High-Z Input
        PAC55XX_GPIOD->INTTYPE.P3 = 0;          // Edge trigger
        PAC55XX_GPIOD->INTEDGEBOTH.P3 = 0;      // Only one edge
        if ((active_high_mask & 0x08) == 0x08)
            PAC55XX_GPIOD->INTCFG.P3 = 1;       // Rising edge
        else
            PAC55XX_GPIOD->INTCFG.P3 = 0;       // Falling edge
        PAC55XX_GPIOD->INTEN.P3 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x10) == 0x10)
    {
        PAC55XX_GPIOD->MODE.P4 = 3;             // High-Z Input
        PAC55XX_GPIOD->INTTYPE.P4 = 0;          // Edge trigger
        PAC55XX_GPIOD->INTEDGEBOTH.P4 = 0;      // Only one edge
        if ((active_high_mask & 0x10) == 0x10)
            PAC55XX_GPIOD->INTCFG.P4 = 1;       // Rising edge
        else
            PAC55XX_GPIOD->INTCFG.P4 = 0;       // Falling edge
        PAC55XX_GPIOD->INTEN.P4 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x20) == 0x20)
    {
        PAC55XX_GPIOD->MODE.P5 = 3;             // High-Z Input
        PAC55XX_GPIOD->INTTYPE.P5 = 0;          // Edge trigger
        PAC55XX_GPIOD->INTEDGEBOTH.P5 = 0;      // Only one edge
        if ((active_high_mask & 0x20) == 0x20)
            PAC55XX_GPIOD->INTCFG.P5 = 1;       // Rising edge
        else
            PAC55XX_GPIOD->INTCFG.P5 = 0;       // Falling edge
        PAC55XX_GPIOD->INTEN.P5 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x40) == 0x40)
    {
        PAC55XX_GPIOD->MODE.P6 = 3;             // High-Z Input
        PAC55XX_GPIOD->INTTYPE.P6 = 0;          // Edge trigger
        PAC55XX_GPIOD->INTEDGEBOTH.P6 = 0;      // Only one edge
        if ((active_high_mask & 0x40) == 0x40)
            PAC55XX_GPIOD->INTCFG.P6 = 1;       // Rising edge
        else
            PAC55XX_GPIOD->INTCFG.P6 = 0;       // Falling edge
        PAC55XX_GPIOD->INTEN.P6 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x80) == 0x80)
    {
        PAC55XX_GPIOD->MODE.P7 = 3;             // High-Z Input
        PAC55XX_GPIOD->INTTYPE.P7 = 0;          // Edge trigger
        PAC55XX_GPIOD->INTEDGEBOTH.P7 = 0;      // Only one edge
        if ((active_high_mask & 0x80) == 0x80)
            PAC55XX_GPIOD->INTCFG.P7 = 1;       // Rising edge
        else
            PAC55XX_GPIOD->INTCFG.P7 = 0;       // Falling edge
        PAC55XX_GPIOD->INTEN.P7 = 1;            // Enable Interrupt
    }
    
    if (port_mask != 0x00)
    {
        PAC55XX_GPIOD->INTCLEAR.w = 0xFF;           // Clear any pending interrupts
        NVIC_EnableIRQ(GpioD_IRQn);	                // Enable interrupts in NVIC
    }
}

RAMFUNC_GPIO void pac5xxx_gpio_configure_interrupt_e(uint8_t port_mask, uint8_t active_high_mask)
{
    if ((port_mask & 0x01) == 0x01)
    {
        PAC55XX_GPIOE->MODE.P0 = 3;             // High-Z Input
        PAC55XX_GPIOE->INTTYPE.P0 = 0;          // Edge trigger
        PAC55XX_GPIOE->INTEDGEBOTH.P0 = 0;      // Only one edge
        if ((active_high_mask & 0x01) == 0x01)
            PAC55XX_GPIOE->INTCFG.P0 = 1;       // Rising edge
        else
            PAC55XX_GPIOE->INTCFG.P0 = 0;       // Falling edge
        PAC55XX_GPIOE->INTEN.P0 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x02) == 0x02)
    {
        PAC55XX_GPIOE->MODE.P1 = 3;             // High-Z Input
        PAC55XX_GPIOE->INTTYPE.P1 = 0;          // Edge trigger
        PAC55XX_GPIOE->INTEDGEBOTH.P1 = 0;      // Only one edge
        if ((active_high_mask & 0x02) == 0x02)
            PAC55XX_GPIOE->INTCFG.P1 = 1;       // Rising edge
        else
            PAC55XX_GPIOE->INTCFG.P1 = 0;       // Falling edge
        PAC55XX_GPIOE->INTEN.P1 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x04) == 0x04)
    {
        PAC55XX_GPIOE->MODE.P2 = 3;             // High-Z Input
        PAC55XX_GPIOE->INTTYPE.P2 = 0;          // Edge trigger
        PAC55XX_GPIOE->INTEDGEBOTH.P2 = 0;      // Only one edge
        if ((active_high_mask & 0x04) == 0x04)
            PAC55XX_GPIOE->INTCFG.P2 = 1;       // Rising edge
        else
            PAC55XX_GPIOE->INTCFG.P2 = 0;       // Falling edge
        PAC55XX_GPIOE->INTEN.P2 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x08) == 0x08)
    {
        PAC55XX_GPIOE->MODE.P3 = 3;             // High-Z Input
        PAC55XX_GPIOE->INTTYPE.P3 = 0;          // Edge trigger
        PAC55XX_GPIOE->INTEDGEBOTH.P3 = 0;      // Only one edge
        if ((active_high_mask & 0x08) == 0x08)
            PAC55XX_GPIOE->INTCFG.P3 = 1;       // Rising edge
        else
            PAC55XX_GPIOE->INTCFG.P3 = 0;       // Falling edge
        PAC55XX_GPIOE->INTEN.P3 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x10) == 0x10)
    {
        PAC55XX_GPIOE->MODE.P4 = 3;             // High-Z Input
        PAC55XX_GPIOE->INTTYPE.P4 = 0;          // Edge trigger
        PAC55XX_GPIOE->INTEDGEBOTH.P4 = 0;      // Only one edge
        if ((active_high_mask & 0x10) == 0x10)
            PAC55XX_GPIOE->INTCFG.P4 = 1;       // Rising edge
        else
            PAC55XX_GPIOE->INTCFG.P4 = 0;       // Falling edge
        PAC55XX_GPIOE->INTEN.P4 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x20) == 0x20)
    {
        PAC55XX_GPIOE->MODE.P5 = 3;             // High-Z Input
        PAC55XX_GPIOE->INTTYPE.P5 = 0;          // Edge trigger
        PAC55XX_GPIOE->INTEDGEBOTH.P5 = 0;      // Only one edge
        if ((active_high_mask & 0x20) == 0x20)
            PAC55XX_GPIOE->INTCFG.P5 = 1;       // Rising edge
        else
            PAC55XX_GPIOE->INTCFG.P5 = 0;       // Falling edge
        PAC55XX_GPIOE->INTEN.P5 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x40) == 0x40)
    {
        PAC55XX_GPIOE->MODE.P6 = 3;             // High-Z Input
        PAC55XX_GPIOE->INTTYPE.P6 = 0;          // Edge trigger
        PAC55XX_GPIOE->INTEDGEBOTH.P6 = 0;      // Only one edge
        if ((active_high_mask & 0x40) == 0x40)
            PAC55XX_GPIOE->INTCFG.P6 = 1;       // Rising edge
        else
            PAC55XX_GPIOE->INTCFG.P6 = 0;       // Falling edge
        PAC55XX_GPIOE->INTEN.P6 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x80) == 0x80)
    {
        PAC55XX_GPIOE->MODE.P7 = 3;             // High-Z Input
        PAC55XX_GPIOE->INTTYPE.P7 = 0;          // Edge trigger
        PAC55XX_GPIOE->INTEDGEBOTH.P7 = 0;      // Only one edge
        if ((active_high_mask & 0x80) == 0x80)
            PAC55XX_GPIOE->INTCFG.P7 = 1;       // Rising edge
        else
            PAC55XX_GPIOE->INTCFG.P7 = 0;       // Falling edge
        PAC55XX_GPIOE->INTEN.P7 = 1;            // Enable Interrupt
    }
    
    if (port_mask != 0x00)
    {
        PAC55XX_GPIOE->INTCLEAR.w = 0xFF;           // Clear any pending interrupts
        NVIC_EnableIRQ(GpioE_IRQn);	                // Enable interrupts in NVIC
    }
}

RAMFUNC_GPIO void pac5xxx_gpio_configure_interrupt_f(uint8_t port_mask, uint8_t active_high_mask)
{
    if ((port_mask & 0x01) == 0x01)
    {
        PAC55XX_GPIOF->MODE.P0 = 3;             // High-Z Input
        PAC55XX_GPIOF->INTTYPE.P0 = 0;          // Edge trigger
        PAC55XX_GPIOF->INTEDGEBOTH.P0 = 0;      // Only one edge
        if ((active_high_mask & 0x01) == 0x01)
            PAC55XX_GPIOF->INTCFG.P0 = 1;       // Rising edge
        else
            PAC55XX_GPIOF->INTCFG.P0 = 0;       // Falling edge
        PAC55XX_GPIOF->INTEN.P0 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x02) == 0x02)
    {
        PAC55XX_GPIOF->MODE.P1 = 3;             // High-Z Input
        PAC55XX_GPIOF->INTTYPE.P1 = 0;          // Edge trigger
        PAC55XX_GPIOF->INTEDGEBOTH.P1 = 0;      // Only one edge
        if ((active_high_mask & 0x02) == 0x02)
            PAC55XX_GPIOF->INTCFG.P1 = 1;       // Rising edge
        else
            PAC55XX_GPIOF->INTCFG.P1 = 0;       // Falling edge
        PAC55XX_GPIOF->INTEN.P1 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x04) == 0x04)
    {
        PAC55XX_GPIOF->MODE.P2 = 3;             // High-Z Input
        PAC55XX_GPIOF->INTTYPE.P2 = 0;          // Edge trigger
        PAC55XX_GPIOF->INTEDGEBOTH.P2 = 0;      // Only one edge
        if ((active_high_mask & 0x04) == 0x04)
            PAC55XX_GPIOF->INTCFG.P2 = 1;       // Rising edge
        else
            PAC55XX_GPIOF->INTCFG.P2 = 0;       // Falling edge
        PAC55XX_GPIOF->INTEN.P2 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x08) == 0x08)
    {
        PAC55XX_GPIOF->MODE.P3 = 3;             // High-Z Input
        PAC55XX_GPIOF->INTTYPE.P3 = 0;          // Edge trigger
        PAC55XX_GPIOF->INTEDGEBOTH.P3 = 0;      // Only one edge
        if ((active_high_mask & 0x08) == 0x08)
            PAC55XX_GPIOF->INTCFG.P3 = 1;       // Rising edge
        else
            PAC55XX_GPIOF->INTCFG.P3 = 0;       // Falling edge
        PAC55XX_GPIOF->INTEN.P3 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x10) == 0x10)
    {
        PAC55XX_GPIOF->MODE.P4 = 3;             // High-Z Input
        PAC55XX_GPIOF->INTTYPE.P4 = 0;          // Edge trigger
        PAC55XX_GPIOF->INTEDGEBOTH.P4 = 0;      // Only one edge
        if ((active_high_mask & 0x10) == 0x10)
            PAC55XX_GPIOF->INTCFG.P4 = 1;       // Rising edge
        else
            PAC55XX_GPIOF->INTCFG.P4 = 0;       // Falling edge
        PAC55XX_GPIOF->INTEN.P4 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x20) == 0x20)
    {
        PAC55XX_GPIOF->MODE.P5 = 3;             // High-Z Input
        PAC55XX_GPIOF->INTTYPE.P5 = 0;          // Edge trigger
        PAC55XX_GPIOF->INTEDGEBOTH.P5 = 0;      // Only one edge
        if ((active_high_mask & 0x20) == 0x20)
            PAC55XX_GPIOF->INTCFG.P5 = 1;       // Rising edge
        else
            PAC55XX_GPIOF->INTCFG.P5 = 0;       // Falling edge
        PAC55XX_GPIOF->INTEN.P5 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x40) == 0x40)
    {
        PAC55XX_GPIOF->MODE.P6 = 3;             // High-Z Input
        PAC55XX_GPIOF->INTTYPE.P6 = 0;          // Edge trigger
        PAC55XX_GPIOF->INTEDGEBOTH.P6 = 0;      // Only one edge
        if ((active_high_mask & 0x40) == 0x40)
            PAC55XX_GPIOF->INTCFG.P6 = 1;       // Rising edge
        else
            PAC55XX_GPIOF->INTCFG.P6 = 0;       // Falling edge
        PAC55XX_GPIOF->INTEN.P6 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x80) == 0x80)
    {
        PAC55XX_GPIOF->MODE.P7 = 3;             // High-Z Input
        PAC55XX_GPIOF->INTTYPE.P7 = 0;          // Edge trigger
        PAC55XX_GPIOF->INTEDGEBOTH.P7 = 0;      // Only one edge
        if ((active_high_mask & 0x80) == 0x80)
            PAC55XX_GPIOF->INTCFG.P7 = 1;       // Rising edge
        else
            PAC55XX_GPIOF->INTCFG.P7 = 0;       // Falling edge
        PAC55XX_GPIOF->INTEN.P7 = 1;            // Enable Interrupt
    }
    
    if (port_mask != 0x00)
    {
        PAC55XX_GPIOF->INTCLEAR.w = 0xFF;           // Clear any pending interrupts
        NVIC_EnableIRQ(GpioF_IRQn);	                // Enable interrupts in NVIC
    }
}

RAMFUNC_GPIO void pac5xxx_gpio_configure_interrupt_g(uint8_t port_mask, uint8_t active_high_mask)
{
    if ((port_mask & 0x01) == 0x01)
    {
        PAC55XX_GPIOG->MODE.P0 = 3;             // High-Z Input
        PAC55XX_GPIOG->INTTYPE.P0 = 0;          // Edge trigger
        PAC55XX_GPIOG->INTEDGEBOTH.P0 = 0;      // Only one edge
        if ((active_high_mask & 0x01) == 0x01)
            PAC55XX_GPIOG->INTCFG.P0 = 1;       // Rising edge
        else
            PAC55XX_GPIOG->INTCFG.P0 = 0;       // Falling edge
        PAC55XX_GPIOG->INTEN.P0 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x02) == 0x02)
    {
        PAC55XX_GPIOG->MODE.P1 = 3;             // High-Z Input
        PAC55XX_GPIOG->INTTYPE.P1 = 0;          // Edge trigger
        PAC55XX_GPIOG->INTEDGEBOTH.P1 = 0;      // Only one edge
        if ((active_high_mask & 0x02) == 0x02)
            PAC55XX_GPIOG->INTCFG.P1 = 1;       // Rising edge
        else
            PAC55XX_GPIOG->INTCFG.P1 = 0;       // Falling edge
        PAC55XX_GPIOG->INTEN.P1 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x04) == 0x04)
    {
        PAC55XX_GPIOG->MODE.P2 = 3;             // High-Z Input
        PAC55XX_GPIOG->INTTYPE.P2 = 0;          // Edge trigger
        PAC55XX_GPIOG->INTEDGEBOTH.P2 = 0;      // Only one edge
        if ((active_high_mask & 0x04) == 0x04)
            PAC55XX_GPIOG->INTCFG.P2 = 1;       // Rising edge
        else
            PAC55XX_GPIOG->INTCFG.P2 = 0;       // Falling edge
        PAC55XX_GPIOG->INTEN.P2 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x08) == 0x08)
    {
        PAC55XX_GPIOG->MODE.P3 = 3;             // High-Z Input
        PAC55XX_GPIOG->INTTYPE.P3 = 0;          // Edge trigger
        PAC55XX_GPIOG->INTEDGEBOTH.P3 = 0;      // Only one edge
        if ((active_high_mask & 0x08) == 0x08)
            PAC55XX_GPIOG->INTCFG.P3 = 1;       // Rising edge
        else
            PAC55XX_GPIOG->INTCFG.P3 = 0;       // Falling edge
        PAC55XX_GPIOG->INTEN.P3 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x10) == 0x10)
    {
        PAC55XX_GPIOG->MODE.P4 = 3;             // High-Z Input
        PAC55XX_GPIOG->INTTYPE.P4 = 0;          // Edge trigger
        PAC55XX_GPIOG->INTEDGEBOTH.P4 = 0;      // Only one edge
        if ((active_high_mask & 0x10) == 0x10)
            PAC55XX_GPIOG->INTCFG.P4 = 1;       // Rising edge
        else
            PAC55XX_GPIOG->INTCFG.P4 = 0;       // Falling edge
        PAC55XX_GPIOG->INTEN.P4 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x20) == 0x20)
    {
        PAC55XX_GPIOG->MODE.P5 = 3;             // High-Z Input
        PAC55XX_GPIOG->INTTYPE.P5 = 0;          // Edge trigger
        PAC55XX_GPIOG->INTEDGEBOTH.P5 = 0;      // Only one edge
        if ((active_high_mask & 0x20) == 0x20)
            PAC55XX_GPIOG->INTCFG.P5 = 1;       // Rising edge
        else
            PAC55XX_GPIOG->INTCFG.P5 = 0;       // Falling edge
        PAC55XX_GPIOG->INTEN.P5 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x40) == 0x40)
    {
        PAC55XX_GPIOG->MODE.P6 = 3;             // High-Z Input
        PAC55XX_GPIOG->INTTYPE.P6 = 0;          // Edge trigger
        PAC55XX_GPIOG->INTEDGEBOTH.P6 = 0;      // Only one edge
        if ((active_high_mask & 0x40) == 0x40)
            PAC55XX_GPIOG->INTCFG.P6 = 1;       // Rising edge
        else
            PAC55XX_GPIOG->INTCFG.P6 = 0;       // Falling edge
        PAC55XX_GPIOG->INTEN.P6 = 1;            // Enable Interrupt
    }

    if ((port_mask & 0x80) == 0x80)
    {
        PAC55XX_GPIOG->MODE.P7 = 3;             // High-Z Input
        PAC55XX_GPIOG->INTTYPE.P7 = 0;          // Edge trigger
        PAC55XX_GPIOG->INTEDGEBOTH.P7 = 0;      // Only one edge
        if ((active_high_mask & 0x80) == 0x80)
            PAC55XX_GPIOG->INTCFG.P7 = 1;       // Rising edge
        else
            PAC55XX_GPIOG->INTCFG.P7 = 0;       // Falling edge
        PAC55XX_GPIOG->INTEN.P7 = 1;            // Enable Interrupt
    }
    
    if (port_mask != 0x00)
    {
        PAC55XX_GPIOG->INTCLEAR.w = 0xFF;           // Clear any pending interrupts
        NVIC_EnableIRQ(GpioG_IRQn);	                // Enable interrupts in NVIC
    }
}
