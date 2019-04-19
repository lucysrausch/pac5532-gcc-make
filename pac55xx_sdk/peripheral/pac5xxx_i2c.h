//=================================================================================
/// @file     pac5xxx_i2c.h
/// @brief    CMSIS Cortex-M Header File for the PAC55XX I2C Controller
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
#ifndef PAC5XXX_I2C_H
#define PAC5XXX_I2C_H

// I2C Enable Enumeration Type
typedef enum{
    I2C_DISABLE = 0,
    I2C_ENABLE  = 1
}I2C_EN_TYPE;

#define I2C_SOFT_RESET  0x07

// I2C Slave Address 
typedef union{
    __IO        uint32_t w;
    struct{
        __IO    uint32_t GC               : 1;             // 0              General Call Enable
        __IO    uint32_t ADDRESS          : 7;             // 7:1            The I2C device address for slave mode.
                uint32_t                  : 24;            // 31:8              
    };
}I2CADR_TYPEDEF;

// I2C Slave Address Mask
typedef union{
    __IO        uint32_t w;
    struct{
                uint32_t                   : 1;            // 0             
        __IO    uint32_t MASK              : 7;            // 7:1           Slave address mask bits
                uint32_t                   : 24;           // 31:7 
    };
}I2CADR_MASK_TYPEDEF;

// I2C 
typedef struct{
    
    // I2CCONSET (I2C Control Set Register, 4001 0000h)
    union{
        __IO     uint32_t w;  
        struct{
            __I  uint32_t ADRF            : 1;             // 0             I2C Slave Address Flag
            __I  uint32_t XADRF           : 1;             // 1             I2C Extended Slave Address Flag (10-bit addressing)
            __IO uint32_t AA              : 1;             // 2             Assert Acknowledge flag
            __I  uint32_t SI              : 1;             // 3             I2C Interrupt flag
            __IO uint32_t STO             : 1;             // 4             STOP flag
            __IO uint32_t STA             : 1;             // 5             START flag
            __IO uint32_t I2CEN           : 1;             // 6             I2C Enabled
            __IO uint32_t I2CIE           : 1;             // 7             Interrupt Enabled
            __I  uint32_t GCF             : 1;             // 8             General Call Flag Address Flag
                 uint32_t                 : 23;            // 31:9
        };
    }I2CCONSET;
    
    // I2CCONCLR (I2C Control Clear Register, 4001 0004h)
    union{
        __IO     uint32_t w;
        struct{
                 uint32_t                : 2;              // 1:0
            __IO uint32_t AAC            : 1;              // 2             Assert Acknowledge Clear
            __IO uint32_t SIC            : 1;              // 3             I2C Interrupt Clear
                 uint32_t                : 1;              // 4             
            __IO uint32_t STAC           : 1;              // 5             START Flag Clear
            __IO uint32_t I2CENC         : 1;              // 6             I2C Interface Disable
            __IO uint32_t I2CIEC         : 1;              // 7             I2C Interrupt Disable
                 uint32_t                : 24;             // 31:8
        };
    }I2CCONCLR;
    
    // I2CSTAT (I2C Status Register, 4001 0008h)
    union{
        __IO     uint32_t w;
        struct{
                 uint32_t                : 3;              // 2:0
            __I  uint32_t STATUS         : 5;              // 7:3           Status code for I2C engine.
                 uint32_t                : 24;             // 31:8
        };
    }I2CSTAT;
    
    // I2CDAT (I2C Data Register, 4001 000Ch)
    union{
        __IO     uint32_t w;
        struct{
            __IO uint32_t DATA          : 8;            // 7:0             Data values received or to be transmit
                 uint32_t               : 24;           // 31:8
        };
    }I2CDAT;
    
    // I2CCLK (I2C Clock Control Register, 4001 0010h)
    union{
        __IO     uint32_t w;
        struct{
            __IO uint32_t N            : 4;            // 3:0              FSCL = PCLK / (2^M x (N+1) x 10)
            __IO uint32_t M            : 3;            // 6:4              FSAMP = PCLK / 2^M
                 uint32_t              : 25;           // 31:7 
        };
    }I2CCLK;
    
    // I2CADR0 (I2C Slave Address Register 0, 4001 0014h)
    I2CADR_TYPEDEF      I2CADR0;
    
    // I2CADRM0 (I2C Slave Address Mask Register 0, 4001 0018h)
    I2CADR_MASK_TYPEDEF I2CADRM0;
    
    // I2CXADR0 (I2C Extended Slave Address Register 0, 4001 001Ch)
    union{
        __IO     uint32_t w;
        struct{
                 uint32_t              : 1;             // 0                 
            __IO uint32_t ADDRESS      : 10;            // 10:1              The I2C device address for slave mode used for extended addressing.
                 uint32_t              : 21;            // 31:11
        };
    }I2CXADR0;
    
    // I2CXADRM0 (I2C Extended Slave Address Mask Register 0, 4001 0020h)
    union{
        __IO     uint32_t w;
        struct{
                 uint32_t              : 1;             // 0
            __IO uint32_t MASK         : 7;             // 7:1               Slave address mask bits
                 uint32_t              : 24;            // 31:8
        };
    }I2CXADRM0;
    
    // I2CRST (I2C Software Reset Register, 4001 0024h)
    union{
        __IO     uint32_t w;  
        struct{
            __IO uint32_t RST          : 8;            // 7:0                 I2C Software Reset
                 uint32_t              : 24;           // 31:8                
        };
    }I2CRST;
    
    // I2CADR1 (I2C Slave Address Register 1, 4001 0028h)
    I2CADR_TYPEDEF               I2CADR1;
    
    // I2CADRM1 (I2C Slave Address Mask Register 1, 4001 002Ch)
    I2CADR_MASK_TYPEDEF          I2CADRM1;
    
    // I2CADR2 (I2C Slave Address Register 2, 4001 0030h)
    I2CADR_TYPEDEF               I2CADR2;
    
    // I2CADRM2 (I2C Slave Address Mask Register 2, 4001 0034h)
    I2CADR_MASK_TYPEDEF          I2CADRM2;
    
    // I2CADR3 (I2C Slave Address Register 3, 4001 0038h)
    I2CADR_TYPEDEF               I2CADR3;
    
    // I2CADRM3 (I2C Slave Address Mask Register 3, 4001 003Ch)
    I2CADR_MASK_TYPEDEF          I2CADRM3;
    
} PAC55XX_I2C_TYPEDEF;


#endif  // PAC5XXX_I2C_H
