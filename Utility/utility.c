/**
 * \file utility.c
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
static const uchar8 UTI_aucHexToAsciiTab[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

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

uchar8 UTI_ucHexToAscii(uchar8 ucHexNum) {
	return UTI_aucHexToAsciiTab[ucHexNum];
}

uchar8 UTI_ucAsciiToNum(uchar8 ucChar) {
	return (uchar8)(ucChar - '0');
}

uchar8 UTI_ucNumToAscii(uchar8 ucNum) {
	return (uchar8)(ucNum + '0');
}

void UTI_vStrCopy(uchar8* pucSrc, uchar8* pucDst) {
	while(*pucSrc != '\0') {
		*pucDst = *pucSrc;
		pucDst++;
		pucSrc++;
	}
	pucDst = '\0';
}

void UTI_vMemCopy(uchar8* pucSrc, uchar8* pucDst, uint32 ulCnt) {
	uint32 ulIdx;
	for(ulIdx = 0; ulIdx < ulCnt; ulIdx++) {
		pucDst[ulIdx] = pucSrc[ulIdx];
	}
}

uint32 UTI_ulStrLen(uchar8* pucString) {
	uint32 ulCnt = 0;

	while(*pucString != '\0') {
		ulCnt++;
	}

	return ulCnt;
}
