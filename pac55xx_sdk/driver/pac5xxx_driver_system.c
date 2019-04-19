/**************************************************************************//**
 * @file     pac5xxx_driver_system_ccs_config.c
 * @brief    Firmware driver for the PAC5XXX System Clock Control
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

#include "pac5xxx_driver_system.h"


RAMFUNC_SYSTEM void pac5xxx_sys_pll_config_enable(uint32_t pllindiv, uint32_t pllfbdiv, uint32_t plloutdiv)
{
    //  Configure PLL control reg and enable PLL
    PAC55XX_SCC->CCSPLLCTL.PLLEN = 0;
    PAC55XX_SCC->CCSPLLCTL.PLLFBDIV = pllfbdiv;
    PAC55XX_SCC->CCSPLLCTL.PLLOUTDIV = plloutdiv;
    PAC55XX_SCC->CCSPLLCTL.PLLINDIV = pllindiv;
    PAC55XX_SCC->CCSPLLCTL.PLLEN = 1;
    // Wait for Lock
    while(PAC55XX_SCC->CCSPLLCTL.PLLLOCK == 0);
}
