//=================================================================================
/// @file     pac5xxx_memory.h
/// @brief    CMSIS Cortex-M Header File for the PAC55XX Memory Controller
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
#ifndef PAC5XXX_MEMORY_H
#define PAC5XXX_MEMORY_H

#define FLASH_LOCK_ALLOW_WRITE_MEMCTL       0xD513B490          // Allow write to MEMCTL register
#define FLASH_LOCK_ALLOW_WRITE_ERASE_FLASH  0x43DF140A          // Allow write an erase operations to FLASH

#define FLASH_START_PAGE_ERASE              0x8C799CA7          // Allow memory controller to start a FLASH page erase opertion.
#define FLASH_ERASE_INFO_3                  0x1266FF45          // Allow erase info-3 flash pages                                                                // It will erase entire FLASH page based on page value of FLASHPAGE
#define FLASH_START_MASS_PAGE_ERASE         0x09EE76C9          // Start a Mass Erase of all flash memory pages
#define FLASH_START_MASS_PROG_INFO_ERASE    0x856E0E70          // Start a Mass Program and INFO2/INFO3 Erase 
#define FLASH_SWDFUSE_ACCESS                0x79B4F762          // Write this value to FLASHLOCK to allow writes to SWDFUSE
#define FLASH_SECEN_ACCESS                  0x1D855C1E          // Write this value to FLASHLOCK to allow writes to SECEN

#define SWDFUSE_ADDRESS                     (PAC55XX_INFO2_FLASH_BASE + 0x3C)
#define SECEN_ADDRESS                       (PAC55XX_INFO2_FLASH_BASE + 0x20)
#define SWD_DISABLE_PERMANENTLY             0xDEAFDEAF                          // Permanent SWD Access Disable

#define FLASH_NUM_PAGES                     128
#define FLASH_PAGE_SIZE_BYTES               1024

// MEMCTL MCLK MUX Select Enumeration Type
typedef enum {
  MEMCTL_MCLK_ROSCCLK   = 0,                  // Select MCLK = ROSCCLK
  MEMCTL_MCLK_HCLKDIV   = 1                   // Select MCLK = HCLKDIV
} MEMCTL_MCLK_TYPE;

//MEMCTL MCLK divider Enumeration Type
typedef enum {
    MEMCTL_MCLK_DIV1 = 0,                   // HCLK /1
    MEMCTL_MCLK_DIV2 = 1,                   // HCLK /2
    MEMCTL_MCLK_DIV3 = 2,                   // HCLK /3
    MEMCTL_MCLK_DIV4 = 3,                   // HCLK /4
    MEMCTL_MCLK_DIV5 = 4,                   // HCLK /5
    MEMCTL_MCLK_DIV6 = 5,                   // HCLK /6
    MEMCTL_MCLK_DIV7 = 6,                   // HCLK /7
    MEMCTL_MCLK_DIV8 = 7,                   // HCLK /8
    MEMCTL_MCLK_DIV9 = 8,                   // HCLK /9
    MEMCTL_MCLK_DIV10 = 9,                  // HCLK /10
    MEMCTL_MCLK_DIV11 = 10,                 // HCLK /11
    MEMCTL_MCLK_DIV12 = 11,                 // HCLK /12
    MEMCTL_MCLK_DIV13 = 12,                 // HCLK /13
    MEMCTL_MCLK_DIV14 = 13,                 // HCLK /14
    MEMCTL_MCLK_DIV15 = 14,                 // HCLK /15
    MEMCTL_MCLK_DIV16 = 15                  // HCLK /16
} MEMCTL_MCLK_DIV_TYPEDEF;

//MEMCTL Wait States Enumeration Type
typedef enum {
    MEMCTL_WSTATE0  = 0,                     // 0  wait states
    MEMCTL_WSTATE1  = 1,                     // 1  wait states
    MEMCTL_WSTATE2  = 2,                     // 2  wait states
    MEMCTL_WSTATE3  = 3,                     // 3  wait states
    MEMCTL_WSTATE4  = 4,                     // 4  wait states
    MEMCTL_WSTATE5  = 5,                     // 5  wait states
    MEMCTL_WSTATE6  = 6,                     // 6  wait states
    MEMCTL_WSTATE7  = 7,                     // 7  wait states
    MEMCTL_WSTATE8  = 8,                     // 8  wait states
    MEMCTL_WSTATE9  = 9,                     // 9  wait states
    MEMCTL_WSTATE10 = 10,                    // 10 wait states
    MEMCTL_WSTATE11 = 11,                    // 11 wait states
    MEMCTL_WSTATE12 = 12,                    // 12 wait states
    MEMCTL_WSTATE13 = 13,                    // 13 wait states
    MEMCTL_WSTATE14 = 14,                    // 14 wait states
    MEMCTL_WSTATE15 = 15                     // 15 wait states
} MEMCTL_FLASH_WSTATE_TYPEDEF;


typedef enum {
    MEMCTL_SEC_LEVEL0  = 0xFF,                 // Security Level 0
    MEMCTL_SEC_LEVEL1  = 0xFE,                 // Security Level 1
    MEMCTL_SEC_LEVEL2  = 0xFC,                 // Security Level 2
} MEMCTL_SECURITY_LEVEL_TYPEDEF;

typedef struct
{
    // MEMCTL ( Memory Controller Configuration Register, 400D 0000h)
    union {
        __IO uint32_t w;
        struct {
            __IO uint32_t WSTATE        : 4;     // 3:0        FLASH Read Wait States
            __IO uint32_t MCLKDIV       : 4;     // 7:4        MCLK Divider for FLASH controller
            __IO uint32_t WRITEWORDCNT  : 2;     // 9:8        Write State Machine 32-bit Word Count - Number of words written so far            
                 uint32_t               : 6;     // 15:10       Reserved
            __IO uint32_t SEIE          : 1;     // 16         Single Bit Detection Interrupt Enable (ECC)
            __IO uint32_t DEIE          : 1;     // 17         Dual Bit Detection Interrupt Enable (ECC)
            __IO uint32_t INVADDRIE     : 1;     // 18         Invalid Memory Access Interrupt Enable            
            __IO uint32_t STDBY         : 1;     // 19         FLASH standby Mode
            __IO uint32_t ECCDIS        : 1;     // 20         FLASH ECC Disable
            __IO uint32_t CACHEDIS      : 1;     // 21         FLASH Cache Disable
            __IO uint32_t MCLKSEL       : 1;     // 22
                 uint32_t               : 9;     // 31:23      Reserved
        };
    } MEMCTL;
    
    // MEMSTATUS ( Memory Controller Status Register, 400D 0004h)
    union {
        __IO uint32_t w;
        struct {
            __I  uint32_t WBUSY         : 1;     // 0          Write Busy
            __I  uint32_t EBUSY         : 1;     // 1          Erase Busy
                 uint32_t               : 6;     // 7:2
            __IO uint32_t WRITEWORDCNT  : 2;     // 9:8        Write State Machine 32-bit Word Count - Number of words written so far
                 uint32_t               : 6;     // 15:10
            __IO uint32_t SE            : 1;     // 16         Single-bit Detection Flag
            __IO uint32_t DE            : 1;     // 17         Double-bit Detection Flag
            __IO uint32_t INVADDR       : 1;     // 18         Invalid Address Fetch Flag
                 uint32_t               : 13;    // 31:19
        };
    } MEMSTATUS;
    
    // FLASHLOCK ( FLASH Lock Access Register , 400D 0008h)
    __IO uint32_t FLASHLOCK;
    
    // FLASHPAGE ( FLASH Page Register ,  400D 000Ch)
    union {
        __IO uint32_t w;
        struct {
            __IO uint32_t PAGE          : 7;     // 6:0          FLASH Page Selection
                 uint32_t               : 25;    // 31:7
        };
    } FLASHPAGE;

    // SWDUNLOCK ( SWD Unlock Register , 400D 0010h) 
    __O uint32_t SWDUNLOCK;

    // Reserved 400D 0014h ~400D 001Ch
    uint32_t RESERVED1[3];
    
    // FLASHPERASE ( FLASH Page Erase Register , 400D 0020h)
    __IO uint32_t FLASHERASE;
    
        // Reserved 400D 0024h ~400D 0FCh
    uint32_t RESERVED2[0x37];
    
    __I uint32_t CACHE1ADDR;
    __I uint32_t CACHE1DATA[4];
   
    __I uint32_t CACHE2ADDR;
    __I uint32_t CACHE2DATA[4];

    __I uint32_t CACHE3ADDR;
    __I uint32_t CACHE3DATA[4];

} PAC55XX_MEMCTL_TYPEDEF;

typedef struct
{
    __IO uint32_t RMASK[4];     // FLASH Lock Access Register , 0010 0800h
         uint32_t RESERVED1[4];
    __IO uint32_t WMASK[4];     // FLASH Page Erase Register , 0010 0820h
         uint32_t RESERVED2[4];
    __IO uint8_t IMASK;         // FLASH Page Erase Register , 0010 0840h
    __IO uint8_t SECLEVEL;         // FLASH Page Erase Register , 0010 0841h
} PAC55XX_INFO3_TYPEDEF;

#endif  // PAC5XXX_MEMORY_H
