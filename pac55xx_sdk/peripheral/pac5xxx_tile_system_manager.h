//==============================================================================
///@file     pac5xxx_tile_system_manager.h
///@brief    CMSIS Header File for the PAC5XXX System Manager Tile
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
 
#ifndef PAC5XXX_TILE_SYSTEM_MANAGER_H
#define PAC5XXX_TILE_SYSTEM_MANAGER_H  


#ifdef __CC_ARM  // KEIL Compiler
#pragma anon_unions
#endif

#ifdef CAFE_ARCH2
//===============================
//===== CAFE Architecture 2 =====
//===============================
/*!< Signal Manager Tile Register Addresses */

//typedef enum {
//} System_Manager_Reg_Addr;

#else  // CAFE_ARCH1
//===============================
//===== CAFE Architecture 1 =====
//===============================
/*!< Signal Manager Tile Register Addresses */

typedef enum {
	ADDR_SYSSTAT = 0x00,		            /*!< System Manager Status Register						        */
	ADDR_DEVID = 0x08,			            /*!< Device Identification Register					          	*/
	ADDR_VERID = 0x09,			            /*!< Version Identification Register				         	*/
} System_Manager_Reg_Addr;

/** PAC5XXX VERID type codes */
typedef enum
{
	PAC5XXX_VERID_AZREVA = 0x01,		    /*!< Driver manager version AZ, revision A			         	*/
	PAC5XXX_VERID_AYREVA = 0x02,		    /*!< Driver manager version AY, revision A			         	*/
	PAC5XXX_VERID_AXREVA = 0x03,		    /*!< Driver manager version AX, revision A			         	*/
	PAC5XXX_VERID_AWREVA = 0x04,		    /*!< Driver manager version AW, revision A			         	*/
	PAC5XXX_VERID_AZREVB = 0x11,		    /*!< Driver manager version AZ, revision B			         	*/
	PAC5XXX_VERID_AYREVB = 0x12,		    /*!< Driver manager version AY, revision B			         	*/
	PAC5XXX_VERID_AXREVB = 0x13,		    /*!< Driver manager version AX, revision B			        	*/
	PAC5XXX_VERID_AWREVB = 0x14,		    /*!< Driver manager version AW, revision B			        	*/
	PAC5XXX_VERID_AZREVC = 0x21,		    /*!< Driver manager version AZ, revision C			         	*/
	PAC5XXX_VERID_AYREVC = 0x22,		    /*!< Driver manager version AY, revision C			        	*/
	PAC5XXX_VERID_AXREVC = 0x23,		    /*!< Driver manager version AX, revision C			        	*/
	PAC5XXX_VERID_AWREVC = 0x24,		    /*!< Driver manager version AW, revision C			        	*/
	PAC5XXX_VERID_AZREVD = 0x31,		    /*!< Driver manager version AZ, revision D		        		*/
	PAC5XXX_VERID_AYREVD = 0x32,		    /*!< Driver manager version AY, revision D			        	*/
	PAC5XXX_VERID_AXREVD = 0x33,		    /*!< Driver manager version AX, revision D			        	*/
	PAC5XXX_VERID_AWREVD = 0x34			    /*!< Driver manager version AW, revision D			        	*/

} System_Manager_VERID_Type;

//
// Type Enumerations
//


/** PAC5XXX Threshold Voltage for Comparator AIO9-6 Type Enumeration */
typedef enum
{
	PAC5XXX_VTHRESH_0p1V = 0,			    /*!< Threshold voltage for comparator for AIO9-6: 0.1V  	    */
	PAC5XXX_VTHRESH_0p2V = 1,			    /*!< Threshold voltage for comparator for AIO9-6: 0.2V	        */
	PAC5XXX_VTHRESH_0p5V = 2,			    /*!< Threshold voltage for comparator for AIO9-6: 0.5V	        */
	PAC5XXX_VTHRESH_1p25V = 3,			    /*!< Threshold voltage for comparator for AIO9-6: 1.25V     	*/
} PAC5XXX_Vthresh_Comp_Type;

//
// Bit Definitions
//

/*!< System Manager Tile Registers */

/*!< SYSSTAT: Address: 0x00		System Manager Register */
typedef union
{
	__IO uint8_t b                      	: 8;
	struct {
		__IO uint8_t nINTM  				: 1;		/*!< Interrupt mask: 0: masked; 1: not masked	*/
		__IO uint8_t FLTM					: 1;		/*!< Fault mask: 0: not masked; 1: masked		*/
		     uint8_t        				: 1;
		__IO uint8_t REFBP					: 1;		/*!< Set external reference via AB5				*/
		__IO uint8_t VTHREF					: 2;		/*!< Threshold voltage for AIO<9:6> (00b: 0.1V, 01b: 0.2V, 10b: 0.5V, 11b: 1.25V	*/
		__I  uint8_t TMPWARN				: 1;		/*!< Temperature warning. Clear on read.		*/
		__IO uint8_t PBSTAT					: 1;		/*!< Push button status. Write 1 to clear.		*/
	};
} SYSSTAT;

#endif // #ifdef CAFE_ARCH2

#endif  // PAC5XXX_TILE_SYSTEM_MANAGER_H
