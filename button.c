/**
 * \file button.c
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

#include "button.h"				/* Include own header */

/*
*********************************************************************************************************
*							LOCAL TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void BTN_vHandleButton(TBtnId tId);
static void BTN_vButtonSamplingTask (void *p_arg);

/*
*********************************************************************************************************
*							LOCAL DEFINITIONS
*********************************************************************************************************
*/

#define BTN_SAMPLING_PERIOD			5			/**< Button sampling period in OS ticks */
#define BTN_MAX_DEBOUNCE_VALUE		6			/**< Max. value of the debounce counter */
#define BTN_PRESSED_THRESHOLD		5
#define BTN_RELEASED_THRESHOLD		1

/*
*********************************************************************************************************
*							LOCAL CONSTANTS
*********************************************************************************************************
*/

extern const TButtonCfg BTN_atConfig[];

/*
*********************************************************************************************************
*							LOCAL VARIABLES
*********************************************************************************************************
*/
static OS_STK	BTN_atButtonSamplingTaskStack[BTN_TASK_STK_SIZE];
static TButton	BTN_atButtons[BTN_NO_OF_BUTTONS] = {0};

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/

static void BTN_vHandleButton(TBtnId tId) {
	BTN_atButtons[tId].bButtonSample = DIO_bReadPortPin(BTN_atConfig[tId].ptBtnIOPort, BTN_atConfig[tId].uiPortMask);

	if (BTN_atButtons[tId].bButtonSample != FALSE) {
		/* Key button is released */
		if (BTN_atButtons[tId].ucDebounceCounter > 0) {
			BTN_atButtons[tId].ucDebounceCounter--;
		}
	} else {
		/* Button is pressed */
		if (BTN_atButtons[tId].ucDebounceCounter < BTN_MAX_DEBOUNCE_VALUE) {
			BTN_atButtons[tId].ucDebounceCounter++;
		}
	}

	switch (BTN_atButtons[tId].tState) {
	case BTN_RELEASED:
		if(BTN_atButtons[tId].ucDebounceCounter > BTN_PRESSED_THRESHOLD) {
			BTN_atButtons[tId].tState = BTN_PRESSED;
			BTN_atConfig[tId].pfBtnPressedEvent(tId);
		}
		break;
	case BTN_PRESSED:
		if(BTN_atButtons[tId].ucDebounceCounter < BTN_RELEASED_THRESHOLD) {
			BTN_atButtons[tId].tState = BTN_RELEASED;
			BTN_atConfig[tId].pfBtnReleasedEvent(tId);
		}
		break;
	default:
		break;
	}
}

static	void  BTN_vButtonSamplingTask (void *p_arg) {
	(void)p_arg;
	uint32 ulIdx = 0;

	/*
	 * 	First initialize all push button data objects
	 * */
	for(ulIdx = 0; ulIdx < BTN_NO_OF_BUTTONS; ulIdx++) {
		BTN_atButtons[ulIdx].tState				= BTN_RELEASED;
		BTN_atButtons[ulIdx].bButtonSample		= 0;
		BTN_atButtons[ulIdx].ucDebounceCounter	= 0;
	}

	/*
	 * 	Enter the endless button debounce loop
	 * */
	while(1) {
		for(ulIdx = 0; ulIdx < BTN_NO_OF_BUTTONS; ulIdx++) {
			BTN_vHandleButton((TBtnId)ulIdx);
		}
		OSTimeDly(BTN_SAMPLING_PERIOD);
	}
}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

void BTN_vDefaultEvent (uint32 tBtnId) {
	(void)tBtnId;		/* Prevent compiler warning */
}

void BTN_vInitButtonTask(void) {
	INT8U  os_err;

	os_err = OSTaskCreate (	(void (*)(void *)) BTN_vButtonSamplingTask,  /* Create the start task.                               */
                            (void          * ) 0,
                            (OS_STK        * )&BTN_atButtonSamplingTaskStack[BTN_TASK_STK_SIZE - 1],
                            (INT8U           ) BTN_SAMPLING_TASK_PRIO);
}
