//==============================================================================
///@file     pac5xxx_tile_signal_manager.h
///@brief    CMSIS Header File for the PAC5XXX Signal Manager Tile
///
///@note
///Copyright (C) 2017, Active-Semi International
///
///THIS SOFTWARE IS SUBJECT TO A SOURCE CODE LICENSE AGREEMENT WHICH PROVIDES, 
///AMONG OTHER THINGS:  (i) THAT IT CAN BE USED ONLY TO ADAPT THE LICENSEE'S 
///APPLICATION TO PAC PROCESSORS SUPPLIED BY ACTIVE-SEMI INTERNATIONAL; 
///(ii) THAT  IT IS PROVIDED "AS IS" WITHOUT WARRANTY;  (iii) THAT 
///ACTIVE-SEMICONDUCTOR IS NOT LIABLE FOR ANY INDIRECT DAMAGES OR FOR DIRECT
///DAMAGES EXCEEDING US$1,500;  AND (iv) THAT IT CAN BE DISCLOSED TO AND USED
///ONLY BY CERTAIN AUTHORIZED PERSONS.
///
//==============================================================================

#ifndef PAC5XXX_TILE_SIGNAL_MANAGER_H
#define PAC5XXX_TILE_SIGNAL_MANAGER_H

/** @addtogroup PAC5XXX_Tile_SignalManager PAC5XXX Signal Manager Tile
@{
*/

#ifdef __CC_ARM  // KEIL Compiler
#pragma anon_unions
#endif

#ifdef CAFE_ARCH2
//===============================
//===== CAFE Architecture 2 =====
//===============================

/*!< Signal Manager EMUX/Mini-SPI data definitions */

typedef enum {
    SIGMGR_AIO10 = 0,                       /*!< Differential Analog AIO10                                  */
    SIGMGR_AIO32 = 1,                       /*!< Differential Analog AIO32                                  */
    SIGMGR_AIO54 = 2,                       /*!< Differential Analog AIO54                                  */
    SIGMGR_AB1 = 3,                         /*!< Analog Bus Input 1 (AB1)                                   */
    SIGMGR_AB2 = 4,                         /*!< Analog Bus Input 2 (AB2)                                   */
    SIGMGR_AB3 = 5,                         /*!< Analog Bus Input 3 (AB3)                                   */
    SIGMGR_AB4 = 6,                         /*!< Analog Bus Input 4 (AB4)                                   */
    SIGMGR_AB5 = 7,                         /*!< Analog Bus Input 5 (AB5)                                   */
    SIGMGR_AB6 = 8,                         /*!< Analog Bus Input 6 (AB6)                                   */
    SIGMGR_AB7 = 9,                         /*!< Analog Bus Input 7 (AB7)                                   */
    SIGMGR_AB8 = 10,                        /*!< Analog Bus Input 8 (AB8)                                   */
    SIGMGR_AB9 = 11,                        /*!< Analog Bus Input 9 (AB9)                                   */
    SIGMGR_AB10 = 12,                       /*!< Analog Bus Input 10 (AB10)                                 */
    SIGMGR_AB11 = 13,                       /*!< Analog Bus Input 11 (AB11)                                 */
    SIGMGR_AB12 = 14,                       /*!< Analog Bus Input 12 (AB12)                                 */
    SIGMGR_VREFDIV2 = 15                    /*!< VREF/2                                                     */
} Signal_Manager_MUX_Select;

/**
 *  EMUX bit definitions
 *
 *  Bits  Function  Description
 *  =============================================================================
 *  b7    COMP_SH   BEMF comparators sample and hold.  0=Sample, 1=Hold
 *  b6:   HLD2      Diff Amp 54 sample and hold.  0=Sample, 1=Hold
 *  b5:   HLD1      Diff Amp 32 sample and hold.  0=Sample, 1=Hold
 *  b4    HLD0      Diff Amp 10 sample and hold.  0=Sample, 1=Hold
 *  b3:0  ADCSEL    Analog mux select.  0=DAO10, 1=DAO32, 2=DAO54, 3:14=AB1:12, 15=VREFDIV2 (from \a Signal_Manager_MUX_Select enumeration)
 */
#define SIGMGR_EN_SH_COMP               0x80        /*!< set HOLD for BEMF Comparators  */
#define SIGMGR_SH_DIFFAMP54_HOLD        0x40        /*!< set HOLD for DiffAmp54         */
#define SIGMGR_SH_DIFFAMP32_HOLD        0x20        /*!< set HOLD for DiffAmp32         */
#define SIGMGR_SH_DIFFAMP10_HOLD        0x10        /*!< set HOLD for DiffAmp10         */

/*!< Signal Manager Tile Register Addresses */


typedef enum {
    ADDR_CFGAIO0 = 0x06,                    /*!< Signal Manager AIO0 Configuration Register                 */
    ADDR_CFGAIO1 = 0x07,                    /*!< Signal Manager AIO1 Configuration Register                 */
    ADDR_CFGAIO2 = 0x08,                    /*!< Signal Manager AIO2 Configuration Register                 */
    ADDR_CFGAIO3 = 0x09,                    /*!< Signal Manager AIO3 Configuration Register                 */
    ADDR_CFGAIO4 = 0x0A,                    /*!< Signal Manager AIO4 Configuration Register                 */
    ADDR_CFGAIO5 = 0x0B,                    /*!< Signal Manager AIO5 Configuration Register                 */
    ADDR_CFGAIO6 = 0x0C,                    /*!< Signal Manager AIO6 Configuration Register                 */
    ADDR_CFGAIO7 = 0x0D,                    /*!< Signal Manager AIO7 Configuration Register                 */
    ADDR_CFGAIO8 = 0x0E,                    /*!< Signal Manager AIO8 Configuration Register                 */
    ADDR_CFGAIO9 = 0x0F,                    /*!< Signal Manager AIO9 Configuration Register                 */
    ADDR_SIGSET = 0x10,                     /*!< Signal Manager Configuration Register                      */
    ADDR_HPDACH = 0x11,                     /*!< Signal Manager HP DAC Threshold High-bits Register         */
    ADDR_HPDACL = 0x12,                     /*!< Signal Manager HP DAC Threshold Low-bits Register          */
    ADDR_LPDACH = 0x13,                     /*!< Signal Manager LP DAC Threshold High-bits Register         */
    ADDR_LPDACL = 0x14,                     /*!< Signal Manager LP DAC Threshold Low-bits Register          */
    ADDR_SHCFG1 = 0x15,                     /*!< Signal Manager Sample and Hold Configuration 1 Register    */
    ADDR_SHCFG2 = 0x16,                     /*!< Signal Manager Sample and Hold Configuration 2 Register    */
    ADDR_PROTINTM = 0x17,                   /*!< Signal Manager Driver Protection Interrupt Mask Register   */
    ADDR_PROTSTAT = 0x18,                   /*!< Signal Manager Driver Protection Interrupt Status Register */
    ADDR_DOUTSIG0 = 0x19,                   /*!< Signal Manager AIO Data Output 0 Register                  */
    ADDR_DOUTSIG1 = 0x1A,                   /*!< Signal Manager AIO Data Output 1 Register                  */
    ADDR_DINSIG0 = 0x1B,                    /*!< Signal Manager AIO Data Input 0 Register                   */
    ADDR_DINSIG1 = 0x1C,                    /*!< Signal Manager AIO Data Input 1 Register                   */
    ADDR_CFGIO1 = 0x1D,                     /*!< Signal Manager AIO10-13 Configuration 0 Register           */
    ADDR_CFGIO2 = 0x1E,                     /*!< Signal Manager AIO10-13 Configuration 1 Register           */
    ADDR_SIGINTM = 0x1F,                    /*!< Signal Manager AIO Interrupt Mask Register                 */
    ADDR_SIGINTF = 0x20,                    /*!< Signal Manager AIO Interrupt Flag Register                 */
    ADDR_BLANKING = 0x21,                   /*!< Signal Manager BEMF Comparator Blanking Register           */
    ADDR_SPECCFG0 = 0x22,                   /*!< Signal Manager AIO7 Hysteresis Configuration Register      */
    ADDR_SPECCFG1 = 0x23,                   /*!< Signal Manager AIO8-9 Hysteresis Configuration Register    */
    ADDR_SPECCFG2 = 0x24,                   /*!< Signal Manager AIO7-8 Comparator MUX Configuration Register*/
    ADDR_SPECCFG3 = 0x25,                   /*!< Signal Manager AIO9 Comparator MUX Configuration Register  */
} Signal_Manager_Reg_Addr;


#else  // CAFE_ARCH1
//===============================
//===== CAFE Architecture 1 =====
//===============================

/*!< Signal Manager EMUX/Mini-SPI data definitions */

typedef enum {
	SIGMGR_AIO10 = 0,				        /*!< Differential Analog AIO01 						            */
	SIGMGR_AIO32 = 1,				        /*!< Differential Analog AIO32 								    */
	SIGMGR_AIO54 = 2,				        /*!< Differential Analog AIO54 								    */
	SIGMGR_AB1 = 3,				        	/*!< Analog Bus Input 1 (AB1)								    */
	SIGMGR_AB2 = 4,				        	/*!< Analog Bus Input 2 (AB2)								    */
	SIGMGR_AB3 = 5,				        	/*!< Analog Bus Input 3 (AB3)								    */
	SIGMGR_AB4 = 6,				        	/*!< Analog Bus Input 4 (AB4)								    */
	SIGMGR_AB5 = 7,				        	/*!< Analog Bus Input 5 (AB5)								    */
	SIGMGR_AB6 = 8,				        	/*!< Analog Bus Input 6 (AB6)								    */
	SIGMGR_AB7 = 9,				        	/*!< Analog Bus Input 7 (AB7)								    */
	SIGMGR_AB8 = 10,			        	/*!< Analog Bus Input 8 (AB8)								    */
	SIGMGR_AB9 = 11,			        	/*!< Analog Bus Input 9 (AB9)								    */
	SIGMGR_AB10 = 12,			        	/*!< Analog Bus Input 10 (AB10)								    */
	SIGMGR_AB11 = 13,			        	/*!< Analog Bus Input 11 (AB11)								    */
	SIGMGR_AB12 = 14,			        	/*!< Analog Bus Input 12 (AB12)								    */
	SIGMGR_VREFDIV2 = 15	                /*!< VREF/2												        */
} Signal_Manager_MUX_Select;

/**
 *  EMUX bit definitions
 *
 *  Bits  Function  Description
 *  =============================================================================
 *  b7:6  C[1:0]    EMUX activate (set to b10)
 *  b5:	  SH1:      Enable sample and hold for 3-phase comparators
 *  b4    SH0:	    Enable sample and hold for AIO10, AIO32 or AIO54
 *  b3:0  A[3:0]:   Analog IO value from \a Signal_Manager_MUX_Select enumeration
 */

#define SIGMGR_EN_MSPI                  0x40        /*!< C[1:0] to activate mini-SPI */
#define SIGMGR_EN_SH_COMP 				0x20		/*!< SH1 to activate S&H for Phase Comparators */
#define SIGMGR_EN_SH_DIFFAMP 			0x10		/*!< SH0 to activate S&H for DiffAmp */

#define SIGMGR_MSPI(channel)			(SIGMGR_EN_MSPI | (channel))						/*!< EMUX data for given channel */
#define SIGMGR_MSPI_SH_DIFFAMP		    (SIGMGR_EN_MSPI | SIGMGR_EN_SH_DIFFAMP)				/*!< EMUX data for S&H start on DiffAmp channels */
#define SIGMGR_MSPI_SH_COMP				(SIGMGR_EN_MSPI | SIGMGR_EN_SH_COMP)				/*!< EMUX data for comparator */

/*!< Signal Manager Tile Register Addresses */

typedef enum {
	ADDR_CFGAIO0 = 0x20,			        /*!< Signal Manager AIO0 Configuration Register				    */
	ADDR_CFGAIO1 = 0x21,			        /*!< Signal Manager AIO1 Configuration Register				    */
	ADDR_CFGAIO2 = 0x22,			        /*!< Signal Manager AIO2 Configuration Register				    */
	ADDR_CFGAIO3 = 0x23,			        /*!< Signal Manager AIO3 Configuration Register				    */
	ADDR_CFGAIO4 = 0x24,			        /*!< Signal Manager AIO4 Configuration Register				    */
	ADDR_CFGAIO5 = 0x25,			        /*!< Signal Manager AIO5 Configuration Register				    */
	ADDR_CFGAIO6 = 0x26,			        /*!< Signal Manager AIO6 Configuration Register				    */
	ADDR_CFGAIO7 = 0x27,			        /*!< Signal Manager AIO7 Configuration Register				    */
	ADDR_CFGAIO8 = 0x28,			        /*!< Signal Manager AIO8 Configuration Register				    */
	ADDR_CFGAIO9 = 0x29,			        /*!< Signal Manager AIO9 Configuration Register				    */
	ADDR_SIGSET = 0x2A,			            /*!< Signal Manager Setting Register						    */
	ADDR_HPDAC = 0x2B,				        /*!< High Protection Threshold DAC Control 0 Register		    */
	ADDR_LPDAC0 = 0x2C,				        /*!< Low Protection Threshold DAC Control 0 Register		    */
	ADDR_LPDAC1 = 0x2D,				        /*!< Low Protection Threshold DAC Control 1 Register		    */
	ADDR_ADCSCAN = 0x2E,			        /*!< ADC Scan Control										    */
	ADDR_ADCIN1 = 0x2F,				        /*!< ADC Input Select 1										    */
	ADDR_PROTINTM = 0x30,			        /*!< Protection Interrupt Mask								    */
	ADDR_PROTSTAT = 0x31,			        /*!< Protection Status										    */
	ADDR_DOUTSIG0 = 0x32,			        /*!< Signal Manager Data Output 0							    */
	ADDR_DOUTSIG1 = 0x33,			        /*!< Signal Manager Data Output 1							    */
	ADDR_DINSIG0 = 0x34,			        /*!< Signal Manager Data Input 0							    */
	ADDR_DINSIG1 = 0x35,			        /*!< Signal Manager Data Input 1							    */
	ADDR_SIGINTM = 0x36,			        /*!< AIO Interrupt Mask										    */
	ADDR_SIGINTF = 0x37,			        /*!< AIO Interrupt Flag										    */
	ADDR_ENSIG = 0x38				        /*!< Signal Manager Enable									    */
} Signal_Manager_Reg_Addr;

/*!< Signal Manager Tile Register Definitions */

/*!< CFGAIO0: Address: 0x20		AIO0 Configuration Register */
typedef union {
	__IO uint8_t b;
	struct {
		__IO uint8_t MUX0     				: 3;		/*!< MUX setting for AIO0 						    */
		__IO uint8_t POL0					: 1;		/*!< Polarity setting for AIO0					    */
		__IO uint8_t OPT0					: 2;		/*!< Option setting for AIO0					    */
		__IO uint8_t MODE0					: 2;		/*!< Mode setting for AIO0						    */
	};
} CFGAIO0;

/*!< CFGAIO1: Address: 0x21		AIO1 Configuration Register */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t MUX1					: 3;		/*!< MUX setting for AIO1						    */
		__IO uint8_t POL1					: 1;		/*!< Polarity setting for AIO1					    */
		__IO uint8_t OPT1					: 2;		/*!< Option setting for AIO1					    */
			 uint8_t						: 2;
	};
} CFGAIO1;

/*!< CFGAIO2: Address: 0x22		AIO2 Configuration Register */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t MUX2					: 3;		/*!< MUX setting for AIO2						    */
		__IO uint8_t POL2					: 1;		/*!< Polarity setting for AIO2					    */
		__IO uint8_t OPT2					: 2;		/*!< Option setting for AIO2					    */
		__IO uint8_t MODE2					: 2;		/*!< Mode setting for AIO2						    */
	};
} CFGAIO2;

/*!< CFGAIO3: Address: 0x23		AIO3 Configuration Register */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t MUX3					: 3;		/*!< MUX setting for AIO3						    */
		__IO uint8_t POL3					: 1;		/*!< Polarity setting for AIO3					    */
		__IO uint8_t OPT3					: 2;		/*!< Option setting for AIO3					    */
			 uint8_t    					: 2;
	};
} CFGAIO3;

/*!< CFGAIO4: Address: 0x24		AIO4 Configuration Register */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t MUX4					: 3;		/*!< MUX setting for AIO4						    */
		__IO uint8_t POL4					: 1;		/*!< Polarity setting for AIO4					    */
		__IO uint8_t OPT4					: 2;		/*!< Option setting for AIO4					    */
		__IO uint8_t MODE4					: 2;		/*!< Mode setting for AIO4						    */
	};
} CFGAIO4;

/*!< CFGAIO5: Address: 0x25		AIO5 Configuration Register */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t MUX5					: 3;		/*!< MUX setting for AIO5						    */
		__IO uint8_t POL5					: 1;		/*!< Polarity setting for AIO5					    */
		__IO uint8_t OPT5					: 2;		/*!< Option setting for AIO5					    */
			 uint8_t    					: 2;
	};
} CFGAIO5;

/*!< CFGAIO6: Address: 0x26		AIO6 Configuration Register */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t MUX6					: 3;		/*!< MUX setting for AIO6						    */
		__IO uint8_t POL6					: 1;		/*!< Polarity setting for AIO6					    */
		__IO uint8_t OPT6					: 2;		/*!< Option setting for AIO6					    */
		__IO uint8_t MODE6					: 2;		/*!< Mode setting for AIO6						    */
	};
} CFGAIO6;

/*!< CFGAIO7: Address: 0x27		AIO7 Configuration Register */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t MUX7					: 3;		/*!< MUX setting for AIO7						    */
		__IO uint8_t POL7					: 1;		/*!< Polarity setting for AIO7					    */
		__IO uint8_t OPT7					: 2;		/*!< Option setting for AIO7					    */
		__IO uint8_t MODE7					: 2;		/*!< Mode setting for AIO7						    */
	};
} CFGAIO7;

/*!< CFGAIO8: Address: 0x28		AIO8 Configuration Register */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t MUX8					: 3;		/*!< MUX setting for AIO8						    */
		__IO uint8_t POL8					: 1;		/*!< Polarity setting for AIO8					    */
		__IO uint8_t OPT8					: 2;		/*!< Option setting for AIO8					    */
		__IO uint8_t MODE8					: 2;		/*!< Mode setting for AIO8						    */
	};
} CFGAIO8;

/*!< CFGAIO9: Address: 0x29		AIO9 Configuration Register */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t MUX9					: 3;		/*!< MUX setting for AIO9						    */
		__IO uint8_t POL9					: 1;		/*!< Polarity setting for AIO9					    */
		__IO uint8_t OPT9					: 2;		/*!< Option setting for AIO9					    */
		__IO uint8_t MODE9					: 2;		/*!< Mode setting for AIO9						    */
	};
} CFGAIO9;

/*!< SIGSET: Address: 0x2A		Signal Manager Setting */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t HPDACAB2				: 1;		/*!< Connect HPDAC output to AB2				    */
		__IO uint8_t LPDACAB3				: 1;		/*!< Connect LPDAC output to AB3				    */
		__IO uint8_t LPROTHYS				: 1;		/*!< Low Protection Comparator Hysteresis enbl      */
		__IO uint8_t HPROTHYS				: 1; 		/*!< High Protection Comparator Hys Enbl		    */
		__IO uint8_t AIO6HYS				: 1;		/*!< AIO6 Comparator Hys Enable					    */
		__IO uint8_t AIO7HYS				: 1;		/*!< AIO7 Comparator Hys Enable					    */
		__IO uint8_t AIO8HYS				: 1;		/*!< AIO8 Comparator Hys Enable					    */
		__IO uint8_t AIO9HYS				: 1;		/*!< AIO9 Comparator Hys Enable					    */
	};
} SIGSTAT;

/*!< LPDAC1: Address: 0x2D		Low Protection Threshold DAC Control 1 */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t VAL					: 2;		/*!< DAC register lower two bits				    */
			 uint8_t                        : 6;
	};
} LPDAC1;

/*!< ADCSCAN: Address: 0x2E		ADC Scan Control */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t DAO54SH					: 1;		/*!< Enable S&H circuit to sync DiffAmp 54		*/
		__IO uint8_t DAO32SH					: 1;		/*!< Enable S&H circuit to sync DiffAmp 32		*/
		__IO uint8_t DAO10SH					: 1;		/*!< Enable S&H circuit to sync DiffAmp 10		*/
		__IO uint8_t ENADCBUF					: 1; 		/*!< ADC buffer circuit enable					*/
		__IO uint8_t ENSCAN						: 1;		/*!< ADC scan control circuit enable			*/
			 uint8_t 							: 3;
	};
} ADCSCAN;

/*!< ADCIN1: Address: 0x2E		ADC Input Select 1 */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t VAL					: 4;		/*!< Signal select for ADCIN when ENMUXCH = 0	    */
			 uint8_t                        : 4;
	};
} ADCIN1;

/*!< PROTINTM: Address: 0x30	Protection Interrupt Mask */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t nLP10INTM				: 1;		/*!< LPROT10 Interrupt Mask (active low)		    */
		__IO uint8_t nLP32INTM				: 1;		/*!< LPROT32 Interrupt Mask (active low)		    */
		__IO uint8_t nLP54INTM				: 1;		/*!< LPROT54 Interrupt Mask (active low)		    */
		     uint8_t						: 1;
		__IO uint8_t nHP10INTM				: 1;		/*!< HPROT10 Interrupt Mask (active low)		    */
		__IO uint8_t nHP32INTM				: 1;		/*!< HPROT32 Interrupt Mask (active low)		    */
		__IO uint8_t nHP54INTM				: 1;		/*!< HPROT54 Interrupt Mask (active low)		    */
		     uint8_t                        : 1;
	};
} PROTINTM;

/*!< PROTSTAT: Address: 0x31	Protection Status */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t LPROT10				: 1;		/*!< LPROT10 Status (write 1 to clear)			    */
		__IO uint8_t LPROT32				: 1;		/*!< LPROT32 Status (write 1 to clear)			    */
		__IO uint8_t LPROT54				: 1;		/*!< LPROT54 Status (write 1 to clear) 			    */
		     uint8_t						: 1;
		__IO uint8_t HPROT10				: 1;		/*!< HPROT10 Status (write 1 to clear)			    */
		__IO uint8_t HPROT32				: 1;		/*!< HPROT32 Status (write 1 to clear)			    */
		__IO uint8_t HPROT54				: 1;		/*!< HPROT54 Status (write 1 to clear)			    */
		     uint8_t						: 1;
	};
} PROTSTAT;

/*!< DOUTSIG0: Address: 0x32	Signal Manager Data Output 0 */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t DOUT0					: 1;		/*!< Data output from AIO0						    */
		__IO uint8_t DOUT1					: 1;		/*!< Data output from AIO1						    */
		__IO uint8_t DOUT2					: 1;		/*!< Data output from AIO2						    */
		__IO uint8_t DOUT3					: 1;		/*!< Data output from AIO3						    */
		__IO uint8_t DOUT4					: 1;		/*!< Data output from AIO4						    */
		__IO uint8_t DOUT5					: 1;		/*!< Data output from AIO5						    */
		     uint8_t 						: 2;
	};
} DOUTSIG0;

/*!< DOUTSIG1: Address: 0x33	Signal Manager Data Output 1 */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t DOUT6					: 1;		/*!< Data output from AIO6						    */
		__IO uint8_t DOUT7					: 1;		/*!< Data output from AIO7						    */
		__IO uint8_t DOUT8					: 1;		/*!< Data output from AIO8						    */
		__IO uint8_t DOUT9					: 1;		/*!< Data output from AIO9						    */
		     uint8_t 						: 4;
	};
} DOUTSIG1;

/*!< DINSIG0: Address: 0x34		Signal Manager Data Input 0 */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t DIN0					: 1;		/*!< Data input from AIO0						    */
		__IO uint8_t DIN1					: 1;		/*!< Data input from AIO1						    */
		__IO uint8_t DIN2					: 1;		/*!< Data input from AIO2						    */
		__IO uint8_t DIN3					: 1;		/*!< Data input from AIO3						    */
		__IO uint8_t DIN4					: 1;		/*!< Data input from AIO4						    */
		__IO uint8_t DIN5					: 1;		/*!< Data input from AIO5						    */
		     uint8_t               			: 2;
	};
} DINSIG0;

/*!< DINSIG1: Address: 0x35		Signal Manager Data Input 1 */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t DIN6					: 1;		/*!< Data input from AIO6						    */
		__IO uint8_t DIN7					: 1;		/*!< Data input from AIO7						    */
		__IO uint8_t DIN8					: 1;		/*!< Data input from AIO8						    */
		__IO uint8_t DIN9					: 1;		/*!< Data input from AIO9						    */
		     uint8_t               			: 4;
	};
} DINSIG1;

/*!< SIGINTM: Address: 0x36		AIO Interrupt Mask */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t nAIO6FINTM				: 1;		/*!< AIO6 Falling Edge mask (0: masked)			    */
		__IO uint8_t nAIO7FINTM				: 1;		/*!< AIO7 Falling Edge mask (0: masked)			    */
		__IO uint8_t nAIO8FINTM				: 1;		/*!< AIO8 Falling Edge mask (0: masked)			    */
		__IO uint8_t nAIO9FINTM				: 1;		/*!< AIO9 Falling Edge mask (0: masked)			    */
		__IO uint8_t nAIO6RINTM				: 1;		/*!< AIO6 Rising Edge mask (0: masked)			    */
		__IO uint8_t nAIO7RINTM				: 1;		/*!< AIO7 Rising Edge mask (0: masked)			    */
		__IO uint8_t nAIO8RINTM				: 1;		/*!< AIO8 Rising Edge mask (0: masked)			    */
		__IO uint8_t nAIO9RINTM				: 1;		/*!< AIO9 Rising Edge mask (0: masked)			    */
	};
} SIGINTM;

/*!< SIGINTF: Address: 0x37		AIO Interrupt Flag */
typedef union
{
	__IO uint8_t b;
	struct {
		__IO uint8_t AIO6INTF				: 1;		/*!< AIO6 Interrupt Flag. Write 1 to clear.		    */
		__IO uint8_t AIO7INTF				: 1;		/*!< AIO7 Interrupt Flag. Write 1 to clear.		    */
		__IO uint8_t AIO8INTF				: 1;		/*!< AIO8 Interrupt Flag. Write 1 to clear.		    */
		__IO uint8_t AIO9INTF				: 1;		/*!< AIO9 Interrupt Flag. Write 1 to clear.		    */
		     uint8_t                        : 4;
	};
} SIGINTF;

/*!< ENSIG: Address: 0x38		Signal Manager Tile Enable */
typedef union
{
	__IO uint8_t b;
	struct
	{
		__IO uint8_t ENSIG					: 1;		/*!< SigMgr tile enable: 1; Disable: 0			    */
			 uint8_t 						: 7;
	};
} ENSIG;

#endif // #ifdef CAFE_ARCH2

/*@}*/ /* end of group PAC5XXX_Tile_SignalManager */

#endif // PAC5XXX_TILE_SIGNAL_MANAGER_H
