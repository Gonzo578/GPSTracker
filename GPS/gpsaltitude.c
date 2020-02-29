/**
 * \file gpsaltitude.c
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
#include "nmeaparser.h"		/* Include NMEA parser interface */

/*
*********************************************************************************************************
*							LOCAL TYPE DEFINITIONS
*********************************************************************************************************
*/

typedef struct _TMSLAltitude {
	uchar8	strMSLAltitude[12];
}TMSLAltitude;

/*
*********************************************************************************************************
*							FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static const uchar8* GPST_pucMSLAltitudeParser(const uchar8* pucData, TMSLAltitude* ptAltitude);

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

static TMSLAltitude	GPSA_tMSLAltitude = {0};

/*
*********************************************************************************************************
*							GLOBAL CONSTANTS
*********************************************************************************************************
*/

/**
 * 	\brief	MSL altitude parser configuration object
 * */
const TParserCfg	GPST_tMSLAltitudeParser	= {(TNMEAParser)GPST_pucMSLAltitudeParser, (void*)&GPSA_tMSLAltitude};

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/

/**
 * 	\brief	MSL altitude parser function
 *
 * 			This function parses the altitude entry within an NMEA input frame.
 * 			If the frame is empty, the parsed result a string with no character.
 * 			Else the altitude entry is copied to the local data object.
 *
 * 	\param	pucData		Pointer to the altitude entry within the NMEA data frame
 * 	\param	ptAltitude	Pointer to the altitude data object
 *
 * 	\return	uchar8*	Pointer behind the last character of the altitude entry
 * */
static const uchar8* GPST_pucMSLAltitudeParser(const uchar8* pucData, TMSLAltitude* ptAltitude) {
	uchar8* pucAltitude = ptAltitude->strMSLAltitude;

	/* First move the data pointer to the first data byte after the field delimiter */
	pucData++;


	/*
	 * 	Copy altitude string
	 * 	If the first string character is the ',' character, there is no altitude value
	 * 	included in the NMEA frame => no data will be copied.
	 * */
	while(*pucData != NMEAP_DATA_FIELD_DELIMITER) {
		*pucAltitude = *pucData;

		pucAltitude++;
		pucData++;
	}

	*pucAltitude = '\0';

	return pucData;
}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/
