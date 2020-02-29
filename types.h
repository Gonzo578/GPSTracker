/**
 * \file types.h
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

#ifndef __TYPES_H
#define __TYPES_H

#include <stdint.h>

#define TRUE        1
#define FALSE       0
#define ON			1
#define OFF			0
#define HIGH		1
#define LOW			0
#define ACTIVE		1
#define INACTIVE	0
#define ENABLE		1
#define DISABLE		0

#ifndef NULL
#define	NULL			((void*)0)	/**< NULL pointer definition */
#endif

typedef unsigned char   BOOL;     /**< Boolean type definitions */
typedef unsigned char   uint8;    /**< 8bit unsigned integer */
typedef unsigned char   uchar8;   /**< 8bit unsigned integer */
typedef unsigned short  uint16;   /**< 16bit unsigned integer */
typedef unsigned int    uint32;   /**< 32bit unsigned integer */
typedef signed char     sint8;    /**< 8bit signed integer */
typedef signed short    sint16;   /**< 16bit signed integer */
typedef signed int      sint32;   /**< 32bit signed integer */

#endif /* __TYPES_H */
