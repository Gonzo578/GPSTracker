/**
 * \file dio.h	Interface of the digital IO HAL
 *
 *				This interface provides a simple means of configuration and
 *				access of general purpose digital IOs. That means it allows
 *				to set and reset digital IOs to a defined level.
 *
 * \author	Ralf Hochhausen
 * \Date	03-09-2012
 *
 * \copyright GNU Public License Version 3.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 * */

#ifndef __DIO_H_
#define __DIO_H_

/*
*********************************************************************************************************
*							INCLUDES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							GLOBAL DEFINITIONS
*********************************************************************************************************
*/

/*
 * Definition of the port pin bit masks
 *
 * These bit masks can be used to set and reset IO port pins.
 * */
#define DIO_IO_0			0x0001			/**< IO port mask pin 0 */
#define DIO_IO_1			0x0002			/**< IO port mask pin 1	*/
#define DIO_IO_2			0x0004			/**< IO port mask pin 2	*/
#define DIO_IO_3			0x0008			/**< IO port mask pin 3	*/
#define DIO_IO_4			0x0010			/**< IO port mask pin 4	*/
#define DIO_IO_5			0x0020			/**< IO port mask pin 5	*/
#define DIO_IO_6			0x0040			/**< IO port mask pin 6	*/
#define DIO_IO_7			0x0080			/**< IO port mask pin 7	*/
#define DIO_IO_8			0x0100			/**< IO port mask pin 8	*/
#define DIO_IO_9			0x0200			/**< IO port mask pin 9	*/
#define DIO_IO_10			0x0400			/**< IO port mask pin 10 */
#define DIO_IO_11			0x0800			/**< IO port mask pin 11 */
#define DIO_IO_12			0x1000			/**< IO port mask pin 12 */
#define DIO_IO_13			0x2000			/**< IO port mask pin 13 */
#define DIO_IO_14			0x4000			/**< IO port mask pin 14 */
#define DIO_IO_15			0x8000			/**< IO port mask pin 15 */
#define	DIO_IO_ALL			0xFFFF			/**< IO port mask, all bits set */

/*
 * Definition of the GPIO port clock enable/disable bit masks
 *
 * Use these bit masks to enable or disable the according GPIO with the
 * configuration object.
 * */
#define GPIOA_ENABLE		RCC_APB2ENR_IOPAEN		/**< GPIO port A enable */
#define GPIOB_ENABLE		RCC_APB2ENR_IOPBEN		/**< GPIO port B enable */
#define GPIOC_ENABLE		RCC_APB2ENR_IOPCEN		/**< GPIO port C enable */
#define GPIOD_ENABLE		RCC_APB2ENR_IOPDEN		/**< GPIO port D enable */
#define GPIOE_ENABLE		RCC_APB2ENR_IOPEEN		/**< GPIO port E enable */
#define GPIOF_ENABLE		RCC_APB2ENR_IOPFEN		/**< GPIO port F enable */
#define GPIOG_ENABLE		RCC_APB2ENR_IOPGEN		/**< GPIO port G enable */

#define GPIOA_DISABLE		((uint32_t)0x00000000)	/**< GPIO port A disable */
#define GPIOB_DISABLE		((uint32_t)0x00000000)	/**< GPIO port B disable */
#define GPIOC_DISABLE		((uint32_t)0x00000000)	/**< GPIO port C disable */
#define GPIOD_DISABLE		((uint32_t)0x00000000)	/**< GPIO port D disable */
#define GPIOE_DISABLE		((uint32_t)0x00000000)	/**< GPIO port E disable */
#define GPIOF_DISABLE		((uint32_t)0x00000000)	/**< GPIO port F disable */
#define GPIOG_DISABLE		((uint32_t)0x00000000)	/**< GPIO port G disable */

#define DIO_PUSHPULL_10MHz_OUT		0x1		/**< IO port push-pull output 10MHz */
#define DIO_PUSHPULL_2MHz_OUT		0x2		/**< IO port push-pull output 2MHz */
#define DIO_PUSHPULL_50MHz_OUT		0x3		/**< IO port push-pull output 50MHz */
#define	DIO_OPENDRAIN_10MHz_OUT		0x5		/**< IO port open-drain output 10MHz */
#define	DIO_OPENDRAIN_2MHz_OUT		0x6		/**< IO port open-drain output 2MHz */
#define	DIO_OPENDRAIN_50MHz_OUT		0x7		/**< IO port open-drain output 50MHz */
#define DIO_ALT_PUSHPULL_10MHz_OUT	0x9		/**< IO port alternate function push-pull output 10MHz */
#define DIO_ALT_PUSHPULL_2MHz_OUT	0xA		/**< IO port alternate function push-pull output 2MHz */
#define DIO_ALT_PUSHPULL_50MHz_OUT	0xB		/**< IO port alternate function push-pull output 50MHz */
#define DIO_ALT_OPENDRAIN_10MHz_OUT	0xD		/**< IO port alternate function open-drain output 10MHz */
#define DIO_ALT_OPENDRAIN_2MHz_OUT	0xE		/**< IO port alternate function open-drain output 2MHz */
#define DIO_ALT_OPENDRAIN_50MHz_OUT	0xF		/**< IO port alternate function open-drain output 50MHz */
#define DIO_ANALOG_IN				0x0		/**< IO port analog input */
#define DIO_FLOATING_IN				0x4		/**< IO port floating input */
#define DIO_PULLDOWN_IN				0x8		/**< IO port pull-down input  (don't forget pull up/down config) */
#define DIO_PULLUP_IN				0x8		/**< IO port pull-up input (don't forget pull up/down config) */

#define	DIO_PULL_NONE				0		/**< IO use this definition if no pull resistor is used */
#define DIO_PULLDOWN				0		/**< IO port pull-down configuration */
#define DIO_PULLUP					1		/**< IO port pull-up configuration */

/*
*********************************************************************************************************
*							GLOBAL TYPES
*********************************************************************************************************
*/

/**
 * 	\brief	Type re-definition of the generic GPIO register set type
 * */
typedef GPIO_TypeDef	TIoPort;

/**
 * \brief	Type definition of an IO Port configuration item
 * */
typedef struct _TDioConfigItem {
	uint32_t	ulPortActivation;		/**< Activate/deactivate port */
	TIoPort*	tIoPort;				/**< Pointer to the GPIO port => use GPIOx where x is A..G*/
	uint32_t	ulPortConfigHigh;		/**< Port configuration register HIGH (pins 8..15) */
	uint32_t	ulPortConfigLow;		/**< Port configuration register LOW (pins 0..7) */
	uint32_t	ulInitialOutputState;	/**< Initial IO port output state */
	uint16_t	uiPullUpDownConfig;		/**< Port pull-up/-down configuration */
}TDioConfig;

/*
*********************************************************************************************************
*							GLOBAL CONSTANTS
*********************************************************************************************************
*/

/**
 * 	\brief	External IO port configuration object
 * */
extern const TDioConfig	DIO_atIoPortConfig[];
/**
 * 	\brief	Size of the port configuration object
 * */
extern const uint32	DIO_ulConfigSize;

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

/**
 * 	\brief	Set IO port interface
 *
 * 			This function sets the passed IO ports to logic HIGH state.
 * 			It is possible to set several pins of one port at a time.
 *
 * 	\param	ptIoPort	IO port GPIOx with x=A..G
 * 	\param	uiPortMask	IO port set mask
 *
 * 	\return	void
 * */
void DIO_vSetPort(TIoPort* ptIoPort, uint16_t uiPortMask);

/**
 * 	\brief	Reset IO port interface
 *
 * 			This function sets the passed IO ports to logic LOW state.
 * 			It is possible to reset several pins of one port at a time.
 *
 * 	\param	ptIoPort	IO port GPIOx with x=A..G
 * 	\param	uiPortMask	IO port reset mask
 *
 * 	\return	void
 * */
void DIO_vResetPort(TIoPort* ptIoPort, uint16_t uiPortMask);

/**
 * 	\brief	Read IO port interface
 *
 * 			This function returns the current state of the passed IO port.
 *
 * 	\param	ptIoPort	IO port to read GPIOx with x=A..G
 *
 * 	\return	void
 * */
uint16_t DIO_uiReadPort(TIoPort* ptIoPort);

/**
 * 	\brief	Read IO port interface
 *
 * 			This function returns the current state of the passed IO port
 * 			pins. Several IO pins of a port can be read at a time via the
 * 			bit mask.
 *
 * 	\param	ptIoPort	IO port to read GPIOx with x=A..G
 * 	\param	uiPortMask	Bit mask with pins to be read
 *
 * 	\return	BOOL	TRUE => All passed pins are set
 * */
BOOL DIO_bReadPortPin(TIoPort* ptIoPort, uint16_t uiPortMask);

/**
 * 	\brief	IO port initialization function
 *
 * 			This function initializes the GPIO ports regarding the passed
 * 			configuration.
 *
 * 	\param	ptCfg		Pointer to the configuration object
 * 	\param	ulCfgSize	Size of the configuration object
 * */
void DIO_vInitPorts(const TDioConfig* ptCfg, const uint32 ulCfgSize);


#endif /* __DIO_H_ */
