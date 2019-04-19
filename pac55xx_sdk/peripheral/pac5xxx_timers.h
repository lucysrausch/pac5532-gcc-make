//=================================================================================
/// @file     pac5xxx_timers.h
/// @brief    CMSIS Cortex-M Header File for the PAC55XX Timers
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
#ifndef PAC5XXX_TIMERS_H
#define PAC5XXX_TIMERS_H
//=============================== Timer (A, B, C, D) ===================================

// TXCTRL Clock Input Enumeration Type 
typedef enum {
    TXCTL_CS_PCLK               = 0,                // Timer clock source: PCLK
    TXCTL_CS_ACLK               = 1                 // Timer clock source: ACLK
} TXCTRL_CLKIN_TYPE, TXCTRL_CLKIN_Type;

// DTGCLK Clock Input Enumeration Type 
typedef enum {
    TXCTL_DTGCLK_PRE            = 0,                // DTG clock source: PRE-divider
    TXCTL_DTGCLK_POST           = 1                 // DTG clock source: POST-divider
} TXCTRL_DTGCLK_TYPE;


// Timer Pre-scaler Enumeration Type
typedef enum {
    TXCTL_PS_DIV1               = 0,                // Timer pre-scaler: /1
    TXCTL_PS_DIV2               = 1,                // Timer pre-scaler: /2
    TXCTL_PS_DIV4               = 2,                // Timer pre-scaler: /4
    TXCTL_PS_DIV8               = 3,                // Timer pre-scaler: /8
    TXCTL_PS_DIV16              = 4,                // Timer pre-scaler: /16
    TXCTL_PS_DIV32              = 5,                // Timer pre-scaler: /32
    TXCTL_PS_DIV64              = 6,                // Timer pre-scaler: /64
    TXCTL_PS_DIV128             = 7                 // Timer pre-scaler: /128       
} TXCTL_PS_TYPE, TXCTRL_PS_Type;

// TXCTRL Timer Period Latch Mode Enumeration Type
typedef enum {
    TXCTL_PRDLATCH_TXCTR_0      = 0,                // Latch TXPRD when TXCTR = 0
    TXCTL_PRDLATCH_TXCTR_TXPRD  = 1,                // Latch TXPRD when TXCTR = TXPRD
    TXCTL_PRDLATCH_TXCTR_IM     = 2                 // Latch TXPRD immediately upon register write
} TXCTL_PRDLATCH_TYPE;

// TXCTRL Timer Mode Enumeration Type
typedef enum {
    TXCTL_MODE_DISABLED         = 0,                // Timer mode: disabled
    TXCTL_MODE_UP               = 1,                // Timer mode: up
    TXCTL_MODE_UPDOWN           = 2,                // Timer mode: up/down
    TXCTL_MODE_ASYMMETRIC       = 3                 // Timer mode: asymmetric mode
} TXCTL_MODE_TYPE;

typedef enum {
    TxCTL_MODE_DISABLED         = 0,                // Timer mode: disabled
    TxCTL_MODE_UP               = 1,                // Timer mode: up
    TxCTL_MODE_UPDOWN           = 2,                // Timer mode: up/down
    TxCTL_MODE_ASYMMETRIC       = 3                 // Timer mode: asymmetric mode
}TXCTRL_MODE_Type;

// Timer CC Mode Enumeration Type 
typedef enum {
    TXCCTL_CCMODE_COMPARE                = 0,                // Timer CC Mode Compare
    TXCCTL_CCMODE_CAPTURE                = 1                 // Timer CC Mode Capture
} TXCCTL_CCMODE_TYPE;

// TXCCTL CC Interrupt Skip Counter Enumeration Type
typedef enum {
    TXCCTL_CCINT_DONT_SKIP            = 0,                //  Don’t skip CCR matches before interrupt
    TXCCTL_CCINT_SKIP_1               = 1,                //  Skip 1 CCR match before interrupt
    TXCCTL_CCINT_SKIP_2               = 2,                //  Skip 2 CCR match before interrupt
    TXCCTL_CCINT_SKIP_3               = 3,                //  Skip 3 CCR match before interrupt
    TXCCTL_CCINT_SKIP_4               = 4,                //  Skip 4 CCR match before interrupt
    TXCCTL_CCINT_SKIP_5               = 5,                //  Skip 5 CCR match before interrupt
    TXCCTL_CCINT_SKIP_6               = 6,                //  Skip 6 CCR match before interrupt
    TXCCTL_CCINT_SKIP_7               = 7,                //  Skip 7 CCR match before interrupt
    TXCCTL_CCINT_SKIP_8               = 8,                //  Skip 8 CCR match before interrupt
    TXCCTL_CCINT_SKIP_9               = 9,                //  Skip 9 CCR match before interrupt
    TXCCTL_CCINT_SKIP_10              = 10,               //  Skip 10 CCR match before interrupt
    TXCCTL_CCINT_SKIP_11              = 11,               //  Skip 11 CCR match before interrupt
    TXCCTL_CCINT_SKIP_12              = 12,               //  Skip 12 CCR match before interrupt
    TXCCTL_CCINT_SKIP_13              = 13,               //  Skip 13 CCR match before interrupt
    TXCCTL_CCINT_SKIP_14              = 14,               //  Skip 14 CCR match before interrupt
    TXCCTL_CCINT_SKIP_15              = 15                //  Skip 15 CCR match before interrupt
} TXCCTL_CCINT_SKIP_TYPE;

// TXCTRL Capture And Compare Mode Enumeration Type
typedef enum {
    TXCCTL_CCLATCH_CAPTURE_RISING_EDGE  = 0,                // Latch TACTR into TXCCTR.CTR on rising edge
    TXCCTL_CCLATCH_CAPTURE_FALLING_EDGE = 1,                // Latch TACTR into TXCCTR.CTR on falling edge
    TXCCTL_CCLATCH_CAPTURE_BOTH_EDGES   = 2,                // Latch TACTR into TXCCTR.CTR on both edges
    TXCCTL_CCLATCH_CAPTURE_PERIOD_DUTY  = 3                 // Latch TACTR into TXCCTR.CAP1 and TACCTR0.CAP2 according to period/duty calculation
} TXCCTL_CCLATCH_CAPTURE_TYPE;

// TXCTRL Timer Period Latch Mode Enumeration Type
typedef enum {
    TXCCTL_CCLATCH_COMPARE_TXCTR_0      = 0,                // Latch TXCCTRL when TXCTR = 0
    TXCCTL_CCLATCH_COMPARE_TXCTR_TXPRD  = 1,                // Latch TXCCTRL when TXCTR = TXPRD
    TXCCTL_CCLATCH_COMPARE_TXCTR_IM     = 2                 // Latch TXCCTRL immediately upon register write
} TXCCTL_CCLATCH_COMPARE_TYPE;


// TXCTRL INPUT SIGNAL DETECT Enumeration Type
typedef enum {
    TXCCTL_CCINT_RISING_EDGE    = 0,                // Input is rising edge
    TXCCTL_CCINT_FALLING_EDGE   = 1,                // Input is falling edge
    TXCCTL_CCINT_BOTH_EDGES     = 2                 // Input is both edges
} TXCCTL_CCINT_EDGE_TYPE;

typedef union {
     __IO    uint32_t w;
    struct {
        __IO uint32_t MODE              : 2;        // 0:1              Timer Mode
        __IO uint32_t PRDLATCH          : 2;        // 2:3              Timer Period Latch Mode
        __IO uint32_t SSYNC             : 1;        // 4                Timer Slave Synchronization Enable
        __IO uint32_t SINGLE            : 1;        // 5                Single Shot Timer
        __IO uint32_t CLKDIV            : 3;        // 6:8              Timer Input Clock Divider
        __IO uint32_t CLKSRC            : 1;        // 9                Timer Clock Source
        __IO uint32_t DTGCLK            : 1;        // 10               DTG Clock Source
        __IO uint32_t LATCH             : 1;        // 11               When written to 1b, this will latch the TXPRD and all TXCCTRn registers on the same clock cycle
        __IO uint32_t CLR	            : 1;        // 12               
        __IO uint32_t BASEIE            : 1;        // 13               Timer Base Interrupt Enable
             uint32_t                   : 18;       // 14:31
    };
} TIMER_CTL_TYPEDEF;

// Timer CCTL Control
typedef union{
    __IO     uint32_t w; 
    // Timer CCTL
    struct {
        __IO uint32_t CCMODE               : 1;        // 0                Select mode: Compare (=0) or Capture (=1)
        __IO uint32_t CCINTEN              : 1;        // 1                CCR interrupt enable
        __IO uint32_t CCINTEDGE            : 2;        // 2:3              Input signal detects
        __IO uint32_t CCOUTINV             : 1;        // 4                Invert CCR output
        __IO uint32_t CCLATCH              : 2;        // 5:6              CCR register latch mode
        __IO uint32_t CCFORCE              : 1;        // 7                Write this bit to a 1b to force this compare event
        __IO uint32_t CCINTSKIP            : 4;        // 8:11             CC Interrupt Skip Counter
             uint32_t                      : 20;       // 12:31
    };
} CCTL_TYPEDEF;

// Timer CCTR Control
typedef union{
    __IO     uint32_t w;
    
    // Timer CCR Counter   
    struct {
        
        // If TACCTL1.CCLATCH = 11b (period/duty mode) and
        // TACCTL1.CCMODE = 1b (capture mode), this is the capture
        // value used for this calculation (number of ticks in period).
        __IO uint32_t CAP1                   : 16;       // 0:15

        // If TACCTL1.CCLATCH = 11b (period/duty mode) and
        // TACCTL1.CCMODE = 1b (capture mode), this is the 2nd
        // capture value used for this calculation (number of ticks in duty cycle)
        __IO uint32_t CAP2                   : 16;       // 16:31
    };

    struct {
        
        // If TACCTL1.CCLATCH != 11b (period/duty mode) and
        // TACCTL1.CCMODE = 0b (compare mode), this is the
        // compare value used for this CCR.
        // If TACCTL1.CCLATCH != 11b (period/duty mode) and
        // TACCTL1.CCMODE = 1b (capture mode), this is the capture
        // value for this CCR.
        __IO uint32_t CTR                   : 16;       // 0:15 
        
        // If TACCTL1.CCLATCH != 11b (period/duty mode) and
        // TACCTL1.CCMODE = 1b (capture mode), this the delay
        // count to use before compare events that can be used for
        // PWM output of phase shifted topologies
        __IO uint32_t DELAY                 : 16;       // 16:31
    };
} CCTR_TYPEDEF;


// Timer Dead-Time Generator Control 
typedef union{
    __IO     uint32_t w;  
    // Timer Dead-Time Generator Control 
    struct {
        __IO uint32_t RED                   : 12;       // 0:11             Rising edge delay
             uint32_t                       : 4;        // 12:15
        __IO uint32_t FED                   : 12;       // 16:27            Falling edge delay
             uint32_t                       : 3;        // 28:30
        __IO uint32_t DTEN                  : 1;        // 31               Dead-time generator enable
    };
}DTGCTL_TYPEDEF;

// PAC55XX_Timer 
typedef struct{
    // CTL (Timer Control Register, Offset: 0x0000)
    TIMER_CTL_TYPEDEF CTL;
    
    // INT (Timer Interrupt Control, Offset: 0x0004)
    union{
        __IO     uint32_t w;  
        struct{
            __IO uint32_t CCR0IF            : 1;        // 0                CCR0 interrupt flag      
            __IO uint32_t CCR1IF            : 1;        // 1                CCR1 interrupt flag      
            __IO uint32_t CCR2IF            : 1;        // 2                CCR2 interrupt flag      
            __IO uint32_t CCR3IF            : 1;        // 3                CCR3 interrupt flag     
            __IO uint32_t CCR4IF            : 1;        // 4                CCR4 interrupt flag     
            __IO uint32_t CCR5IF            : 1;        // 5                CCR5 interrupt flag      
            __IO uint32_t CCR6IF            : 1;        // 6                CCR6 interrupt flag      
            __IO uint32_t CCR7IF            : 1;        // 7                CCR7 interrupt flag     
            __IO uint32_t BASEIF            : 1;        // 8                Base timer interrupt flag
                 uint32_t                   : 23;       // 9:31    
        };
    } INT;
    
    // PRD (Timer Period, Offset: 0x0008)
    union{
        __IO     uint32_t w;  
        struct{
            __IO uint32_t PERIOD            : 16;        // 0:15            Timer period value      
                 uint32_t                   : 16;        // 16:31
        };
    } PRD;

    // CTR (Timer Counter, Offset: 0x000C)
    union{
        __IO     uint32_t w;  
        struct {     
            __IO uint32_t COUNTER           : 16;        // 0:15            Timer counter     
                 uint32_t                   : 16;        // 16:31
        };
    } CTR;

    // QEPCTL (Timer QEP Control, Offset: 0x0010)
    union{
        __IO     uint32_t w;  
        struct {
            __IO uint32_t QEPEN             : 1;        // 0                QEP peripheral enabled    
            __I  uint32_t DIR               : 1;        // 1                Motor direction   
            __IO uint32_t DIRIE             : 1;        // 2                Direction change interrupt enable     
            __IO uint32_t PHAIE             : 1;        // 3                Phase A rising edge interrupt enable     
            __IO uint32_t PHBIE             : 1;        // 4                Phase B rising edge interrupt enable    
            __IO uint32_t WRIE              : 1;        // 5                Counter wrap interrupt enable    
            __IO uint32_t IDXEVIE           : 1;        // 6                Index event interrupt enable    
            __IO uint32_t IDXRST            : 1;        // 7                Reset counter on index     
            __I  uint32_t DIRIF             : 1;        // 8                Direction change interrupt flag     
            __I  uint32_t PHAIF             : 1;        // 9                Phase A rising edge interrupt flag     
            __I  uint32_t PHBIF             : 1;        // 10               Phase B rising edge interrupt flag
            __I  uint32_t WRIF              : 1;        // 11               Counter wrap interrupt flag  
            __I  uint32_t IDXEVIF           : 1;        // 12               Index event interrupt flag    
            __IO uint32_t CNTAB             : 1;        // 13               Count on A/B     
            __IO uint32_t CNTEDGE           : 1;        // 14               Count on edge       
                 uint32_t                   : 1;        // 15                     
            __IO uint32_t TICKS             : 16;       // 16:31            Number of counted phase edges according to counting mode     
        };
        struct {
                 uint32_t                   : 8;        // 0:7
            __IO uint32_t IFCLEAR           : 5;        // 8:12             Interrupt flags
                 uint32_t                   : 19;       // 13:31
        };
    } QEPCTL;    
    
    uint32_t RESERVER1[59];
    
    // CCTL0 (Timer CC control 0, Offset: 0100h) 
    CCTL_TYPEDEF CCTL0;
    // CCTR0 (Timer CC counter 0, Offset: 0104h) 
    CCTR_TYPEDEF CCTR0;
    
    // CCTL1 (Timer  CC control 1, Offset: 0108h)
    CCTL_TYPEDEF CCTL1;
    // CCTR1 (Timer CC counter 1, Offset: 010Ch)
    CCTR_TYPEDEF CCTR1;
    
    // CCTL2 (Timer CC control 2, Offset: 0110h)
    CCTL_TYPEDEF CCTL2;
    // CCTR2 (Timer CC counter 2, Offset: 0114h)
    CCTR_TYPEDEF CCTR2;
    
    // CCTL3 (Timer CC control 3, Offset: 0118h)
    CCTL_TYPEDEF CCTL3;
    // CCTR3 (Timer CC counter 3, Offset: 011Ch)
    CCTR_TYPEDEF CCTR3;
    
    // CCTL4 (Timer CC control 4, Offset: 0120h)
    CCTL_TYPEDEF CCTL4;
    // CCTR4 (Timer CC counter 4, Offset: 0124h)
    CCTR_TYPEDEF CCTR4;
    
    // CCTL5 (Timer CC control 5, Offset: 0128h)
    CCTL_TYPEDEF CCTL5;
    // CCTR5 (Timer CC counter 5, Offset: 012Ch)
    CCTR_TYPEDEF CCTR5;
    
    // CCTL6 (Timer CC control 6, Offset: 0130h)
    CCTL_TYPEDEF CCTL6;
    // CCTR6 (Timer CC counter 6, Offset; 0134h)
    CCTR_TYPEDEF CCTR6;
    
    // CCTL7 (Timer CC control 7, Offset; 0138h)
    CCTL_TYPEDEF CCTL7;
    // CCTR7 (Timer CC counter 7, Offset: 013Ch)
    CCTR_TYPEDEF CCTR7;
    
    uint32_t RESERVER2[48];
    
    // DTGCTL0 (Timer DTG control 0, Offset: 0200h)
    DTGCTL_TYPEDEF DTGCTL0;
    
    // DTGCTL1 (Timer DTG control 1, Offset: 0204h)
    DTGCTL_TYPEDEF DTGCTL1;
    
    // DTGCTL2 (Timer DTG control 2, Offset: 0208h)
    DTGCTL_TYPEDEF DTGCTL2;
    
    // DTGCTL3 (Timer DTG control 3, Offset: 020Ch)
    DTGCTL_TYPEDEF DTGCTL3;
    
}PAC55XX_TIMER_TYPEDEF;


#endif  // PAC5XXX_TIMERS_H
