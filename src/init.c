/****************************************************************************
 * @file     init.c
 * @brief    BLDC Initialization
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

void app_init(void)
{
	last_sample_stored = 0;						// Last good commutation state sample store

	hp_over_current_limit = HP_OCP_DEF;
	lp_over_current_limit = LP_OCP_DEF;

	sample_delay = SAMPLE_DELAY_DEF;
	PAC55XX_TIMERA->CCTR2.CTR = sample_delay;

	closed_loop_speed_hz = START_SPEED_HZ << 16;
	speed_ref_command = HertzToTicks(closed_loop_speed_hz, (TIMER_D_FREQ_F16 >> timer_d_div));
	speed_ref_ticks = speed_ref_command;
	speed_ref_command_hz = START_SPEED_HZ;
	speed_ref_hz = speed_ref_command_hz;

	blanking_cycles = START_BLANKING_CYCLES;
	good_samples = START_GOOD_SAMPLES;

	SMS_Counter = 0;
	SMS_State = SMS_Idle;

	start_iq_ref = START_IQ_REF_DEF;
	align_time_ms = ALIGN_TIME_MS_DEF;
	ol_start_hz = OL_START_HZ_DEF;
	ol_switchover_hz = OL_SWITCHOVER_HZ_DEF;

	ol_accel_period = DEFAULT_OL_ACCEL_PERIOD;
	ol_accel_increase = DEFAULT_OL_ACCEL_INC;

	sine_scale_max = SCALE_PERCENT;
	sine_scale = (fix16_mul_new_16_16(pwm_period_ticks << 16, sine_scale_max)) >> 16;

	cl_accel_period = DEFAULT_CL_ACCEL_PERIOD;
	cl_accel_increase = DEFAULT_CL_ACCEL_INC;
	tmp_cl_accel = 0;

	commutation_advanced_rise = ADV_DLY_DEF << 16;
	commutation_advanced_fall = ADV_DLY_DEF << 16;

	commutation_advanced_rise = fix16_mul_new_16_16(commutation_advanced_rise, HALF_DEGREE_ADV_DLY);
	commutation_advanced_fall = fix16_mul_new_16_16(commutation_advanced_fall, HALF_DEGREE_ADV_DLY);

	open_loop = 1;
	sine_mode = 1;

	vin_check_debounce = VIN_CHECK_DEB_MAX;

	millisecond = 0;

	beep_freq_hz = BEEP_FREQ_HZ_DEF;
	beep_pwm_dc = BEEP_PWM_DC_DEF;

	enable_speed_pi = 1;
	
	switchover = 1;

	tmp_current_min = IQ_PI_MIN;
	tmp_current_max = IQ_PI_MAX;
}

/**
 * @brief  This function Initializes the PI Loops
 *
 * @return none
 *
 */

void pi_init(void)
{

#if IREG
	iq_pid.Kp = IQ_PI_KP;
	iq_pid.Ki = IQ_PI_KI;
	iq_pid.min_value = fix16_mul_new_16_16(tmp_current_min, pwm_period_ticks << 16);
	iq_pid.PI_sat = iq_pid.min_value;
	iq_pid.I_prev = iq_pid.min_value;
	iq_pid.max_value = fix16_mul_new_16_16(tmp_current_max, pwm_period_ticks << 16);

	iq_pid.Td = fix16_div(IQ_PI_TD, (app_pwm_period << 16));	//1024 / (PWM_FREQ_KHZ * ADC_FREQ)
	iq_pid.Td = fix16_mul_new_16_16(iq_pid.Td, iq_pid.Ki);		//IQ PID TD must include both the TD as well as the KI

	speed_pid.Td = SPEED_PI_TD;
	speed_pid.Kp = SPEED_PI_KP;
	speed_pid.Ki = SPEED_PI_KI;
	speed_pid.min_value = FIX16(SPEED_PI_MIN);
	speed_pid.max_value = FIX16(SPEED_PI_MAX);

	speed_pid.Td = fix16_mul_new_16_16(speed_pid.Td, speed_pid.Ki);

#else
	speed_pid.Td = SPEED_PI_TD;
	speed_pid.Kp = IQ_PI_KP;
	speed_pid.Ki = IQ_PI_KI;
	speed_pid.min_value = fix16_mul_new_16_16(tmp_current_min, pwm_period_ticks << 16);
	speed_pid.PI_sat = iq_pid.min_value;
	speed_pid.I_prev = iq_pid.min_value;
	speed_pid.max_value = fix16_mul_new_16_16(tmp_current_max, pwm_period_ticks << 16);

	speed_pid.Td = fix16_mul_new_16_16(speed_pid.Td, speed_pid.Ki);
#endif
}

/**
 * @brief  This function configures the UART Serial Communications Block
 *
 * @return none
 *
 */
void UART_init(void)
{
	// Configure UART C (Expects 150MHz PCLK)
	// Configure UART C (Depends on pclk input)
    PAC55XX_SCC->CCSCTL.USCMODE = 1;                // UART mode
    pac5xxx_uart_config_LCR2(PAC55XX_UARTC, UARTLCR_WL_BPC_8, UART_STOP_BITS_1, UART_PEN_DISABLE, UART_PARITY_FORCE_STICK_1, UART_BRKCTL_DISABLE);
    pac5xxx_uart_config_divisor_latch2(PAC55XX_UARTC, 27);    // 115kbps = PCLK / (16 * DLR)
	pac5xxx_uart_rx_fifo_threshold2(PAC55XX_UARTC, UARTFCR_TL_1B);
    pac5xxx_uart_tx_fifo_threshold2(PAC55XX_UARTC, UARTFCR_TL_1B);
	pac5xxx_uart_int_enable_RDAI2(PAC55XX_UARTC, 1); 
	pac5xxx_uart_int_enable_THREI2(PAC55XX_UARTC, 1);
	pac5xxx_uart_io_config2();
    NVIC_ClearPendingIRQ(USARTC_IRQn);	
    NVIC_SetPriority(USARTC_IRQn,3);
    NVIC_EnableIRQ(USARTC_IRQn);
}
/*
 *
 * Configure ADC sampling engine:
 * =============================
 *
 * 	  Mode: 		Independent AS0 Trigger
 *    Repeat: 		on
 *    Divider:		/3 (PLLCLK = 50MHz/3 = 16.66MHz)
 *    Seq time: 	15 clocks (13 convert, 1 copy, 1 state machine switch) * (1/16.66MHz) = 0.9us
 *
 *    Emux Divider:	/2 (HCLK = 50MHz/2 = 25MHz)
 *
 *    AS0 Series:	Trigger: PWMC0
 *
 *    Seq #			Signal				Time offset (conversion to AS1 trigger/period end)
 *    -----------------------------------------------------------------------------------------
 *     Seq 0: 		HBI	 				-4.0 us
 *
 */
void adc_init(void)
{
	pac5xxx_adc_enable(0);
	// EMUX configuration
	pac5xxx_adc_emux_config(ADCEMUXCTL_DTSE_SEQ, ADCEMUXCTL_EMUXDIV_DIV16);	 		// Configure EMUX to do conversions from ADC sequencer, /2 EMUX divider (HCLK=50MHz/2 = 25MHz)
	pac5xxx_adc_config_emux_io();													// Configure device IO for EMUX

	//ADC configuration
	pac5xxx_adc_config(ADCCTL_MODE_DTSE, ADCCTL_CLKDIV_DIV8, 0);		// Configure ADC for ASC0 independent trigger sequence, /3 divider (PLLCLK=100MHz/3=16.66MHz), repeat mode
	pac5xxx_adc_config_io(ADC_CHANNEL_MASK);										// Configure device IO for ADC conversions (as Analog inputs)
	PAC55XX_GPIOF->MODE.P6 = 0;                     // ADC INPUT
	//AS0 configuration
	
	//pac5xxx_adc_config_pwm()
	PAC55XX_ADC->DTSETRIGENT0TO3.TRIG2CFGIDX = 0;						//PWMA2 triggers a sequence starting with element 0
	PAC55XX_ADC->DTSETRIGENT0TO3.TRIG2EDGE = ADCDTSE_TRIGEDGE_FALLING;

	//void pac55xx_adc_dtse_element_config(DTSE_SEQ_CFG_TYPEDEF * reg_add, int sel_emuxc, int adc_channel, int delay, int EMUX_data, int NoConv, int Seq_done, int IRQ_number, int IRQ_enable)
	pac55xx_adc_dtse_element_config((DTSE_SEQ_CFG_TYPEDEF *) &PAC55XX_ADC->DTSESEQCFG0.w, DTSESEQCFG_EMUXC_BSH, ADCCTL_CHANNEL_ADC6, 0, ADC_SEQ_HBU_EDATA, 0, 0, ADCDTSE_IRQNUM_ADC0, 0);	// Convert VIN - Dummy EMUX
	pac55xx_adc_dtse_element_config((DTSE_SEQ_CFG_TYPEDEF *) &PAC55XX_ADC->DTSESEQCFG1.w, DTSESEQCFG_EMUXC_BSH, ADCCTL_CHANNEL_ADC0, 0, ADC_SEQ_HBU_EDATA, 0, 0, ADCDTSE_IRQNUM_ADC0, 0);	// RSU - Dummy EMUX
	pac55xx_adc_dtse_element_config((DTSE_SEQ_CFG_TYPEDEF *) &PAC55XX_ADC->DTSESEQCFG2.w, DTSESEQCFG_EMUXC_BSH, ADCCTL_CHANNEL_ADC0, 0, ADC_SEQ_HBV_EDATA, 0, 0, ADCDTSE_IRQNUM_ADC0, 0);	// Convert RSU
	pac55xx_adc_dtse_element_config((DTSE_SEQ_CFG_TYPEDEF *) &PAC55XX_ADC->DTSESEQCFG3.w, DTSESEQCFG_EMUXC_BSH, ADCCTL_CHANNEL_ADC0, 0, ADC_SEQ_HBV_EDATA, 0, 0, ADCDTSE_IRQNUM_ADC0, 0);	// RSV - Dummy EMUX
	pac55xx_adc_dtse_element_config((DTSE_SEQ_CFG_TYPEDEF *) &PAC55XX_ADC->DTSESEQCFG4.w, DTSESEQCFG_EMUXC_BSH, ADCCTL_CHANNEL_ADC0, 0, ADC_SEQ_HBW_EDATA, 0, 0, ADCDTSE_IRQNUM_ADC0, 0);	// Convert RSV
	pac55xx_adc_dtse_element_config((DTSE_SEQ_CFG_TYPEDEF *) &PAC55XX_ADC->DTSESEQCFG5.w, DTSESEQCFG_EMUXC_BSH, ADCCTL_CHANNEL_ADC0, 0, ADC_SEQ_HBW_EDATA, 0, 0, ADCDTSE_IRQNUM_ADC0, 0);	// RSw - Dummy EMUX
	pac55xx_adc_dtse_element_config((DTSE_SEQ_CFG_TYPEDEF *) &PAC55XX_ADC->DTSESEQCFG6.w, DTSESEQCFG_EMUXC_BSH, ADCCTL_CHANNEL_ADC0, 0, ADC_SEQ_HBU_EDATA, 0, 1, ADCDTSE_IRQNUM_ADC0, 1);	// Convert RSW

	// Enable ADC interrupts on AS0 for control loop
	NVIC_SetPriority(ADC0_IRQn, 2);													// Configure interrupt priority
	NVIC_EnableIRQ(ADC0_IRQn);														// Enable ADC interrupts in the NVIC

	// Enable ADC
	pac5xxx_adc_enable(1);
	pac5xxx_adc_start();
}

/**
 * @brief  This function configures PAC analog peripheral
 *
 * @return none
 *
 */
void cafe_init(void)
{
	// Configure SOC Bridge for talking to MC02
	pac5xxx_tile_socbridge_config(1, 0);						// enable, int_enable

	// Write all CAFE registers
	if (pac5xxx_tile_register_read(ADDR_STATUS))				// If any power manager error bits set on startup, clear them
		{
		//Add desired checks here and then clear
		pac5xxx_tile_register_write(ADDR_STATUS, 0xFF);
		}

	pac5xxx_tile_register_write(ADDR_PWRCTL, 0x04);

	// Set HPROT protection threshold
	pac5xxx_tile_register_write(ADDR_HPDACH, hp_over_current_limit >> 2);
	pac5xxx_tile_register_write(ADDR_HPDACL, hp_over_current_limit & 0x03);

	// Set LPROT protection threshold
	pac5xxx_tile_register_write(ADDR_LPDACH, lp_over_current_limit >> 2);
	pac5xxx_tile_register_write(ADDR_LPDACL, lp_over_current_limit & 0x03);

	// Enable Module - Must be done before configuring Diff Amp and OCP Protection Scheme
	module_enable_bits = MODULE_ENABLE_FLAGS_DEF;
	pac5xxx_tile_register_write(ADDR_MISC, module_enable_bits);

	// Configure AIOxx for ADC sampling with OC protection
	pac5xxx_tile_register_write(ADDR_CFGAIO0, 0x40 + (DIFFAMP_GAIN_OPT0 << 3) + HPOPT_SEL);			// AIO10: DiffAmp, 16X gain, LPOPT (4 us)
	pac5xxx_tile_register_write(ADDR_CFGAIO1, 0x30 + LPOPT_SEL);			// AIO10: nHP10PR1M set, NO ENOS10, HPOPT (4us)

	pac5xxx_tile_register_write(ADDR_CFGAIO2, 0x40 + (DIFFAMP_GAIN_OPT0 << 3) + HPOPT_SEL);			// AIO32: DiffAmp, 16X gain, LPOPT (4 us)
	pac5xxx_tile_register_write(ADDR_CFGAIO3, 0x30 + LPOPT_SEL);			// AIO32: nHP32PR1M set, NO ENOS32, HPOPT (4us)

	pac5xxx_tile_register_write(ADDR_CFGAIO4, 0x40 + (DIFFAMP_GAIN_OPT0 << 3) + HPOPT_SEL);			// AIO54: DiffAmp, 16X gain, LPOPT (4 us)
	pac5xxx_tile_register_write(ADDR_CFGAIO5, 0x30 + LPOPT_SEL);			// AIO54: nHP54PR1M set, NO ENOS54, HPOPT (4us)

	// Enable protection interrupt mask
	// PROTINTM: nHP54INTM, nHP32INTM, nHP10INTM
	pac5xxx_tile_register_write(ADDR_PROTINTM, PROTINTM_MASK);

	// Disable both HS and LS drivers on PR event (nHSPRM=1, nLSPRM=1);
	// Prop Delay 0 ns; Enable Break Before Make
	pac5xxx_tile_register_write(ADDR_CFGDRV1, 0x0F); //0x0D
	// Cycle By Cycle on Diff Amp AIO10/32/54. Disable only high side
	pac5xxx_tile_register_write(ADDR_CFGDRV2, 0x1D);
	// Cycle By Cycle on Diff Amp AIO10/32/54 compared against LPDAC
	pac5xxx_tile_register_write(ADDR_CFGDRV3, 0x54);

	//Configure Blanking Time Feature
	pac5xxx_tile_register_write(ADDR_BLANKING, BLANKING_CONFIG);

	// Set HP comparator hysteresis (HPROTHYS=1b, LPROTHYS=1b)
	pac5xxx_tile_register_write(ADDR_SIGSET, 0x0C);

	//Configure Sensorless Comparators
	pac5xxx_tile_register_write(ADDR_CFGAIO6, 0x26);

	pac5xxx_tile_register_write(ADDR_CFGAIO7, (0xC0 + COMP_POL));			// MODE7[1:0] = 11b (special mode)
	pac5xxx_tile_register_write(ADDR_CFGAIO8, (0xD0 + COMP_POL));			// MODE8[1:0] = 11b (special mode), OPT8[1:0] = 01b (bypass FF, select MUX out for nIRQ2/POS), POL8 = 0 (act high), MUX[2:0] = n/a
	pac5xxx_tile_register_write(ADDR_CFGAIO9, SLCOMP7);			// MODE9[1:0] = 01b (CT Vfilt), OPT9[1:0] = 0bxx (AIO7), POL9 = 0 (act high), MUX[2:0] = n/a

	// HYSMODE[7] = 1b (0/20/40/80), HYSAIO7[3:0] = 1010b (40/40)
	pac5xxx_tile_register_write(ADDR_SPECCFG0, SPECCFG0_CONFIG);
	// HYSAIO8[7:4] = 1010b (40/40), HYSAIO9[3:0] = 1010b (40/40)
	pac5xxx_tile_register_write(ADDR_SPECCFG1, SPECCFG1_CONFIG);

	// SMUXAIO7[3:0] = 01b (AB1 as COMP-), SMUXAIO8[3:0] = 01b (AB1 as COMP-)
	pac5xxx_tile_register_write(ADDR_SPECCFG2, 0x11);
	// SMUXAIO9[3:0] = 01b (AB1 as COMP-)
	pac5xxx_tile_register_write(ADDR_SPECCFG3, 0x10);

	// ADCBUFEN=1 to enable ADC buffer, SCANEN=1 for auto-scan
	pac5xxx_tile_register_write(ADDR_SHCFG1, 0x18);

	// Enable Drivers
	pac5xxx_tile_register_write(ADDR_ENDRV, 0x01);

}
