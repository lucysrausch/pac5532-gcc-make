/****************************************************************************
 * @file     bldc_common.h
 * @brief    Public interface to BLDC Common Application
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

#ifndef BLDC_COMMON_H
#define BLDC_COMMON_H

#ifndef INCLUDE_EXTERNS
#define	EXTERN	volatile
#else
#define	EXTERN	extern	volatile
#endif

#define	CAFE_ARCH2	1
#define PAC5523

#include "pac5xxx.h"
#include "pac5xxx_tile_driver_manager.h"
#include "pac5xxx_tile_power_manager.h"
#include "pac5xxx_tile_signal_manager.h"
#include "pac5xxx_tile_system_manager.h"


#include "pac5xxx_driver_adc.h"
#include "pac5xxx_driver_timer.h"
#include "pac5xxx_driver_socbridge.h"
#include "pac5xxx_driver_tile.h"
#include "pac5xxx_driver_system.h"
#include "pac5xxx_driver_memory.h"
#include "pac5xxx_driver_uart.h"
#include "uart.h"
#include "fix16.h"
#include "version.h"
#include "pid.h"
#include "motordef.h"
#include "state_machine.h"

#define FIX16(n)	((long)(65536.0 * n ))

#define	IREG				1							// Current Regulation PI Loop
#define	STALL_DETECT		1
#define	UPDATE_DEBUG		1							// 1 for running the Update Debug functionality
#define	CHECK_VBAT			0

#define APP_RAMFUNC_LINK
#ifdef APP_RAMFUNC_LINK
#define APP_RAMFUNC PAC5XXX_RAMFUNC
#else
#define APP_RAMFUNC
#endif

#define ADC_CHANNEL_MASK	((1L << ADCCTL_ADMUX_AD0) | (1L << ADCCTL_ADMUX_AD2) | (1L << ADCCTL_ADMUX_AD3) | (1L << ADCCTL_ADMUX_AD4))	// Mask of ADC channels to perform conversions for
#define	ADC_SEQ_EDATA		SIGMGR_MSPI_SH_COMP										// Latch for the comparator output (SH1 on EMUX) Selecting AD0 on ADCMux, although irrelevant

#define ADC_SEQ_VIN				0													// AS0 sequence number for VIN
#define	ADC_SEQ_U1				1													// AS0 sequence number for H Bridge Current (HBI)
#define	ADC_SEQ_V1				2													// AS0 sequence number for H Bridge Current (HBI)
#define	ADC_SEQ_W1				3													// AS0 sequence number for H Bridge Current (HBI)
#define	ADC_SEQ_VPOT			4													// AS0 sequence number for H Bridge Current (HBI)
#define	ADC_SEQ_U2				5													// AS0 sequence number for Potentiometer (VPOT)
#define ADC_SEQ_V2				6													// AS0 sequence number for VIN
#define	ADC_SEQ_W2				7													// AS0 sequence number for H Bridge Current (HBI)
#define	ADC_SEQ_HBU_EDATA		SIGMGR_AIO10
#define	ADC_SEQ_HBV_EDATA		SIGMGR_AIO32
#define	ADC_SEQ_HBW_EDATA		SIGMGR_AIO54

#define	VIN_VOLTS_VAL			PAC55XX_ADC->DTSERES0.VAL
#define	U1_ADC_VAL				PAC55XX_ADC->DTSERES1.VAL
#define	V1_ADC_VAL				PAC55XX_ADC->DTSERES2.VAL
#define	W1_ADC_VAL				PAC55XX_ADC->DTSERES3.VAL
#define	U2_ADC_VAL				PAC55XX_ADC->DTSERES5.VAL
#define	V2_ADC_VAL				PAC55XX_ADC->DTSERES6.VAL
#define	W2_ADC_VAL				PAC55XX_ADC->DTSERES7.VAL

typedef enum
{
	TimerC_idle = 0,
	TimerC_Align_And_Go,
	TimerC_getslcomp_first_sample,
	TimerC_getslcomp_samples,
	TimerC_getslcomp_commutation_wait,
	TimerC_getslcomp_blanking_cycles
}TimerC_States;

typedef enum
{
	status_motor_enabled = 1,
	status_over_current = 2,
	status_motor_stalled = 4,
	status_closed_loop = 8,
	status_under_voltage = 16
} StatusStateBits;

// System's Definitions
#define	TIMER_A_FREQ_CNV			100000
#define	MOTOR_OUT_PORTB_ALL_PWMS	0x01110111
#define	MOTOR_OUT_PORTB_ALL_GPIO	0
#define	MOTOR_OUTPUTS_PUSH_PULL		0x1515

#define DT_LED_TICKS			25
#define DT_TED_TICKS			25
#define	SAMPLE_DELAY_DEF		150
#define NIRQ1_PIN_MASK			0x80
#define NIRQ2_PIN_MASK			0x01

#define	POS_POLARITY			1

#if POS_POLARITY
	#define	COMP_POL			0x08
#else
	#define	COMP_POL			0x00
#endif

#define SLCOMP7					0xD1 + COMP_POL				//AIO7 - PHASE U to Comparator POS
#define SLCOMP8					0xE1 + COMP_POL				//AIO8 - PHASE V to Comparator POS
#define SLCOMP9					0xF1 + COMP_POL	 			//AIO9 - PHASE W to Comparator POS

#define	TIMER_D_FREQ_F16		0xBEBC2000				//TMRD Freq = 50MHz (This number is divided by 1024 so it can be represented by a Fix16 type)
#define	STALL_DETECT_DEF		25000
#define	AVG_SMP_CNT				6
#define	AVRG_DIV				FIX16(1/AVG_SMP_CNT)
#define	ONEDIV60				FIX16(1/60)
#define ONE_SIXTH_F16			FIX16(1/6)
#define	DEBUG_MAX				60

//***********************************************************************
// Voltage Scaling
// Scale Factor = 2.5 * (RTOP + RBOT) / (RBOT * 1023)
#define RTOP					560
#define RBOT					10
#define VOLT_DIV_FIX16			FIX16((RTOP + RBOT) * 2.5 / (RBOT * 1023))

//***********************************************************************
// VIN Checking - if VIN readings fall below VIN_VOLTS_LEGAL motor is disabled
// and marked as stalled
#define	VIN_VOLTS_LEGAL			FIX16(12.2)
#define	VIN_CHECK_DEB_MAX		100

//***********************************************************************
// Potentiometer Driving - if using a potentiometer to drive motor speed
#define	TURN_ON_THRESHOLD_MIN	60
#define	TURN_ON_THRESHOLD_MAX	100
#define	MAX_HZ					512

//***********************************************************************
// BEEP ON Defines
#define BEEP_FREQ_HZ_DEF		1000
#define BEEP_PWM_DC_DEF			10

//***********************************************************************
// Differential Amplifier Gain Setting
// Only one item can be chosen

//#define	DIFF_AMP_GAIN_X_0		1
//#define	DIFF_AMP_GAIN_X_1		1
//#define	DIFF_AMP_GAIN_X_2		2
//#define	DIFF_AMP_GAIN_X_3		4
#define	DIFF_AMP_GAIN_X_4		8
//#define	DIFF_AMP_GAIN_X_5		16
//#define	DIFF_AMP_GAIN_X_6		32
//#define	DIFF_AMP_GAIN_X_7		48

#if DIFF_AMP_GAIN_X_0
	#define DIFFAMP_GAIN_X				1
	#define	DIFFAMP_GAIN_OPT0			0
#elif DIFF_AMP_GAIN_X_1
	#define DIFFAMP_GAIN_X				1
	#define	DIFFAMP_GAIN_OPT0			1
#elif DIFF_AMP_GAIN_X_2
	#define DIFFAMP_GAIN_X				2
	#define	DIFFAMP_GAIN_OPT0			2
#elif DIFF_AMP_GAIN_X_3
	#define DIFFAMP_GAIN_X				4
	#define	DIFFAMP_GAIN_OPT0			3
#elif DIFF_AMP_GAIN_X_4
	#define DIFFAMP_GAIN_X				8
	#define	DIFFAMP_GAIN_OPT0			4
#elif DIFF_AMP_GAIN_X_5
	#define DIFFAMP_GAIN_X				16
	#define	DIFFAMP_GAIN_OPT0			5
#elif DIFF_AMP_GAIN_X_6
	#define DIFFAMP_GAIN_X				32
	#define	DIFFAMP_GAIN_OPT0			6
#elif DIFF_AMP_GAIN_X_7
	#define DIFFAMP_GAIN_X				48
	#define	DIFFAMP_GAIN_OPT0			7
#endif

//***********************************************************************
// HP/LP Over Current Protection (OCP) Defines
#define HP_IOCP_AMPS			30					//Desired OCP Current in Amps
#define LP_IOCP_AMPS			30					//Desired OCP Current in Amps
#define RSENSE_mOHMS			10
#define	HP_OCP_DEF				(HP_IOCP_AMPS * DIFFAMP_GAIN_X * 1023 * RSENSE_mOHMS) / (2.5 * 1000)
#define	LP_OCP_DEF				(LP_IOCP_AMPS * DIFFAMP_GAIN_X * 1023 * RSENSE_mOHMS) / (2.5 * 1000)

//***********************************************************************
// HPOPT and LPOPT
#define	xPOPT_DIS				0
#define	xPOPT_1US				1
#define	xPOPT_2US				2
#define	xPOPT_4US				3

#define	LPOPT_SEL				xPOPT_2US
#define	HPOPT_SEL				xPOPT_2US
//***********************************************************************
// Protection Interrupt Mask PROTINTM REGISTER

#define	NHP54INTM_MASK			1
#define	NHP32INTM_MASK			1
#define	NHP10INTM_MASK			1
#define	NLP54INTM_MASK			1
#define	NLP32INTM_MASK			1
#define	NLP10INTM_MASK			1

#define	PROTINTM_MASK			((NHP54INTM_MASK << 6)	+ (NHP32INTM_MASK << 5) + (NHP10INTM_MASK << 4) + (NLP54INTM_MASK << 2) + (NLP32INTM_MASK << 1) + (NLP10INTM_MASK << 0))

//***********************************************************************
// MODULE ENABLE CAFE REGISTER
#define	HIB_BIT					0					//0 = Normal Shutdown Mode; 1 = HIbernate Shutdown Mode
#define PBEN_BIT				0					//0 = Push Button Disabled; 1 = Push Button Enabled (AIO6)
#define	VREFSET_BIT				0					//0 = ADC VREF is 2.5V; 1 = ADC VREF is 3.0V
#define	CLKOUTEN_BIT			0					//0 = Disabled; 1 = Enabled
#define	TPBD					1					//0 = 32 ms; 1 = 1 ms Push Button Deglitch Time
#define	MCUALIVE_BIT			1					//1
#define	ENSIG_BIT				1					//0 = Disabled; 1 = Enabled
#define MODULE_ENABLE_FLAGS_DEF		(HIB_BIT << 7) + (PBEN_BIT << 6) + (VREFSET_BIT << 5) + (CLKOUTEN_BIT << 4) + (MCUALIVE_BIT << 3) + (TPBD << 2) + (ENSIG_BIT << 0)

//***********************************************************************
// BLANKING CAFE REGISTER
#define	BLANKING_100ns			0x00
#define	BLANKING_250ns			0x01
#define	BLANKING_500ns			0x02
#define	BLANKING_750ns			0x03
#define	BLANKING_1000ns			0x04
#define	BLANKING_1250ns			0x05
#define	BLANKING_1500ns			0x06
#define	BLANKING_2000ns			0x07
#define	BLANKING_2500ns			0x08
#define	BLANKING_3000ns			0x09
#define	BLANKING_3500ns			0x0A
#define	BLANKING_4000ns			0x0B
#define	BLANKING_4500ns			0x0C
#define	BLANKING_5000ns			0x0D
#define	BLANKING_5500ns			0x0E
#define	BLANKING_6000ns			0x0F

#define	BLANKING_DIS			0x00
#define	BLANKING_LEAD			0x01
#define	BLANKING_TRAIL			0x02
#define	BLANKING_BOTH			0x03

#define	BLANKING_CONFIG			(BLANKING_1000ns << 4) + BLANKING_BOTH

//***********************************************************************
// HYSTERESIS CAFE REGISTER

#define	HYSMODE_0				0x00
#define	HYSMODE_1				0x80

#define	HYSAIO_0_R0_F0			0x00
#define	HYSAIO_0_R0_F5			0x01
#define	HYSAIO_0_R0_F10			0x02
#define	HYSAIO_0_R0_F20			0x03
#define	HYSAIO_0_R5_F0			0x04
#define	HYSAIO_0_R5_F5			0x05
#define	HYSAIO_0_R5_F10			0x06
#define	HYSAIO_0_R5_F20			0x07
#define	HYSAIO_0_R10_F0			0x08
#define	HYSAIO_0_R10_F5			0x09
#define	HYSAIO_0_R10_F10		0x0A
#define	HYSAIO_0_R10_F20		0x0B
#define	HYSAIO_0_R20_F0			0x0C
#define	HYSAIO_0_R20_F5			0x0D
#define	HYSAIO_0_R20_F10		0x0E
#define	HYSAIO_0_R20_F20		0x0F

#define	HYSAIO_1_R0_F0			0x00
#define	HYSAIO_1_R0_F20			0x01
#define	HYSAIO_1_R0_F40			0x02
#define	HYSAIO_1_R0_F80			0x03
#define	HYSAIO_1_R20_F0			0x04
#define	HYSAIO_1_R20_F20		0x05
#define	HYSAIO_1_R20_F40		0x06
#define	HYSAIO_1_R20_F80		0x07
#define	HYSAIO_1_R40_F0			0x08
#define	HYSAIO_1_R40_F20		0x09
#define	HYSAIO_1_R40_F40		0x0A
#define	HYSAIO_1_R40_F80		0x0B
#define	HYSAIO_1_R80_F0			0x0C
#define	HYSAIO_1_R80_F20		0x0D
#define	HYSAIO_1_R80_F40		0x0E
#define	HYSAIO_1_R80_F80		0x0F

#define	HYSAIO_SEL				HYSAIO_0_R0_F0

#define	SPECCFG0_CONFIG			HYSMODE_1 + HYSAIO_SEL
#define	SPECCFG1_CONFIG			(HYSAIO_SEL << 4) + HYSAIO_SEL

//***********************************************************************
// Debug Quick Functions
#define	DEBUG_E0_R		PAC5XXX_GPIOE->OUT.b |= 0x01;
#define	DEBUG_E0_F		PAC5XXX_GPIOE->OUT.b &= ~0x01;

#define	DEBUG_E3_R		PAC5XXX_GPIOE->OUT.b |= 0x08;
#define	DEBUG_E3_F		PAC5XXX_GPIOE->OUT.b &= ~0x08;

#define	DEBUG_E4_R		PAC5XXX_GPIOE->OUT.b |= 0x10;
#define	DEBUG_E4_F		PAC5XXX_GPIOE->OUT.b &= ~0x10;

#define	DEBUG_E5_R		PAC5XXX_GPIOE->OUT.b |= 0x20;
#define	DEBUG_E5_F		PAC5XXX_GPIOE->OUT.b &= ~0x20;

#define	OPTIMIZE_O0		__attribute__((optimize("O0")))
#define	OPTIMIZE_O1		__attribute__((optimize("O1")))
#define	OPTIMIZE_O2		__attribute__((optimize("O2")))
#define	OPTIMIZE_O3		__attribute__((optimize("O3")))
#define	OPTIMIZE_Os		__attribute__((optimize("Os")))

// Function Prototypes
void speed_control_loop(void);
void check_vbat(void);
void check_adc(void);
void motor_pwm_disable(void);
void app_init(void);
void peripheral_init(void);
void cafe_init(void);
void adc_init(void);
void UART_init(void);
void Set_Dead_Time(void);
void UpdateDebug(void);
void oc_reset(void);
void pi_init(void);
void beep_on(int note);
void beep_off(void);
void state_machine(void);
void pac55xx_adc_dtse_element_config(DTSE_SEQ_CFG_TYPEDEF * reg_add, int sel_emuxc, int adc_channel, int delay, int EMUX_data, int NoConv, int Seq_done, int IRQ_number, int IRQ_enable);
fix16_t HertzToTicks(fix16_t Hertz, uint32_t Freq);
fix16_t HertzToTicksSine(fix16_t Hertz, uint32_t Freq);

EXTERN PID_Data_Type iq_pid;
EXTERN PID_Data_Type speed_pid;

EXTERN uint8_t good_samples;
EXTERN uint8_t good_samples_rx;
EXTERN uint8_t timer_d_div;
EXTERN uint8_t avg_speed_index;
EXTERN uint8_t tmp_pi_debug_index, pi_debug_index;
EXTERN uint8_t open_loop;
EXTERN uint8_t SMS_State;
EXTERN uint8_t vin_check_debounce;
EXTERN uint8_t debug_index;
EXTERN uint8_t diag_message_offset, diag_note_offset;

EXTERN uint16_t dt_leading_ticks, dt_trailing_ticks;
EXTERN uint16_t pwm_period_ticks;								/*!< Number of timer A ticks for PWM period */
EXTERN uint16_t sample_delay;
EXTERN uint16_t SMS_Counter;
EXTERN uint16_t speed_ref_hz, speed_ref_command_hz;
EXTERN uint16_t ol_accel_period, ol_accel_increase;
EXTERN uint16_t cl_accel_period, tmp_cl_accel, cl_accel_increase;
EXTERN uint16_t start_iq_ref;
EXTERN uint16_t align_time_ms;
EXTERN uint16_t ol_start_hz;
EXTERN uint16_t ol_switchover_hz;
EXTERN uint16_t sine_index;
EXTERN uint16_t beep_freq_hz;
EXTERN uint16_t beep_pwm_dc;

EXTERN uint32_t pwm_duty;
EXTERN uint32_t sine_mode;
EXTERN uint32_t ADC_Counter;
EXTERN uint32_t single_shunt_current;
EXTERN uint32_t sample;
EXTERN uint32_t app_status;
EXTERN uint32_t app_pwm_period;
EXTERN uint32_t hp_over_current_limit;
EXTERN uint16_t lp_over_current_limit;
EXTERN uint32_t stall_counter;
EXTERN uint32_t debug_1;
EXTERN uint32_t debug_2;
EXTERN uint32_t debug_3;
EXTERN uint32_t debug_4;
EXTERN uint32_t timer_d_latch_in;
EXTERN uint32_t timer_d_offset;
EXTERN uint32_t last_sample_stored;
EXTERN uint32_t samplecounter;
EXTERN uint32_t getslcomp_state;
EXTERN uint32_t millisecond;
EXTERN uint32_t blanking_cycles, tmp_blanking_cycles;
EXTERN uint32_t commutation_time;
EXTERN uint32_t sl_current_state;
EXTERN uint32_t motorspeed;
EXTERN uint32_t avg_speed_array[AVG_SMP_CNT];
EXTERN uint32_t enable_speed_pi;
EXTERN uint32_t switchover;
EXTERN uint32_t module_enable_bits;
EXTERN uint32_t cafe_write_data;
EXTERN uint32_t switchover;
EXTERN uint32_t hysteresis;
EXTERN uint32_t bemf_blanking;
EXTERN uint32_t oc_flags;

EXTERN fix16_t debug_array[DEBUG_MAX];
EXTERN fix16_t vin_volts;
EXTERN fix16_t avg_speed;
EXTERN fix16_t pi_debug_value[2][5];
EXTERN fix16_t iq_ref;
EXTERN fix16_t speed_ref_ticks, speed_ref_command;
EXTERN fix16_t closed_loop_speed_hz;
EXTERN fix16_t commutation_advanced_rise;
EXTERN fix16_t commutation_advanced_fall;
EXTERN fix16_t stall_speed_hz;
EXTERN fix16_t sine_scale;
EXTERN fix16_t sine_scale_increase;
EXTERN fix16_t sine_scale_max;
EXTERN fix16_t tmp_current_min, tmp_current_max;

extern const uint16_t beep_notes[128];
extern const uint8_t diag_tunes[4][4];
extern const fix16_t sine_wave_3phase[360][3];

// BLDC DIRECTION 1 LOGIC
//STATE TABLE		PWM-HI			PWM-LO			LO-SIDE		CurrentFlow		TriState	Comparator	Floating Phase	Polarity
//0					PWM4-A3(UH)		PWM0-A0(UL)		A1(VL)		U->V			W			SLCOMP9		W-Rising		0
//1					PWM6-A5(WH)		PWM2-A2(WL)		A1(VL)		W->V			U			SLCOMP7		U-Falling		1
//2					PWM6-A5(WH)		PWM2-A2(WL)		A0(UL)		W->U			V			SLCOMP8		V-Rising		0
//3					PWM5-A4(VH)		PWM1-A1((VL)	A0(UL)		V->U			W			SLCOMP9		W-Falling		1
//4					PWM5-A4(VH)		PWM1-A1((VL)	A2(WL)		V->W			U			SLCOMP7		U-Rising		0
//5					PWM4-A3(UH)		PWM0-A0(UL)		A2(WL)		U->W			V			SLCOMP8		V-Falling		1

// BLDC DIRECTION 0 LOGIC
//STATE TABLE		PWM-HI			PWM-LO			LO-SIDE		CurrentFlow		TriState	Comparator	Floating Phase	Polarity
//0					PWM4-A3(UH)		PWM0-A0(UL)		A2(WL)		U->W			V			SLCOMP8		V-Falling		1
//1					PWM5-A4(VH)		PWM1-A1((VL)	A2(WL)		V->W			U			SLCOMP7		U-Rising		0
//2					PWM5-A4(VH)		PWM1-A1((VL)	A0(UL)		V->U			W			SLCOMP9		W-Falling		1
//3					PWM6-A5(WH)		PWM2-A2(WL)		A0(UL)		W->U			V			SLCOMP8		V-Rising		0
//4					PWM6-A5(WH)		PWM2-A2(WL)		A1(VL)		W->V			U			SLCOMP7		U-Falling		1
//5					PWM4-A3(UH)		PWM0-A0(UL)		A1(VL)		U->V			W			SLCOMP9		W-Rising		0

#ifndef INCLUDE_EXTERNS
#if BLDC_DIRECTION

	EXTERN const uint32_t psel_mask[6] = {0x00010001, 0x01000100, 0x01000100, 0x00100010, 0x00100010, 00010001};
	EXTERN const uint8_t c_pwm_io_state[6] = {0x02, 0x02, 0x01, 0x01, 0x04, 0x04 };
	EXTERN const uint8_t slcomp_mux[6] = {SLCOMP9, SLCOMP7, SLCOMP8, SLCOMP9, SLCOMP7, SLCOMP8};
	EXTERN const uint32_t slcomp_cross_polarity[6] = {0x01, 0, 0x01, 0, 0x01, 0};
	EXTERN const uint8_t hs_to_commutation[8] = {0,0,2,1,4,5,3,0};
#else
	EXTERN const uint32_t psel_mask[6] = {0x00010001, 0x00100010, 0x00100010, 0x01000100, 0x01000100, 0x00010001};
	EXTERN const uint8_t c_pwm_io_state[6] = {0x04, 0x04, 0x01, 0x01, 0x02, 0x02};
	EXTERN const uint8_t slcomp_mux[6] = {SLCOMP8, SLCOMP7, SLCOMP9, SLCOMP8, SLCOMP7, SLCOMP9};
	EXTERN const uint32_t slcomp_cross_polarity[6] = {0x01, 0, 0x01, 0, 0x01, 0};
	EXTERN const uint8_t hs_to_commutation[8] = {0,2,0,1,4,3,5,0};
#endif

#else
	EXTERN const uint8_t slcomp_mux[6];
	EXTERN const uint8_t c_pwm_io_state[6];
	EXTERN const uint32_t psel_mask[6];
	EXTERN const uint32_t slcomp_cross_polarity[6];
	EXTERN const uint8_t hs_to_commutation[8];
#endif

#endif
