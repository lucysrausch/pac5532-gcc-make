//=================================================================================
/// @file     pac5xxx_wwdt.h
/// @brief    CMSIS Cortex-M Header File for the PAC55XX Windowed Watch Dog Timer
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

#ifndef PAC5XXX_WWDT_H
#define PAC5XXX_WWDT_H

// WWDTCTL Clock Select Enumeration Type
typedef enum {
    WWDTCTL_CLKSEL_FRCLK   =    0,
    WWDTCTL_CLKSEL_ROSCCLK =    1
} WWDTCTL_CLKSEL_TYPE;

// WWDT Input Clock Divider Enumeration Type
typedef enum {
    WWDT_CLKDIV_DIV1     =  0, // WWDTCTL.CLKSEL / 1
    WWDT_CLKDIV_DIV2     =  1, // WWDTCTL.CLKSEL / 2
    WWDT_CLKDIV_DIV4     =  2, // WWDTCTL.CLKSEL / 4
    WWDT_CLKDIV_DIV8     =  3, // WWDTCTL.CLKSEL / 8
    WWDT_CLKDIV_DIV16    =  4, // WWDTCTL.CLKSEL / 16
    WWDT_CLKDIV_DIV32    =  5, // WWDTCTL.CLKSEL / 32
    WWDT_CLKDIV_DIV64    =  6, // WWDTCTL.CLKSEL / 64
    WWDT_CLKDIV_DIV128   =  7, // WWDTCTL.CLKSEL / 128
    WWDT_CLKDIV_DIV256   =  8, // WWDTCTL.CLKSEL / 256
    WWDT_CLKDIV_DIV512   =  9, // WWDTCTL.CLKSEL / 512
    WWDT_CLKDIV_DIV1024  = 10, // WWDTCTL.CLKSEL / 1024
    WWDT_CLKDIV_DIV2048  = 11, // WWDTCTL.CLKSEL / 2048
    WWDT_CLKDIV_DIV4096  = 12, // WWDTCTL.CLKSEL / 4096
    WWDT_CLKDIV_DIV8192  = 13, // WWDTCTL.CLKSEL / 8192
    WWDT_CLKDIV_DIV16384 = 14, // WWDTCTL.CLKSEL / 16384
    WWDT_CLKDIV_DIV32768 = 15  // WWDTCTL.CLKSEL / 32768
} WWDT_CLKDIV_TYPE;

// WWDT Interrupt Flag Enumeration Type
typedef enum {
    WWDT_INTF_NO_FLAG =  0,                  // no flags
    WWDT_INTF_FLAG    =  1                   // flags
} WWDT_INTF_TYPE;

#define WWDTLOCK_REGS_WRITE_AVALABLE        0x55AA6699      // All registers in the WWDT available for writing
#define WWDTLOCK_REGS_READ_ONLY             0x55AA6698      // All registers in the WWDT are read-only

typedef struct
{
    // WWDTCTL ( WWDT Controller Register, 400D 0800h)
    union 
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t EN        : 1;        // 0          WWDT Enable
            __IO uint32_t INTEN     : 1;        // 1          WWDT Interrupt Enable
            __IO uint32_t RSTEN     : 1;        // 2          WWDT Reset Output Enable
            __IO uint32_t CLKSEL    : 1;        // 3          WWDT Input Clock Selection
            __IO uint32_t CLKDIV    : 4;        // 7:5        WWDT Input Clock Divider
                 uint32_t           : 24;       // 31:8
        };
    } WWDTCTL;
    
    // WWDTCDCTL (WWDT Count-Down Control Register, 400D 0804h)
    union 
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t CDV       : 16;        // 15:0   WWDT Count Down Value
            __IO uint32_t WINDOW    : 16;        // 31:16  WWDT Window – Can clear WWDT when CTR is below this value
        };
    } WWDTCDCTL;

    
    // WWDTCTR (WWDT Counter Register, 400D 0808h)
    __I  uint32_t WWDTCTR;
    
    // WWDTFLAG (WWDT Flag Register, 400D 080Ch)
    union 
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t IF        : 1;        // 0        WWDT Interrupt Flag
            __IO uint32_t RSTF      : 1;        // 1        WWDT Reset Flag
                 uint32_t           : 30;       // 31:2     
        };
    } WWDTFLAG;
    
    // WWDTCLEAR (WWDT Clear Register, 400D 0810h)
     __IO  uint32_t WWDTCLEAR;
    
    //  WWDTLOCK (WWDT Lock Register, 400D 0814h)
    __IO uint32_t WWDTLOCK;
    
} PAC55XX_WWDT_TYPEDEF;

#endif // PAC5XXX_WWDT_H
