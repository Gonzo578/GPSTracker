/**
 * \file gpsaltitude.h
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

#ifndef __GPSALTITUDE_H_
#define __GPSALTITUDE_H_

/*
*********************************************************************************************************
*							INCLUDES
*********************************************************************************************************
*/

#include "gps_types.h"		/* Include GPS related data types */
#include "nmeaparser.h"		/* Include NMEA parser interface */

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

/**
 * 	\brief	Declaration of the external MSL altitude parser
 * */
extern const TParserCfg	GPST_tMSLAltitudeParser;

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/


#endif /* __GPSALTITUDE_H_ */
