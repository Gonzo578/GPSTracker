/**
 * \file nmeaparsercfg.c
 *
 * \author	Ralf Hochhausen
 * \Date	11.03.2012
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

#include "includes.h"		/* Include generic definitions and declarations */
#include "gps_types.h"		/* Include GPS related data types */

/*
 * 	Parser includes
 * */
#include "gpslocation.h"		/* GPS location interface */
#include "gpsaltitude.h"		/* GPS altitude interface */
#include "gpsdatetime.h"		/* GPS data and time interface */
#include "gpsstate.h"			/* GPS state interface */


/*
 * 	Others
 * */
#include "nmeaparser.h"			/* Include own header */

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

/*---------------------------------------------------------------------------------------------------------------------
 * NMEA parsing configuration
 *--------------------------------------------------------------------------------------------------------------------- */

/**
 * \brief	Configuration of the GPRMC message content handlers
 * */
static const TParserCfg*	GPS_aptParserConfig_GPRMC[] = {
	&NMEAP_tDefaultParser,	/* UTC */
	&GPSS_tPosFixParser,	/* Status */
	&NMEAP_tDefaultParser,	/* Latitude */
	&NMEAP_tDefaultParser,	/* N/S Indicator */
	&NMEAP_tDefaultParser,	/* Longitude */
	&NMEAP_tDefaultParser,	/* E/W Indicator */
	&NMEAP_tDefaultParser,	/* Speed over ground */
	&NMEAP_tDefaultParser,	/* Course over ground */
	&NMEAP_tDefaultParser,	/* Date */
	&NMEAP_tDefaultParser,	/* Magnetic variation value */
	&NMEAP_tDefaultParser,	/* Magnetic variation E/W indicator */
	&NMEAP_tDefaultParser,	/* Mode indicator */
};

/**
 * \brief	Configuration of the GPGLL message content handlers
 * */
static const TParserCfg*	GPS_aptParserConfig_GPGLL[] = {
	&NMEAP_tDefaultParser,	/* Latitude */
	&NMEAP_tDefaultParser,	/* N/S Indicator */
	&NMEAP_tDefaultParser,	/* Longitude */
	&NMEAP_tDefaultParser,	/* E/W Indicator */
	&NMEAP_tDefaultParser,	/* UTC */
	&NMEAP_tDefaultParser,	/* Valid state */
	&NMEAP_tDefaultParser,	/* Optional: Mode */
};

/**
 * \brief	Configuration of the GPGGA message content handlers
 * */
static const TParserCfg*	GPS_aptParserConfig_GPGGA[] = {
	&NMEAP_tDefaultParser,	/* UTC */
	&GPSL_tLatitudeParser,	/* Latitude */
	&GPSL_tLongitudeParser,	/* Longitude */
	&NMEAP_tDefaultParser,	/* Position fixed status */
	&NMEAP_tDefaultParser,	/* Satellites in range */
	&NMEAP_tDefaultParser,	/* HDOP, horizontal dilution */
	&GPST_tMSLAltitudeParser,	/* MSL Altitude */
	&NMEAP_tDefaultParser,	/* Unit, Meters (fixed field) */
	&NMEAP_tDefaultParser,	/* Geoid separation */
	&NMEAP_tDefaultParser,	/* Unit Meters (fixed field) */
	&NMEAP_tDefaultParser,	/* Age of differential Corrections */
	&NMEAP_tDefaultParser,	/* Diff. Reference Station ID */
};

/**
 * \brief	Configuration of the GPZDA message content handlers
 * */
static const TParserCfg*	GPS_aptParserConfig_GPZDA[] = {
	&GPST_tUTCTimeParser,	/* UTC */
	&GPST_tDateParser,		/* Date */
	&NMEAP_tDefaultParser,	/* (Not supported) Local zone hours */
	&NMEAP_tDefaultParser,	/* (Not supported) Local zone minutes */
};

/**
 * \brief Configuration of the NMEA frames
 * */
const TNMEAProtFrame NMEAP_atFrameConfig[] = {
//	{"GPGLL", 7,	GPS_aptParserConfig_GPGLL},
	{"GPRMC", 12,	GPS_aptParserConfig_GPRMC},
	{"GPGGA", 14,	GPS_aptParserConfig_GPGGA},
	{"GPZDA", 6,	GPS_aptParserConfig_GPZDA},
};

/**
 * \brief	No. of items in the parser configuration table
 *
 * \note	Do not change!
 * */
const uint32 NMEAP_ulFrameConfigSize = (uint32)(sizeof(NMEAP_atFrameConfig)/sizeof(TNMEAProtFrame));

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
