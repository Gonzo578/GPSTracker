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

/*
*********************************************************************************************************
*							INCLUDES
*********************************************************************************************************
*/

#include "includes.h"			/* Include generic definitions and include files */
#include "portmapping.h"		/* Include IO port mapping */
#include "button.h"				/* Include push button interface */

/*
*********************************************************************************************************
*							FUNCTION PROTOTYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							LOCAL DEFINITIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							LOCAL CONSTANTS
*********************************************************************************************************
*/

const TButtonCfg BTN_atConfig[BTN_NO_OF_BUTTONS] = {
/*		tBtnID					ptBtnIOPort					uiPortMask					pfBtnPressedEvent	pfBtnReleasedEvent*/
	{	BTN_TRACK_START_STOP,	BTN_TRACK_ENABLE_PORT,		BTN_TRACK_ENABLE_INPUT,		BTN_vDefaultEvent,	BTN_vDefaultEvent},		/**< Track start/stop button */
	{	BTN_LAP_RESET,			BTN_LAP_RESET_PORT,			BTN_LAP_RESET_INPUT,		BTN_vDefaultEvent,	BTN_vDefaultEvent},		/**< Lap/Reset button */
	{	BTN_JOYSTICK_UP,		BTN_JOYSTICK_UP_PORT,		BTN_JOYSTICK_UP_INPUT,		BTN_vDefaultEvent,	BTN_vDefaultEvent},		/**< Joystick 'UP' */
	{	BTN_JOYSTICK_DOWN,		BTN_JOYSTICK_DOWN_PORT,		BTN_JOYSTICK_DOWN_INPUT,	BTN_vDefaultEvent,	BTN_vDefaultEvent},		/**< Joystick 'DOWN' */
	{	BTN_JOYSTICK_LEFT,		BTN_JOYSTICK_LEFT_PORT,		BTN_JOYSTICK_LEFT_INPUT,	BTN_vDefaultEvent,	BTN_vDefaultEvent},		/**< Joystick 'LEFT' */
	{	BTN_JOYSTICK_RIGHT,		BTN_JOYSTICK_RIGHT_PORT,	BTN_JOYSTICK_RIGHT_INPUT,	BTN_vDefaultEvent,	BTN_vDefaultEvent},		/**< Joystick 'RIGHT' */
	{	BTN_JOYSTICK_SELECT,	BTN_JOYSTICK_SELECT_PORT,	BTN_JOYSTICK_SELECT_INPUT,	BTN_vDefaultEvent,	BTN_vDefaultEvent},		/**< Joystick 'SELECT' */
};

/*
*********************************************************************************************************
*							LOCAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/
