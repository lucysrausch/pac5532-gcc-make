/**************************************************************************//**
 * @file     pac5xxx_driver_uart.h
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

#ifndef PAC5XXX_DRIVER_UART_H
#define PAC5XXX_DRIVER_UART_H

/** @addtogroup PAC5XXX_Driver_UART PAC5XXX UART
  @{
*/

#include "pac5xxx.h"
#include "pac5xxx_driver_config.h"

#ifdef PAC5XXX_DRIVER_UART_RAM
#define RAMFUNC_UART	PAC5XXX_RAMFUNC
#else 
#define RAMFUNC_UART
#endif

// Function Prototypes for support functions

/**
 * @brief  This function returns the status of Interrupt Identification staus
 *
 * @return status of uart interrpt identification register
 *
 */
RAMFUNC_UART static  int pac5xxx_uart_interrupt_identification2(PAC55XX_UART_TYPEDEF* uart_ptr) { return uart_ptr->IIR.INTID; }

/**
 * @brief  This function reads the next character from the UART Receive FIFO
 *
 * @return Character read from FIFO
 * @note This function does not check if a character is available in the RX FIFO. It just returns the first character from the FIFO.
 */
RAMFUNC_UART static  uint8_t pac5xxx_uart_read2(PAC55XX_UART_TYPEDEF* uart_ptr) { return (uint8_t) (uart_ptr->RBR.RBR); }

RAMFUNC_UART void pac5xxx_uart_config_LCR2(PAC55XX_UART_TYPEDEF* uart_ptr, 
                                           UARTLCR_WL_TYPE bpc,
                                           UART_STOPBITS_TYPE stop_bits,
							               UART_PEN_TYPE parity_enabled,
						                   UART_PARITY_TYPE parity,
						                   UART_BREAKCONTROL_TYPE break_control);

/**
 * @brief  This function writes a character to the UART Transmit FIFO
 *
 * @param  data Character to send
 * @return none
 *
 */
RAMFUNC_UART static  void pac5xxx_uart_write2(PAC55XX_UART_TYPEDEF* uart_ptr, uint8_t data) { uart_ptr->THR.THR = data; }

/**
 * @brief  This function sets the interrupt state for the Transmit Holding Register Empty Condition (THREI).
 *
 * @param enable Set to 1 to enable the interrupt, 0 to disable.
 * @return none
 *
 */
RAMFUNC_UART static void pac5xxx_uart_int_enable_THREI2(PAC55XX_UART_TYPEDEF* uart_ptr, int enable) { uart_ptr->IER.THRIE = enable; }

/**
 * @brief  This function sets the interrupt state for the Receive Data Available (RBRIE).
 *
 * @param enable Set to 1 to enable the interrupt, 0 to disable.
 * @return none
 *
 */
RAMFUNC_UART static void pac5xxx_uart_int_enable_RDAI2(PAC55XX_UART_TYPEDEF* uart_ptr, int enable) { uart_ptr->IER.RBRIE = enable; }

 /**
 * @brief  This function resets the Receive FIFO.
 *
 * @return none
 *
 */
RAMFUNC_UART static  void pac5xxx_uart_rx_fifo_reset2(PAC55XX_UART_TYPEDEF* uart_ptr) { uart_ptr->FCR.RXFIFORST = 1; }

RAMFUNC_UART void pac5xxx_uart_config_divisor_latch2(PAC55XX_UART_TYPEDEF* uart_ptr, uint32_t latch_value);

/**
 * @brief  This function configures the Receive FIFO depth.
 *
 * @param depth FIFO depth from \a UART_FIFO_Depth_Type.
 * @return none
 *
 */
RAMFUNC_UART static  void pac5xxx_uart_rx_fifo_threshold2(PAC55XX_UART_TYPEDEF* uart_ptr, UARTFCR_FIFO_DEPTH_TYPE depth) { uart_ptr->FCR.RXTL = depth; }

/**
 * @brief  This function configures the Transmit FIFO depth.
 *
 * @param depth FIFO depth from \a UART_FIFO_Depth_Type.
 * @return none
 *
 */
RAMFUNC_UART static  void pac5xxx_uart_tx_fifo_threshold2(PAC55XX_UART_TYPEDEF* uart_ptr, UARTFCR_FIFO_DEPTH_TYPE depth) { uart_ptr->FCR.TXTL = depth; }

/**
 * @brief  This function configures IO for use with the UART peripheral
 *
 * @return none
 */ 
RAMFUNC_UART void pac5xxx_uart_io_config2(void);

/*@}*/ /* end of group PAC5XXX_Driver_Uart */

#endif // PAC5XXX_DRIVER_UART_H

