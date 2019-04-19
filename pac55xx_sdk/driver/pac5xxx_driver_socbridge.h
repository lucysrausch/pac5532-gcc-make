/**************************************************************************//**
 * @file     pac5xxx_driver_socbridge.h
 * @brief    Firmware driver for the PAC5XXX SOC Bridge
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

#ifndef PAC5XXX_DRIVER_SOCBRIDGE_H
#define PAC5XXX_DRIVER_SOCBRIDGE_H

/** @addtogroup PAC5XXX_Driver_SocBridge PAC5XXX SOC Bridge Peripheral
  @{
*/

#include "pac5xxx.h"
#include "pac5xxx_driver_config.h"
#include "pac5xxx_driver_gpio.h"

#ifdef PAC5XXX_DRIVER_SOCBRIDGE_RAM
#define RAMFUNC_SOCBRIDGE	PAC5XXX_RAMFUNC
#else
#define RAMFUNC_SOCBRIDGE
#endif

/**
 * @brief  This function configures and enables the SOC bridge
 *
 * @paramn enable Set to 1 to enable SOC Bridge, 0 to disable
 * @param  int_enable Set to 1 to enable interrupts, 0 to disable interrupts
 * @return none
 *
 */
RAMFUNC_SOCBRIDGE void pac5xxx_socbridge_config(int enable, int int_enable);

/**
 * @brief  This function configures the IO ports on the device for SOC bridge operation
 *
 * @return none
 *
 */
RAMFUNC_SOCBRIDGE void pac5xxx_socbridge_config_io(void);

/*@}*/ /* end of group PAC5XXX_Driver_SocBridge */

#endif // PAC5XXX_DRIVER_SOCBRIDGE_H
