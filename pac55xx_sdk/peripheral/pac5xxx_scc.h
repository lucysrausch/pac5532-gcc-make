//=================================================================================
/// @file     pac55xx_scc.h
/// @brief    CMSIS Cortex-M Header File for the PAC55XX System and Clock Controller
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

#ifndef PAC55XX_SCC_H
#define PAC55XX_SCC_H

// USART Mode Enumeration Type
typedef enum {
    USART_MODE_SSP      = 0,                //SSP mode
    USART_MODE_UART     = 1                 //UART mode
} USART_MODE_TYPE;

// CCSCTL Clock In MUX Select Enumeration Type
typedef enum {
  CCSCTL_CLKIN_ROSC     = 0,                // Select FRCLK = Ring Oscillator Clock
  CCSCTL_CLKIN_CLKREF   = 1,                // Select FRCLK = CLKREF
  CCSCTL_CLKIN_XTALCLK  = 2,                // Select FRCLK = Crystal Clock
  CCSCTL_CLKIN_EXTCLK   = 3                 // Select FRCLK = External Clock
} CCSCTL_CLKIN_TYPE;

// CCSCTL PLLCLK MUX Select Enumeration Type
typedef enum {
  CCSCTL_PLLCLK_CLKREF  = 0,                // Select PLLCLK = CLKREF
  CCSCTL_PLLCLK_XTALCLK = 1,                // Select PLLCLK = Crystal Clock
  CCSCTL_PLLCLK_EXTCLK  = 2                 // Select PLLCLK = External Clock
} CCSCTL_PLLCLK_TYPE;

// CCSCTL SCLK MUX Select Enumeration Type
typedef enum {
  CCSCTL_SCLK_FRCLK     = 0,                // Select SCLK = FRCLK
  CCSCTL_SCLK_PLLCLK    = 1                 // Select SCLK = PLLCLK
} CCSCTL_SCLK_TYPE;

// CCSCTL PCLK Divider Enumeration Type
typedef enum {
  CCSCTL_PCLKDIV_DIV1   = 0,               	// SCLK /1
  CCSCTL_PCLKDIV_DIV2   = 1,               	// SCLK /2
  CCSCTL_PCLKDIV_DIV3   = 2,               	// SCLK /3
  CCSCTL_PCLKDIV_DIV4   = 3,               	// SCLK /4
  CCSCTL_PCLKDIV_DIV5   = 4,              	// SCLK /5
  CCSCTL_PCLKDIV_DIV6   = 5,              	// SCLK /6
  CCSCTL_PCLKDIV_DIV7   = 6,              	// SCLK /7
  CCSCTL_PCLKDIV_DIV8   = 7            	    // SCLK /8
} CCSCTL_PCLKDIV_TYPE;

// CCSCTL ACLK Divider Enumeration Type
typedef enum {
  CCSCTL_ACLKDIV_DIV1   = 0,                // SCLK /1
  CCSCTL_ACLKDIV_DIV2   = 1,               	// SCLK /2
  CCSCTL_ACLKDIV_DIV3   = 2,               	// SCLK /3
  CCSCTL_ACLKDIV_DIV4   = 3,               	// SCLK /4
  CCSCTL_ACLKDIV_DIV5   = 4,              	// SCLK /5
  CCSCTL_ACLKDIV_DIV6   = 5,              	// SCLK /6
  CCSCTL_ACLKDIV_DIV7   = 6,              	// SCLK /7
  CCSCTL_ACLKDIV_DIV8   = 7             	// SCLK /8
} CCSCTL_ACLKDIV_TYPE;

// CCSCTL HCLK Divider Enumeration Type
typedef enum {
  CCSCTL_HCLKDIV_DIV1   = 0,               	// SCLK /1
  CCSCTL_HCLKDIV_DIV2   = 1,               	// SCLK /2
  CCSCTL_HCLKDIV_DIV3   = 2,               	// SCLK /3
  CCSCTL_HCLKDIV_DIV4   = 3,               	// SCLK /4
  CCSCTL_HCLKDIV_DIV5   = 4,              	// SCLK /5
  CCSCTL_HCLKDIV_DIV6   = 5,              	// SCLK /6
  CCSCTL_HCLKDIV_DIV7   = 6,              	// SCLK /7
  CCSCTL_HCLKDIV_DIV8   = 7            	    // SCLK /8
} CCSCTL_HCLKDIV_TYPE;

// CCSCTL CLKFAIL Enumeration Type
typedef enum {
  CCSCTL_CLKFAIL_FRCLK  = 0,                // Select FRCLK for clock failure detection
  CCSCTL_CLKFAIL_PLLCLK = 1                 // Select PLLCLK for clock failure detection
} CCSCTL_CLKFAIL_TYPE;

// GPIODS Drive Strength Enumeration Type
typedef enum {
  IODS_DS_6MA           = 0,                // Select Drive Strength 6mA
  IODS_DS_8MA           = 1,                // Select Drive Strength 8mA
  IODS_DS_11MA          = 2,                // Select Drive Strength 11mA
  IODS_DS_14MA          = 3,                // Select Drive Strength 14mA  
  IODS_DS_17MA          = 4,                // Select Drive Strength 17mA
  IODS_DS_20MA          = 5,                // Select Drive Strength 20mA
  IODS_DS_22MA          = 6,                // Select Drive Strength 22mA
  IODS_DS_25MA          = 7                 // Select Drive Strength 25mA   
} IODS_DS_TYPE;

typedef union
{
    __IO uint32_t w;
    struct {
        __IO uint32_t P0                : 3;    // 2:0      Pin 0 MUX Select
             uint32_t                   : 1;    // 3
        __IO uint32_t P1                : 3;    // 6:4      Pin 1 MUX Select
             uint32_t                   : 1;    // 7
        __IO uint32_t P2                : 3;    // 10:8     Pin 2 MUX Select
             uint32_t                   : 1;    // 11  
        __IO uint32_t P3                : 3;    // 14:12    Pin 3 MUX Select  
             uint32_t                   : 1;    // 15    
        __IO uint32_t P4                : 3;    // 18:16    Pin 4 MUX Select  
             uint32_t                   : 1;    // 19  
        __IO uint32_t P5                : 3;    // 22:20    Pin 5 MUX Select   
             uint32_t                   : 1;    // 23  
        __IO uint32_t P6                : 3;    // 26:24    Pin 6 MUX Select  
             uint32_t                   : 1;    // 27  
        __IO uint32_t P7                : 3;    // 30:28    Pin 7 MUX Select
             uint32_t                   : 1;    // 31              
    };
} IO_MUXSEL_TYPEDEF;

#ifndef IO_PINS_TYPEDEF_DEFINE
#define IO_PINS_TYPEDEF_DEFINE
//GPIO PINS register typedef
typedef union
{
    __IO uint32_t w;
    struct {
        __IO uint32_t P0                : 1;    // 0      Pin 0
        __IO uint32_t P1                : 1;    // 1      Pin 1
        __IO uint32_t P2                : 1;    // 2      Pin 2
        __IO uint32_t P3                : 1;    // 3      Pin 3 
        __IO uint32_t P4                : 1;    // 4      Pin 4 
        __IO uint32_t P5                : 1;    // 5      Pin 5  
        __IO uint32_t P6                : 1;    // 6      Pin 6
        __IO uint32_t P7                : 1;    // 7      Pin 7
             uint32_t                   : 24;   // 31:8              
    };
} IO_PINS_TYPEDEF;
#endif // IO_PINS_TYPEDEF_DEFINE

// GPIO Drive Strength/Schmitt Trigger
typedef union
{
    __IO uint32_t w;
    struct {
        __IO uint32_t P0DS              : 3;    // 2:0      Pin 0 Drive Strength
        __IO uint32_t P0ST              : 1;    // 3        Pin 0 Schmitt Trigger enabled
        __IO uint32_t P1DS              : 3;    // 6:4      Pin 1 Drive Strength
        __IO uint32_t P1ST              : 1;    // 7        Pin 1 Schmitt Trigger enabled
        __IO uint32_t P2DS              : 3;    // 10:8     Pin 2 Drive Strength
        __IO uint32_t P2ST              : 1;    // 11       Pin 2 Schmitt Trigger enabled
        __IO uint32_t P3DS              : 3;    // 14:12    Pin 3 Drive Strength
        __IO uint32_t P3ST              : 1;    // 15       Pin 3 Schmitt Trigger enabled   
        __IO uint32_t P4DS              : 3;    // 18:16    Pin 4 Drive Strength
        __IO uint32_t P4ST              : 1;    // 19       Pin 4 Schmitt Trigger enabled
        __IO uint32_t P5DS              : 3;    // 22:20    Pin 5 Drive Strength
        __IO uint32_t P5ST              : 1;    // 23       Pin 5 Schmitt Trigger enabled
        __IO uint32_t P6DS              : 3;    // 26:24    Pin 6 Drive Strength
        __IO uint32_t P6ST              : 1;    // 27       Pin 6 Schmitt Trigger enabled
        __IO uint32_t P7DS              : 3;    // 30:28    Pin 7 Drive Strength
        __IO uint32_t P7ST              : 1;    // 31       Pin 7 Schmitt Trigger enabled
    };
} IO_DS_TYPEDEF;

// SCC Peripheral
typedef struct
{
    // CCSCTL (CCS Configuration, 400D 0400h):     
    union
    {
        __IO uint32_t w;

       struct {
            __IO uint32_t FRCLKMUXSEL       : 2;    // 1:0      FRCLK MUX Select
            __IO uint32_t ROSCEN            : 1;    // 2        ROSC Enabled
            __IO uint32_t XTALEN            : 1;    // 3        Crystal Driver Enabled           

            __IO uint32_t SCLKMUXSEL        : 1;    // 4        SCLK MUX Select
            __IO uint32_t CLKFAILEN         : 1;    // 5        Clock Fail Enabled
            __IO uint32_t CLKFAILMUXSEL     : 1;    // 6        Clock Fail Mux Select
            __IO uint32_t CLKFAILIF         : 1;    // 7        Clock Fail Interrupt Flag

                 uint32_t                   : 3;    // 10:8
            __IO uint32_t SWPOR             : 1;    // 11       Software Power-On-Reset (self clearing)

            __IO uint32_t PCLKEN            : 1;    // 12       PCLK enable           
            __IO uint32_t ACLKEN            : 1;    // 13       ACLK enable            
            __IO uint32_t ADCCLKEN          : 1;    // 14       ADCCLK enable            
            __IO uint32_t STCLKSLPEN        : 1;    // 15
           
            __IO uint32_t PCLKDIV           : 3;    // 18:16    PCLK Divider    
                 uint32_t                   : 1;    // 19
           
            __IO uint32_t ACLKDIV           : 3;    // 22:20    ACLK Divider
                 uint32_t                   : 1;    // 23
           
            __IO uint32_t HCLKDIV           : 3;    // 26:24    HCLK Divider
                 uint32_t                   : 1;    // 27

            __IO uint32_t USAMODE           : 1;    // 28       USART A Mode
            __IO uint32_t USBMODE           : 1;    // 29       USART B Mode
            __IO uint32_t USCMODE           : 1;    // 30       USART C Mode
            __IO uint32_t USDMODE           : 1;    // 31       USART D Mode
        };    
    } CCSCTL;
      
    // CCSPLLCTL (CCS PLL Configuration, 400D 0404h)
    union
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t PLLEN             : 1;    // 0        PLL Enabled
            __IO uint32_t PLLBP             : 1;    // 1        PLL Bypass
            __IO uint32_t PLLOUTDIV         : 2;    // 3:2      PLL Output Divider               
            __IO uint32_t PLLINDIV          : 4;    // 7:4      PLL Input Divider
            __IO uint32_t PLLFBDIV          : 14;   // 21:8     PLL Feedback Divider
                 uint32_t                   : 2;    // 23:22            
            __I  uint32_t PLLLOCK           : 1;    // 24       PLL Lock Status
                 uint32_t                   : 7;    // 31:25
        };
    } CCSPLLCTL;  

    // CCSROSCTRIM (CCS ROSC Trim Configuration, 400D 0408h)
     union
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t TRIM              : 7;    // 6:0      ROSC Trim Value
                 uint32_t                   : 25;   // 31:7
        };
    } CCSROSCTRIM;   
  
    // PAMUXSEL (PA Peripheral MUX Select, 400D 040Ch)
    IO_MUXSEL_TYPEDEF PAMUXSEL;
    
    // PBMUXSEL (PB Peripheral MUX Select, 400D 0410h)
    IO_MUXSEL_TYPEDEF PBMUXSEL;
    
    // PCMUXSEL (PC Peripheral MUX Select, 400D 0414h)
    IO_MUXSEL_TYPEDEF PCMUXSEL;
    
    // PDMUXSEL (PD Peripheral MUX Select, 400D 0418h)
    IO_MUXSEL_TYPEDEF PDMUXSEL;
    
    // PEMUXSEL (PE Peripheral MUX Select, 400D 041Ch)
    IO_MUXSEL_TYPEDEF PEMUXSEL;
    
    // PFMUXSEL (PF Peripheral MUX Select, 400D 0420h)
    IO_MUXSEL_TYPEDEF PFMUXSEL;
    
    // PGMUXSEL (PG Peripheral MUX Select, 400D 0424h)
    IO_MUXSEL_TYPEDEF PGMUXSEL;
    
    

    // PAPUEN (PA Pull-up Enable, 400D 0428h)
    IO_PINS_TYPEDEF PAPUEN;  
       
    // PBPUEN (PB Pull-up Enable, 400D 042Ch)
    IO_PINS_TYPEDEF PBPUEN; 
  
    // PCPUEN (PC Pull-up Enable, 400D 0430h)
    IO_PINS_TYPEDEF PCPUEN; 
   
    // PDPUEN (PD Pull-up Enable, 400D 0434h)
    IO_PINS_TYPEDEF PDPUEN; 
        
    // PEPUEN (PE Pull-up Enable, 400D 0438h)
    IO_PINS_TYPEDEF PEPUEN; 
       
    // PFPUEN (PF Pull-up Enable, 400D 043Ch)
    IO_PINS_TYPEDEF PFPUEN; 
      
    // PGPUEN (PG Pull-up Enable, 400D 0440h)
    IO_PINS_TYPEDEF PGPUEN; 
    
    

    // PAPDEN (PA Pull-Down Enable, 400D 0444h)
    IO_PINS_TYPEDEF PAPDEN;
    
    // PBPDEN (PB Pull-Down Enable, 400D 0448h)
    IO_PINS_TYPEDEF PBPDEN;
    
    // PCPDEN (PC Pull-Down Enable, 400D 044Ch)
    IO_PINS_TYPEDEF PCPDEN;
   
    // PDPDEN (PD Pull-Down Enable, 400D 0450h)
    IO_PINS_TYPEDEF PDPDEN;
       
    // PEPDEN (PE Pull-Down Enable, 400D 0454h)
    IO_PINS_TYPEDEF PEPDEN;

    // PFPDEN (PF Pull-Down Enable, 400D 0458h)
    IO_PINS_TYPEDEF PFPDEN;
   
    // PGPDEN (PG Pull-Down Enable, 400D 045Ch)
    IO_PINS_TYPEDEF PGPDEN;
    
    
  
    // PADS (PA Drive Strength/Schmitt Trigger, 400D 0460h)
    IO_DS_TYPEDEF PADS;
    
    // PBDS (PB Drive Strength/Schmitt Trigger, 400D 0464h)
    IO_DS_TYPEDEF PBDS;
   
    // PCDS (PC Drive Strength/Schmitt Trigger, 400D 0468h)
    IO_DS_TYPEDEF PCDS;
    
    // PDDS (PD Drive Strength/Schmitt Trigger, 400D 046Ch)
    IO_DS_TYPEDEF PDDS;
  
    // PEDS (PE Drive Strength/Schmitt Trigger, 400D 0470h)
    IO_DS_TYPEDEF PEDS;
  
    // PFDS (PF Drive Strength/Schmitt Trigger, 400D 0474h)
    IO_DS_TYPEDEF PFDS;
 
    // PGDS (PG Drive Strength/Schmitt Trigger, 400D 0478h)
    IO_DS_TYPEDEF PGDS;
     
} PAC55XX_SCC_TYPEDEF;

#endif  // PAC55XX_SCC_H
