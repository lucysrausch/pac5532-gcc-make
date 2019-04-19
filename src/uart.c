/****************************************************************************
 * @file     uart.c
 * @brief    Peripheral and initialization routines for the application.
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

static int uart_rx_byte_count = 0;
static int uart_tx_byte_count = 0;

uint8_t uart_rx_buffer[UART_MESSAGE_SIZE];
uint8_t uart_tx_buffer[UART_MESSAGE_SIZE];

Uart_Status uart_message_process(void);
static uint8_t uart_checksum(uint8_t* pBuffer);
static void int_to_buffer(uint32_t data);

// ENUMs

enum Uart_Message_Code
{
    cmd_version,
    cmd_set_address,
    cmd_read_word,
    cmd_write_word,
    cmd_set_buffer,
    cmd_parameter_read,
    cmd_parameter_write,
    cmd_cafe_reg_read
};

enum Uart_Parameter_Code
{
	// status commands
    parm_status,								//1
    parm_debug_1,
    parm_debug_2,
    parm_debug_3,
    parm_debug_4,
    parm_pwm_period,
    parm_hp_over_current_limit,
    parm_lp_over_current_limit,
    parm_dt_leading_ticks,
    parm_dt_trailing_ticks,						//10
    parm_oc_reset,
    parm_timer_d_div,
    parm_sample_delay,
    parm_vpot,
    parm_vin,
    parm_blanking_cycles,
    parm_good_samples,
    parm_motor_speed,
    parm_iq_ref,
    parm_current_Kp,							//20
    parm_current_Ki,
    parm_current_min,
    parm_current_max,
    parm_speed_command,
    parm_speed_Kp,
    parm_speed_Ki,
    parm_speed_min,
    parm_speed_max,
    parm_ol_accel_period,
    parm_ol_accel_increase,						//30
    parm_on_off,
    parm_stall_detect_speed_hz,
    parm_stall_detect_time_ms,
    parm_commutation_advanced_rise_delay,
    parm_commutation_advanced_fall_delay,
    parm_start_iq_ref,
    parm_align_time_ms,
    parm_ol_start_hz,
    parm_ol_switchover_hz,
    parm_cl_accel_period,						//40
    parm_cl_accel_increase,
    parm_debug_array,
    parm_pi_debug_index,
    parm_pi_debug_error,
	parm_pi_debug_p,
    parm_pi_debug_i,
    parm_pi_debug_pi,
    parm_pi_debug_pisat,
    parm_speed_ref_command_hz,
    parm_beep_freq,								//50
    parm_beep_on,
    parm_beep_off,
    parm_enable_speed_pi,
    parm_hibernate,
    parm_switchover,
    parm_sine_scale,
    parm_hysteresis,
    parm_blanking
	
};

// Function declarations

extern Uart_Status uart_message_process(void);

Uart_Status uart_message_process(void)
{
	uint32_t rx_data;
	Uart_Status status = success;

	// Full message received in uart_rx_buffer, process and then queue up transmit (response) message

	uart_tx_buffer[0] = 0xEE;											/*!< Response message type is always 0xEE */
	uart_tx_buffer[1] = uart_rx_buffer[1] + 0x80;						/*!< Response message code is received message code + 0x80 */

	// Put data from uart_rx_buffer into word for processing

	rx_data = (uart_rx_buffer[4] << 24);
	rx_data |= (uart_rx_buffer[5] << 16);
	rx_data |= (uart_rx_buffer[6] << 8);
	rx_data |= uart_rx_buffer[7];

	// Validate checksum

	if (uart_checksum((uint8_t*)&uart_rx_buffer) != uart_rx_buffer[8])
	{
		status = checksum_error;								/*!< Put in checksum error */
		uart_tx_buffer[8] = uart_checksum((uint8_t*)&uart_tx_buffer);				/*!< Calculate checksum for outgoing message */
	}
	else
	{
		switch (uart_rx_buffer[1])			// Switch on command code
		{
		case cmd_version:
			uart_tx_buffer[5] = VERSION_TYPE;
			uart_tx_buffer[6] = VERSION_MAJOR;
			uart_tx_buffer[7] = VERSION_MINOR;
			break;

		case cmd_cafe_reg_read:
			uart_tx_buffer[4] = 0;
			uart_tx_buffer[5] = 0;
			uart_tx_buffer[6] = 0;
			uart_tx_buffer[7] = pac5xxx_tile_register_read(uart_rx_buffer[7]);
			break;
		case cmd_parameter_read:
			switch (uart_rx_buffer[2])
			{
			case parm_status:
				int_to_buffer(app_status);
				break;
			case parm_debug_1:
				int_to_buffer(debug_1);
				break;
			case parm_debug_2:
				int_to_buffer(debug_2);
				break;
			case parm_debug_3:
				int_to_buffer(debug_3);
				break;
			case parm_debug_4:
				int_to_buffer(debug_4);
				break;
			case parm_pwm_period:
				int_to_buffer(app_pwm_period);
				break;
			case parm_debug_array:
				int_to_buffer(debug_array[debug_index]);
				break;
			
			case parm_motor_speed:
				int_to_buffer(motorspeed);
			break;
			
			case parm_pi_debug_error:
				int_to_buffer(pi_debug_value[pi_debug_index][0]);
				break;
			case parm_pi_debug_p:
				int_to_buffer(pi_debug_value[pi_debug_index][1]);
				break;
			case parm_pi_debug_i:
				int_to_buffer(pi_debug_value[pi_debug_index][2]);
				break;
			case parm_pi_debug_pi:
				int_to_buffer(pi_debug_value[pi_debug_index][3]);
				break;
			case parm_pi_debug_pisat:
				int_to_buffer(pi_debug_value[pi_debug_index][4]);
				break;
			default:
				status = host_write_error;
			}

			break;
			
		case cmd_parameter_write:
		
			switch (uart_rx_buffer[2])
			{	
			case parm_pwm_period:

				if (rx_data != app_pwm_period)
				{
					app_pwm_period = rx_data >> 16;							//Number of KHz
					//PWM ticks = 100 MHz / PWM FREQ KHz. Since 100,000 is too large, app_pwm_period is shifted 17 instead of 16 = multiplying by 2.
					pwm_period_ticks = TIMER_A_FREQ_CNV / (app_pwm_period);			//100,000 / # KHz
					pac5xxx_timer_base_config(TimerA, pwm_period_ticks, 0, TxCTL_MODE_UP, 0);	// Configure Timer
					iq_pid.max_value = pwm_period_ticks << 16;

					//Update IQ PI TD
					iq_pid.Td = fix16_div(IQ_PI_TD, (app_pwm_period << 16));	//1024 / (PWM_FREQ_KHZ * ADC_FREQ)
					iq_pid.Td = fix16_mul_new_16_16(iq_pid.Td, iq_pid.Ki);		//IQ PID TD must include both the TD as well as the KI

					//Update IQ PI Min and Max
					iq_pid.min_value = fix16_mul_new_16_16(tmp_current_min, pwm_period_ticks << 16);
					iq_pid.max_value = fix16_mul_new_16_16(tmp_current_max, pwm_period_ticks << 16);
				}
				break;
			case parm_hp_over_current_limit:
				hp_over_current_limit = rx_data;
				pac5xxx_tile_register_write(ADDR_HPDACH, hp_over_current_limit >> 2);
				pac5xxx_tile_register_write(ADDR_HPDACL, hp_over_current_limit & 0x03);
				break;
			case parm_lp_over_current_limit:
				lp_over_current_limit = rx_data;
				pac5xxx_tile_register_write(ADDR_LPDACH, lp_over_current_limit >> 2);	// LPDAC: LPROT DAC (8b)
				pac5xxx_tile_register_write(ADDR_LPDACL, lp_over_current_limit & 0x03);	// LPDAC: LPROT DAC (1b)
				break;
			case parm_iq_ref:
				iq_ref = rx_data;
				break;
			case parm_current_Kp:
				iq_pid.Kp = rx_data;
				break;
			case parm_current_Ki:
				iq_pid.Ki = rx_data;
				iq_pid.Td = fix16_div(IQ_PI_TD, (app_pwm_period << 16));	//1024 / (PWM_FREQ_KHZ * ADC_FREQ)
				iq_pid.Td = fix16_mul_new_16_16(iq_pid.Td, iq_pid.Ki);		//IQ PID TD must include both the TD as well as the KI
				break;
			case parm_current_min:
				tmp_current_min = rx_data;
				iq_pid.min_value = fix16_mul_new_16_16(tmp_current_min, pwm_period_ticks << 16);
				break;
			case parm_current_max:
				tmp_current_max = rx_data;
				iq_pid.max_value = fix16_mul_new_16_16(tmp_current_max, pwm_period_ticks << 16);
				break;
			case parm_speed_command:
				closed_loop_speed_hz = rx_data;
				speed_ref_command = HertzToTicks(closed_loop_speed_hz, (TIMER_D_FREQ_F16 >> timer_d_div)) ;
				break;
			case parm_speed_Kp:
				speed_pid.Kp = rx_data;
				break;
			case parm_speed_Ki:
				speed_pid.Ki = rx_data;
				speed_pid.Td = SPEED_PI_TD;
				speed_pid.Td = fix16_mul_new_16_16(speed_pid.Td, speed_pid.Ki);		//SPEED PID TD must include both the TD as well as the KI
				break;
			case parm_speed_min:
				speed_pid.min_value = (rx_data) << 16;
				break;
			case parm_speed_max:
				speed_pid.max_value = (rx_data) << 16;
				break;
			case parm_dt_leading_ticks:
				dt_leading_ticks = rx_data >> 16;
				Set_Dead_Time();
				break;
			case parm_dt_trailing_ticks:
				dt_trailing_ticks = rx_data >> 16;
				Set_Dead_Time();
				break;
			case parm_oc_reset:
				oc_reset();
				break;
			case parm_timer_d_div:
				timer_d_div = rx_data >> 16;
				break;
			case parm_sample_delay:
				sample_delay = rx_data >> 16;
				PAC55XX_TIMERA->CCTR2.CTR = sample_delay;
				break;
			case parm_blanking_cycles:
				blanking_cycles = rx_data >> 16;
				break;
			case parm_good_samples:
				good_samples = rx_data >> 16;;
				break;
			case parm_ol_accel_period:
				ol_accel_period = rx_data >> 16;
				break;
			case parm_ol_accel_increase:
				ol_accel_increase = rx_data >> 16;
				break;
			case parm_on_off:
				if (rx_data)
					{
					SMS_State = SMS_Align;
					}
				else
					{
					motor_pwm_disable();
					}
				break;
			case parm_stall_detect_speed_hz:
				//
				break;
			case parm_stall_detect_time_ms:
				//
				break;
			case parm_commutation_advanced_rise_delay:
				__disable_irq();
				commutation_advanced_rise = rx_data;
				commutation_advanced_rise = fix16_mul_new_16_16(commutation_advanced_rise, HALF_DEGREE_ADV_DLY);
				__enable_irq();
				break;
			case parm_commutation_advanced_fall_delay:
				__disable_irq();
				commutation_advanced_fall = rx_data;
				commutation_advanced_fall = fix16_mul_new_16_16(commutation_advanced_fall, HALF_DEGREE_ADV_DLY);
				__enable_irq();
				break;
			case parm_start_iq_ref:
				start_iq_ref = rx_data >> 16;
				break;
			case parm_align_time_ms:
				align_time_ms = rx_data >> 16;
				break;
			case parm_ol_start_hz:
				ol_start_hz = rx_data >> 16;
				break;
			case parm_ol_switchover_hz:
				ol_switchover_hz = rx_data >> 16;
                break;
			case parm_debug_array:
				debug_index = rx_data >> 16;
				break;
			case parm_pi_debug_index:
				pi_debug_index = rx_data;
				break;
			case parm_speed_ref_command_hz:
				speed_ref_command_hz = rx_data >> 16;
				break;
			case parm_cl_accel_period:
				cl_accel_period = rx_data >> 16;
				break;
			case parm_cl_accel_increase:
				cl_accel_increase = rx_data >> 16;
				break;
			case parm_beep_freq:
				beep_freq_hz = rx_data >> 16;
				break;
			case parm_beep_on:
				SMS_State = SMS_Diag_Init;
				break;
			case parm_beep_off:
				SMS_State = SMS_Beep_OFF;
				break;
			case parm_enable_speed_pi:
				enable_speed_pi = rx_data;
				break;
			case parm_hibernate:
				//mcu_hibernate();
				break;
			case parm_switchover:
				switchover = rx_data >> 16;
				break;
			case parm_sine_scale:
				sine_scale_max = rx_data;
				sine_scale = (fix16_mul_new_16_16(pwm_period_ticks << 16, sine_scale_max)) >> 16;
				break;
			case parm_hysteresis:
				hysteresis = rx_data >> 16;
				__disable_irq();
				pac5xxx_tile_register_write(ADDR_SPECCFG0, (HYSMODE_0 + hysteresis));
				pac5xxx_tile_register_write(ADDR_SPECCFG1, ((hysteresis << 4) + hysteresis));
				__enable_irq();
				break;
			case parm_blanking:
				bemf_blanking = rx_data >> 16;
				__disable_irq();
				pac5xxx_tile_register_write(ADDR_BLANKING, (bemf_blanking << 4) + BLANKING_BOTH);
				__enable_irq();
				break;
			default:
				status = host_write_error;
			}

			break;

		default:
			status = host_write_error; 	/* Do not respond - invalid command */
		}
	}

	uart_tx_buffer[2] = status;
	uart_tx_buffer[8] = uart_checksum((uint8_t*)&uart_tx_buffer);				/*!< Calculate checksum for outgoing message */

	return status;
}

static uint8_t uart_checksum(uint8_t* pBuffer)
{
	uint8_t checksum = 0;
	int i;

	for (i = 0; i < 8; i++)
		checksum += *pBuffer++;

	return checksum;
}

static void int_to_buffer(uint32_t data)
{
	uart_tx_buffer[4] = ((data >> 24) & 0xFF);
	uart_tx_buffer[5] = ((data >> 16) & 0xFF);
	uart_tx_buffer[6] = ((data >> 8)  & 0xFF);
	uart_tx_buffer[7] = (data & 0xFF);
}

void USARTC_IRQHandler(void) 
{
	uint8_t int_type = pac5xxx_uart_interrupt_identification2(PAC55XX_UARTC);
    uint8_t data = pac5xxx_uart_read2(PAC55XX_UARTC);

    if (int_type == UARTIIR_INTID_TX_HOLD_EMPTY)
		{
		pac5xxx_uart_write2(PAC55XX_UARTC, uart_tx_buffer[uart_tx_byte_count++]);

        if (uart_tx_byte_count == UART_MESSAGE_SIZE)                // Last byte of message to transmit
			{
	        pac5xxx_uart_int_enable_THREI2(PAC55XX_UARTC, 0);        // Disable transmit interrupt
			pac5xxx_uart_int_enable_RDAI2(PAC55XX_UARTC, 1);         // Enable receive data interrupt for next incoming message
		  uart_tx_byte_count = 0;
			}
		}
    else
		{
        if (uart_rx_byte_count == 0)                                // For the first byte received, the start byte must be 0x89
			{
            if (data != 0x89)
                return;
			}

        uart_rx_buffer[uart_rx_byte_count++] = data;                // Store data in buffer and increment index

        if (uart_rx_byte_count == UART_MESSAGE_SIZE)                // Received all bytes of message
			{
            uart_message_process();                                 // Process incoming message in uart_rx_buffer and put response in uart_tx_buffer
			uart_rx_byte_count = 0;
            uart_tx_byte_count = 0;

            pac5xxx_uart_int_enable_RDAI2(PAC55XX_UARTC, 0);          // Disable receive data interrupt  
            pac5xxx_uart_rx_fifo_reset2(PAC55XX_UARTC);               // Reset RX FIFO, to clear RDAI interrupt
			pac5xxx_uart_int_enable_THREI2(PAC55XX_UARTC, 1);         // Enable transmit intrerrupt to send reponse to host						
			}
		}
}



