/**
 * \file nmeadll.h
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

#ifndef __NMEADLL_H_
#define __NMEADLL_H_

/*
*********************************************************************************************************
*							INCLUDES
*********************************************************************************************************
*/
#include "includes.h"				/* Include generic header */

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

/**
 * 	\brief	Function is used to fetch the next complete NMEA Frame by the application
 *
 * 			This function returns a pointer to the start of the next completely received NMEA
 * 			data frame. This frame is the oldest frame in the frame buffer as the buffer is
 * 			implemented as a fifo structure. If there is actually no complete frame in buffer
 * 			the function blocks until there is at least one complete Frame in buffer. The
 * 			blocking mechanism is implemented via a counting semaphore.
 *
 * 	\return	uchar8*	Pointer to the start of the next complete NMEA frame in buffer
 * */
uchar8* NMEAD_pucGetNMEAFrame(void);

/**
 * 	\brief	This function releases the currently processed frame from buffer
 *
 * 			After processing the NMEA data within a frame, the higher layer module has to
 * 			call this function to allow the NMEA dll layer to overwrite the frame with
 * 			new data, i.e. to virtually remove the processed frame from the buffer.
 * 			This function needs to be called to prevent a buffer overflow.
 *
 * 	\return	void
 * */
void NMEAD_vReleaseFrame(void);

/**
 * 	\brief	NMEA data link layer initialization function
 *
 * 			This function initializes the NMEA data link layer (dll). The function first
 * 			initializes the internal data structures and then sets up the USART interface
 * 			where the GPS receiver is connected to. All NMEA input data an frame handling
 * 			is done within the USART Rx interrupt routine.
 *
 * \return void
 * */
void NMEAD_vInitNMEADll(void) ;

#endif /* __NMEADLL_H_ */
