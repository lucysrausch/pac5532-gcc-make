//=================================================================================
/// @file     pac5xxx_can.h
/// @brief    CMSIS Cortex-M Header File for the PAC55XX CAN
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

#ifndef PAC5XXX_CAN_H
#define PAC5XXX_CAN_H

// CAN Arbitration Lost Capture Enumeration Type
typedef enum {

  ARBITRATION_LOST_IN_ID28_P_10  = 0,
  ARBITRATION_LOST_IN_ID28_P_9   = 1,
  ARBITRATION_LOST_IN_ID28_P_8   = 2,
  ARBITRATION_LOST_IN_ID28_P_7   = 3, 
  ARBITRATION_LOST_IN_ID28_P_6   = 4,
  ARBITRATION_LOST_IN_ID28_P_5   = 5,
  ARBITRATION_LOST_IN_ID28_P_4   = 6,
  ARBITRATION_LOST_IN_ID28_P_3   = 7, 
  ARBITRATION_LOST_IN_ID28_P_2   = 8,
  ARBITRATION_LOST_IN_ID28_P_1   = 9,
  ARBITRATION_LOST_IN_ID28_P_0   = 10, 
  ARBITRATION_LOST_IN_SRTR_P_RTR = 11,   
  ARBITRATION_LOST_IN_IDE_BIT    = 12,   
  ARBITRATION_LOST_IN_ID17       = 13,   
  ARBITRATION_LOST_IN_ID16       = 14,   
  ARBITRATION_LOST_IN_ID15       = 15,   
  ARBITRATION_LOST_IN_ID14       = 16,   
  ARBITRATION_LOST_IN_ID13       = 17,   
  ARBITRATION_LOST_IN_ID12       = 18,   
  ARBITRATION_LOST_IN_ID11       = 19,   
  ARBITRATION_LOST_IN_ID10       = 20,   
  ARBITRATION_LOST_IN_ID9        = 21,   
  ARBITRATION_LOST_IN_ID8        = 22,   
  ARBITRATION_LOST_IN_ID7        = 23,   
  ARBITRATION_LOST_IN_ID6        = 24,   
  ARBITRATION_LOST_IN_ID5        = 25,   
  ARBITRATION_LOST_IN_ID4        = 26,   
  ARBITRATION_LOST_IN_ID3        = 27,   
  ARBITRATION_LOST_IN_ID2        = 28,   
  ARBITRATION_LOST_IN_ID1        = 29,   
  ARBITRATION_LOST_IN_ID0        = 30,   
  ARBITRATION_LOST_IN_RTR        = 31   
} CAN_ALC_TYPE;

typedef volatile enum {
  AFM     = 0x01,
  LOM     = 0x02,
  RM      = 0x04
} dcan_mr_t;

typedef volatile enum {
  AT     =   0x2,
  TR     =   0x4
} dcan_cmd_t;


typedef volatile enum {
  DOI    =   0x1,
  BEI    =   0x2,
  TI     =   0x4,
  RI     =   0x8,
  EPI    =   0x10,
  EWI    =   0x20,
  ALI    =   0x40
} dcan_isr_t;

typedef volatile enum {
  DOIM   =   0x1,
  BEIM   =   0x2,
  TIM    =   0x4,
  RIM    =   0x8,
  EPIM   =   0x10,
  EWIM   =   0x20,
  ALIM   =   0x40
} dcan_imr_t;

typedef volatile struct {
  uint8_t BRP : 6;
  uint8_t SJW : 2;
} dcan_btr0_t;

typedef volatile struct {
  uint8_t  TSEG1 : 4;
  uint8_t  TSEG2 : 3;
  uint8_t  SAM   : 1;
} dcan_btr1_t;


typedef volatile struct
{
    union   // mr, cmd, sr, isr
    {
        __IO uint32_t w;
        struct {
            __IO dcan_mr_t mr       : 8;    // 7:0                      // MR (CAN Mode Register, 400A 0000h): 
                 uint32_t           : 24;   // 31:8      Reserved
        };
        struct {
                 uint32_t           : 8;    // 7:0       Reserved
            __IO dcan_cmd_t cmd     : 8;    // 15:8                     // CMD (CAN Command Register, 400A 0001h): 
                 uint32_t           : 16;   // 31:16     Reserved
        };
        struct{
                 uint32_t           : 16;   // 15:0      Reserved
            __I  uint32_t sr        : 8;    // 23:16                    // SR (CAN Status Register, 400A 0002h): 
                 uint32_t           : 8;    // 31:24     Reserved
        };
        struct{            
                 uint32_t           : 24;   // 23:0      Reserved
            __IO dcan_isr_t isr     : 8;    // 31:24                    // ISR (CAN Interrupt Status/Ack Register, 400A 0003h): 
        };
    };

    union   // imr, rmc, btr0, btr1
    {
        struct {
            __IO dcan_imr_t imr     : 8;    // 7:0                      // IMR (CAN Interrupt Mask Register, 400A 0004h): 
                 uint32_t           : 24;   // 31:8      Reserved
        };
        struct {
                 uint32_t           : 8;    // 7:0       Reserved
            __I  uint32_t rmc       : 8;    // 15:8                     // RMC (CAN Receive Message Counter Register, 400A 0005h): 
                 uint32_t           : 16;   // 31:16     Reserved
        };
        struct{
                 uint32_t           : 16;   // 15:0      Reserved
            __IO dcan_btr0_t btr0   ;       // 23:16                    // BTR0 (CAN Bus Timing Register 0, 400A 0006h): 
                 uint32_t           : 8;    // 31:24     Reserved
        };
        struct{            
                 uint32_t           : 24;   // 23:0      Reserved
            __IO dcan_btr1_t btr1   ;       // 31:24                    // BTR1 (CAN Bus Timing Register 1, 400A 0007h): 
        };
    };

    // txbuf (CAN Transmit Buffer Register, 400A 0008h):
    __IO uint32_t txbuf;
   
    // rxbuf (CAN Receive Buffer Register, 400A 000Ch):
    __I  uint32_t rxbuf;
   
    // acr (CAN Acceptance Code Register, 400A 0010h):
    __IO uint32_t acr;    
 
    // amr (CAN Acceptance Mask Register, 400A 0014h):
    __IO uint32_t amr;
 
    union   // ecc, rxerr, txerr, alc
    {
        struct {
            __I  uint32_t ecc   : 8;    // 7:0                      // ECC (CAN Error Code Capture Register, 400A 0018h): 
                 uint32_t       : 24;   // 31:8      Reserved
        };
        struct {
                 uint32_t       : 8;    // 7:0       Reserved
            __I  uint32_t rxerr  : 8;    // 15:8                    // RXERR (CAN RX Error Counter Register, 400A 0019h): 
                 uint32_t       : 16;   // 31:16     Reserved
        };
        struct{
                 uint32_t       : 16;   // 15:0      Reserved
            __I  uint32_t txerr : 8;    // 23:16                    // TXERR (CAN TX Error Counter Register, 400A 001Ah): 
                 uint32_t       : 8;    // 31:24     Reserved
        };
        struct{            
                 uint32_t       : 24;   // 23:0      Reserved
            __I  uint32_t alc   : 8;    // 31:24                    // ALC (CAN Arbitration Lost Code Capture Register, 400A 001Bh): 
        };
    };
} dcan_t;

 
//typedef struct
//{
//    //  (CAN ISR_SR_CMR_MR Register, 400A 0000h):
//    union
//    {
//        __IO uint32_t w;
//        struct {
//            __IO uint32_t AFM   : 1;    // 0      Hardware acceptance filter scheme
//            __IO uint32_t LOM   : 1;    // 1      Listen only mode
//            __IO uint32_t RM    : 1;    // 2      Reset mode:
//                 uint32_t       : 5;    // 7:3    Reserved
//                 uint32_t       : 1;    // 8      Reserved
//            __IO uint32_t AT    : 1;    // 9      Abort transmission
//            __IO uint32_t TR    : 1;    // 10     Transmit request
//                 uint32_t       : 5;    // 15:11  Reserved
//            __I  uint32_t BS    : 1;    // 16     Bus Off Status
//            __I  uint32_t ES    : 1;    // 17     Error Status
//            __I  uint32_t TS    : 1;    // 18     Transmit Status
//            __I  uint32_t RS    : 1;    // 19     Receive Status
//                 uint32_t       : 1;    // 20     Reserved
//            __I  uint32_t TBS   : 1;    // 21     Transmit Buffer Status
//            __I  uint32_t DSO   : 1;    // 22     Data Overrun Status
//            __I  uint32_t RBS   : 1;    // 23     Receive Buffer Status
//            __IO uint32_t DOI   : 1;    // 24     Data Overflow Interrupt
//            __IO uint32_t BEI   : 1;    // 25     Bus Error Interrupt
//            __IO uint32_t TI    : 1;    // 26     Transmit Interrupt
//            __IO uint32_t RI    : 1;    // 27     Receive Interrupt
//            __IO uint32_t EPI   : 1;    // 28     Error Passive Interrupt
//            __IO uint32_t EWI   : 1;    // 29     Error Warning Interrupt
//            __IO uint32_t ALI   : 1;    // 30     Arbitration Lost Interrupt
//                 uint32_t       : 1;    // 31     Reserved
//        };
//    } ISR_SR_CMR_MR;
//
//    // (CAN BTR1_BTR0_RMC_IMR Register, 400A 0004h):
//
//    union
//    {
//        __IO uint32_t w;
//        struct {
//            __IO  uint32_t DOIM   : 1;    // 0       DOI Interrupt Mask
//            __IO  uint32_t BEIM   : 1;    // 1       BEI Interrupt Mask
//            __IO  uint32_t TIM    : 1;    // 2       TI Interrupt Mask
//            __IO  uint32_t RIM    : 1;    // 3       RI Interrupt Mask
//            __IO  uint32_t EPIM   : 1;    // 4       EPI Interrupt Mask
//            __IO  uint32_t EWIM   : 1;    // 5       EWI Interrupt Mask
//            __IO  uint32_t ALIM   : 1;    // 6       ALI Interrupt Mask
//                  uint32_t        : 1;    // 7
//            __I   uint32_t RMC    : 5;    // 12:8    Number of frames stored in the receive FIFO
//                  uint32_t        : 3;    // 15:13
//            __IO  uint32_t BRP    : 6;    // 21:16   Baud Rate Pre-scaler
//            __IO  uint32_t SJW    : 2;    // 23:22   Synchronization jump width
//            __IO  uint32_t TSEG1  : 4;    // 27:24   Number of clock cycles per Time Segment 1.
//            __IO  uint32_t TSEG2  : 3;    // 295:28  Number of clock cycles per Time Segment 2.
//            __IO  uint32_t SAM    : 1;    // 31      Number of bus level samples:
//        };
//    } BTR1_BTR0_RMC_IMR;
//
//    // TXBUF (CAN Transmit Buffer Register, 400A 0008h):
//    __IO uint32_t TXBUF;
//
//    // RXBUF (CAN Receive Buffer Register, 400A 000Ch):
//    __I  uint32_t RXBUF;
//
//    // ACR (CAN Acceptance Code Register, 400A 0010h):
//    __IO uint32_t ACR;
//
//    // AMR (CAN Acceptance Mask Register, 400A 0014h):
//    __IO uint32_t AMR;
//
//    // ALC_TXERR_RXERR_ECC (CAN Error Code Capture Register, 400A 0018h):
//    union
//    {
//        __I   uint32_t w;
//        struct {
//            __I   uint32_t BER            : 1;    // 0     Bit error occurred
//            __I   uint32_t STFER          : 1;    // 1     Stuff error occurred
//            __I   uint32_t CRCER          : 1;    // 2     CRC error occurred
//            __I   uint32_t FRMER          : 1;    // 3     Form error occurred
//            __I   uint32_t ACKER          : 1;    // 4     ACK error occurred
//            __I   uint32_t EDIR           : 1;    // 5     Direction of transfer while error occurred
//            __I   uint32_t TXWRN          : 1;    // 6     Set when CANTXERR ≥ 96
//            __I   uint32_t RXWRN          : 1;    // 7     Set when CANRXERR ≥ 96
//            __I   uint32_t RXERR          : 8;    // 15:8
//            __I   uint32_t TXERR          : 8;    // 23:16
//            __I   uint32_t ALC            : 8;    // 31:24
//        };
//    } ALC_TXERR_RXERR_ECC;
//} PAC55XX_CAN_TYPEDEF;

#endif  // PAC5XXX_CAN_H
