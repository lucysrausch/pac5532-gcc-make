//=================================================================================
/// @file     pac5xxx_ssp.h
/// @brief    CMSIS Cortex-M Header File for the PAC55XX SSP Controller
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

#ifndef PAC5XXX_SSP_H
#define PAC5XXX_SSP_H

// SSP Endian Order Enumeration Type
typedef enum {
    SSP_ENDIAN_MSB = 0,                     // MSB transmit / receive first
    SSP_ENDIAN_LSB = 1                      // LSB transmit / receive first
} SSP_ENDIAN_TYPE;

// SSP loopback Enumeration Type
typedef enum {
    SSP_LP_NORMAL   = 0,                    // Normal mode
    SSP_LP_LOOPBACK = 1                     // Loopback mode
} SSP_LOOPBACK_TYPE;

// SSP Controller Enumeration Type
typedef enum {
    SSP_CONTROL_DISABLE = 0,
    SSP_CONTROL_ENABLE  = 1
} SSP_CONTROL_TYPE;

// SSP Master/Slave Enumeration Type
typedef enum {
    SSP_MS_MASTER = 0,                      // The SSP controller acts as a bus master, driving the SCLK, MOSI, and SS signals and receiving MISO
    SSP_MS_SLAVE  = 1                       // The SSP controller acts as a bus slave, driving the MISO and receiving SCLK, MOSI, and SS
} SSP_MS_TYPE;

// SSP Output Enumeration Type
typedef enum {
    SSP_OUTPUT_DRIVE     = 0,               // The SSP can drive the MISO output in slave mode
    SSP_OUTPUT_NOT_DRIVE = 1                // The SSP must not drive the MISO output in slave mode
} SSP_OUTPUT_TYPE;

// SSP Out Enumeration Type
typedef enum {
    SSP_PUT_PHASE_1 = 0,                    // The SSP controller captures serial data on the first edge transition of the frame.
    SSP_PUT_PHASE_2 = 1                     // The SSP controller captures serial data on the second edge transition of the frame.
} SSP_PUT_PHASE_TYPE;

// SSP Clock Out Polarity Enumeration Type
typedef enum {
    SSP_CLK_POLARITY_LOW   = 0,             //The SSP controller maintains the bus clock low between frames
    SSP_CLK_POLARITY_HIGH  = 1              //The SSP controller maintains the bus clock hight between frames
} SSP_CLK_POLARITY_TYPE;

// SSP Frame Format Enumeration Type
typedef enum {
    SSP_FRAME_FORMAT_SPI        = 0,
    SSP_FRAME_FORMAT_TI         = 1,
    SSP_FRAME_FORMAT_MICROWIRE  = 2 
} SSP_FRAME_FORMAT_TYPE;

// SSP Data Size Select Enumeration Type
typedef enum {
    SSP_DATA_SIZE_4  = 3,                   // 4-bit transfer
    SSP_DATA_SIZE_5  = 4,                   // 5-bit transfer
    SSP_DATA_SIZE_6  = 5,                   // 6-bit transfer
    SSP_DATA_SIZE_7  = 6,                   // 7-bit transfer
    SSP_DATA_SIZE_8  = 7,                   // 8-bit transfer
    SSP_DATA_SIZE_9  = 8,                   // 9-bit transfer
    SSP_DATA_SIZE_10 = 9,                   // 10-bit transfer
    SSP_DATA_SIZE_11 = 10,                  // 11-bit transfer
    SSP_DATA_SIZE_12 = 11,                  // 12-bit transfer
    SSP_DATA_SIZE_13 = 12,                  // 13-bit transfer
    SSP_DATA_SIZE_14 = 13,                  // 14-bit transfer
    SSP_DATA_SIZE_15 = 14,                  // 15-bit transfer
    SSP_DATA_SIZE_16 = 15                   // 16-bit transfer
} SSP_DATA_SIZE_TYPE;

// SSP Chip Select Pull High Enumeration Type
typedef enum {
    SSP_CS_PULL_HIGH_NONE = 0,              // SS cannot pull high after frame transfer
    SSP_CS_PULL_HIGH_MUST = 1               // SS must pull high after frame transfer
} SSP_CS_PULL_HIGH_TYPE;

// SSP Chip Select State Enumeration Type
typedef enum {
    SSP_CS_STATE_LOW  = 0,                  // SS is low
    SSP_CS_STATE_HIGH = 1                   // SS is high
} SSP_CS_STATE_TYPE;

// SSP Chip Select Software Control Enumeration Type
typedef enum {
    SSP_CS_SWSEL_AUTO = 0,                  // SS is automatically controlled by the SPI module
    SSP_CS_SWSEL_SOFT = 1                   // SS is software controlled by SSPACSCR.SWCS
} SSP_CS_SWSEL_TYPE;

typedef struct
{
    // CON (SSP Control Register, Offset: 0x0000)
    union {
        __IO uint32_t w;
        struct {
            __IO uint32_t DSS           : 5;    // 4:0      Data Size Select
            __IO uint32_t FRF           : 2;    // 6:5      Frame Format
            __IO uint32_t CPO           : 1;    // 7        Clock Out Polarity
            __IO uint32_t CPH           : 1;    // 8        Clock Out Phase
            __IO uint32_t SOD           : 1;    // 9        Slave Output Disable
            __IO uint32_t MS            : 1;    // 10       Master/Slave mode
            __IO uint32_t SSPEN         : 1;    // 11       SSP Enable
            __IO uint32_t LBM           : 1;    // 12       Loobback Mode
            __IO uint32_t LSBFIRST      : 1;    // 13       Endian Order
                 uint32_t               : 18;   // 31:14
        };
    } CON;
    
    // STAT (SSP Status Register, Offset: 0x0004)
    union {
        __I uint32_t w;
        struct {
            __I uint32_t TFE           : 1;     // 0        TX FIFO empty
            __I uint32_t TNF           : 1;     // 1        TX FIFO not full
            __I uint32_t RNE           : 1;     // 2        RX FIFO not empty
            __I uint32_t RFF           : 1;     // 3        RX FIFO full
            __I uint32_t BSY           : 1;     // 4        Busy Bit
                uint32_t               : 27;    // 31:5
        };
    } STAT;
    
    // DAT (SSP Data Register, Offset: 0x0008)
    union {
        __IO uint32_t w;
        struct {
            __IO uint32_t DATA         : 32;    // 31:0
        };
    } DAT;
    
    // CLK (SSP Clock Control Register, Offset: 0x000C)
    union {
        __IO uint32_t w;
        struct {
            __IO uint32_t N            : 8;     // 7:0      N nust be event value from 2 to 254.
            __IO uint32_t M            : 8;     // 15:8     Fsspclk = PCLK/((SSPxCLK.M + 1)*SSPxCLK.N)
                 uint32_t              : 16;    // 31:16
        };
    } CLK;
    
    // IMSC (SSP Interrupt Mask Set and Clear Register, Offset: 0x0010)
    union {
        __IO uint32_t w;
        struct {
            __IO uint32_t ROIM          : 1;    // 0        RX FIFO Overrun Interrupt Mask
            __IO uint32_t RTIM          : 1;    // 1        RX FIFO Timeout Interrupt Mask
            __IO uint32_t RXIM          : 1;    // 2        RX FIFO Interrupt Mask
            __IO uint32_t TXIM          : 1;    // 3        TX FIFO Interrupt Mask
                 uint32_t               : 28;   // 31:4
        };
    } IMSC;
    
    // RIS (SSP Raw Interrupt Status Register, Offset: 0x0014)
    union {
        __I uint32_t w;
        struct {
            __I uint32_t RORIS         : 1;     // 0        RX FIFO Overrun Interrupt Status
            __I uint32_t RTRIS         : 1;     // 1        RX FIFO Timeout Interrupt Status
            __I uint32_t RXRIS         : 1;     // 2        RX FIFO Interrupt Status
            __I uint32_t TXRIS         : 1;     // 3        TX FIFO Interrupt Status
                uint32_t               : 28;    // 31:4
        };
    } RIS;
    
    // MIS (SSP Masked Interrupt Status Register, Offset: 0x0018)
    union {
        __I uint32_t w;
        struct {
            __I uint32_t ROMIS         : 1;     // 0        RX FIFO Overrun Interrupt Status
            __I uint32_t RTMIS         : 1;     // 1        RX FIFO Timeout Interrupt Status
            __I uint32_t RXMIS         : 1;     // 2        RX FIFO Interrupt Status
            __I uint32_t TXMIS         : 1;     // 3        TX FIFO Interrupt Status
                uint32_t               : 28;    // 31:4
        };
    } MIS;
    
    // ICLR (SSP Interrupt Clear Register, Offset: 0x001C)
    union {
        __IO uint32_t w;
        struct {
            __IO uint32_t ROIC          : 1;    // 0        RX FIFO Overrun Interrupt Clear
            __IO uint32_t RTIC          : 1;    // 1        RX FIFO Timeout Interrupt Clear
                 uint32_t               : 30;   // 31:2
        };
    } ICLR;

    // Reserved memory from 0x0020 ~ 0x0024
    uint32_t RESERVED1[2];
    
    // CSCR (SSP Slave Select Configuration Register, Offset: 0x0028)
    union {
        __IO uint32_t w;
        struct {
            __IO uint32_t SELSS         : 2;    // 1:0      Slave Select Signal Control
            __IO uint32_t SWSEL         : 1;    // 2        Slave Select Software Control
            __IO uint32_t SWSS          : 1;    // 3        Slave Select State
            __IO uint32_t SPHDONTCARE   : 1;    // 4        Slave Select Pull High
                 uint32_t               : 27;   // 31:5
        };
    } SSCR;
    
} PAC55XX_SSP_TYPEDEF;
#endif // PAC5XXX_SSP_H
