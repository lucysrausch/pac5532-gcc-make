/**************************************************************************//**
 * @file     pac5xxx_driver_adc.c
 * @brief    Firmware driver for the PAC5XXX ADC
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

#include "pac5xxx_driver_adc.h"

RAMFUNC_ADC void pac5xxx_adc_config_emux_io()
{
    PAC55XX_SCC->PAMUXSEL.P1 = 1;       // EMUX Data   EMUXD
    PAC55XX_SCC->PAMUXSEL.P2 = 1;       // EMUX Clock  EMUXC
    PAC55XX_GPIOA->MODE.P1 = 1;         // GPIOA1 Push and Pull output
    PAC55XX_GPIOA->MODE.P2 = 1;         // GPIOA2 Push and Pull output	
}

RAMFUNC_ADC void pac5xxx_adc_config_io(unsigned char channel_mask)
{
    if ((channel_mask & 0x01) == 0x01)
    {
        PAC55XX_SCC->PGMUXSEL.P7 = 0;   // GPIOG7 ADCIN0
        PAC55XX_GPIOG->MODE.P7 = 0;     // GPIOG7 ADCIN0
    }
        
    if ((channel_mask & 0x02) == 0x02)
    {
        PAC55XX_SCC->PDMUXSEL.P3 = 0;   // GPIOD3 ADCIN1
        PAC55XX_GPIOD->MODE.P3 = 0;     // GPIOD3 ADCIN1

//        PAC55XX_SCC->PGMUXSEL.P5 = 0;   // GPIOG5 ADCIN1
//        PAC55XX_GPIOG->MODE.P5 = 0;     // GPIOG5 ADCIN1
    }
    
    if ((channel_mask & 0x04) == 0x04)
    {
        PAC55XX_SCC->PDMUXSEL.P2 = 0;   // GPIOD2 ADCIN2
        PAC55XX_GPIOD->MODE.P2 = 0;     // GPIOD2 ADCIN2

//        PAC55XX_SCC->PGMUXSEL.P6 = 0;   // GPIOG6 ADCIN2
//        PAC55XX_GPIOG->MODE.P6 = 0;     // GPIOG6 ADCIN2
    }

    if ((channel_mask & 0x08) == 0x08)
    {
        PAC55XX_SCC->PDMUXSEL.P1 = 0;   // GPIOD1 ADCIN3
        PAC55XX_GPIOD->MODE.P1 = 0;     // GPIOD1 ADCIN3
    }        
    
    if ((channel_mask & 0x10) == 0x10)
    {
        PAC55XX_SCC->PFMUXSEL.P4 = 0;   // GPIOF4 ADCIN4
        PAC55XX_GPIOF->MODE.P4 = 0;     // GPIOF4 ADCIN4

//        PAC55XX_SCC->PDMUXSEL.P0 = 0;   // GPIOD0 ADCIN4
//        PAC55XX_GPIOD->MODE.P0 = 0;     // GPIOD0 ADCIN4
    }            

    if ((channel_mask & 0x20) == 0x20)
    {
        PAC55XX_SCC->PFMUXSEL.P5 = 0;   // GPIOF5 ADCIN5
        PAC55XX_GPIOF->MODE.P5 = 0;     // GPIOF5 ADCIN5
    }            
 
    if ((channel_mask & 0x40) == 0x40)
    {
        PAC55XX_SCC->PFMUXSEL.P6 = 0;   // GPIOF6 ADCIN6
        PAC55XX_GPIOF->MODE.P6 = 0;     // GPIOF6 ADCIN6
    }            

    if ((channel_mask & 0x80) == 0x80)
    {
        PAC55XX_SCC->PFMUXSEL.P7 = 0;   // GPIOF7 ADCIN7
        PAC55XX_GPIOF->MODE.P7 = 0;     // GPIOF7 ADCIN7
    }
}

RAMFUNC_ADC void pac5xxx_adc_emux_config(ADC_EMUX_CTL_TYPE control_type, ADCEMUXCTL_DIV_TYPE divider)
{
	PAC55XX_ADC->EMUXCTL.EMUXMODE = control_type;
	PAC55XX_ADC->EMUXCTL.EMUXDIV = divider;
}

RAMFUNC_ADC void pac5xxx_adc_config(ADCCTL_MODE_TYPE adc_mode, ADCCTL_CLKDIV_Type clock_divider, int repeat)
{
	PAC55XX_ADC->ADCCTL.MODE = adc_mode;
	PAC55XX_ADC->ADCCTL.ADCDIV = clock_divider;
	PAC55XX_ADC->ADCCTL.REPEAT = repeat;
}

RAMFUNC_ADC void pac5xxx_dtse_seq_config_table(DTSE_SEQ_CFG_TYPEDEF *ptr_seq_config_table, unsigned int emuxc, unsigned int channel,
											                         unsigned int delay, unsigned int seq_done, unsigned int emux_data,
                                               unsigned int irq_number, unsigned int irq_enable, unsigned int no_conversion)
{
    ptr_seq_config_table->EMUXC = emuxc;
    ptr_seq_config_table->CHANNEL = channel;
    ptr_seq_config_table->DELAY = delay;
    ptr_seq_config_table->SEQDONE = seq_done;
    ptr_seq_config_table->EMUXD = emux_data;
    ptr_seq_config_table->IRQNUM = irq_number;
    ptr_seq_config_table->IRQEN = irq_enable;
    ptr_seq_config_table->NOCVT = no_conversion;
}
