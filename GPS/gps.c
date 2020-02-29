/**
 * \file gps.c
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

#include "includes.h"		/* Include global header file */
#include "nmeadll.h"		/* Include NMEA data link layer interface */
#include "nmeaparser.h"		/* Include NMEA parser interface */
#include "gpsstate.h"		/* INclude GPS state interface */
#include "gps.h"			/* Include own interface declaration */

/*
*********************************************************************************************************
*							LOCAL TYPE DEFINITIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static void GPS_vGPSDeviceTask (void *p_arg);

/*
*********************************************************************************************************
*							LOCAL DEFINITIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							LOCAL VARIABLES
*********************************************************************************************************
*/
static OS_STK GPS_atGPSDeviceTaskStack[GPS_DEVICE_TASK_STK_SIZE];

/*
*********************************************************************************************************
*							LOCAL CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/


/**
 * \brief	GPS Device TASK Handler
 *
 * 			This function is an OS TASK!\n
 * 			The function waits until a new NMEA frame has been received form the
 * 			GPS receiver and then it triggers the parser to parse the frame
 * 			and to extract all needed data. When the frame is parsed, the frame
 * 			is released from the NMEA DLL buffer to allow a new frame to be stored.
 *
 * \return	void
 * */
static	void  GPS_vGPSDeviceTask (void *p_arg) {
	uchar8*		pucNMEAFrame;

	(void)p_arg;		/* Prevent compiler warnings */

	while(1) {
		/*
		 * Fetch next frame from NMEA data link layer.
		 * Note: 	The Task will be blocked by the interface until the next frame
		 * 			is received.
		 * */
		pucNMEAFrame = NMEAD_pucGetNMEAFrame();

		/*
		 * Parse the received frame
		 * */
		(void)NMEAP_tParseNMEAFrame(pucNMEAFrame, NMEAP_atFrameConfig, NMEAP_ulFrameConfigSize);

		/*
		 * NMEA frame data has been parsed
		 * => Release frame from buffer
		 * */
		NMEAD_vReleaseFrame();

		/*
		 * Check GPS position signal state
		 * */
		GPSS_vCheckGPSPositionFixState();
	}
}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

/*---------------------------------------------------------------------------------------------------------------------
 * void GPS_vInitGPSDeviceTask(void)
 *--------------------------------------------------------------------------------------------------------------------- */
void GPS_vInitGPSDeviceTask(void) {
	INT8U  os_err;

    os_err = OSTaskCreate (	(void (*)(void *)) GPS_vGPSDeviceTask,  /* Create the start task.                               */
                            (void          * ) 0,
                            (OS_STK        * )&GPS_atGPSDeviceTaskStack[GPS_DEVICE_TASK_STK_SIZE - 1],
                            (INT8U           ) GPS_DEVICE_TASK_PRIO);

	NMEAD_vInitNMEADll();				/* NMEA protocol data link layer */
}
