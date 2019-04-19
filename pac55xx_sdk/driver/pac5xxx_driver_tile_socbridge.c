/**************************************************************************//**
 * @file     pac5xxx_driver_tile_socbridge.c
 * @brief    Firmware driver for the PAC5XXX tile read/write registers via SOC Bridge
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

#include "pac5xxx_driver_tile.h"
#include "pac5xxx_driver_socbridge.h"

RAMFUNC_TILE void pac5xxx_tile_socbridge_config(int enable, int int_enable)
{
	  // Configure SOC Bridge
    pac5xxx_socbridge_config(enable, int_enable);      	// Enabled

    pac5xxx_socbridge_config_io();					    // Enable SPI IOs
}

// To optimize only the tile write, force function in RAM by replacing RAMFUNC_TILE with PAC5XXX_RAMFUNC
RAMFUNC_TILE void pac5xxx_tile_register_write(uint8_t address, uint8_t data)
{
    volatile unsigned int data_read;

    // Ensure no transmission is pending
    while (!PAC55XX_SSPA->STAT.TNF);
	
    // Write 16-bits containing Addr, R/W=1, Data
    // Format: Addr(15:9) | R/W(8) | Data(7:0)
   	PAC55XX_SSPA->DAT.DATA = (address << 9) | (1 << 8) | data;

	// Wait for transmission to be complete
    while (!PAC55XX_SSPA->STAT.TNF);

    // Must empty receive buffer
    while (!PAC55XX_SSPA->STAT.RNE);         // Wait for receive data ready 	    
    data_read = PAC55XX_SSPA->DAT.DATA;      // Read receive buffer data
}

// To optimize only the tile read, force function in RAM by replacing RAMFUNC_TILE with PAC5XXX_RAMFUNC
RAMFUNC_TILE uint8_t pac5xxx_tile_register_read(uint8_t address)
{
    uint8_t data;
    volatile int32_t test_count_var1;

    // Send SPI address with address 7 bit; first 9 bits are 1 bit read-write and 8 bit data
    PAC55XX_SSPA->DAT.DATA = (address << 9);
    
    // Wait for transmission to be complete 
    while (!PAC55XX_SSPA->STAT.TNF);
    
    // Wait for receive data ready 	    
    while (!PAC55XX_SSPA->STAT.RNE);  

    data = PAC55XX_SSPA->DAT.DATA;

	// Return read data
    return data;
}
