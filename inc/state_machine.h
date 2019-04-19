/****************************************************************************
 * @file     state_machine.h
 * @brief    Public interface to State Machine
 * @date     22 September 2015
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
#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

typedef enum
{
	SMS_Idle = 0,
	SMS_Align,
	SMS_Align_Wait,
	SMS_Align_Hold,
	SMS_Align_Discharge,
	SMS_Start_Motor,
	SMS_Accel_Motor,
	SMS_SREG_Wait,
	SMS_SREG_Engage,
	SMS_StartUp,
	SMS_Beep_ON,
	SMS_Beep_OFF,
	SMS_Diag_Init,
	SMS_Diag_On_Wait,
	SMS_Diag_Off_Wait
}SMS_States;

#endif
