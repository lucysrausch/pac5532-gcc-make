//=================================================================================
/// @file     pac5xxx_gptimers.h
/// @brief    CMSIS Cortex-M Header File for the PAC55XX General Purpose Timers
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
#ifndef PAC5XXX_GPTIMERS_H
#define PAC5XXX_GPTIMERS_H
//=================================== GPTimer (A, B) =====================================
// GPTimer Pre-scaler Enumeration Type
typedef enum {
    GPTCTL_PS_DIV1             = 0,                // GPTimer pre-scaler: /1
    GPTCTL_PS_DIV2             = 1,                // GPTimer pre-scaler: /2
    GPTCTL_PS_DIV4             = 2,                // GPTimer pre-scaler: /4
    GPTCTL_PS_DIV8             = 3,                // GPTimer pre-scaler: /8
    GPTCTL_PS_DIV16            = 4,                // GPTimer pre-scaler: /16
    GPTCTL_PS_DIV32            = 5,                // GPTimer pre-scaler: /32
    GPTCTL_PS_DIV64            = 6,                // GPTimer pre-scaler: /64
    GPTCTL_PS_DIV128           = 7,                // GPTimer pre-scaler: /128   
    GPTCTL_PS_DIV256           = 8,                // GPTimer pre-scaler: /256   
    GPTCTL_PS_DIV512           = 9,                // GPTimer pre-scaler: /512
    GPTCTL_PS_DIV1024          = 10,               // GPTimer pre-scaler: /1024
    GPTCTL_PS_DIV2018          = 11,               // GPTimer pre-scaler: /2018
    GPTCTL_PS_DIV4096          = 12,               // GPTimer pre-scaler: /4096
    GPTCTL_PS_DIV8192          = 13,               // GPTimer pre-scaler: /18192
    GPTCTL_PS_DIV16384         = 14,               // GPTimer pre-scaler: /16384
    GPTCTL_PS_DIV32768         = 15,               // GPTimer pre-scaler: /32768
} GPTCTL_PS_TYPE;

// PAC55XX_GPTimerX 
typedef struct
{
    // GPTXCTL (GPTimer Control, Offset: 0x0000)
    union {
         __IO uint32_t w;
        struct {
            __IO uint32_t EN                : 1;        // 0                Timer Enable
            __IO uint32_t IE                : 1;        // 1                Interrupt Enable
            __IO uint32_t IF                : 1;        // 2                Interrupt Flag
            __IO uint32_t DIV               : 4;        // 3:6              GPTimer Clock Divider
                 uint32_t                   : 1;        // 7
            __IO uint32_t CDV               : 24;       // 8:31             Count-down Value
        };
    } CTL;
    
    // GPTXCTR (GPTimer Counter, Offset: 0x0004)
    union{
        __IO uint32_t w;  
        struct{
                 uint32_t                   : 8;         // 0:7
            __IO uint32_t CDV               : 24;        // 8:31            Counter Value      
        };
    } CTR;
} PAC55XX_GPTTIMER_TYPEDEF;

#endif //PAC5XXX_GPTIMERS_H
