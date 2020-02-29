/**
 * \file gpslocation.c
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
#include "utility.h"		/* Include generic utilities*/
#include "nmeaparser.h"		/* Include NMEA parser interface */

/*
*********************************************************************************************************
*							FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void GPSL_vConvLonStringToNum(TLongitudeObj* ptLon);
static void GPSL_vConvLatStringToNum(TLatitudeObj* ptLat);
static const uchar8* GPSL_pucLatitudeParser(const uchar8* pucData, TLatitudeObj* ptLatObj);
static const uchar8* GPSL_pucLongitudeParser(const uchar8* pucData, TLongitudeObj* ptLonObj);

/*
*********************************************************************************************************
*							LOCAL DEFINITIONS
*********************************************************************************************************
*/

#define NMEAC_LAT_MIN_START_IDX		2
#define NMEAC_LON_MIN_START_IDX		3

/*
*********************************************************************************************************
*							LOCAL VARIABLES
*********************************************************************************************************
*/
TLatitudeObj		GPSL_tLatitude = {0};
TLongitudeObj	GPSL_tLongitude = {0};

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

const TParserCfg	GPSL_tLatitudeParser	= {(TNMEAParser)GPSL_pucLatitudeParser,	&GPSL_tLatitude};
const TParserCfg	GPSL_tLongitudeParser	= {(TNMEAParser)GPSL_pucLongitudeParser,	&GPSL_tLongitude};

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/

/**
 * 	\brief
 * */
static void GPSL_vConvLonStringToNum(TLongitudeObj* ptLon) {
	TLongitude	tLon;
	TLongitude	tTemp;
	uchar8* 	pucLon;

	/*
	 * 	Input data format:
	 *
	 * 		dddmm.mmmmm
	 * */
	pucLon = ((uchar8*)(&ptLon->strLongitude)) + NMEAC_LON_MIN_START_IDX;

	/*
	 * First convert the longitude minutes to fractional degrees
	 * */
	tLon = (TLatitude)0;

	while(*pucLon != 0) {
		tLon *= 10;
		tLon += (TLatitude)UTI_ucAsciiToNum(*pucLon);

		pucLon++;

		/*
		 * 	If we reach the '.' we need to skip it to compute the fractional part correctly
		 * */
		if(*pucLon == '.') {
			pucLon++;
		}
	}

	/*
	 * Finally we need to multiply by 10 because one multiplication is not executed in
	 * the loop. The we divide by 60 to convert the minutes in fractional degrees.
	 * */
	tLon *= 10;
	tLon += 30;		/* Round */
	tLon /= 60;

	/*
	 * 	Convert degrees part to numerical format
	 * */
	tTemp 	= (TLongitude)UTI_ucAsciiToNum(ptLon->strLongitude[0]);
	tTemp 	*= 10;
	tTemp	+= (TLongitude)UTI_ucAsciiToNum(ptLon->strLongitude[1]);
	tTemp 	*= 10;
	tTemp	+= (TLongitude)UTI_ucAsciiToNum(ptLon->strLongitude[2]);

	tTemp	*=	1000000;

	/*
	 * 	Put it all together, i.e. integer + fractional part
	 * */
	if(ptLon->tEWInd == EAST) {
		ptLon->tLongitude	= tLon + tTemp;
	} else {
		ptLon->tLongitude	= - tLon - tTemp;
	}
}

/**
 * 	\brief
 * */
static void GPSL_vConvLatStringToNum(TLatitudeObj* ptLat) {
	TLatitude	tLat;
	TLatitude	tTemp;
	uchar8* 	pucLat;

	/*
	 * 	Input data format:
	 *
	 * 		dddmm.mmmmm
	 * */
	pucLat = ((uchar8*)(&ptLat->strLatitude)) + 2;

	/*
	 * First convert the latitude minutes to fractional degrees
	 * */
	tLat = (TLatitude)0;

	while(*pucLat != 0) {
		tLat *= 10;
		tLat += (TLatitude)UTI_ucAsciiToNum(*pucLat);

		pucLat++;

		/*
		 * 	If we reach the '.' we need to skip it to compute the fractional part correctly
		 * */
		if(*pucLat == '.') {
			pucLat++;
		}
	}

	/*
	 * Finally we need to multiply by 10 because one multiplication is not executed in
	 * the loop. The we divide by 60 to convert the minutes in fractional degrees.
	 * */
	tLat *= 10;
	tLat += 30;
	tLat /= 60;

	/*
	 * 	Convert degrees part to numerical format
	 * */
	tTemp 	= (TLatitude)UTI_ucAsciiToNum(ptLat->strLatitude[0]);
	tTemp 	*= 10;
	tTemp	+= (TLatitude)UTI_ucAsciiToNum(ptLat->strLatitude[1]);

	tTemp	*=	1000000;

	/*
	 * 	Put it all together, i.e. integer + fractional part
	 * */
	if(ptLat->tNSInd == NORTH) {
		ptLat->tLatitude	= tLat + tTemp;
	} else {
		ptLat->tLatitude	= - tLat - tTemp;
	}
}

/*---------------------------------------------------------------------------------------------------------------------
 * static const uchar8* GPSL_pucLatitudeParser(const uchar8* pucData, TLatitudeObj* ptLatObj)
 *--------------------------------------------------------------------------------------------------------------------- */
static const uchar8* GPSL_pucLatitudeParser(const uchar8* pucData, TLatitudeObj* ptLatObj) {
	uchar8*	pucLatData;

	/* First move the data pointer to the first data byte after the field delimiter */
	pucData++;

	if(*pucData == NMEAP_DATA_FIELD_DELIMITER) {
		/*
		 * Data field is empty
		 * => Move empty strings to the data field
		 * */
		ptLatObj->strLatitude[0] = '\0';
		ptLatObj->strNSIndicator[0] = '\0';
		ptLatObj->tLatitude = 0;
		ptLatObj->tNSInd = NS_UNDEFINED;
	} else {
		pucLatData = &ptLatObj->strLatitude[0];
		while(*pucData != NMEAP_DATA_FIELD_DELIMITER) {
			*pucLatData = *pucData;
			pucLatData++;
			pucData++;
		}

		/* Move data pointer to the N/S indicator */
		pucData++;

		ptLatObj->strNSIndicator[0] = *pucData;

		if(ptLatObj->strNSIndicator[0] == 'N') {
			ptLatObj->tNSInd = NORTH;
		} else {
			ptLatObj->tNSInd = SOUTH;
		}

		GPSL_vConvLatStringToNum(ptLatObj);
	}

	/* Finally move data pointer behind the latitude data field */
	pucData++;

	return pucData;
}

/*---------------------------------------------------------------------------------------------------------------------
 * static const uchar8* GPSL_pucLongitudeParser(const uchar8* pucData, TLongitudeObj* ptLonObj)
 *--------------------------------------------------------------------------------------------------------------------- */
static const uchar8* GPSL_pucLongitudeParser(const uchar8* pucData, TLongitudeObj* ptLonObj) {
	uchar8*	pucLonData;

	/* First move the data pointer to the first data byte after the field delimiter */
	pucData++;

	if(*pucData == NMEAP_DATA_FIELD_DELIMITER) {
		/*
		 * Data field is empty
		 * => Move empty strings to the data field
		 * */
		ptLonObj->strLongitude[0] = '\0';
		ptLonObj->strEWIndicator[0] = '\0';
		ptLonObj->tLongitude = 0;
		ptLonObj->tEWInd = EW_UNDEFINED;
	} else {
		pucLonData = &ptLonObj->strLongitude[0];
		while(*pucData != NMEAP_DATA_FIELD_DELIMITER) {
			*pucLonData = *pucData;
			pucLonData++;
			pucData++;
		}

		/* Move data pointer to the N/S indicator */
		pucData++;

		ptLonObj->strEWIndicator[0] = *pucData;

		if(ptLonObj->strEWIndicator[0] == 'E') {
			ptLonObj->tEWInd = EAST;
		} else {
			ptLonObj->tEWInd = WEST;
		}

		GPSL_vConvLonStringToNum(ptLonObj);
	}

	/* Finally move data pointer behind the latitude data field */
	pucData++;

	return pucData;
}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/
