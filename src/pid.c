/****************************************************************************
 * @file     pid.c
 * @brief    PID controller
 * @date     13 February 2015
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
#define INCLUDE_EXTERNS
#include "bldc_common.h"

/*!
 *  @brief Initializes the PID controller data
 *
 *  @param pid_data Pointer to the PID controller data
 *  @returns none
 *
 *  @note Note that the user must make sure that the pointer is valid and that the user-defined
 *        fields in the data structure are initialized properly (see the definition for the
 *        \a PID_Data_Type data structure).
 */
void pid_reset(PID_Data_Type* pid_data)
{
	pid_data->I_prev = 0;
	pid_data->PI = 0;
	pid_data->PI_sat = 0;
}

/*!
 *  @brief Runs the PID controller
 *
 *  @param pid_data Pointer to the PID controller data
 *  @param error Error from last controller
 */
APP_RAMFUNC void pid_run(volatile PID_Data_Type* f_pid_data, fix16_t f_error)
{
	fix16_t f_P = 0;
	fix16_t f_I = 0;

	// P = Kp * error
	f_P = fix16_mul_new_16_16(f_pid_data->Kp, f_error);

	// I = (error * Ki * TD + I_prev)
	f_I = fix16_mul_new_16_16(f_error, f_pid_data->Td);	//TD value includes the KI gain and the TD
	f_I >>= 10;											// De-scale because of Td
	f_I = fix16_add(f_I, f_pid_data->I_prev);

	// Saturate output
	f_pid_data->PI = fix16_add(f_P, f_I);
	f_pid_data->PI_sat = f_pid_data->PI;

	if (f_pid_data->PI > f_pid_data->max_value)
	{
		f_pid_data->PI_sat = f_pid_data->max_value;
		f_pid_data->I_prev = f_pid_data->PI_sat;
	}

	else if (f_pid_data->PI < f_pid_data->min_value)
	{
		f_pid_data->PI_sat = f_pid_data->min_value;
		f_pid_data->I_prev = f_pid_data->PI_sat;
	}
	else
	{
		f_pid_data->I_prev = f_I;
	}

//	Uncomment for PI Debug ONLY
//	pi_debug_value[tmp_pi_debug_index][0] = f_error;
//	pi_debug_value[tmp_pi_debug_index][1] = f_P;
//	pi_debug_value[tmp_pi_debug_index][2] = f_I;
//	pi_debug_value[tmp_pi_debug_index][3] = f_pid_data->PI;
//	pi_debug_value[tmp_pi_debug_index][4] = f_pid_data->PI_sat;
}

void pid_sync(PID_Data_Type* to_data, PID_Data_Type* from_data)
{
	to_data->I_prev = from_data->I_prev;
	to_data->PI = from_data->PI;
	to_data->PI_sat = from_data->PI_sat;
}

