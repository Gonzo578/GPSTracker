/**
 * \file ButtonConfig.c
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

#ifndef __BUTTONCONFIG_H_
#define __BUTTONCONFIG_H_

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
*********************************************************************************************************
*							GLOBAL TYPES
*********************************************************************************************************
*/

/**
 * 	\brief	Enumerated type definition of the configured push buttons
 * */
typedef enum _TBtnId {
	BTN_TRACK_START_STOP,		/**< Track start/stop button */
	BTN_LAP_RESET,				/**< Lap and track reset button */
	BTN_JOYSTICK_UP,			/**< Joystick 'UP' */
	BTN_JOYSTICK_DOWN,			/**< Joystick 'DOWN' */
	BTN_JOYSTICK_LEFT,			/**< Joystick 'LEFT' */
	BTN_JOYSTICK_RIGHT,			/**< Joystick 'RIGHT' */
	BTN_JOYSTICK_SELECT,		/**< Joystick 'SELECT' */
	BTN_NO_OF_BUTTONS			/**< End marker for button configuration */
}TBtnId;

/*
*********************************************************************************************************
*							GLOBAL CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

#endif /* __BUTTONCONFIG_H_ */
