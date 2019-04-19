//=================================================================================
/// @file     pac5xxx_crc.h
/// @brief    CMSIS Cortex-M Header File for the PAC55XX CRC
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
#ifndef PAC5XXX_CRC_H
#define PAC5XXX_CRC_H

// CRC Polynomial Select Enumeration Type
typedef enum{
    CRC16_CCITT        = 0,
    CRC16_IBM          = 1,
    CRC8_DALLAS_MAXIM  = 2
} CRC_POLYSEL_TYPE;

// CRC Data Input Width Enumeration Type
typedef enum{
    CRC_DATA_WIDTH_32BITS       = 0,
    CRC_DATA_WIDTH_8BITS        = 1
} CRC_DATA_WIDTH_TYPE;

// CRC
typedef struct{
    
    // CRCCTL (CRC Control RW, 400D 1000h)
    union{
        __IO      uint32_t w;
        struct{
            __IO  uint32_t POLYSEL            : 2;            // 0:1                CRC Polynomial Select
            __IO  uint32_t DATAWIDTH          : 1;            // 2                  DATAIN input data width
            __IO  uint32_t OUTREF             : 1;            // 3                  Reflect DATAOUT output data from CRC engine
            __IO  uint32_t INREF              : 1;            // 4                  Reflect DATAIN input data to CRC engine
                  uint32_t                    : 27;           // 5:31
        };
    } CTL;
    
    // CRCDATAIN (CRC Data Input Value RW, 400D 1004h)
    __IO  uint32_t DATAIN;                                    

    
    // CRCSEED (CRC Seed Value RW, 400D 1008h)
    union{
        __IO      uint32_t w;
        struct{
            __IO  uint32_t CRCSEED            : 16;            // 0:15              CRC seed value
                  uint32_t                    : 16;            // 16:31
        };
    } SEED;
    
    // CRCDATAOUT (CRC Data Output Value RO, 400D 100Ch)
    union{
        __I       uint32_t w;
        struct{
            __I   uint32_t CRCOUT            : 16;            // 0:15               CRC data output value.
                  uint32_t                   : 16;            // 16:31
        };
    } OUT;
    
} PAC55XX_CRC_TYPEDEF;

#endif  // PAC5XXX_CRC_H
