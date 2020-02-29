/**
 * \file gpsstate.c
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
#include "dio.h"			/* Include digital IO interface */
#include "nmeaparser.h"		/* Include NMEA parser interface */

/*
*********************************************************************************************************
*							FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static const uchar8* GPSS_pucPosFixStateRMCParser(const uchar8* pucData, TGPSPosFixStatus* ptPosFixObj);

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
TGPSPosFixStatus	GPSS_tPosFixStatus = {0};

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

const TParserCfg	GPSS_tPosFixParser		= {(TNMEAParser)GPSS_pucPosFixStateRMCParser,	&GPSS_tPosFixStatus};

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/

/*---------------------------------------------------------------------------------------------------------------------
 * const uchar8* NMEAP_pucPosFixStateRMCParser(const uchar8* pucData, TGPSPosFixStatus* ptPosFixObj)
 *--------------------------------------------------------------------------------------------------------------------- */
static const uchar8* GPSS_pucPosFixStateRMCParser(const uchar8* pucData, TGPSPosFixStatus* ptPosFixObj) {
	/* First move the data pointer to the first data byte after the field delimiter */
	pucData++;

	if(*pucData == NMEAP_DATA_FIELD_DELIMITER) {
		ptPosFixObj->strPositionFixStatus[0] = '\0';
	} else {
		ptPosFixObj->strPositionFixStatus[0] = *pucData;
		switch (*pucData) {
		case 'A':
			ptPosFixObj->tPosFixStatus = POSITION_FIXED;
			break;
		case 'V':
		default:
			ptPosFixObj->tPosFixStatus = POSITION_INVALID;
			break;
		}
		pucData++;
	}

	return pucData;
}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

/**
 *
 * */
void GPSS_vCheckGPSPositionFixState(void) {
	OS_CPU_SR  cpu_sr = 0;
	if(GPSS_tPosFixStatus.tPosFixStatus == POSITION_FIXED) {
		DIO_vSetPort(GPS_POS_FIXED_PORT, GPS_POS_FIXED_OUTPUT);
	} else {
		DIO_vResetPort(GPS_POS_FIXED_PORT, GPS_POS_FIXED_OUTPUT);
	}
}
