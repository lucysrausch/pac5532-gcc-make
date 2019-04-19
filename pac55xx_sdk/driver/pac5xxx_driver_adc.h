/**************************************************************************//**
 * @file     pac5xxx_driver_adc.h
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
 
#ifndef PAC5XXX_DRIVER_ADC_H
#define PAC5XXX_DRIVER_ADC_H

/** @addtogroup PAC5XXX_Driver_ADC PAC5XXX ADC
  @{
*/

#include "pac5xxx.h"
#include "pac5xxx_driver_config.h"

#ifdef PAC5XXX_DRIVER_ADC_RAM
#define RAMFUNC_ADC	PAC5XXX_RAMFUNC
#else 
#define RAMFUNC_ADC
#endif

/**
 * @brief  This function starts an ADC Conversion with the current configuration
 *
 * @return none
 */
static inline void pac5xxx_adc_start(void) { PAC55XX_ADC->ADCCTL.START = 1; }

/**
 * @brief  This function sets the enable state of the ADC
 *
 * @param  enable If set to a 1, enables the ADC. If set to a 0, disables the ADC
 * @return none
 */
RAMFUNC_ADC static inline void pac5xxx_adc_enable(int enable) { PAC55XX_ADC->ADCCTL.ENABLE = enable; }

/**
 * @brief  This function configures the EMUX IO ports on the device for EMUX output
 *
 * @return none
 *
 */
RAMFUNC_ADC void pac5xxx_adc_config_emux_io(void);

/**
 * @brief  This function configures the IO ports on the device for the given ADC channels
 *
 * @param  channel_mask Bit-mask of the ADC channels to enable or disable IOs for
 * @return none
 *
 */
RAMFUNC_ADC void pac5xxx_adc_config_io(uint8_t channel_mask);

// EMUX SUPPORT

RAMFUNC_ADC void pac5xxx_adc_emux_config(ADC_EMUX_CTL_TYPE control_type, ADCEMUXCTL_DIV_TYPE divider);
	
RAMFUNC_ADC void pac5xxx_adc_config(ADCCTL_MODE_TYPE adc_mode, ADCCTL_CLKDIV_Type clock_divider, int repeat);

/**
 * @brief  This function configures the DTSE Sequence Config Table
 *
 * @param  DTSE_SEQ_CFG_TYPEDEF, EMUXC, CHANNEL, DELAY, SEQDONE, EMUXD, IRQNUM, IRQEN, NOCVT
 * @return none
 *
 */
RAMFUNC_ADC void pac5xxx_dtse_seq_config_table(DTSE_SEQ_CFG_TYPEDEF *ptr_seq_config_table, unsigned int emuxc, unsigned int channel,
											                         unsigned int delay, unsigned int seq_done, unsigned int emux_data,
                                               unsigned int irq_number, unsigned int irq_enable, unsigned int no_conversion);
																								 
/*@}*/ /* end of group PAC5XXX_Driver_ADC */

#endif // PAC5XXX_DRIVER_ADC_H
