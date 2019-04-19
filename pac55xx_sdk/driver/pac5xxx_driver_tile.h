/**************************************************************************//**
 * @file     pac5xxx_driver_tile.h
 * @brief    Firmware driver for communications with analog tiles
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

#ifndef PAC5XXX_DRIVER_TILE_H
#define PAC5XXX_DRIVER_TILE_H

/** @addtogroup PAC5XXX_Driver_Tile PAC5XXX Tile Driver
  @{
*/

#include "pac5xxx.h"
#include "pac5xxx_driver_config.h"

#ifdef PAC5XXX_DRIVER_TILE_RAM
#define RAMFUNC_TILE	PAC5XXX_RAMFUNC
#else 
#define RAMFUNC_TILE
#endif

/**
 * @brief	This function reads a tile register via polling
 *
 * @param	address Register address to read from
 * @return	Data read from register
 */
RAMFUNC_TILE uint8_t pac5xxx_tile_register_read(uint8_t address);

/**
 * @brief  This function writes a tile register
 *
 * @param  address Register address to write
 * @param  data Data to write
 * @return 0: success, non-zero: failure
 *
 * @note The user must configure interrupts for the SOC Bridge interface after calling this function
 *       and is responsible for registering the Cortex interrupts and providing the interrupt handlers.
 */
RAMFUNC_TILE void pac5xxx_tile_register_write(uint8_t address, uint8_t data);

/**
 * @brief  This function configures the device for configuration with the Analog tiles via SOC Bridge
 *
 * @param  enable Set to 1 to enable SOC Bridge
 * @param  int_enable Set to 1 to enable interrupts for SOC bridge
 * @return none
 *
 */
RAMFUNC_TILE void pac5xxx_tile_socbridge_config(int enable, int int_enable);

/*@}*/ /* end of group PAC5XXX_Driver_Tile */

#endif // PAC5XXX_DRIVER_TILE_H

