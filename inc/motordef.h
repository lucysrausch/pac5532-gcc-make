/****************************************************************************
 * @file     motordef.h
 * @brief    Motor Definitions
 * @date     10 June 2015
 *
 * @note
 * Copyright (C) 2015, Active-Semi International
 *
 * THIS SOFTWARE IS SUBJECT TO A SOURCE CODE LICENSE AGREEMENT WHICH PROVIDES,
 * AMONG OTHER THINGS:  (i) THAT IT CAN BE USED ONLY TO ADAPT THE LICENSEE'S
 * APPLICATION TO PAC PROCESSORS SUPPLIED BY ACTIVE-SEMI INTERNATIONAL;
 * (ii) THAT  IT IS PROVIDED "AS IS" WITHOUT WARRANTY;  (iii) THAT
 * ACTIVE-SEMICONDUCTOR IS NOT LIABLE FOR ANY INDIRECT DAMAGES OR FOR DIRECT
 * DAMAGES EXCEEDING US$1,500;  AND (iv) THAT IT CAN BE DISCLOSED TO AND USED
 * ONLY BY CERTAIN AUTHORIZED PERSONS.
 ******************************************************************************/
#ifndef MOTOR_DEF_H
#define MOTOR_DEF_H

// **********************************************************************************
// Motor Parameters - Can be configured from GUI during Run Time
// **********************************************************************************

#define	PWM_SWITCH_FREQ			30

// Speed PI Loop Gains
#define SPEED_PI_TD				FIX16(1024 / 1000)		// 1 ms * 1024 in fix16 format
#define	SPEED_PI_KP				FIX16(3.0)
#define	SPEED_PI_KI				FIX16(9.0)
#define	SPEED_PI_MIN			-500
#define	SPEED_PI_MAX			500

#define	ADC_SKIP				PWM_SWITCH_FREQ / 10
#define	TD_HZ_DEF				100
//#define	TD_HZ_DEF				1000 / ADC_SKIP
#define IQ_PI_TD				FIX16(1024 / TD_HZ_DEF)	//TD_DEF = 1024*ADC_COUNTER#/(PWMFREQHZ*1000)
#define	IQ_PI_KP				FIX16(0.075)
#define	IQ_PI_KI				FIX16(9.0)
#define	IQ_PI_MIN				FIX16(0.05)						//Minimum Duty Cycle to start the motor
#define	IQ_PI_MAX				FIX16(0.99)						//Maximum Duty Cycle

#define	START_BLANKING_CYCLES	30
#define	START_GOOD_SAMPLES		5

#define START_IQ_REF_DEF		9
#define ALIGN_TIME_MS_DEF		100
#define OL_START_HZ_DEF			15
#define	OL_CL_TRANSITION_MS		100						//Number Of Milliseconds after Closed Loop Transition where the START_BLANKING_CYCLES and START_GOOD_SAMPLES are used
#define OL_SWITCHOVER_HZ_DEF	65

#define DEFAULT_OL_ACCEL_PERIOD	10						//Number of ms between speed increase during Open Loop Mode
#define DEFAULT_OL_ACCEL_INC	1						//Number of Hz for the speed increase during Open Loop Mode
#define DEFAULT_CL_ACCEL_PERIOD	3						//Number of ms between speed increase during Closed Loop Mode
#define DEFAULT_CL_ACCEL_INC	1						//Number of Hz for the speed increase during Closed Loop Mode

#define	RUN_BLANKING_CYCLES		15						//Blanking period in TIMER C Cycles
#define	RUN_GOOD_SAMPLES		1						//Number of good samples (in TIMER C Cycles) to acknowledge a BEMF transition

#define	TIMERC_PERIOD			400						//Use to set Timer C Sample Frequency (Freq = TIMERC_FREQ / TIMERC_PERIOD = 100MHz / 500 = 200 KHz)
#define	START_SPEED_HZ			200						//Closed Loop Start Speed (ramps from Switchover to this when transitioning from open loop to closed loop)

#define	HALF_DEGREE_ADV_DLY		FIX16(1/120)			// 0.5 degree advance delay factor = 1/2 Comm Adv Delay * 1/2 degree * 1/30 degrees
#define	ADV_DLY_DEF				60

#define	BLDC_DIRECTION			0						//1 for forward rotation, 0 for reverse rotation

#define	SCALE_PERCENT 			FIX16(0.1)				// Sine Wave Commutation Scaling Factor

#endif
