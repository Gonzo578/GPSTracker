/**
 * \file mmi.c
 *
 * \author	Ralf Hochhausen
 * \Date	04.04.2012
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

#include "includes.h"		/* Include global header file */
#include "tracker.h"		/* Include tracker interface */
#include "mmi.h"			/* Include own interface */

/*
*********************************************************************************************************
*							LOCAL TYPE DEFINITIONS
*********************************************************************************************************
*/

/**
 * 	\brief	Enumerated type definition of the supported views
 * */
typedef enum _TViewMode {
	MMI_DATA_VIEW,			/**< Data view => Displaying actual GPS data */
	MMI_MENU_VIEW,			/**< Menu view => Parameter setting */
	MMI_SERVICE_VIEW,		/**< Service view => Displaying service data */
	MMI_NO_OF_VIEWS			/**< Number of supported views */
}TViewMode;

/**
 * 	\brief	Enumerated type definition of the supported data views
 * */
typedef enum _TDataView {
	MMI_DATA_VIEW_1,		/**< Data view no. 1 */
	MMI_DATA_VIEW_2,		/**< Data view no. 2 */
	MMI_DATA_VIEW_3,		/**< Data view no. 3 */
	MMI_DATA_VIEW_4,		/**< Data view no. 4 */
	MMI_No_OF_DATA_VIEWS	/**< Number of supported data views */
}TDataView;

/**
 * 	\brief	Type definition of the tracker state machine states
 * */
typedef enum _TTrackerStates {
	MMI_TRACK_STATE_IDLE,			/**< Tracker is in idle state => no data is tracked */
	MMI_TRACK_STATE_ACTIVE			/**< Tracker is active => position data is tracked */
}TTrackerStates;

/*
*********************************************************************************************************
*							FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void MMI_vHandleTask(void *p_arg);

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

/*
*********************************************************************************************************
*							LOCAL VARIABLES
*********************************************************************************************************
*/

static OS_STK MMI_atTaskStack[MMI_TASK_STK_SIZE];		/* MMI task stack */

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/
static void MMI_vHandleTask(void *p_arg) {

	/* Start of endless loop */
	while(1) {
		OSTimeDly(100);
	}
}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

void MMI_vInitTask(void) {
	INT8U  os_err;

	os_err = OSTaskCreate (	(void (*)(void *)) MMI_vHandleTask,  /* Create the start task */
	                            (void          * ) 0,
	                            (OS_STK        * )&MMI_atTaskStack[MMI_TASK_STK_SIZE - 1],
	                            (INT8U           ) MMI_TASK_PRIO);
}
