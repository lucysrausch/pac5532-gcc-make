//=================================================================================
/// @file     pac5xxx_adc.h
/// @brief    CMSIS Cortex-M Header File for the PAC55XX ADC and DTSE
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

#ifndef PAC5XXX_ADC_H
#define PAC5XXX_ADC_H

/** ADCCTL Positive Input MUX channel select */
typedef enum {
  ADCCTL_ADMUX_AD0 = 0,                        /*!< ADC positive input MUX channel select: AD0 (Analog die)        */
  ADCCTL_ADMUX_AD1 = 1,                        /*!< ADC positive input MUX channel select: AD1                     */
  ADCCTL_ADMUX_AD2 = 2,                        /*!< ADC positive input MUX channel select: AD2                     */
  ADCCTL_ADMUX_AD3 = 3,                        /*!< ADC positive input MUX channel select: AD3                     */
  ADCCTL_ADMUX_AD4 = 4,                        /*!< ADC positive input MUX channel select: AD4                     */
  ADCCTL_ADMUX_AD5 = 5,                        /*!< ADC positive input MUX channel select: AD5                     */
  ADCCTL_ADMUX_VSSA = 7                        /*!< ADC positive input MUX channel select: VSSA                    */
} ADCCTL_ADMUX_Type;

// ADC EMUX Clock Divider Enumeration Type
typedef enum {
    ADCEMUXCTL_EMUXDIV_DIV1  = 0,               // External MUX clock divider: /1
    ADCEMUXCTL_EMUXDIV_DIV2  = 1,               // External MUX clock divider: /2
    ADCEMUXCTL_EMUXDIV_DIV3  = 2,               // External MUX clock divider: /3
    ADCEMUXCTL_EMUXDIV_DIV4  = 3,               // External MUX clock divider: /4
    ADCEMUXCTL_EMUXDIV_DIV5  = 4,               // External MUX clock divider: /5
    ADCEMUXCTL_EMUXDIV_DIV6  = 5,               // External MUX clock divider: /6
    ADCEMUXCTL_EMUXDIV_DIV7  = 6,               // External MUX clock divider: /7
    ADCEMUXCTL_EMUXDIV_DIV8  = 7,               // External MUX clock divider: /8  
    ADCEMUXCTL_EMUXDIV_DIV9  = 8,               // External MUX clock divider: /9
    ADCEMUXCTL_EMUXDIV_DIV10 = 9,               // External MUX clock divider: /10
    ADCEMUXCTL_EMUXDIV_DIV11 = 10,              // External MUX clock divider: /11                                
    ADCEMUXCTL_EMUXDIV_DIV12 = 11,              // External MUX clock divider: /12                                 
    ADCEMUXCTL_EMUXDIV_DIV13 = 12,              // External MUX clock divider: /13                                
    ADCEMUXCTL_EMUXDIV_DIV14 = 13,              // External MUX clock divider: /14                                
    ADCEMUXCTL_EMUXDIV_DIV15 = 14,              // External MUX clock divider: /15                                 
    ADCEMUXCTL_EMUXDIV_DIV16 = 15               // External MUX clock divider: /16    
} ADCEMUXCTL_DIV_TYPE;

// ADC EMUX Control Enumeration Type
typedef enum {
    ADCEMUXCTL_EMUXDATA = 0,                    // EMUX is controlled by EMUXDATA                              
    ADCEMUXCTL_DTSE_SEQ = 1                     // EMUX is controlled by DTSE sequencer commands  
} ADC_EMUX_CTL_TYPE;

// ADCCTL Clock Input Divider Enumeration Type
typedef enum {
    ADCCTL_CLKDIV_DIV1  = 0,                    // ADC module clock input divider: /1                                
    ADCCTL_CLKDIV_DIV2  = 1,                    // ADC module clock input divider: /2                                 
    ADCCTL_CLKDIV_DIV3  = 2,                    // ADC module clock input divider: /3                                
    ADCCTL_CLKDIV_DIV4  = 3,                    // ADC module clock input divider: /4                                 
    ADCCTL_CLKDIV_DIV5  = 4,                    // ADC module clock input divider: /5                                
    ADCCTL_CLKDIV_DIV6  = 5,                    // ADC module clock input divider: /6                                
    ADCCTL_CLKDIV_DIV7  = 6,                    // ADC module clock input divider: /7                                 
    ADCCTL_CLKDIV_DIV8  = 7,                    // ADC module clock input divider: /8 
    ADCCTL_CLKDIV_DIV9  = 8,                    // ADC module clock input divider: /9                                 
    ADCCTL_CLKDIV_DIV10 = 9,                    // ADC module clock input divider: /10                                 
    ADCCTL_CLKDIV_DIV11 = 10,                   // ADC module clock input divider: /11                                
    ADCCTL_CLKDIV_DIV12 = 11,                   // ADC module clock input divider: /12                                 
    ADCCTL_CLKDIV_DIV13 = 12,                   // ADC module clock input divider: /13                               
    ADCCTL_CLKDIV_DIV14 = 13,                   // ADC module clock input divider: /14                                
    ADCCTL_CLKDIV_DIV15 = 14,                   // ADC module clock input divider: /15                                
    ADCCTL_CLKDIV_DIV16 = 15                    // ADC module clock input divider: /16    
} ADCCTL_CLKDIV_TYPE, ADCCTL_CLKDIV_Type;

// ADC Channel Enumeration Type
typedef enum {
    ADCCTL_CHANNEL_ADC0 = 0,                    // Chanel 0                             
    ADCCTL_CHANNEL_ADC1 = 1,                    // Chanel 1                             
    ADCCTL_CHANNEL_ADC2 = 2,                    // Chanel 2                             
    ADCCTL_CHANNEL_ADC3 = 3,                    // Chanel 3                             
    ADCCTL_CHANNEL_ADC4 = 4,                    // Chanel 4                             
    ADCCTL_CHANNEL_ADC5 = 5,                    // Chanel 5                             
    ADCCTL_CHANNEL_ADC6 = 6,                    // Chanel 6  
	ADCCTL_CHANNEL_ADC7 = 7                     // Chanel 7  
} ADCCTL_CHANNEL_TYPE;

// ADC Mode Enumeration Type
typedef enum {
    ADCCTL_MODE_MANUAL = 0,                     // Manual Mode                             
    ADCCTL_MODE_DTSE   = 1                      // DTSE Mode 
} ADCCTL_MODE_TYPE;

// DTSE Trigger Edge Enumeration Type
typedef enum {
    ADCDTSE_TRIGEDGE_UNUSED  = 0,               // Trigger Unused
    ADCDTSE_TRIGEDGE_RISING  = 1,               // Trigger Rising Edge
    ADCDTSE_TRIGEDGE_FALLING = 2,               // Trigger Falling Edge                           
    ADCDTSE_TRIGEDGE_BOTH    = 3                // Trigger both Rising and Falling Edges   
} ADCDTSE_TRIGEDGE_TYPE;

// DTSE IRQ Number Enumeration Type
typedef enum {
    ADCDTSE_IRQNUM_ADC0 = 0,                    // Assert ADC0 IRQ to NVIC when the sequence has completed conversion                             
    ADCDTSE_IRQNUM_ADC1 = 1,                    // Assert ADC1 IRQ to NVIC when the sequence has completed conversion 
    ADCDTSE_IRQNUM_ADC2 = 2,                    // Assert ADC2 IRQ to NVIC when the sequence has completed conversion                            
    ADCDTSE_IRQNUM_ADC3 = 3                     // Assert ADC3 IRQ to NVIC when the sequence has completed conversion    
} ADCDTSE_IRQNUM_TYPE;

// DTSE EMUX Control Enumeration Type
typedef enum {
    DTSESEQCFG_EMUXC_NONE = 0,                  // Do not send EMUX Command
    DTSESEQCFG_EMUXC_BSH  = 1,                  // Send EMUX command before sample and hold
    DTSESEQCFG_EMUXC_AEOC = 2,                  // Send EMUX command after conversion complete
} DTSESEQCFG_EMUXC_TYPE;



// ADC RESULT Type
typedef union
{
    __I uint32_t w;
    struct {
        __I uint32_t VAL                    : 12;   // 11:0      12bit digitized result
            uint32_t                        : 20;   // 31:12                 
    };
} ADC_RESULT_TYPEDEF; 

// DTSE Sequence Configuration Type     
typedef union
{
    __IO uint32_t w;
    struct {
        __IO uint32_t EMUXC                 : 2;    // 1:0      Controls the behavior of the EMUX during this conversion sequence
        __IO uint32_t CHANNEL               : 3;    // 4:2      DC channel to convert during this sequence
        __IO uint32_t DELAY                 : 2;    // 6:5      Conversion Delay.
        __IO uint32_t SEQDONE               : 1;    // 7        Final sequence of series.
        __IO uint32_t EMUXD                 : 8;    // 15:8     EMUX data to send.
        __IO uint32_t IRQNUM                : 2;    // 17:16    IRQ number to assert. 
        __IO uint32_t IRQEN                 : 1;    // 18       Assert IRQ after converting this sequence.
		__IO uint32_t NOCVT				    : 1;	// 19		No Conversion. EMUX Communications only.
             uint32_t                       : 12;   // 31:20
    };
} DTSE_SEQ_CFG_TYPEDEF;


typedef struct
{
    // EMUXCTL (EMUX Control, 4000 0000h):     
    union
    {
        __IO uint32_t w;     
        struct {
            __IO uint32_t EMUXDIV           : 4;    // 3:0      EMUX Clock Divider
            __IO uint32_t EMUXBUSY          : 1;    // 4        EMUX Busy Status
            __IO uint32_t EMUXMODE          : 1;    // 5        EMUX Mode
                 uint32_t                   : 26;   // 31:6
        };
    } EMUXCTL;

    // EMUXDATA (ADC EMUX DATA , 4000 0004h)
    union
    {
        __IO uint32_t w;     
        struct {
            __IO uint32_t VAL               : 8;    // 7:0      MUX data to send 
                 uint32_t                   : 24;   // 31:8
        };
    } EMUXDATA;  
  
    // ADCCTL (ADC Configuration, 4000 0008h)
     union
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t ADCDIV            : 4;    // 3:0      ADC Clock Divider
            __IO uint32_t CHANNEL           : 3;    // 6:4      ADC Channel
            __I  uint32_t ADBUSY            : 1;    // 7        ADC Busy
            __IO uint32_t MODE              : 2;    // 9:8      ADC Mode 
            __IO uint32_t REPEAT            : 1;    // 10       ADC Repeated Conversion Mode
            __IO uint32_t START             : 1;    // 11       ADC Conversion Start   
            __IO uint32_t ENABLE            : 1;    // 12       ADC Enable
            __IO uint32_t INTENMAN          : 1;    // 13       ADC Manual Mode Conversion Complete  
            __IO uint32_t INTENEMUX         : 1;    // 14       EMUX Complete Interrupt Enable
            __IO uint32_t INTENCOL          : 1;    // 15       Sequence Collision Interrupt Enable              
                 uint32_t                   : 16;   // 31:16
        };
    } ADCCTL;   
  
    // ADCRES (ADC Result, 4000 000Ch)
    ADC_RESULT_TYPEDEF ADCRES;    
    
    // ADCINT (ADC Interrupt Control, 4000 0010h)
    union
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t INTF0             : 1;    // 0        DTSE Sequence 0 Interrupt Flag
            __IO uint32_t INTF1             : 1;    // 1        DTSE Sequence 1 Interrupt Flag   
            __IO uint32_t INTF2             : 1;    // 2        DTSE Sequence 2 Interrupt Flag
            __IO uint32_t INTF3             : 1;    // 3        DTSE Sequence 3 Interrupt Flag  
            __IO uint32_t INTF4             : 1;    // 4        DTSE Sequence 4 Interrupt Flag
            __IO uint32_t INTF5             : 1;    // 5        DTSE Sequence 5 Interrupt Flag   
            __IO uint32_t INTF6             : 1;    // 6        DTSE Sequence 6 Interrupt Flag
            __IO uint32_t INTF7             : 1;    // 7        DTSE Sequence 7 Interrupt Flag   
            __IO uint32_t INTF8             : 1;    // 8        DTSE Sequence 8 Interrupt Flag
            __IO uint32_t INTF9             : 1;    // 9        DTSE Sequence 9 Interrupt Flag   
            __IO uint32_t INTF10            : 1;    // 10       DTSE Sequence 10 Interrupt Flag
            __IO uint32_t INTF11            : 1;    // 11       DTSE Sequence 11 Interrupt Flag  
            __IO uint32_t INTF12            : 1;    // 12       DTSE Sequence 12 Interrupt Flag
            __IO uint32_t INTF13            : 1;    // 13       DTSE Sequence 13 Interrupt Flag   
            __IO uint32_t INTF14            : 1;    // 14       DTSE Sequence 14 Interrupt Flag
            __IO uint32_t INTF15            : 1;    // 15       DTSE Sequence 15 Interrupt Flag 
            __IO uint32_t INTF16            : 1;    // 16       DTSE Sequence 16 Interrupt Flag
            __IO uint32_t INTF17            : 1;    // 17       DTSE Sequence 17 Interrupt Flag   
            __IO uint32_t INTF18            : 1;    // 18       DTSE Sequence 18 Interrupt Flag
            __IO uint32_t INTF19            : 1;    // 19       DTSE Sequence 19 Interrupt Flag  
            __IO uint32_t INTF20            : 1;    // 20       DTSE Sequence 20 Interrupt Flag
            __IO uint32_t INTF21            : 1;    // 21       DTSE Sequence 21 Interrupt Flag   
            __IO uint32_t INTF22            : 1;    // 22       DTSE Sequence 22 Interrupt Flag
            __IO uint32_t INTF23            : 1;    // 23       DTSE Sequence 23 Interrupt Flag
            __IO uint32_t INTFMAN           : 1;    // 24       DTSE Manual Mode Conversion Complete Interrupt Flag
            __IO uint32_t INTFEMUX          : 1;    // 25       DTSE EMUX Complete Interrupt Flag   
            __IO uint32_t INTFCOL           : 1;    // 26       DTSE Sequence Collision Interrupt Flag
                 uint32_t                   : 1;    // 27       Reserved  
            __IO uint32_t ADCIRQ0IF         : 1;    // 28       ADCIRQ0 Interrupt Flag
            __IO uint32_t ADCIRQ1IF         : 1;    // 29       ADCIRQ1 Interrupt Flag  
            __IO uint32_t ADCIRQ2IF         : 1;    // 30       ADCIRQ2 Interrupt Flag
            __IO uint32_t ADCIRQ3IF         : 1;    // 31       ADCIRQ3 Interrupt Flag             
        };
    } ADCINT; 
    
    uint32_t RESERVED0[11];
    
    // DTSETRIGENT0TO3 (DTSE Trigger Entry 0 to 3, 4000 0040h)
    union
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t TRIG0CFGIDX       : 5;    // 4:0      DTSE Trigger 0 Sequence Configuration Entry Index
            __IO uint32_t TRIG0EDGE         : 2;    // 6:5      DTSE Trigger 0 Edge Configuration
            __IO uint32_t FORCE0            : 1;    // 7        Force Trigger 0
            __IO uint32_t TRIG1CFGIDX       : 5;    // 12:8     DTSE Trigger 1 Sequence Configuration Entry Index 
            __IO uint32_t TRIG1EDGE         : 2;    // 14:13    DTSE Trigger 1 Edge Configuration  
            __IO uint32_t FORCE1            : 1;    // 15       Force Trigger 1  
            __IO uint32_t TRIG2CFGIDX       : 5;    // 20:16    DTSE Trigger 2 Sequence Configuration Entry Index  
            __IO uint32_t TRIG2EDGE         : 2;    // 22:21    DTSE Trigger 2 Edge Configuration 
            __IO uint32_t FORCE2            : 1;    // 23       Force Trigger 2   
            __IO uint32_t TRIG3CFGIDX       : 5;    // 28:24    DTSE Trigger 3 Sequence Configuration Entry Index  
            __IO uint32_t TRIG3EDGE         : 2;    // 30:29    DTSE Trigger 3 Edge Configuration 
            __IO uint32_t FORCE3            : 1;    // 31       Force Trigger 3             
        };
    } DTSETRIGENT0TO3;  

    // DTSETRIGENT0TO3 (DTSE Trigger Entry 4 to 7, 4000 0044h)
    union
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t TRIG4CFGIDX       : 5;    // 4:0      DTSE Trigger 4 Sequence Configuration Entry Index
            __IO uint32_t TRIG4EDGE         : 2;    // 6:5      DTSE Trigger 4 Edge Configuration
            __IO uint32_t FORCE4            : 1;    // 7        Force Trigger 4
            __IO uint32_t TRIG5CFGIDX       : 5;    // 12:8     DTSE Trigger 5 Sequence Configuration Entry Index 
            __IO uint32_t TRIG5EDGE         : 2;    // 14:13    DTSE Trigger 5 Edge Configuration  
            __IO uint32_t FORCE5            : 1;    // 15       Force Trigger 5  
            __IO uint32_t TRIG6CFGIDX       : 5;    // 20:16    DTSE Trigger 6 Sequence Configuration Entry Index  
            __IO uint32_t TRIG6EDGE         : 2;    // 22:21    DTSE Trigger 6 Edge Configuration 
            __IO uint32_t FORCE6            : 1;    // 23       Force Trigger 6   
            __IO uint32_t TRIG7CFGIDX       : 5;    // 28:24    DTSE Trigger 7 Sequence Configuration Entry Index  
            __IO uint32_t TRIG7EDGE         : 2;    // 30:29    DTSE Trigger 7 Edge Configuration 
            __IO uint32_t FORCE7            : 1;    // 31       Force Trigger 7             
        };
    } DTSETRIGENT4TO7;     

    // DTSETRIGENT8TO11 (DTSE Trigger Entry 8 to 11, 4000 0048h)
    union
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t TRIG8CFGIDX       : 5;    // 4:0      DTSE Trigger 8 Sequence Configuration Entry Index
            __IO uint32_t TRIG8EDGE         : 2;    // 6:5      DTSE Trigger 8 Edge Configuration
            __IO uint32_t FORCE8            : 1;    // 7        Force Trigger 8
            __IO uint32_t TRIG9CFGIDX       : 5;    // 12:8     DTSE Trigger 9 Sequence Configuration Entry Index 
            __IO uint32_t TRIG9EDGE         : 2;    // 14:13    DTSE Trigger 9 Edge Configuration  
            __IO uint32_t FORCE9            : 1;    // 15       Force Trigger 9  
            __IO uint32_t TRIG10CFGIDX      : 5;    // 20:16    DTSE Trigger 10 Sequence Configuration Entry Index  
            __IO uint32_t TRIG10EDGE        : 2;    // 22:21    DTSE Trigger 10 Edge Configuration 
            __IO uint32_t FORCE10           : 1;    // 23       Force Trigger 10   
            __IO uint32_t TRIG11CFGIDX      : 5;    // 28:24    DTSE Trigger 11 Sequence Configuration Entry Index  
            __IO uint32_t TRIG11EDGE        : 2;    // 30:29    DTSE Trigger 11 Edge Configuration 
            __IO uint32_t FORCE11           : 1;    // 31       Force Trigger 11             
        };
    } DTSETRIGENT8TO11; 

    // DTSETRIGENT12TO15 (DTSE Trigger Entry 12 to 15, 4000 004Ch)
    union
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t TRIG12CFGIDX      : 5;    // 4:0      DTSE Trigger 12 Sequence Configuration Entry Index
            __IO uint32_t TRIG12EDGE        : 2;    // 6:5      DTSE Trigger 12 Edge Configuration
            __IO uint32_t FORCE12           : 1;    // 7        Force Trigger 12
            __IO uint32_t TRIG13CFGIDX      : 5;    // 12:8     DTSE Trigger 13 Sequence Configuration Entry Index 
            __IO uint32_t TRIG13EDGE        : 2;    // 14:13    DTSE Trigger 13 Edge Configuration  
            __IO uint32_t FORCE13           : 1;    // 15       Force Trigger 13  
            __IO uint32_t TRIG14CFGIDX      : 5;    // 20:16    DTSE Trigger 14 Sequence Configuration Entry Index  
            __IO uint32_t TRIG14EDGE        : 2;    // 22:21    DTSE Trigger 14 Edge Configuration 
            __IO uint32_t FORCE14           : 1;    // 23       Force Trigger 14   
            __IO uint32_t TRIG15CFGIDX      : 5;    // 28:24    DTSE Trigger 15 Sequence Configuration Entry Index  
            __IO uint32_t TRIG15EDGE        : 2;    // 30:29    DTSE Trigger 15 Edge Configuration 
            __IO uint32_t FORCE15           : 1;    // 31       Force Trigger 15             
        };
    } DTSETRIGENT12TO15;  

    // DTSETRIGENT16TO19 (DTSE Trigger Entry 16 to 19, 4000 0050h)
    union
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t TRIG16CFGIDX      : 5;    // 4:0      DTSE Trigger 16 Sequence Configuration Entry Index
            __IO uint32_t TRIG16EDGE        : 2;    // 6:5      DTSE Trigger 16 Edge Configuration
            __IO uint32_t FORCE16           : 1;    // 7        Force Trigger 16
            __IO uint32_t TRIG17CFGIDX      : 5;    // 12:8     DTSE Trigger 17 Sequence Configuration Entry Index 
            __IO uint32_t TRIG17EDGE        : 2;    // 14:13    DTSE Trigger 17 Edge Configuration  
            __IO uint32_t FORCE17           : 1;    // 15       Force Trigger 17  
            __IO uint32_t TRIG18CFGIDX      : 5;    // 20:16    DTSE Trigger 18 Sequence Configuration Entry Index  
            __IO uint32_t TRIG18EDGE        : 2;    // 22:21    DTSE Trigger 18 Edge Configuration 
            __IO uint32_t FORCE18           : 1;    // 23       Force Trigger 18   
            __IO uint32_t TRIG19CFGIDX      : 5;    // 28:24    DTSE Trigger 19 Sequence Configuration Entry Index  
            __IO uint32_t TRIG19EDGE        : 2;    // 30:29    DTSE Trigger 19 Edge Configuration 
            __IO uint32_t FORCE19           : 1;    // 31       Force Trigger 19             
        };
    } DTSETRIGENT16TO19; 
    
    // DTSETRIGENT20TO23 (DTSE Trigger Entry 20 to 23, 4000 0054h)
    union
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t TRIG20CFGIDX      : 5;    // 4:0      DTSE Trigger 20 Sequence Configuration Entry Index
            __IO uint32_t TRIG20EDGE        : 2;    // 6:5      DTSE Trigger 20 Edge Configuration
            __IO uint32_t FORCE20           : 1;    // 7        Force Trigger 20
            __IO uint32_t TRIG21CFGIDX      : 5;    // 12:8     DTSE Trigger 21 Sequence Configuration Entry Index 
            __IO uint32_t TRIG21EDGE        : 2;    // 14:13    DTSE Trigger 21 Edge Configuration  
            __IO uint32_t FORCE21           : 1;    // 15       Force Trigger 21  
            __IO uint32_t TRIG22CFGIDX      : 5;    // 20:16    DTSE Trigger 22 Sequence Configuration Entry Index  
            __IO uint32_t TRIG22EDGE        : 2;    // 22:21    DTSE Trigger 22 Edge Configuration 
            __IO uint32_t FORCE22           : 1;    // 23       Force Trigger 22   
            __IO uint32_t TRIG23CFGIDX      : 5;    // 28:24    DTSE Trigger 23 Sequence Configuration Entry Index  
            __IO uint32_t TRIG23EDGE        : 2;    // 30:29    DTSE Trigger 23 Edge Configuration 
            __IO uint32_t FORCE23           : 1;    // 31       Force Trigger 23             
        };
    } DTSETRIGENT20TO23;  
    
    // DTSETRIGENT24TO27 (DTSE Trigger Entry 24 to 27, 4000 0058h)
    union
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t TRIG24CFGIDX      : 5;    // 4:0      DTSE Trigger 24 Sequence Configuration Entry Index
            __IO uint32_t TRIG24EDGE        : 2;    // 6:5      DTSE Trigger 24 Edge Configuration
            __IO uint32_t FORCE24           : 1;    // 7        Force Trigger 24
            __IO uint32_t TRIG25CFGIDX      : 5;    // 12:8     DTSE Trigger 25 Sequence Configuration Entry Index 
            __IO uint32_t TRIG25EDGE        : 2;    // 14:13    DTSE Trigger 25 Edge Configuration  
            __IO uint32_t FORCE25           : 1;    // 15       Force Trigger 25  
            __IO uint32_t TRIG26CFGIDX      : 5;    // 20:16    DTSE Trigger 26 Sequence Configuration Entry Index  
            __IO uint32_t TRIG26EDGE        : 2;    // 22:21    DTSE Trigger 26 Edge Configuration 
            __IO uint32_t FORCE26           : 1;    // 23       Force Trigger 26   
            __IO uint32_t TRIG27CFGIDX      : 5;    // 28:24    DTSE Trigger 27 Sequence Configuration Entry Index  
            __IO uint32_t TRIG27EDGE        : 2;    // 30:29    DTSE Trigger 27 Edge Configuration 
            __IO uint32_t FORCE27           : 1;    // 31       Force Trigger 27             
        };
    } DTSETRIGENT24TO27; 

    // DTSETRIGENT28TO31 (DTSE Trigger Entry 28 to 31, 4000 005Ch)
    union
    {
        __IO uint32_t w;
        struct {
            __IO uint32_t TRIG28CFGIDX      : 5;    // 4:0      DTSE Trigger 28 Sequence Configuration Entry Index
            __IO uint32_t TRIG28EDGE        : 2;    // 6:5      DTSE Trigger 28 Edge Configuration
            __IO uint32_t FORCE28           : 1;    // 7        Force Trigger 28
            __IO uint32_t TRIG29CFGIDX      : 5;    // 12:8     DTSE Trigger 29 Sequence Configuration Entry Index 
            __IO uint32_t TRIG29EDGE        : 2;    // 14:13    DTSE Trigger 29 Edge Configuration  
            __IO uint32_t FORCE29           : 1;    // 15       Force Trigger 29  
            __IO uint32_t TRIG30CFGIDX      : 5;    // 20:16    DTSE Trigger 30 Sequence Configuration Entry Index  
            __IO uint32_t TRIG30EDGE        : 2;    // 22:21    DTSE Trigger 30 Edge Configuration 
            __IO uint32_t FORCE30           : 1;    // 23       Force Trigger 30   
            __IO uint32_t TRIG31CFGIDX      : 5;    // 28:24    DTSE Trigger 31 Sequence Configuration Entry Index  
            __IO uint32_t TRIG31EDGE        : 2;    // 30:29    DTSE Trigger 31 Edge Configuration 
            __IO uint32_t FORCE31           : 1;    // 31       Force Trigger 31             
        };
    } DTSETRIGENT28TO31;  
    
    uint32_t RESERVED1[8];
    
    //DTSE Sequence Configuration 0 to 23, 4000 0080h)
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG0;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG1;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG2;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG3;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG4;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG5;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG6;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG7;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG8;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG9;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG10;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG11;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG12;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG13;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG14;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG15; 
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG16;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG17;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG18;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG19;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG20;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG21;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG22;
    DTSE_SEQ_CFG_TYPEDEF DTSESEQCFG23; //4000 00DC
    
    //Reserved for feature, 4000 00E0h)
    uint32_t RESERVED2[8];
    
    // DTSE Conversion Result 0 to 23, 4000 0100h)
    ADC_RESULT_TYPEDEF DTSERES0;
    ADC_RESULT_TYPEDEF DTSERES1;
    ADC_RESULT_TYPEDEF DTSERES2;
    ADC_RESULT_TYPEDEF DTSERES3;
    ADC_RESULT_TYPEDEF DTSERES4;
    ADC_RESULT_TYPEDEF DTSERES5;
    ADC_RESULT_TYPEDEF DTSERES6;
    ADC_RESULT_TYPEDEF DTSERES7; 
    ADC_RESULT_TYPEDEF DTSERES8;
    ADC_RESULT_TYPEDEF DTSERES9;
    ADC_RESULT_TYPEDEF DTSERES10;
    ADC_RESULT_TYPEDEF DTSERES11;
    ADC_RESULT_TYPEDEF DTSERES12;
    ADC_RESULT_TYPEDEF DTSERES13;
    ADC_RESULT_TYPEDEF DTSERES14;
    ADC_RESULT_TYPEDEF DTSERES15;
    ADC_RESULT_TYPEDEF DTSERES16;
    ADC_RESULT_TYPEDEF DTSERES17;
    ADC_RESULT_TYPEDEF DTSERES18;
    ADC_RESULT_TYPEDEF DTSERES19;
    ADC_RESULT_TYPEDEF DTSERES20;
    ADC_RESULT_TYPEDEF DTSERES21;
    ADC_RESULT_TYPEDEF DTSERES22;
    ADC_RESULT_TYPEDEF DTSERES23;    
} PAC55XX_ADC_TYPEDEF;

#endif  // PAC5XXX_ADC_H
