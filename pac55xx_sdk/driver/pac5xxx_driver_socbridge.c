/**************************************************************************//**
 * @file     pac5xxx_driver_socbridge_config.c
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

#include "pac5xxx_driver_socbridge.h"

RAMFUNC_SOCBRIDGE void pac5xxx_socbridge_config(int enable, int int_enable)
{
    PAC55XX_SCC->CCSCTL.USAMODE = 0;            // SET SSPA to SPI mode
    PAC55XX_SSPA->CLK.M = 2;                 // PCLK/((SSPxCLK.M + 1)*SSPxCLK.N)
    PAC55XX_SSPA->CLK.N = 2;                 // N nust be event value from 2 to 254 	
    PAC55XX_SSPA->CON.FRF = 0;               // Frame Format, SPI frame format
    PAC55XX_SSPA->CON.MS = 0;                // Master/Slave mode, master mode
    PAC55XX_SSPA->CON.LSBFIRST = 0;          // Endian Order, MSB transmit 1st
    PAC55XX_SSPA->CON.LBM = 0;               // Loobback Mode, no loopback mode
    PAC55XX_SSPA->CON.CPH = 0;               // Clock Out Phase, SPI captuers data sat 1st edge transition of the frame
    PAC55XX_SSPA->CON.CPO = 0;               // Clock Out Polarity, SPI clock active high
    PAC55XX_SSPA->CON.DSS = 0xF;             // Data Size Select, 16 bit data
    PAC55XX_SSPA->CON.SOD = 1;               // Slave Output Disable
    PAC55XX_SSPA->SSCR.SELSS = 0;            // Slave Select Signal Control
    PAC55XX_SSPA->SSCR.SWSEL = 0;            // Slave Select controlled by SPI
    PAC55XX_SSPA->SSCR.SWSS = 0;             // Slave Select State, Low active
    PAC55XX_SSPA->SSCR.SPHDONTCARE = 1;      // Slave Select Pull High
    if (int_enable)
    {
        NVIC_ClearPendingIRQ(USARTA_IRQn);
        NVIC_EnableIRQ(USARTA_IRQn);
    }
    PAC55XX_SSPA->CON.SSPEN = enable;        // SSP Enable	
}

RAMFUNC_SOCBRIDGE void pac5xxx_socbridge_config_io(void)
{

    // ICBSS:    PAMUXSEL.P6 = 001b (PA6 - output)
    // ICBMISO:  PAMUXSEL.P5 = 001b (PA5 - input)
    // ICBMOSI:  PAMUXSEL.P4 = 001b (PA4 - output)
    // ICBCLK:   PAMUXSEL.P3 = 001b (PA3 - output)

    PAC55XX_SCC->PAMUXSEL.w &= 0xF0000FFF;      // Clear PMUX for SSP bits
    PAC55XX_SCC->PAMUXSEL.w |= 0x01111000;      // PA6 = ICBSS, PA5 = ICBMISO, PA4 = ICBMOSI, PA3 = ICBCLK

    // Select SSP peripherals
    PAC55XX_GPIOA->MODE.P3 = 1;                 // SCLK
    PAC55XX_GPIOA->MODE.P6 = 1;                 // SS
    PAC55XX_GPIOA->MODE.P4 = 1;                 // MOSI
    PAC55XX_GPIOA->MODE.P5 = 3;                 // MISO
}
