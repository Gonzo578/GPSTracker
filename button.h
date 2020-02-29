/**
 * \file button.h
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

#ifndef __BUTTON_H_
#define __BUTTON_H_

/*
*********************************************************************************************************
*							INCLUDES
*********************************************************************************************************
*/
#include "includes.h"			/* Include generic header */
#include "dio.h"				/* Include digital IO interface */
#include "ButtonConfig.h"		/* Include button configuration header */

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
 * 	\brief	Type definition of a button callback event function
 * */
typedef void (*pfBtnCallback)(uint32 tBtnId);

/**
 * 	\brief	Type definition of a button configuration item
 * */
typedef struct _TButtonCfg {
	TBtnId			tBtnID;					/**< ID of the button */
	TIoPort*		ptBtnIOPort;			/**< IO Port the button is located on */
	uint16_t		uiPortMask;				/**< IO port mask of the button */
	pfBtnCallback	pfBtnPressedEvent;		/**< Button pressed event function */
	pfBtnCallback	pfBtnReleasedEvent;		/**< Button released event function */
}TButtonCfg;

/**
 * \brief	Button state type definition
 * */
typedef enum _TButtonState {
	BTN_RELEASED,			/**< Button is released */
	BTN_PRESSED,			/**< Button is pressed */
}TButtonState;

/**
 * 	\brief	Button data object
 * */
typedef struct _TButton {
	TButtonState	tState;
	BOOL			bButtonSample;
	uchar8			ucDebounceCounter;
}TButton;

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

/**
 * 	\brief	Init function of the button debounce task
 *
 * 	\return	void
 * */
void BTN_vInitButtonTask(void);

/**
 * 	\brief	Declaration of a default button event which can be used for button configuration
 * */
void BTN_vDefaultEvent (uint32 tBtnId);

#endif /* __BUTTON_H_ */
