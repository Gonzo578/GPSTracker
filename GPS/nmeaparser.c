/**
 * \file nmeaparser.c
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

#include "includes.h"
#include "nmeaparser.h"

/*
*********************************************************************************************************
*							FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static BOOL NMEAP_bCompareMessageID(uchar8* pucNMEAFrameID, uchar8* pucNMEAFrameIDConfig);
static const TNMEAProtFrame* NMEAP_ptGetFrameConfig(const uchar8* pucNMEAFrame, const TNMEAProtFrame* ptFrameCfg, const uint32 ulCfgSize);
static void NMEAP_vParseFrame(const uchar8* pucNMEAFrame, const TNMEAProtFrame* ptFrameCfg);

/*
*********************************************************************************************************
*							LOCAL DEFINITIONS
*********************************************************************************************************
*/

#define NMEAP_MESSAGE_ID_OFFSET				1		/**< Offset of the message ID within the NMEA frame */
#define NMEAP_DATA_FIELD_START_OFFSET		6		/**< The first data field starts with this offset
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 within the frame */

/*
*********************************************************************************************************
*							LOCAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							LOCAL CONSTANTS
*********************************************************************************************************
*/

const TParserCfg	NMEAP_tDefaultParser	= {NMEAP_pucDefaultParser,	NULL};

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/

/**
 * \brief	Function checks if the NMEA frame ID matches the configuration ID
 *
 * This function is used to find the parsing configuration for the current
 * NMEA frame.
 * */
static BOOL NMEAP_bCompareMessageID(uchar8* pucNMEAFrameID, uchar8* pucNMEAFrameIDConfig) {
	uint32	ulIdx;
	BOOL	bRetVal = TRUE;

	for (ulIdx = 0; ulIdx < NMEAP_MESSAGE_ID_STR_SIZE; ulIdx++) {
		if(*pucNMEAFrameID != *pucNMEAFrameIDConfig) {
			bRetVal = FALSE;
			break;
		}
		pucNMEAFrameID++;
		pucNMEAFrameIDConfig++;
	}

	return bRetVal;
}

/**
 * \brief	Function searches the NMEA parsing configuration for the current NMEA frame
 * */
static const TNMEAProtFrame* NMEAP_ptGetFrameConfig(const uchar8* pucNMEAFrame, const TNMEAProtFrame* ptFrameCfg, const uint32 ulCfgSize) {
	uint32			ulIdx = 0;
	const TNMEAProtFrame*	ptFrameConfigFound = (TNMEAProtFrame*)NULL;

	while (ulIdx < ulCfgSize) {
		if(NMEAP_bCompareMessageID((uchar8*)(pucNMEAFrame+NMEAP_MESSAGE_ID_OFFSET), (uchar8*)(ptFrameCfg[ulIdx].aucMessageID)) != FALSE) {
			ptFrameConfigFound = &ptFrameCfg[ulIdx];
			break;
		} else {
			ulIdx++;
		}

	}
	return ptFrameConfigFound;
}

/**
 * \brief
 * */
static void NMEAP_vParseFrame(const uchar8* pucNMEAFrame, const TNMEAProtFrame* ptFrameCfg) {
	uint32 			ulIdx;
	const uchar8*	pucData;

	/*
	 * Set data pointer immediately in front of the the first data item.
	 * Note: Each data item has a leading ',' character!
	 * */
	pucNMEAFrame += NMEAP_DATA_FIELD_START_OFFSET;

	for(ulIdx = 0; ulIdx < ptFrameCfg->ulNoOfParsers; ulIdx++) {
		if(*pucNMEAFrame == NMEAP_EOF_DELIMITIER) {
			/*
			 * End of frame character '*' has been reached
			 * This can be possible in case of optional data fields that are not included
			 * in the current NMEA frame
			 *  */
			break;
		}

		/*
		 * Call parser for the current data item
		 * */
		pucNMEAFrame = ptFrameCfg->ptParserCfg[ulIdx]->pfParser(pucNMEAFrame, ptFrameCfg->ptParserCfg[ulIdx]->pvDataObj);
	}
}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

/*---------------------------------------------------------------------------------------------------------------------
 * NMEA DATA ITEM PARSING FUNCTIONS
 * Note:
 * These parsing functions can be used to extract certain data items out of the NMEA
 * frames.
 *--------------------------------------------------------------------------------------------------------------------- */

/*---------------------------------------------------------------------------------------------------------------------
 * const uchar8* NMEAP_pucDefaultParser(const uchar8* pucData, ...)
 *--------------------------------------------------------------------------------------------------------------------- */
const uchar8* NMEAP_pucDefaultParser(const uchar8* pucData, ...) {

	/* First move the data pointer to the first data byte after the field delimiter */
	pucData++;

	while( 		(*pucData != NMEAP_DATA_FIELD_DELIMITER)
			&& 	(*pucData != NMEAP_EOF_DELIMITIER) ) {
		/* Continue searching until the next field delimiter is reached */
		pucData++;
	}
	return pucData;
}

/*---------------------------------------------------------------------------------------------------------------------
 * TNMEAPErr  NMEAP_tParseNMEAFrame(const uchar8* pucNMEAFrame, const TNMEAProtFrame* ptFrameCfg, const uint32 ulCfgSize)
 *--------------------------------------------------------------------------------------------------------------------- */
TNMEAPErr  NMEAP_tParseNMEAFrame(const uchar8* pucNMEAFrame, const TNMEAProtFrame* ptFrameCfg, const uint32 ulCfgSize) {
	const TNMEAProtFrame* ptFoundFrameConfig;

	ptFoundFrameConfig = NMEAP_ptGetFrameConfig(pucNMEAFrame, ptFrameCfg, ulCfgSize);

	if (ptFoundFrameConfig != NULL) {
		NMEAP_vParseFrame(pucNMEAFrame, ptFoundFrameConfig);
		return NMEAP_OK;
	} else {
		return NMEAP_UNSUPPORTED_FRAME;
	}
}
