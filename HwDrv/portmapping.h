/**
 * \file portmapping.h
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

#ifndef __PORTMAPPING_H_
#define __PORTMAPPING_H_

/*
*********************************************************************************************************
*							INCLUDES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							IO PORT MAPPING DEFINITIONS
*********************************************************************************************************
*/

/**********************************************************************************************************************
 * 	OUTPUT CONFIGURATION
 ********************************************************************************************************************** */
#define GPS_POS_FIXED_PORT			GPIOB			/**< GPS position fixed IO port */
#define GPS_POS_FIXED_OUTPUT		DIO_IO_12		/**< GPS position fixed IO port pin */

#define GPS_TRACK_MODE_PORT			GPIOB			/**< GPS SD card tracking IO port */
#define GPS_TRACK_MODE_OUTPUT		DIO_IO_13		/**< GPS SD card tracking IO port pin */

#define ERR_ERROR_MODE_PORT			GPIOB			/**< Error mode IO port */
#define ERR_ERROR_MODE_OUTPUT		DIO_IO_14		/**< Error mode IO port pin */

#define SOL_LED_PORT				GPIOB			/**< Sign of life IO port */
#define SOL_LED_OUTPUT				DIO_IO_15		/**< Sign of life IO port pin */

/**********************************************************************************************************************
 * 	BUTTON INPUT CONFIGURATION
 ********************************************************************************************************************** */
#define BTN_TRACK_ENABLE_PORT		GPIOG			/**< GPS tracking enable/disable IO port */
#define BTN_TRACK_ENABLE_INPUT		DIO_IO_8		/**< GPS tracking enable/disable IO port pin */

#define BTN_LAP_RESET_PORT			GPIOC			/**< Lap/Reset IO port */
#define BTN_LAP_RESET_INPUT			DIO_IO_13		/**< Lap/Reset IO port pin */

#define BTN_JOYSTICK_UP_PORT		GPIOG
#define BTN_JOYSTICK_UP_INPUT		DIO_IO_15

#define BTN_JOYSTICK_DOWN_PORT		GPIOD
#define BTN_JOYSTICK_DOWN_INPUT		DIO_IO_3

#define BTN_JOYSTICK_LEFT_PORT		GPIOG
#define BTN_JOYSTICK_LEFT_INPUT		DIO_IO_14

#define BTN_JOYSTICK_RIGHT_PORT		GPIOG
#define BTN_JOYSTICK_RIGHT_INPUT	DIO_IO_13

#define BTN_JOYSTICK_SELECT_PORT	GPIOG
#define BTN_JOYSTICK_SELECT_INPUT	DIO_IO_7

#endif /* __PORTMAPPING_H_ */
