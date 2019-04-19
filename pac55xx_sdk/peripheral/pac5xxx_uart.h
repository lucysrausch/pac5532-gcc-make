//=================================================================================
/// @file     pac5xxx_uart.h
/// @brief    CMSIS Cortex-M Header File for the PAC55XX UART Controller
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
//=================================================================================

#ifndef PAC5XXX_UART_H
#define PAC5XXX_UART_H

// Interrupt Enable Enumeration Type
typedef enum {
    UARTA =   0,
    UARTB =   1,
    UARTC =   2,
    UARTD =   3
} UART_TYPE;

// Interrupt Enable Enumeration Type
typedef enum {
    UART_INT_DISABLE =   0,
    UART_INT_ENABLE  =   1
} UART_INTERUPT_ENABLE_TYPE;

// UART Interrupt Identification Enumeration Type
typedef enum {
    UARTIIR_INTID_TX_HOLD_EMPTY     = 1,        // TX Holding Register Empty
    UARTIIR_INTID_RX_DATA_AVAIL     = 2,        // Receive Data Available
    UARTIIR_INTID_RX_LINE_STATUS    = 3,        // Receive Line Status
    UARTIIR_INTID_FIFO_TIMEOUT      = 6         // Receive FIFO Character time-out
} UARTIIR_INTID_TYPE;

// UART FIFO Depth Enumeration Type
typedef enum {
    UARTFCR_TL_1B  = 0,                         // 1 character
    UARTFCR_TL_4B  = 1,                         // 4 characters
    UARTFCR_TL_8B  = 2,                         // 8 character
    UARTFCR_TL_14B = 3                          // 14 characters
} UARTFCR_FIFO_DEPTH_TYPE;

// UART Word Length Enumeration Type
typedef enum {
    UARTLCR_WL_BPC_5 = 0,                       // 5 bits per character
    UARTLCR_WL_BPC_6 = 1,                       // 6 bits per character
    UARTLCR_WL_BPC_7 = 2,                       // 7 bits per character
    UARTLCR_WL_BPC_8 = 3                        // 8 bits per character
} UARTLCR_WL_TYPE;

//UART Break Control Enumeration Type
typedef enum {
    UART_BRKCTL_DISABLE =   0,                  // Disable break transmission
    UART_BRKCTL_FORCE_0 =   1                   // Force UARTxTXD to logic 0
} UART_BREAKCONTROL_TYPE;

// UART Parity Select Enumeration Type
typedef enum {
    UART_PARITY_ODD           = 0,              // ODD parity
    UART_PARITY_EVEN          = 1,              // EVEN parity
    UART_PARITY_FORCE_STICK_1 = 2,              // Forced 1 stick parity
    UART_PARITY_FORCE_STICK_0 = 3               // Forced 0 stick parity
} UART_PARITY_TYPE;

//UART Parity Enabel Enumeration Type
typedef enum {
    UART_PEN_DISABLE = 0,                       // Disable parity generation and checking
    UART_PEN_ENABLE  = 1                        // Enable parity generation and checking
} UART_PEN_TYPE;

//UART Stop Bits Enumeration Type
typedef enum {
    UART_STOP_BITS_1 = 0,                       // 1 stop bits
    UART_STOP_BITS_2 = 1                        // 2 stop bits
} UART_STOPBITS_TYPE;

typedef struct
{
    // RBR (UART Receive Buffer Register, Offset: 0x0000)
    union {
        __I uint32_t w;
        struct {
            __I uint32_t RBR       : 8;         // 7:0      Contains the oldest received character in the UART RX FIFO.
                uint32_t           : 24;        // 31:8
        };
    } RBR;
    
    // THR (UART Transmit Holding Register, Offset: 0x0004)
    union {
        __IO uint32_t w;
        struct {
            __O uint32_t THR       : 8;         // 7:0      Writing UARTxTHR causes the data to be stored in the UART transmit FIFO
                uint32_t           : 24;        // 31:8
        };
    } THR;
    
    // DLR (UART Divisor Latch Register, Offset: 0x0008)
    union {
        __IO uint32_t w;
        struct {
            __IO uint32_t DLR      : 16;        // 15:0     Baud rate = PCLK/(16* DLR)
                 uint32_t          : 16;        // 31:16
        };
    } DLR;
    
    // IER (UART Interrupt Enable Register, Offset: 0x000C)
    union {
        __IO uint32_t w;
        struct {
            __IO uint32_t RBRIE     : 1;        // 0        RX Buffer Register Interrupt Enable
            __IO uint32_t THRIE     : 1;        // 1        TX Holding Register Empty Interrupt Enable
            __IO uint32_t RLSIE     : 1;        // 2        RX Line Status Interrupt Enable
                 uint32_t           : 29;       // 31:3
        };
    } IER;
    
    // IIR (UART Interrupt Identification Register, Offset: 0x0010)
    union {
        __IO uint32_t w;
        struct {
            __I uint32_t INTSTATUS     : 1;     // 0        Interrupt Status
            __I uint32_t INTID         : 3;     // 3:1      Interrupt identification
                uint32_t               : 28;    // 31:4
        };
    } IIR;
    
    // FCR (UART FIFO Control Register, Offset: 0x0014)
    union {
        __IO uint32_t w;
        struct {
            __IO uint32_t FIFOEN        : 1;    // 0        FIFO Enable
            __IO uint32_t RXFIFORST     : 1;    // 1        RX FIFO Reset
            __IO uint32_t TXFIFORST     : 1;    // 2        TX FIFO Reset
                 uint32_t               : 1;    // 3
            __IO uint32_t TXTL          : 2;    // 5:4      TX Trigger Level
            __IO uint32_t RXTL          : 2;    // 7:6      RX Trigger Level
                 uint32_t               : 24;   // 31:8
        };
    } FCR;
    
    // LCR (UART Line Control Register, Offset: 0x0018)
    union {
        __IO uint32_t w;
        struct {
            __IO uint32_t WLS           : 2;    // 1:0      Word Length Select
            __IO uint32_t SBS           : 1;    // 2        Stop Bit Select
            __IO uint32_t PEN           : 1;    // 3        Parity Enable
            __IO uint32_t PSEL          : 2;    // 5:4      Parity Select
            __IO uint32_t BCON          : 1;    // 6        Break Control
                 uint32_t               : 25;   // 31:7
        };
    } LCR;
    
    // Reserved memory 0x001C
    uint32_t RESERVED;
    
    // LSR (UART Line Status Register, Offset: 0x0020)
    union {
        __I uint32_t w;
        struct {
            __I uint32_t RDR            : 1;    // 0        Receiver Data Ready
            __I uint32_t OE             : 1;    // 1        Overrun Error
            __I uint32_t PE             : 1;    // 2        Parity Error
            __I uint32_t FE             : 1;    // 3        Framing Error
            __I uint32_t BI             : 1;    // 4        Break Interrupt
            __I uint32_t THRE           : 1;    // 5        Transmitter Holding Register Empty
            __I uint32_t TEMT           : 1;    // 6        Transmitter Empty
            __I uint32_t RXFE           : 1;    // 7        Error in RX FIFO
                uint32_t                : 24;   // 31:8
        };
    } LSR;
    
    // Reserved memory 0x0024
    uint32_t RESERVED1;
    
    // SCR (UART Scratch Pad Register, Offset: 0x0028)
    union {
        __IO uint32_t w;
        struct {
            __IO uint32_t PAD       : 8;        // 7:0      A read-able, write-able byte
                 uint32_t           : 24;       // 31:8
        };
    } SCR;

    // EFR (UART Enhanced Features Register, Offset: 0x002C)
    union {
        __IO uint32_t w;
        struct {
                 uint32_t           : 4;        // 3:0
            __IO uint32_t ENMODE    : 1;        // 4      	Enhanced Mode Enable
                 uint32_t           : 27;       // 31:5
        };
    } EFR;
    
    // Reserved memory 0x0030 - 0x003C
    uint32_t RESERVED2[4];

} PAC55XX_UART_TYPEDEF;

#endif // PAC5XXX_UART_H
