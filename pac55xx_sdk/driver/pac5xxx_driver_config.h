/**************************************************************************//**
 * @file     pac5xxx_driver_config.h
 * @brief    Firmware driver configuration for the PAC5XXX
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
 
#ifndef PAC5XXX_DRIVER_CONFIG_H
#define PAC5XXX_DRIVER_CONFIG_H

/** @addtogroup PAC5XXX_Driver_Config PAC5XXX Driver Config
  @{
*/

//#define ALL_RAM

#ifdef ALL_RAM
#define PAC5XXX_DRIVER_GPIO_RAM		    /*!< Link GPIO driver functions in RAM    				*/
#define PAC5XXX_DRIVER_SPI_RAM		    /*!< Link SPI driver functions in RAM     				*/
#define PAC5XXX_DRIVER_SOCBRIDGE_RAM		/*!< Link SOC Bridge driver functions in RAM 			*/
#define PAC5XXX_DRIVER_TIMER_RAM		  /*!< Link Timer driver functions in RAM    				*/
#define PAC5XXX_DRIVER_I2C_RAM	  		/*!< Link I2C driver functions in RAM    				*/
#define PAC5XXX_DRIVER_SYSTEM_RAM     /*!< Link System driver functions in RAM    			*/
#define PAC5XXX_DRIVER_UART_RAM       /*!< Link UART driver functions in RAM    				*/
#define PAC5XXX_DRIVER_ADC_RAM        /*!< Link ADC driver functions in RAM    				*/
#define PAC5XXX_DRIVER_MEMORY_RAM     /*!< Link Memory Controller driver functions in RAM    	*/
#define PAC5XXX_DRIVER_WATCHDOG_RAM   /*!< Link Watchdog Timer driver functions in RAM    	*/
#define PAC5XXX_DRIVER_RTC_RAM        /*!< Link Real-time Clock driver functions in RAM */
#define PAC5XXX_DRIVER_ARM_RAM        /*!< Link ARM driver functions into RAM        */
#define PAC5XXX_DRIVER_TILE_RAM		/*!< Link Tile driver functions into RAM		*/
#else
//#define PAC5XXX_DRIVER_GPIO_RAM		    /*!< Link GPIO driver functions in RAM    				*/
//#define PAC5XXX_DRIVER_SPI_RAM		    /*!< Link SPI driver functions in RAM     				*/
//#define PAC5XXX_DRIVER_SOCBRIDGE_RAM		/*!< Link SOC Bridge driver functions in RAM 			*/
//#define PAC5XXX_DRIVER_TIMER_RAM		  /*!< Link Timer driver functions in RAM    				*/
//#define PAC5XXX_DRIVER_I2C_RAM	  		/*!< Link I2C driver functions in RAM    				*/
//#define PAC5XXX_DRIVER_SYSTEM_RAM     /*!< Link System driver functions in RAM    			*/
//#define PAC5XXX_DRIVER_UART_RAM       /*!< Link UART driver functions in RAM    				*/
//#define PAC5XXX_DRIVER_ADC_RAM        /*!< Link ADC driver functions in RAM    				*/
//#define PAC5XXX_DRIVER_MEMORY_RAM     /*!< Link Memory Controller driver functions in RAM    	*/
//#define PAC5XXX_DRIVER_WATCHDOG_RAM   /*!< Link Watchdog Timer driver functions in RAM    	*/
//#define PAC5XXX_DRIVER_RTC_RAM        /*!< Link Real-time Clock driver functions in RAM */
//#define PAC5XXX_DRIVER_ARM_RAM        /*!< Link ARM driver functions into RAM        */
//#define PAC5XXX_DRIVER_TILE_RAM			/*!< Link tile driver functions into RAM		*/
#endif

/*@}*/ /* end of group PAC5XXX_Driver_Config */

#endif // PAC5XXX_DRIVER_CONFIG_H

