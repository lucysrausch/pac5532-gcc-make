/**************************************************************************//**
 * @file     pac5xxx_driver_memory.h
 * @brief    Firmware driver for the PAC5XXX memory controller
 *
 * @note
 * Copyright (C) 2015-2017, Active-Semi International
 *
 * THIS SOFTWARE IS SUBJECT TO A SOURCE CODE LICENSE AGREEMENT WHICH PROVIDES,
 * AMONG OTHER THINGS:  (i) THAT IT CAN BE USED ONLY TO ADAPT THE LICENSEE'S
 * APPLICATION TO PAC PROCESSORS SUPPLIED BY ACTIVE-SEMI INTERNATIONAL;
 * (ii) THAT  IT IS PROVIDED "AS IS" WITHOUT WARRANTY;  (iii) THAT
 * ACTIVE-SEMICONDUCTOR IS NOT LIABLE FOR ANY INDIRECT DAMAGES OR FOR DIRECT
 * DAMAGES EXCEEDING US$1,500;  AND (iv) THAT IT CAN BE DISCLOSED TO AND USED
 * ONLY BY CERTAIN AUTHORIZED PERSONS.
 *
 ******************************************************************************/

#ifndef PAC5XXX_DRIVER_MEMORY_H
#define PAC5XXX_DRIVER_MEMORY_H

/** @addtogroup PAC5XXX_Driver_Memory PAC5XXX Memory Controller
  @{
*/

#include "pac5xxx.h"
#include "pac5xxx_driver_config.h"

#ifdef PAC5XXX_DRIVER_MEMORY_RAM
#define RAMFUNC_MEMORY	PAC5XXX_RAMFUNC
#else 
#define RAMFUNC_MEMORY
#endif

/*@}*/ /* end of group PAC5XXX_Driver_Memory */

#endif 	// PAC5XXX_DRIVER_MEMORY_H

