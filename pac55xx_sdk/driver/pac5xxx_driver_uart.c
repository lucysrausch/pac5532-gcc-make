/**************************************************************************//**
 * @file     pac5xxx_driver_uart_config.c
 * @brief    Firmware driver for the PAC5XXX UART
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

#include "pac5xxx_driver_uart.h"

RAMFUNC_UART void pac5xxx_uart_config_LCR2(PAC55XX_UART_TYPEDEF* uart_ptr, 
                                            UARTLCR_WL_TYPE bpc,
                                            UART_STOPBITS_TYPE stop_bits,
                                            UART_PEN_TYPE parity_enabled,
                                            UART_PARITY_TYPE parity,
                                            UART_BREAKCONTROL_TYPE break_control)
{
    uart_ptr->LCR.WLS = bpc;
    uart_ptr->LCR.SBS = stop_bits;
    uart_ptr->LCR.PEN = parity_enabled;
    uart_ptr->LCR.PSEL = parity;
    uart_ptr->LCR.BCON = break_control;
}

RAMFUNC_UART void pac5xxx_uart_config_divisor_latch2(PAC55XX_UART_TYPEDEF* uart_ptr, uint32_t latch_value)
{
	uart_ptr->DLR.w = latch_value;
}

RAMFUNC_UART void pac5xxx_uart_io_config2()  //TODO: make it configurable depending on UART Pins selected
{
    // Select UART C peripheral on PE2 and PE3
    PAC55XX_GPIOE->MODE.P2 = 1;                     // TX
    PAC55XX_GPIOE->MODE.P3 = 3;                     // RX
    PAC55XX_SCC->PEMUXSEL.w &= 0xFFFFF0FF;          // Clear Port E Pin 2 selection
    PAC55XX_SCC->PEMUXSEL.w |= 0x00000500;          // Set Port E Pin 2 UART C MOSI	
    PAC55XX_SCC->PEMUXSEL.w &= 0xFFFF0FFF;          // Clear Port F Pin 3 selection
    PAC55XX_SCC->PEMUXSEL.w |= 0x00005000;          // Set Port E Pin 3 UART C MOSI	
}
