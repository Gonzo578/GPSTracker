/**
 * \file sol.c
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

#include "includes.h"				/* Generic include file */
#include "dio.h"					/* Include digital IO interface */
#include "sol.h"					/* Include own interface definition */


/*
*********************************************************************************************************
*							LOCAL DEFINITIONS
*********************************************************************************************************
*/

#define SOL_LED_ON_TIME			OS_TICKS_PER_SEC
#define SOL_LED_OFF_TIME		OS_TICKS_PER_SEC

/*
*********************************************************************************************************
*							LOCAL TYPES
*********************************************************************************************************
*/

typedef enum _TTaskState {
	SOL_ON,			/**< Sign of life LED is on */
	SOL_OFF			/**< Sign of life LED is off*/
}TTaskState;

/*
*********************************************************************************************************
*							FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void SOL_vHandleTask(void *p_arg);

/*
*********************************************************************************************************
*							LOCAL CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							LOCAL VARIABLES
*********************************************************************************************************
*/
static OS_STK		SOL_atTaskStack[APP_TASK_SOL_STK_SIZE];		/* Sign of life task stack */
static TTaskState	SOL_tTaskState	= SOL_OFF;

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/

/**
 * \brief Sign of life task function
 * */
static void SOL_vHandleTask(void *p_arg) {
	while (1) {
		/* Keep task in an endless loop */
		switch(SOL_tTaskState) {
		case SOL_ON:
			SOL_tTaskState = SOL_OFF;
			DIO_vSetPort(SOL_LED_PORT, SOL_LED_OUTPUT);
			OSTimeDly(SOL_LED_ON_TIME);
			break;
		case SOL_OFF:
			DIO_vResetPort(SOL_LED_PORT, SOL_LED_OUTPUT);
			SOL_tTaskState = SOL_ON;
			OSTimeDly(SOL_LED_OFF_TIME);
			break;
		}
	}
}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

void SOL_vInitSignOfLifeTask(void) {
	INT8U  os_err;

	os_err = OSTaskCreate (	(void (*)(void *)) SOL_vHandleTask,  /* Create the start task.                               */
	                            (void          * ) 0,
	                            (OS_STK        * )&SOL_atTaskStack[APP_TASK_SOL_STK_SIZE - 1],
	                            (INT8U           ) SOL_TASK_PRIO);
}
