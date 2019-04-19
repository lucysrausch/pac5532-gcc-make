/****************************************************************************
 * @file     bldc_common.c
 * @brief    Support functions for all BLDC Algorithms
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
#define INCLUDE_EXTERNS
#include "bldc_common.h"

/**
 * @brief  This is the interrupt handler for the SysTick which will be used to generate 1 ms periodic pulses to
 * 			run the main loop state machine.
 *
 * @return none
 *
 */
void SysTick_Handler(void)
{
	millisecond = 1;
}

/**
 * @brief  This is the interrupt handler for GPIOA, which is where the IRQ1 pin
 *         resides.
 *
 *
 * @return none
 */

void GpioA_IRQHandler(void)
{

	if (PAC55XX_GPIOA->INTFLAGMASKED.w & NIRQ1_PIN_MASK)
		{
		oc_flags = pac5xxx_tile_register_read(ADDR_PROTSTAT);	
			
			
		motor_pwm_disable();
		app_status |= status_over_current;
		PAC55XX_GPIOA->INTCLEAR.P7 = 1;
		PAC55XX_TIMERD->CCTL0.CCINTEN = 0;
		}
}

/**
 * @brief	This function configures dead time.
 *
 * @return none
 *
 */

void Set_Dead_Time(void)
{
	// Configure Hardware Dead time Generator
	pac5xxx_dtg_config2(&(PAC55XX_TIMERA->DTGCTL0), dt_leading_ticks, dt_trailing_ticks);				// Configure DTGA0
	pac5xxx_dtg_config2(&(PAC55XX_TIMERA->DTGCTL1), dt_leading_ticks, dt_trailing_ticks);				// Configure DTGA1
	pac5xxx_dtg_config2(&(PAC55XX_TIMERA->DTGCTL2), dt_leading_ticks, dt_trailing_ticks);				// Configure DTGA2
}

/**
 * @brief	This function clears Over Current Events and re-enables the power manager.
 *
 * @return none
 *
 */
void oc_reset(void)
{
	uint16_t register_val;

	// Disable global interrupts until OC reset is complete
	__disable_irq();

	// Clear int/fault flags
	pac5xxx_tile_register_write(ADDR_PROTINTM, 0x00);
	while (pac5xxx_tile_register_read(ADDR_PROTSTAT))
		{
		pac5xxx_tile_register_write(ADDR_PROTSTAT, PROTINTM_MASK);	
		}
	pac5xxx_tile_register_write(ADDR_PROTINTM, PROTINTM_MASK);
	// Disable driver
	do {
		pac5xxx_tile_register_write(ADDR_ENDRV, 0);
		register_val = pac5xxx_tile_register_read(ADDR_ENDRV);
	} while ((register_val&0x1) != 0x0);


	// Enable global interrupts
	__enable_irq();

	pac5xxx_tile_register_write(ADDR_ENDRV, 1);

	// Update status
	app_status &= ~(status_motor_enabled + status_over_current + status_motor_stalled);
	oc_flags = 0;

	// Turn back on ADC and start for control processing. Motor still disabled until UART command.
	pac5xxx_adc_enable(1);

	pac5xxx_adc_start();
}

/**
 * @brief	This function transforms the motor speed in Hz to the respective number of clock cycles required
 * 			The equation on this function is # ticks = PWM_FREQ / (6 * SpeedInHz)
 * 			The PWM_FREQ (units is KHz) is programmable and is computed in the UART module
 *
 * @return 	The number of clock cycles corresponding to the desired frequency
 *
 */

APP_RAMFUNC fix16_t HertzToTicks(fix16_t Hertz, uint32_t Freq)
{
	fix16_t tmp;
	tmp = fix16_mul_new_16_16(6 << 16, Hertz);						// Hz * 6 commutation states
	tmp = fix16_div(Freq, tmp);
	return tmp << 10; 												// Converted to fix16 after multiplying by 1024
}

fix16_t HertzToTicksSine(fix16_t Hertz, uint32_t Freq)
{
	fix16_t tmp;
	tmp = fix16_mul_new_16_16(360 << 16, Hertz);						// Hz * 6 commutation states
	tmp = fix16_div(Freq, tmp);
	return tmp << 10; 												// Converted to fix16 after multiplying by 1024

}

/**
 * @brief	This function gets the ADC conversions for the VIN scaler and the potentiometer
 *
 * @return 	NONE
 *
 */
void check_adc(void)
{
	vin_volts = fix16_mul_new_16_16((VIN_VOLTS_VAL << 16), VOLT_DIV_FIX16);
}

/**
 * @brief	This function checks the VIN scaled voltage and determines whether there is
 * 			enough battery voltage to maintain motor operational. When battery voltage is below
 * 			threshold, the motor is disabled.
 *
 * @return 	NONE
 *
 */

void check_vbat(void)
{
	if (vin_volts < VIN_VOLTS_LEGAL)
		{
		vin_check_debounce--;
		if (vin_check_debounce <= 0)
			{
			if (app_status & status_motor_enabled)
				{
				motor_pwm_disable();
				}
			app_status |= status_under_voltage;
			}
		}
	else
		{
		vin_check_debounce++;
		if (vin_check_debounce > VIN_CHECK_DEB_MAX)
			{
			vin_check_debounce = VIN_CHECK_DEB_MAX;
			app_status &= ~status_under_voltage;
			}
		}
}

/**
 * @brief	This function configures the H Bridge as a speaker driver and enables the motor
 * 			to apply a beep sound at the frequency of the musical notes denoted from 0 to 127
 *
 * @return 	NONE
 *
 */

void beep_on(int note)
{
	app_status &= ~status_motor_stalled;

	PAC55XX_TIMERA->CCTR4.CTR = beep_pwm_dc;
	PAC55XX_TIMERA->CCTR5.CTR = beep_pwm_dc;
	PAC55XX_TIMERA->CCTR6.CTR = beep_pwm_dc;
	
	sl_current_state = 0;

	PAC55XX_GPIOB->OUT.w = c_pwm_io_state[sl_current_state];
	PAC55XX_SCC->PBMUXSEL.w = psel_mask[sl_current_state];	        // Set peripheral select state
	
	sl_current_state++;

	app_status |= status_motor_enabled;
	open_loop = 1;
	sine_mode = 0;

	pac5xxx_timer_base_config(TimerD, beep_notes[note], 0, TxCTL_MODE_UP, 0);
	PAC55XX_TIMERD->CTL.BASEIE = 1;									// Enable Timer D Base Interrupt
	NVIC_EnableIRQ(TimerD_IRQn);
}

/**
 * @brief	This function disables the H Bridge and stops the sound function
 *
 * @return 	NONE
 *
 */

void beep_off(void)
{
	PAC55XX_GPIOB->OUT.w = 0;			//PORTB OUT GPIO = 0;
	PAC55XX_SCC->PBMUXSEL.w = 0;		//PORTB PSEL is ALL GPIO's
	app_status &= ~status_motor_enabled;
	PAC55XX_TIMERD->CTL.BASEIE = 0;
	NVIC_DisableIRQ(TimerD_IRQn);
	SMS_State = SMS_Idle;

}

/**
 * @brief	This function configures the ADC DTSE Sequence Element
 *
 * @return 	NONE
 *
 */

void pac55xx_adc_dtse_element_config(DTSE_SEQ_CFG_TYPEDEF * reg_add, int sel_emuxc, int adc_channel, int delay, int EMUX_data, int NoConv, int Seq_done, int IRQ_number, int IRQ_enable)
{
	reg_add->EMUXC = sel_emuxc;
	reg_add->CHANNEL = adc_channel;
	reg_add->DELAY = delay;
	reg_add->SEQDONE = Seq_done;
	reg_add->EMUXD = EMUX_data;
	reg_add->IRQNUM = IRQ_number;
	reg_add->IRQEN = IRQ_enable;
	reg_add->NOCVT = NoConv;
}
