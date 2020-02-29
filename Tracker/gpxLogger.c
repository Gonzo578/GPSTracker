/**
 * \file gpxLogger.c
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

#ifndef __GPXLOGGER_C_
#define __GPXLOGGER_C_

/*
*********************************************************************************************************
*							INCLUDES
*********************************************************************************************************
*/

#include "ff.h"					/* Include FAT file system interface */
#include "gpxLogger.h"			/* Include own interface */

/*
*********************************************************************************************************
*							LOCAL TYPES
*********************************************************************************************************
*/

struct TGPXLogger {
	FATFS		tFATFilesystem;			/**< FAT file system structure, see ff.h for details */
	FIL			tGPXFile;				/**< GPS GPX track file object */
};

/*
*********************************************************************************************************
*							LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void GPXL_vConvDegValToStr(sint32 slVal, uchar8* pucStr);

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

/*-------------------------------------------------------------------------------------------------
 * GPX file preamble and start tags
 *------------------------------------------------------------------------------------------------- */
static const uchar8 GPXL_strXMLDeclaration[] = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
static const uchar8 GPXL_strCPXRootElementStartTag[] = "<gpx xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\" xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd\" version=\"1.1\" creator=\"MySportTracker\" xmlns=\"http://www.topografix.com/GPX/1/1\">\n";
	static const uchar8 GPXL_strMetaTag[] = " <metadata />\n";
	static const uchar8 GPXL_strTrackStartTag[] = " <trk>\n";
		static const uchar8 GPXL_strNameTag[] = "  <name />\n";
		static const uchar8 GPXL_strCMTTag[] = "  <cmt />\n";

/*-------------------------------------------------------------------------------------------------
 * GPX file end tags
 *------------------------------------------------------------------------------------------------- */
	static const uchar8 GPXL_strTrackEndTag[] = " </trk>\n";
static const uchar8 GPXL_strCPXRootElementEndTag[] = "</gpx>\n";

/*-------------------------------------------------------------------------------------------------
 * TRACK segmentation tags
 *------------------------------------------------------------------------------------------------- */
static const uchar8 GPXL_strTrackSegmentStartTag[] = "  <trkseg>\n";
static const uchar8 GPXL_strTrackSegmentEndTag[] = "  </trkseg>\n";

/*-------------------------------------------------------------------------------------------------
 * TRACK point tags
 *------------------------------------------------------------------------------------------------- */
//<trkpt lat="49.0743370056152" lon="12.0546398162842">
static const uchar8 GPXL_strTrackPointStartTag[] = "   <trkpt";
static const uchar8 GPXL_strTrackPointEndTag[] = "   </trkpt>\n";

/*-------------------------------------------------------------------------------------------------
 * TIME tags
 *------------------------------------------------------------------------------------------------- */
static const uchar8 GPXL_strTimeStartTag[] = "    <time>";
static const uchar8 GPXL_strTimeEndTag[] = "</time>\n";

/*
*********************************************************************************************************
*							LOCAL VARIABLES
*********************************************************************************************************
*/

static TGPXLogger GPXL_tGPXLogger;

TGPXLogger* const GPXL_ptGPXLogger = &GPXL_tGPXLogger;

static uchar8 GPXL_strBuffer[100];

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/
#define RADIX					((uint32)10)
#define FRACTIONAL_DIGITS		((uint32)6)
static void GPXL_vConvDegValToStr(sint32 slVal, uchar8* pucStr) {
	BOOL	bSign;
	uint32	ulValue;
	uint32	ulDigit;
	uchar8	aucBuffer[11];
	uchar8*	pucPtr = aucBuffer;

	if(slVal < 0) {
		/* Value is negative */
		bSign = TRUE;
		ulValue = (uint32)(-slVal);
	} else {
		/* Value is positive */
		bSign = FALSE;
		ulValue = (uint32)(slVal);
	}

	while((ulValue != 0) || (pucPtr==aucBuffer)) {
		ulDigit		= ulValue % RADIX;
		ulValue		/= RADIX;
		*pucPtr		= (uchar8)(ulDigit + '0');
		pucPtr++;
	}

	pucPtr--;

	if(bSign == TRUE) {
		*pucStr	= '-';
		pucStr++;
	}

	while(pucPtr != aucBuffer) {
		if(pucPtr == (aucBuffer + FRACTIONAL_DIGITS - 1)) {
			*pucStr	= '.';
			pucStr++;
		}
		*pucStr = *pucPtr;
		pucPtr--;
		pucStr++;
	}
	*pucStr = *pucPtr;
	pucStr++;
	*pucStr = '\0';
}

static void GPXL_vConvLonToStr(TLatitude tLat, uchar8* pucStr) {

}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

/**
 *
 * */
TGPXLoggerErr GPXL_tStartLogging(TGPXLogger* this) {
	FRESULT		tFsResult;				/**< Return code for file related operations */
	UINT		uiWrittenCharacters;	/**< Number of written character */
	int			iByteCount;

	/* Mount file system */
	tFsResult = f_mount(0, &this->tFATFilesystem);

	tFsResult = f_open(&this->tGPXFile, "0:track.gpx", FA_CREATE_ALWAYS | FA_WRITE);

	iByteCount = f_puts((const TCHAR* )GPXL_strXMLDeclaration, &this->tGPXFile);
	iByteCount = f_puts((const TCHAR* )GPXL_strCPXRootElementStartTag, &this->tGPXFile);
		iByteCount = f_puts((const TCHAR* )GPXL_strMetaTag, &this->tGPXFile);
		iByteCount = f_puts((const TCHAR* )GPXL_strTrackStartTag, &this->tGPXFile);
			iByteCount = f_puts((const TCHAR* )GPXL_strNameTag, &this->tGPXFile);
			iByteCount = f_puts((const TCHAR* )GPXL_strCMTTag, &this->tGPXFile);
			iByteCount = f_puts((const TCHAR* )GPXL_strTrackSegmentStartTag, &this->tGPXFile);

	return GPLX_ERR_OK;
}

/**
 *
 * */
TGPXLoggerErr GPXL_tStopLogging(TGPXLogger* this) {
	FRESULT		tFsResult;				/**< Return code for file related operations */
	int			iByteCount;

		iByteCount = f_puts((const TCHAR* )GPXL_strTrackSegmentEndTag, &this->tGPXFile);
	iByteCount = f_puts((const TCHAR* )GPXL_strTrackEndTag, &this->tGPXFile);
	iByteCount = f_puts((const TCHAR* )GPXL_strCPXRootElementEndTag, &this->tGPXFile);

	tFsResult = f_close(&this->tGPXFile);

	return GPLX_ERR_OK;
}

/**
 *
 * */
TGPXLoggerErr GPXL_tLogTrackPoint(TGPXLogger* this, TTrackPoint* ptTrkPt) {
	FRESULT		tFsResult;				/**< Return code for file related operations */
	UINT		uiWrittenCharacters;	/**< Number of written character */
	int			iByteCount;
	uchar8		strString[11];

	iByteCount = f_puts((const TCHAR* )GPXL_strTrackPointStartTag, &this->tGPXFile);
	iByteCount = f_puts((const TCHAR* )" lat=\"", &this->tGPXFile);
	GPXL_vConvDegValToStr((sint32)ptTrkPt->tLat, strString);
	iByteCount = f_puts((const TCHAR* )strString, &this->tGPXFile);
	iByteCount = f_puts((const TCHAR* )"\" lon=\"", &this->tGPXFile);
	GPXL_vConvDegValToStr((sint32)ptTrkPt->tLon, strString);
	iByteCount = f_puts((const TCHAR* )strString, &this->tGPXFile);
	iByteCount = f_puts((const TCHAR* )"\">\n", &this->tGPXFile);

		tFsResult = f_write(&this->tGPXFile, GPXL_strTimeStartTag, sizeof(GPXL_strTimeStartTag)-1, &uiWrittenCharacters);
		tFsResult = f_write(&this->tGPXFile, ptTrkPt->strDateISO8601, sizeof(ptTrkPt->strDateISO8601)-1, &uiWrittenCharacters);
		tFsResult = f_write(&this->tGPXFile, "T", 1, &uiWrittenCharacters);
		tFsResult = f_write(&this->tGPXFile, ptTrkPt->strUTC, sizeof(ptTrkPt->strUTC)-1, &uiWrittenCharacters);
		tFsResult = f_write(&this->tGPXFile, "Z", 1, &uiWrittenCharacters);
		iByteCount = f_puts((const TCHAR* )GPXL_strTimeEndTag, &this->tGPXFile);

	iByteCount = f_puts((const TCHAR* )GPXL_strTrackPointEndTag, &this->tGPXFile);

	return GPLX_ERR_OK;
}

/**
 *
 * */
TGPXLoggerErr GPXL_tLogLap(TGPXLogger* this) {
	return GPLX_ERR_OK;
}

#endif /* __GPXLOGGER_C_ */
