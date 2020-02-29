/**
 * \file gpsdatetime.c
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
*							FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static const uchar8* GPST_pucUTCParser(const uchar8* pucData, TUTCTime* ptUTCObj);
static const uchar8* GPST_pucDateParser(const uchar8* pucData, TDate* ptDateObj);

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

TUTCTime	GPST_tUTCTime = {0};
TDate		GPST_tDate = {0};

/*
*********************************************************************************************************
*							LOCAL CONSTANTS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							GLOBAL CONSTANTS
*********************************************************************************************************
*/

const TParserCfg	GPST_tUTCTimeParser	= {(TNMEAParser)GPST_pucUTCParser,		&GPST_tUTCTime};
const TParserCfg	GPST_tDateParser	= {(TNMEAParser)GPST_pucDateParser,		&GPST_tDate};

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/

/*---------------------------------------------------------------------------------------------------------------------
 * const uchar8* NMEAP_pucUTCParser(const uchar8* pucData, TUTCTime* ptUTCObj)
 *--------------------------------------------------------------------------------------------------------------------- */
static const uchar8* GPST_pucUTCParser(const uchar8* pucData, TUTCTime* ptUTCObj) {
	/* First move the data pointer to the first data byte after the field delimiter */
	pucData++;

	if(*pucData == NMEAP_DATA_FIELD_DELIMITER) {
		/*
		 * Data field is empty
		 * => Move empty strings to the data field
		 * */
		ptUTCObj->strUTCTime[0] = '\0';
		ptUTCObj->ucHours = 0;
		ptUTCObj->ucMinutes = 0;
		ptUTCObj->ucSeconds = 0;
		ptUTCObj->ucHundredthSeconds = 0;
	} else {
		ptUTCObj->strUTCTime[0]		= pucData[0];
		ptUTCObj->strUTCTime[1]		= pucData[1];
		ptUTCObj->strUTCTime[2]		= ':';
		ptUTCObj->strUTCTime[3]		= pucData[2];
		ptUTCObj->strUTCTime[4]		= pucData[3];
		ptUTCObj->strUTCTime[5]		= ':';
		ptUTCObj->strUTCTime[6]		= pucData[4];
		ptUTCObj->strUTCTime[7]		= pucData[5];
		ptUTCObj->strUTCTime[8]		= pucData[6];
		ptUTCObj->strUTCTime[9]		= pucData[7];
		ptUTCObj->strUTCTime[10]	= pucData[8];
	}

	return &pucData[9];
}

static const uchar8* GPST_pucDateParser(const uchar8* pucData, TDate* ptDateObj) {
	/* First move the data pointer to the first data byte after the field delimiter */
	pucData++;

	if(*pucData == NMEAP_DATA_FIELD_DELIMITER) {
		/*
		 * Data field is empty
		 * => Move empty strings to the data field
		 * */
		ptDateObj->strDate[0] = '\0';
	} else {
		/*
		 * Date string is present
		 * => copy string to target variable
		 * =>
		 * */
		ptDateObj->strDate[0]	= pucData[0];
		ptDateObj->strDate[1]	= pucData[1];
		ptDateObj->strDate[2]	= '.';
		ptDateObj->strDate[3]	= pucData[3];
		ptDateObj->strDate[4]	= pucData[4];
		ptDateObj->strDate[5]	= '.';
		ptDateObj->strDate[6]	= pucData[6];
		ptDateObj->strDate[7]	= pucData[7];
		ptDateObj->strDate[8]	= pucData[8];
		ptDateObj->strDate[9]	= pucData[9];
	}

	return &pucData[10];
}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/
