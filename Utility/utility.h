/**
 * \file utility.h
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

#ifndef __UTILITY_H_
#define __UTILITY_H_

/*
*********************************************************************************************************
*							INCLUDES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							GLOBAL DEFINITIONS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*							GLOBAL TYPES
*********************************************************************************************************
*/

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
uchar8 UTI_ucHexToAscii(uchar8 ucHexNum);
uchar8 UTI_ucAsciiToNum(uchar8 ucChar);
uchar8 UTI_ucNumToAscii(uchar8 ucNum);

void UTI_vStrCopy(uchar8* pucSrc, uchar8* pucDst);
void UTI_vMemCopy(uchar8* pucSrc, uchar8* pucDst, uint32 ulCnt);

uint32 UTI_ulStrLen(uchar8* pucString);

#endif /* __UTILITY_H_ */
