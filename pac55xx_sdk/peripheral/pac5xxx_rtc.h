//=================================================================================
/// @file     pac5xxx_rtc.h
/// @brief    CMSIS Cortex-M Header File for the PAC55XX Real-Time Clock
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
#ifndef PAC5XXX_RTC_H
#define PAC5XXX_RTC_H

// RTC Enable Enumeration Type
typedef enum{
    RTC_DISABLE         =0,
    RTC_ENABLE          =1
} RTC_EN_TYPE;

// RTC Clock Divider (to get 1MHz) Enumeration Type 
typedef enum{
    RTC_CLKDIV_1        =0,
    RTC_CLKDIV_2        =1,
    RTC_CLKDIV_3        =2,
    RTC_CLKDIV_4        =3,
    RTC_CLKDIV_5        =4,
    RTC_CLKDIV_6        =5,
    RTC_CLKDIV_7        =6,
    RTC_CLKDIV_8        =7,
    RTC_CLKDIV_9        =8,
    RTC_CLKDIV_10       =9,
    RTC_CLKDIV_11       =10,
    RTC_CLKDIV_12       =11,
    RTC_CLKDIV_13       =12,
    RTC_CLKDIV_14       =13,
    RTC_CLKDIV_15       =14,
    RTC_CLKDIV_16       =15,
    RTC_CLKDIV_17       =16,
    RTC_CLKDIV_18       =17,
    RTC_CLKDIV_19       =18,
    RTC_CLKDIV_20       =19,
    RTC_CLKDIV_21       =20,
    RTC_CLKDIV_22       =21,
    RTC_CLKDIV_23       =22,
    RTC_CLKDIV_24       =23,
    RTC_CLKDIV_25       =24,
    RTC_CLKDIV_26       =25,
    RTC_CLKDIV_27       =26,
    RTC_CLKDIV_28       =27,
    RTC_CLKDIV_29       =28,
    RTC_CLKDIV_30       =29,
    RTC_CLKDIV_31       =30,
    RTC_CLKDIV_32       =31
} RTC_CLKDIV_TYPE;

// RTC Type Definition
typedef struct{
    
    // RTCCTL (RTC Control ,400D 0C00h)
    union{
        __IO      uint32_t w;
        struct{
            __IO  uint32_t EN               : 1;            // 0            RTC Enable
            __IO  uint32_t IE               : 1;            // 1            Alarm match interrupt enable
            __IO  uint32_t IF               : 1;            // 2            Alarm match interrupt flag
                  uint32_t                  : 1;            // 3
            __IO  uint32_t CLKDIV           : 5;            // 4:8          RTC Clock DIV (01-31)
                  uint32_t                  : 22;           // 9:30
            __IO  uint32_t SETCAL           : 1;            // 31           Enable TIME/DATE to the value of TIMESETTING and 
                                                            //                DATESETTING. Must be 1 before set DATE/TIME
        };
    }CTL;
    
    // RTCTIME (RTC Time Reading ,400D 0C04h)
    union{
        __IO      uint32_t w;
        struct{
            __I   uint32_t SECOND           : 7;            // 0:6          Second (0-59)
                  uint32_t                  : 1;            // 7
            __I   uint32_t MINUTE           : 7;            // 8:14         Minute (0-59)
                  uint32_t                  : 1;            // 15
            __I   uint32_t HOUR             : 6;            // 16:21        Hour (0-23)
                  uint32_t                  : 10;           // 22:31
        };
    } TIME;
    
    // RTCDATE (RTC Date Reading , 400D 0C08h)
    union{
        __IO      uint32_t w;
        struct{
            __I   uint32_t DAYOFWEEK        : 3;            // 0:2          Day of Week (0-6) (Monday-Sunday)
                  uint32_t                  : 5;            // 3:7
            __I   uint32_t DAY              : 6;            // 8:13         Day (01-31)
                  uint32_t                  : 2;            // 14:15
            __I   uint32_t MONTH            : 5;            // 16:20        Month (01-12)
                  uint32_t                  : 3;            // 21:23
            __I   uint32_t YEAR             : 8;            // 24:31        Year (00-99)
        }; 
    }DATE;
    
    // RTCTIMESET (RTC Time Setting ,400D 0C0Ch)
    union{
        __IO uint32_t w;
        struct{
            __IO  uint32_t SECOND           : 7;             // 0:6         Second (0-59)
                  uint32_t                  : 1;             // 7
            __IO  uint32_t MINUTE           : 7;             // 8:14        Minute (0-59)
                  uint32_t                  : 1;             // 15
            __IO  uint32_t HOUR             : 6;             // 16:21       Hour (0-23)
                  uint32_t                  : 10;            // 22:31
        };
    } TIMESET;
    
    // RTCDATESET (RTC Date Setting ,400D 0C10h)
    union{
        __IO      uint32_t w;
        struct{
            __IO  uint32_t DAYOFWEEK        : 3;             // 0:2         Day of Week (0-6)
                  uint32_t                  : 5;             // 3:7
            __IO  uint32_t DAY              : 6;             // 8:13        Day (01-31)
                  uint32_t                  : 2;             // 14:15
            __IO  uint32_t MONTH            : 5;             // 16:20       Month (01-12)
                  uint32_t                  : 3;             // 21:23
            __IO  uint32_t YEAR             : 8;             // 24:31       Year (00-99)
        };
    }DATESET;
    
    // RTCALARMSET (RTC Alarm Setting ,400D 0C14h)
    union{
        __IO      uint32_t w;
        struct{
            __IO  uint32_t MINUTEALARM      : 7;            // 0:6          Minute Alarm Setting (0-59)
            __IO  uint32_t MINUTEALARMEN    : 1;            // 7            Enable Minute Alarm 
            __IO  uint32_t HOURALARM        : 6;            // 8:13         Hour Alarm Setting (0-23)
            __IO  uint32_t HOURALARMEN      : 1;            // 14           Enable Hour Alarm 
                  uint32_t                  : 1;            // 15
            __IO  uint32_t DAYOFWEEKALARM   : 3;            // 16:18        Day of Week Alarm Setting (0-6)
            __IO  uint32_t DAYOFWEEKALARMEN : 1;            // 19           Enable Weekday Alarm 
                  uint32_t                  : 4;            // 20:23
            __IO  uint32_t DAYALARM         : 6;            // 24:29        Day Alarm Setting (01-31)
            __IO  uint32_t DAYALARMEN       : 1;            // 30           Enable Day Alarm 
                  uint32_t                  : 1;            // 31
        };
    }ALARMSET;
} PAC55XX_RTC_TYPEDEF;

#endif  // PAC5XXX_RTC_H
