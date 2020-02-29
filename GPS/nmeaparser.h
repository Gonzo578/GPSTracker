/**
 * \file nmeaparser.h
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

#ifndef __NMEAPARSER_H_
#define __NMEAPARSER_H_

/*
*********************************************************************************************************
*							INCLUDES
*********************************************************************************************************
*/
#include "includes.h"				/* Include generic header file */

/*
*********************************************************************************************************
*							GLOBAL DEFINITIONS
*********************************************************************************************************
*/

#define NMEAP_MESSAGE_ID_STR_SIZE		5		/**< The ID always consists of five characters */
#define NMEAP_DATA_FIELD_DELIMITER		','		/**< Each data field of a message is separated with this
 	 	 	 	 	 	 	 	 	 	 	 	 	 character */
#define NMEAP_EOF_DELIMITIER			'*'		/**< End of Frame delimiter */

/*
*********************************************************************************************************
*							GLOBAL TYPES
*********************************************************************************************************
*/

typedef enum _TNMEAPErr {
	NMEAP_OK,					/**< Frame parsing has finished without error */
	NMEAP_UNSUPPORTED_FRAME		/**< Frame was not found in configuration */
}TNMEAPErr;

typedef const uchar8* (*TNMEAParser)(const uchar8* pucData, ...);

typedef struct _TParserCfg {
	TNMEAParser	pfParser;		/**< Pointer to the parser function */
	void*		pvDataObj;		/**< Pointer to the parser data object */
}TParserCfg;

/**
 * \brief	Type definition of a NMEA protocol frame
 * */
typedef struct _TNMEAProtFrame {
	const uchar8					aucMessageID[NMEAP_MESSAGE_ID_STR_SIZE+1];	/**< NMEA frame ID (e.g. "GPGGA") (+ \0) */
	uint32							ulNoOfParsers;								/**< No. of data items within the NMEA message */
	const TParserCfg**				ptParserCfg;								/**< Array with pointers to parser objects */
}TNMEAProtFrame;

/*
*********************************************************************************************************
*							GLOBAL CONSTANTS
*********************************************************************************************************
*/

extern const TParserCfg	NMEAP_tDefaultParser;

/**
 * 	\brief	NMEA parser frame configuration
 * */
extern const TNMEAProtFrame NMEAP_atFrameConfig[];

/**
 * \brief	No. of items in the parser configuration table
 * */
extern const uint32 NMEAP_ulFrameConfigSize;

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

/**
 * \brief	Default parsing function
 *
 * This parser is used to skip one data item.
 *
 * \param pucData	Pointer to the begin of a data item string
 *
 * \return const uchar8*	Pointer to the begin of the next data item string
 * */
const uchar8* NMEAP_pucDefaultParser(const uchar8* pucData, ...);

/*---------------------------------------------------------------------------------------------------------------------
 * NMEA PARSER INTERFACE
 *--------------------------------------------------------------------------------------------------------------------- */
/**
 * \brief	NMEA parser interface function
 * */
TNMEAPErr NMEAP_tParseNMEAFrame(const uchar8* pucNMEAFrame, const TNMEAProtFrame* ptFrameCfg, const uint32 ulCfgSize);

#endif /* __NMEAPARSER_H_ */
