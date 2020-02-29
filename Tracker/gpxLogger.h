/**
 * \file gpxLogger.h
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

#ifndef __GPXLOGGER_H_
#define __GPXLOGGER_H_

/*
*********************************************************************************************************
*							INCLUDES
*********************************************************************************************************
*/

#include "includes.h"			/* Include generic includes */
#include "gps_types.h"			/* Include generic GPX types */

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

typedef struct TGPXLogger TGPXLogger;

typedef enum _TGPXLoggerErr {
	GPLX_ERR_OK,				/**< No error */
	GPXL_ERR_ERROR				/**< Error */
}TGPXLoggerErr;

typedef struct _TTrackPoint {
	TLatitude	tLat;
	TLongitude	tLon;
	uchar8		strUTC[NMEAD_UTC_STR_SIZE+1];
	uchar8		strDateISO8601[NMEAD_DATE_STR_SIZE+1];
}TTrackPoint;

/*
*********************************************************************************************************
*							GLOBAL CONSTANTS
*********************************************************************************************************
*/

extern TGPXLogger* const GPXL_ptGPXLogger;		/** Pointer to the GPX logger object */

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

/**
 *
 * */
TGPXLoggerErr GPXL_tStartLogging(TGPXLogger* this);

/**
 *
 * */
TGPXLoggerErr GPXL_tStopLogging(TGPXLogger* this);

/**
 *
 * */
TGPXLoggerErr GPXL_tLogTrackPoint(TGPXLogger* this, TTrackPoint* ptTrkPt);

/**
 *
 * */
TGPXLoggerErr GPXL_tLogLap(TGPXLogger* this);

/**
 *
 * */
TGPXLoggerErr GPXL_tInit(TGPXLogger* this);

#endif /* __GPXLOGGER_H_ */
