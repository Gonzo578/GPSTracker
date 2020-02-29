/**
 * \file tracker.c
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

#include "includes.h"			/* Include generic header file */
#include <string.h>
#include "gpxLogger.h"
#include "nmeaparser.h"
#include "utility.h"

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

/**
 * 	\brief	Tracker task stack
 * */
static OS_STK TRK_atTaskStack[TRK_TASK_STACK_SIZE];

OS_EVENT*	TRK_ptTrackStartStop;		/**< Tracker start stop semaphore */
static TTrackPoint	TRK_tTackPoint;


extern TLatitudeObj		GPSL_tLatitude;
extern TLongitudeObj	GPSL_tLongitude;
extern TUTCTime			GPST_tUTCTime;
extern TDate			GPST_tDate;

/*
*********************************************************************************************************
*							FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static	void  TRK_vHandleTask(void *p_arg);

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/
uint8 DBG_ucTriggerLog = 0;
uint8 DBG_ucLog = 0;
uint8 DBG_ucStopLog = 0;
static	void  TRK_vHandleTask(void *p_arg) {
	(void)p_arg;

	while(1) {
		if(DBG_ucTriggerLog != 0) {
			DBG_ucTriggerLog = 0;
			GPXL_tStartLogging(GPXL_ptGPXLogger);
		}

		if(DBG_ucLog != 0) {
			UTI_vStrCopy(GPST_tUTCTime.strUTCTime, TRK_tTackPoint.strUTC);
			TRK_tTackPoint.strDateISO8601[0] = GPST_tDate.strDate[6];
			TRK_tTackPoint.strDateISO8601[1] = GPST_tDate.strDate[7];
			TRK_tTackPoint.strDateISO8601[2] = GPST_tDate.strDate[8];
			TRK_tTackPoint.strDateISO8601[3] = GPST_tDate.strDate[9];
			TRK_tTackPoint.strDateISO8601[4] = '-';
			TRK_tTackPoint.strDateISO8601[5] = GPST_tDate.strDate[3];
			TRK_tTackPoint.strDateISO8601[6] = GPST_tDate.strDate[4];
			TRK_tTackPoint.strDateISO8601[7] = '-';
			TRK_tTackPoint.strDateISO8601[8] = GPST_tDate.strDate[0];
			TRK_tTackPoint.strDateISO8601[9] = GPST_tDate.strDate[1];
			TRK_tTackPoint.tLat = GPSL_tLatitude.tLatitude;
			TRK_tTackPoint.tLon = GPSL_tLongitude.tLongitude;
			GPXL_tLogTrackPoint(GPXL_ptGPXLogger, &TRK_tTackPoint);
		}

		if(DBG_ucStopLog != 0) {
			DBG_ucStopLog = 0;
			GPXL_tStopLogging(GPXL_ptGPXLogger);
		}
		OSTimeDly(100);
	}
}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

void	TRK_vInitTask(void) {
	INT8U  os_err;

    os_err = OSTaskCreate (	(void (*)(void *)) TRK_vHandleTask,  /* Create the start task.                               */
                            (void          * ) 0,
                            (OS_STK        * )&TRK_atTaskStack[TRK_TASK_STACK_SIZE - 1],
                            (INT8U           ) TRK_TASK_PRIO);
}
