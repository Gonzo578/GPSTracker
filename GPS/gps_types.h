/**
 * \file gps_types.h
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

#ifndef __GPS_TYPES_H_
#define __GPS_TYPES_H_

/*
*********************************************************************************************************
*							INCLUDES
*********************************************************************************************************
*/

#include "types.h"			/**< Include generic data types */

/*
*********************************************************************************************************
*							GLOBAL DEFINITIONS
*********************************************************************************************************
*/

#define	NMEAD_LONGITUDE_STR_SIZE		11		/**< */
#define	NMEAD_LATITUDE_STR_SIZE			10		/**< */
#define NMEAD_UTC_STR_SIZE				11		/**< */
#define NMEAD_DATE_STR_SIZE				10		/**< */
#define NMEAD_EW_IND_STR_SIZE			1		/**< */
#define NMEAD_NS_IND_STR_SIZE			1		/**< */
#define NMEAD_POS_FIX_STR_SIZE			1		/**< */

/*
*********************************************************************************************************
*							GLOBAL TYPES
*********************************************************************************************************
*/

/**
 * \brief	Type definition of the numerical longitude data type
 * */
typedef sint32	TLongitude;

/**
 * \brief	Type definition of the numerical latitude data type
 * */
typedef sint32	TLatitude;

/**
 * \brief	Type definition of the East/West indicator
 * */
typedef enum _TEWIndicator {
	EW_UNDEFINED,
	EAST,
	WEST
}TEWIndicator;

/**
 * \brief	Type definition of the North/South indicator
 * */
typedef enum _TNSIndicator {
	NS_UNDEFINED,
	NORTH,
	SOUTH
}TNSIndicator;

typedef enum _TPosFixStatus {
	POSITION_INVALID,
	POSITION_FIXED
}TPosFixStatus;

/**
 * \brief	Latitude data object
 * */
typedef struct _TLatitude {
	uchar8			strLatitude[NMEAD_LATITUDE_STR_SIZE+1];		/**< Longitude string */
	uchar8			strNSIndicator[NMEAD_NS_IND_STR_SIZE+1];	/**< North/South indicator string */
	TLatitude		tLatitude;									/**< Numerical longitude value */
	TNSIndicator	tNSInd;										/**< Enumerated N/S indicator */
}TLatitudeObj;

/**
 * \brief	Longitude data object
 * */
typedef struct _TLongitude {
	uchar8			strLongitude[NMEAD_LONGITUDE_STR_SIZE+1];	/**< Longitude string */
	uchar8			strEWIndicator[NMEAD_EW_IND_STR_SIZE+1];	/**< East/West indicator string */
	TLongitude		tLongitude;									/**< Numerical longitude value */
	TEWIndicator	tEWInd;										/**< Enumerated E/W indicator */
}TLongitudeObj;

/**
 * \brief	UTC Time object
 * */
typedef struct _TUTCTime {
	uchar8			strUTCTime[NMEAD_UTC_STR_SIZE+1];			/**< UTC time string */
	uchar8			ucHours;
	uchar8			ucMinutes;
	uchar8			ucSeconds;
	uchar8			ucHundredthSeconds;
}TUTCTime;

typedef struct _TDate {
	uchar8			strDate[NMEAD_DATE_STR_SIZE+1];				/**< Date string */
}TDate;


typedef struct _TGPSPosnFixStatus {
	uchar8			strPositionFixStatus[NMEAD_POS_FIX_STR_SIZE+1];
	TPosFixStatus	tPosFixStatus;
}TGPSPosFixStatus;


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


#endif /* __GPS_TYPES_H_ */
