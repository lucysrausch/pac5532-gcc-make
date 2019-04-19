//=================================================================================
/// @file     pac5xxx_io.h
/// @brief    CMSIS Cortex-M Header File for the PAC55XX GPIO Controller
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

#ifndef PAC5XXX_GPIO_H
#define PAC5XXX_GPIO_H

// GPIO Mode Configuration Enumeration Type
typedef enum {
  IO_ANAOG_INPUT               = 0,                 // Analog Input for ADC Pins only - Reserved for the other pins                            
  IO_PUSH_PULL_OUTPUT          = 1,                 // Push-Pull Digital Output 
  IO_OPEN_DRAIN_OUTPUT         = 2,                 // Open-Drain Digital Output                          
  IO_HIGH_IMPEDENCE_INPUT      = 3                  // High-Impedance Digital Input 
} IO_MODE_TYPE;    

// GPIOMODE register typedef
typedef union
{
    __IO uint32_t w;
    struct {
        __IO uint32_t P0            : 2;            //  1:0     P0 (bit 0)
        __IO uint32_t P1            : 2;            //  3:2     P1 (bit 1)
        __IO uint32_t P2            : 2;            //  5:4     P2 (bit 2)
        __IO uint32_t P3            : 2;            //  7:6     P3 (bit 3)
        __IO uint32_t P4            : 2;            //  9:8     P4 (bit 4)
        __IO uint32_t P5            : 2;            //  11:10   P5 (bit 5)
        __IO uint32_t P6            : 2;            //  13:12   P6 (bit 6)
        __IO uint32_t P7            : 2;            //  15:14   P7 (bit 7)
             uint32_t               : 16;
    };
} IO_MODE_TYPEDEF;

#ifndef IO_PINS_TYPEDEF_DEFINE
#define IO_PINS_TYPEDEF_DEFINE
//GPIO PINS register typedef
typedef union
{
    __IO uint32_t w;
    struct {
        __IO uint32_t P0            : 1;            // 0
        __IO uint32_t P1            : 1;            // 1
        __IO uint32_t P2            : 1;            // 2
        __IO uint32_t P3            : 1;            // 3
        __IO uint32_t P4            : 1;            // 4
        __IO uint32_t P5            : 1;            // 5
        __IO uint32_t P6            : 1;            // 6
        __IO uint32_t P7            : 1;            // 7
             uint32_t               : 24;           // 31:8
    };
} IO_PINS_TYPEDEF;
#endif // IO_PINS_TYPEDEF_DEFINE

typedef struct
{
    IO_MODE_TYPEDEF MODE;                           // Offset: 0x0000    GPIO Mode Configuration Register  
    IO_PINS_TYPEDEF OUTMASK;                        // Offset: 0x0004    GPIO Data Output Write Mask Register
    IO_PINS_TYPEDEF OUT;                            // Offset: 0x0008    GPIO Data Output Value Register
    IO_PINS_TYPEDEF IN;                             // Offset: 0x000C    GPIO Data Input Value Register
    IO_PINS_TYPEDEF INTEN;                          // Offset: 0x0010    GPIO Interrupt Enable Register
    IO_PINS_TYPEDEF INTFLAGRAW;                     // Offset: 0x0014    GPIO Interrupt Flag Raw Status Register
    IO_PINS_TYPEDEF INTFLAGMASKED;                  // Offset: 0x0018    GPIO Interrupt Flag Masked Status Register
    IO_PINS_TYPEDEF INTCLEAR;                       // Offset: 0x001C    GPIO Interrupt Clear Register
    IO_PINS_TYPEDEF INTTYPE;                        // Offset: 0x0020    GPIO Interrupt Type Register
    IO_PINS_TYPEDEF INTCFG;                         // Offset: 0x0024    GPIO Interrupt Configuration Register
    IO_PINS_TYPEDEF INTEDGEBOTH;                    // Offset: 0x0028    GPIO Interrupt Edge Both Register
    IO_PINS_TYPEDEF DEBOUNCE;                       // Offset: 0x002C    GPIO De-bounce Register
    IO_PINS_TYPEDEF DOSET;                          // Offset: 0x0030    GPIO Data Output Set Register
    IO_PINS_TYPEDEF DOCLEAR;                        // Offset: 0x0034    GPIO Data Output Clear Register
} PAC55XX_GPIO_TYPEDEF;

#endif  // PAC5XXX_GPIO_H
