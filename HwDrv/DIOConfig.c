/**
 * \file DIOConfig.c
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

#include "includes.h"			/**< Include generic header */
#include "dio.h"				/**< Include digital IO interface */

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

/*-------------------------------------------------------------------------------------------------
 * PORT A CONFIGURATION ---------------------------------------------------------------------------
 *------------------------------------------------------------------------------------------------- */

#define DIO_CFG_PORTA_CONFIG_HIGH	(	(DIO_FLOATING_IN << 0)	/* PA08 */	\
									|	(DIO_FLOATING_IN << 4)	/* PA09 */	\
									|	(DIO_FLOATING_IN << 8)	/* PA10 */	\
									|	(DIO_FLOATING_IN << 12)	/* PA11 */	\
									|	(DIO_FLOATING_IN << 16)	/* PA12 */	\
									|	(DIO_FLOATING_IN << 20)	/* PA13 */	\
									|	(DIO_FLOATING_IN << 24)	/* PA14 */	\
									|	(DIO_FLOATING_IN << 28)	/* PA15 */	\
									)

#define DIO_CFG_PORTA_CONFIG_LOW	(	(DIO_FLOATING_IN << 0)	/* PA00 */	\
									|	(DIO_FLOATING_IN << 4)	/* PA01 */	\
									|	(DIO_FLOATING_IN << 8)	/* PA02 */	\
									|	(DIO_FLOATING_IN << 12)	/* PA03 */	\
									|	(DIO_FLOATING_IN << 16)	/* PA04 */	\
									|	(DIO_FLOATING_IN << 20)	/* PA05 */	\
									|	(DIO_FLOATING_IN << 24)	/* PA06 */	\
									|	(DIO_FLOATING_IN << 28)	/* PA07 */	\
									)

#define DIO_CFG_PORTA_INITIAL_OUTPUT	(	(LOW << 0)	/* PA00 */	\
										|	(LOW << 1)	/* PA01 */	\
										|	(LOW << 2)	/* PA02 */	\
										|	(LOW << 3)	/* PA03 */	\
										|	(LOW << 4)	/* PA04 */	\
										|	(LOW << 5)	/* PA05 */	\
										|	(LOW << 6)	/* PA06 */	\
										|	(LOW << 7)	/* PA07 */	\
										|	(LOW << 8)	/* PA08 */	\
										|	(LOW << 9)	/* PA09 */	\
										|	(LOW << 10)	/* PA10 */	\
										|	(LOW << 11)	/* PA11 */	\
										|	(LOW << 12)	/* PA12 */	\
										|	(LOW << 13)	/* PA13 */	\
										|	(LOW << 14)	/* PA14 */	\
										|	(LOW << 15)	/* PA15 */	\
										)

#define DIO_CFG_PORTA_PULL_UP_DOWN_CONFIG	(	(DIO_PULL_NONE << 0)	 /* PA00 */	\
											|	(DIO_PULL_NONE << 1)	 /* PA01 */	\
											|	(DIO_PULL_NONE << 2)	 /* PA02 */	\
											|	(DIO_PULL_NONE << 3)	 /* PA03 */	\
											|	(DIO_PULL_NONE << 4)	 /* PA04 */	\
											|	(DIO_PULL_NONE << 5)	 /* PA05 */	\
											|	(DIO_PULL_NONE << 6)	 /* PA06 */	\
											|	(DIO_PULL_NONE << 7)	 /* PA07 */	\
											|	(DIO_PULL_NONE << 8)	 /* PA08 */	\
											|	(DIO_PULL_NONE << 9)	 /* PA09 */	\
											|	(DIO_PULL_NONE << 10)	 /* PA10 */	\
											|	(DIO_PULL_NONE << 11)	 /* PA11 */	\
											|	(DIO_PULL_NONE << 12)	 /* PA12 */	\
											|	(DIO_PULL_NONE << 13)	 /* PA13 */	\
											|	(DIO_PULL_NONE << 14)	 /* PA14 */	\
											|	(DIO_PULL_NONE << 15)	 /* PA15 */	\
											)

/*-------------------------------------------------------------------------------------------------
 * PORT B CONFIGURATION ---------------------------------------------------------------------------
 *------------------------------------------------------------------------------------------------- */

#define DIO_CFG_PORTB_CONFIG_HIGH	(	(DIO_PUSHPULL_50MHz_OUT << 0)	/* PB08: LED out */	\
									|	(DIO_PUSHPULL_50MHz_OUT << 4)	/* PB09: LED out */	\
									|	(DIO_PUSHPULL_50MHz_OUT << 8)	/* PB10: LED out */	\
									|	(DIO_FLOATING_IN << 12)			/* PB11: USART3 Rx GPS NMEA */	\
									|	(DIO_PUSHPULL_50MHz_OUT << 16)	/* PB12: LED out "GPS position fixed" */	\
									|	(DIO_PUSHPULL_50MHz_OUT << 20)	/* PB13: LED out "GPS tracking active" */	\
									|	(DIO_PUSHPULL_50MHz_OUT << 24)	/* PB14: LED out */	\
									|	(DIO_PUSHPULL_50MHz_OUT << 28)	/* PB15: LED out "Sign of life" */	\
									)

#define DIO_CFG_PORTB_CONFIG_LOW	(	(DIO_FLOATING_IN << 0)	/* PB00 */	\
									|	(DIO_FLOATING_IN << 4)	/* PB01 */	\
									|	(DIO_FLOATING_IN << 8)	/* PB02 */	\
									|	(DIO_FLOATING_IN << 12)	/* PB03 */	\
									|	(DIO_FLOATING_IN << 16)	/* PB04 */	\
									|	(DIO_FLOATING_IN << 20)	/* PB05 */	\
									|	(DIO_FLOATING_IN << 24)	/* PB06 */	\
									|	(DIO_FLOATING_IN << 28)	/* PB07 */	\
									)

#define DIO_CFG_PORTB_INITIAL_OUTPUT	(	(LOW << 0)	/* PB00 */	\
										|	(LOW << 1)	/* PB01 */	\
										|	(LOW << 2)	/* PB02 */	\
										|	(LOW << 3)	/* PB03 */	\
										|	(LOW << 4)	/* PB04 */	\
										|	(LOW << 5)	/* PB05 */	\
										|	(LOW << 6)	/* PB06 */	\
										|	(LOW << 7)	/* PB07 */	\
										|	(LOW << 8)	/* PB08 */	\
										|	(LOW << 9)	/* PB09 */	\
										|	(LOW << 10)	/* PB10 */	\
										|	(LOW << 11)	/* PB11 */	\
										|	(LOW << 12)	/* PB12 */	\
										|	(LOW << 13)	/* PB13 */	\
										|	(LOW << 14)	/* PB14 */	\
										|	(LOW << 15)	/* PB15 */	\
										)

#define DIO_CFG_PORTB_PULL_UP_DOWN_CONFIG	(	(DIO_PULL_NONE << 0)	 /* PB00 */	\
											|	(DIO_PULL_NONE << 1)	 /* PB01 */	\
											|	(DIO_PULL_NONE << 2)	 /* PB02 */	\
											|	(DIO_PULL_NONE << 3)	 /* PB03 */	\
											|	(DIO_PULL_NONE << 4)	 /* PB04 */	\
											|	(DIO_PULL_NONE << 5)	 /* PB05 */	\
											|	(DIO_PULL_NONE << 6)	 /* PB06 */	\
											|	(DIO_PULL_NONE << 7)	 /* PB07 */	\
											|	(DIO_PULL_NONE << 8)	 /* PB08 */	\
											|	(DIO_PULL_NONE << 9)	 /* PB09 */	\
											|	(DIO_PULL_NONE << 10)	 /* PB10 */	\
											|	(DIO_PULL_NONE << 11)	 /* PB11 */	\
											|	(DIO_PULL_NONE << 12)	 /* PB12 */	\
											|	(DIO_PULL_NONE << 13)	 /* PB13 */	\
											|	(DIO_PULL_NONE << 14)	 /* PB14 */	\
											|	(DIO_PULL_NONE << 15)	 /* PB15 */	\
											)

/*-------------------------------------------------------------------------------------------------
 * PORT C CONFIGURATION ---------------------------------------------------------------------------
 *------------------------------------------------------------------------------------------------- */

#define DIO_CFG_PORTC_CONFIG_HIGH	(	(DIO_FLOATING_IN << 0)	/* PC08 */	\
									|	(DIO_FLOATING_IN << 4)	/* PC09 */	\
									|	(DIO_FLOATING_IN << 8)	/* PC10 */	\
									|	(DIO_FLOATING_IN << 12)	/* PC11 */	\
									|	(DIO_FLOATING_IN << 16)	/* PC12 */	\
									|	(DIO_FLOATING_IN << 20)	/* PC13 */	\
									|	(DIO_FLOATING_IN << 24)	/* PC14 */	\
									|	(DIO_FLOATING_IN << 28)	/* PC15 */	\
									)

#define DIO_CFG_PORTC_CONFIG_LOW	(	(DIO_FLOATING_IN << 0)	/* PC00 */	\
									|	(DIO_FLOATING_IN << 4)	/* PC01 */	\
									|	(DIO_FLOATING_IN << 8)	/* PC02 */	\
									|	(DIO_FLOATING_IN << 12)	/* PC03 */	\
									|	(DIO_FLOATING_IN << 16)	/* PC04 */	\
									|	(DIO_FLOATING_IN << 20)	/* PC05 */	\
									|	(DIO_FLOATING_IN << 24)	/* PC06 */	\
									|	(DIO_FLOATING_IN << 28)	/* PC07 */	\
									)

#define DIO_CFG_PORTC_INITIAL_OUTPUT	(	(LOW << 0)	/* PC00 */	\
										|	(LOW << 1)	/* PC01 */	\
										|	(LOW << 2)	/* PC02 */	\
										|	(LOW << 3)	/* PC03 */	\
										|	(LOW << 4)	/* PC04 */	\
										|	(LOW << 5)	/* PC05 */	\
										|	(LOW << 6)	/* PC06 */	\
										|	(LOW << 7)	/* PC07 */	\
										|	(LOW << 8)	/* PC08 */	\
										|	(LOW << 9)	/* PC09 */	\
										|	(LOW << 10)	/* PC10 */	\
										|	(LOW << 11)	/* PC11 */	\
										|	(LOW << 12)	/* PC12 */	\
										|	(LOW << 13)	/* PC13 */	\
										|	(LOW << 14)	/* PC14 */	\
										|	(LOW << 15)	/* PC15 */	\
										)

#define DIO_CFG_PORTC_PULL_UP_DOWN_CONFIG	(	(DIO_PULL_NONE << 0)	 /* PC00 */	\
											|	(DIO_PULL_NONE << 1)	 /* PC01 */	\
											|	(DIO_PULL_NONE << 2)	 /* PC02 */	\
											|	(DIO_PULL_NONE << 3)	 /* PC03 */	\
											|	(DIO_PULL_NONE << 4)	 /* PC04 */	\
											|	(DIO_PULL_NONE << 5)	 /* PC05 */	\
											|	(DIO_PULL_NONE << 6)	 /* PC06 */	\
											|	(DIO_PULL_NONE << 7)	 /* PC07 */	\
											|	(DIO_PULL_NONE << 8)	 /* PC08 */	\
											|	(DIO_PULL_NONE << 9)	 /* PC09 */	\
											|	(DIO_PULL_NONE << 10)	 /* PC10 */	\
											|	(DIO_PULL_NONE << 11)	 /* PC11 */	\
											|	(DIO_PULL_NONE << 12)	 /* PC12 */	\
											|	(DIO_PULL_NONE << 13)	 /* PC13 */	\
											|	(DIO_PULL_NONE << 14)	 /* PC14 */	\
											|	(DIO_PULL_NONE << 15)	 /* PC15 */	\
											)

/*-------------------------------------------------------------------------------------------------
 * PORT D CONFIGURATION ---------------------------------------------------------------------------
 *------------------------------------------------------------------------------------------------- */

#define DIO_CFG_PORTD_CONFIG_HIGH	(	(DIO_FLOATING_IN << 0)	/* PD08 */	\
									|	(DIO_FLOATING_IN << 4)	/* PD09 */	\
									|	(DIO_FLOATING_IN << 8)	/* PD10 */	\
									|	(DIO_FLOATING_IN << 12)	/* PD11 */	\
									|	(DIO_FLOATING_IN << 16)	/* PD12 */	\
									|	(DIO_FLOATING_IN << 20)	/* PD13 */	\
									|	(DIO_FLOATING_IN << 24)	/* PD14 */	\
									|	(DIO_FLOATING_IN << 28)	/* PD15 */	\
									)

#define DIO_CFG_PORTD_CONFIG_LOW	(	(DIO_FLOATING_IN << 0)	/* PD00 */	\
									|	(DIO_FLOATING_IN << 4)	/* PD01 */	\
									|	(DIO_FLOATING_IN << 8)	/* PD02 */	\
									|	(DIO_FLOATING_IN << 12)	/* PD03 */	\
									|	(DIO_FLOATING_IN << 16)	/* PD04 */	\
									|	(DIO_FLOATING_IN << 20)	/* PD05 */	\
									|	(DIO_FLOATING_IN << 24)	/* PD06 */	\
									|	(DIO_FLOATING_IN << 28)	/* PD07 */	\
									)

#define DIO_CFG_PORTD_INITIAL_OUTPUT	(	(LOW << 0)	/* PD00 */	\
										|	(LOW << 1)	/* PD01 */	\
										|	(LOW << 2)	/* PD02 */	\
										|	(LOW << 3)	/* PD03 */	\
										|	(LOW << 4)	/* PD04 */	\
										|	(LOW << 5)	/* PD05 */	\
										|	(LOW << 6)	/* PD06 */	\
										|	(LOW << 7)	/* PD07 */	\
										|	(LOW << 8)	/* PD08 */	\
										|	(LOW << 9)	/* PD09 */	\
										|	(LOW << 10)	/* PD10 */	\
										|	(LOW << 11)	/* PD11 */	\
										|	(LOW << 12)	/* PD12 */	\
										|	(LOW << 13)	/* PD13 */	\
										|	(LOW << 14)	/* PD14 */	\
										|	(LOW << 15)	/* PD15 */	\
										)

#define DIO_CFG_PORTD_PULL_UP_DOWN_CONFIG	(	(DIO_PULL_NONE << 0)	/* PD00 */	\
											|	(DIO_PULL_NONE << 1)	/* PD01 */	\
											|	(DIO_PULL_NONE << 2)	/* PD02 */	\
											|	(DIO_PULL_NONE << 3)	/* PD03 */	\
											|	(DIO_PULL_NONE << 4)	/* PD04 */	\
											|	(DIO_PULL_NONE << 5)	/* PD05 */	\
											|	(DIO_PULL_NONE << 6)	/* PD06 */	\
											|	(DIO_PULL_NONE << 7)	/* PD07 */	\
											|	(DIO_PULL_NONE << 8)	/* PD08 */	\
											|	(DIO_PULL_NONE << 9)	/* PD09 */	\
											|	(DIO_PULL_NONE << 10) 	/* PD10 */	\
											|	(DIO_PULL_NONE << 11) 	/* PD11 */	\
											|	(DIO_PULL_NONE << 12) 	/* PD12 */	\
											|	(DIO_PULL_NONE << 13) 	/* PD13 */	\
											|	(DIO_PULL_NONE << 14) 	/* PD14 */	\
											|	(DIO_PULL_NONE << 15) 	/* PD15 */	\
											)

/*-------------------------------------------------------------------------------------------------
 * PORT E CONFIGURATION ---------------------------------------------------------------------------
 *------------------------------------------------------------------------------------------------- */

#define DIO_CFG_PORTE_CONFIG_HIGH	(	(DIO_FLOATING_IN << 0)	/* PE08 */	\
									|	(DIO_FLOATING_IN << 4)	/* PE09 */	\
									|	(DIO_FLOATING_IN << 8)	/* PE10 */	\
									|	(DIO_FLOATING_IN << 12)	/* PE11 */	\
									|	(DIO_FLOATING_IN << 16)	/* PE12 */	\
									|	(DIO_FLOATING_IN << 20)	/* PE13 */	\
									|	(DIO_FLOATING_IN << 24)	/* PE14 */	\
									|	(DIO_FLOATING_IN << 28)	/* PE15 */	\
									)

#define DIO_CFG_PORTE_CONFIG_LOW	(	(DIO_FLOATING_IN << 0)	/* PE00 */	\
									|	(DIO_FLOATING_IN << 4)	/* PE01 */	\
									|	(DIO_FLOATING_IN << 8)	/* PE02 */	\
									|	(DIO_FLOATING_IN << 12)	/* PE03 */	\
									|	(DIO_FLOATING_IN << 16)	/* PE04 */	\
									|	(DIO_FLOATING_IN << 20)	/* PE05 */	\
									|	(DIO_FLOATING_IN << 24)	/* PE06 */	\
									|	(DIO_FLOATING_IN << 28)	/* PE07 */	\
									)

#define DIO_CFG_PORTE_INITIAL_OUTPUT	(	(LOW << 0)	/* PE00 */	\
										|	(LOW << 1)	/* PE01 */	\
										|	(LOW << 2)	/* PE02 */	\
										|	(LOW << 3)	/* PE03 */	\
										|	(LOW << 4)	/* PE04 */	\
										|	(LOW << 5)	/* PE05 */	\
										|	(LOW << 6)	/* PE06 */	\
										|	(LOW << 7)	/* PE07 */	\
										|	(LOW << 8)	/* PE08 */	\
										|	(LOW << 9)	/* PE09 */	\
										|	(LOW << 10)	/* PE10 */	\
										|	(LOW << 11)	/* PE11 */	\
										|	(LOW << 12)	/* PE12 */	\
										|	(LOW << 13)	/* PE13 */	\
										|	(LOW << 14)	/* PE14 */	\
										|	(LOW << 15)	/* PE15 */	\
										)

#define DIO_CFG_PORTE_PULL_UP_DOWN_CONFIG	(	(DIO_PULL_NONE << 0)	/* PE00 */	\
											|	(DIO_PULL_NONE << 1)	/* PE01 */	\
											|	(DIO_PULL_NONE << 2)	/* PE02 */	\
											|	(DIO_PULL_NONE << 3)	/* PE03 */	\
											|	(DIO_PULL_NONE << 4)	/* PE04 */	\
											|	(DIO_PULL_NONE << 5)	/* PE05 */	\
											|	(DIO_PULL_NONE << 6)	/* PE06 */	\
											|	(DIO_PULL_NONE << 7)	/* PE07 */	\
											|	(DIO_PULL_NONE << 8)	/* PE08 */	\
											|	(DIO_PULL_NONE << 9)	/* PE09 */	\
											|	(DIO_PULL_NONE << 10)	/* PE10 */	\
											|	(DIO_PULL_NONE << 11)	/* PE11 */	\
											|	(DIO_PULL_NONE << 12)	/* PE12 */	\
											|	(DIO_PULL_NONE << 13)	/* PE13 */	\
											|	(DIO_PULL_NONE << 14)	/* PE14 */	\
											|	(DIO_PULL_NONE << 15)	/* PE15 */	\
											)

/*-------------------------------------------------------------------------------------------------
 * PORT F CONFIGURATION ---------------------------------------------------------------------------
 *------------------------------------------------------------------------------------------------- */

#define DIO_CFG_PORTF_CONFIG_HIGH	(	(DIO_FLOATING_IN << 0)	/* PF08 */	\
									|	(DIO_FLOATING_IN << 4)	/* PF09 */	\
									|	(DIO_FLOATING_IN << 8)	/* PF10 */	\
									|	(DIO_FLOATING_IN << 12)	/* PF11 */	\
									|	(DIO_FLOATING_IN << 16)	/* PF12 */	\
									|	(DIO_FLOATING_IN << 20)	/* PF13 */	\
									|	(DIO_FLOATING_IN << 24)	/* PF14 */	\
									|	(DIO_FLOATING_IN << 28)	/* PF15 */	\
									)

#define DIO_CFG_PORTF_CONFIG_LOW	(	(DIO_FLOATING_IN << 0)	/* PF00 */	\
									|	(DIO_FLOATING_IN << 4)	/* PF01 */	\
									|	(DIO_FLOATING_IN << 8)	/* PF02 */	\
									|	(DIO_FLOATING_IN << 12)	/* PF03 */	\
									|	(DIO_FLOATING_IN << 16)	/* PF04 */	\
									|	(DIO_FLOATING_IN << 20)	/* PF05 */	\
									|	(DIO_FLOATING_IN << 24)	/* PF06 */	\
									|	(DIO_FLOATING_IN << 28)	/* PF07 */	\
									)

#define DIO_CFG_PORTF_INITIAL_OUTPUT	(	(LOW << 0)	/* PF00 */	\
										|	(LOW << 1)	/* PF01 */	\
										|	(LOW << 2)	/* PF02 */	\
										|	(LOW << 3)	/* PF03 */	\
										|	(LOW << 4)	/* PF04 */	\
										|	(LOW << 5)	/* PF05 */	\
										|	(LOW << 6)	/* PF06 */	\
										|	(LOW << 7)	/* PF07 */	\
										|	(LOW << 8)	/* PF08 */	\
										|	(LOW << 9)	/* PF09 */	\
										|	(LOW << 10)	/* PF10 */	\
										|	(LOW << 11)	/* PF11 */	\
										|	(LOW << 12)	/* PF12 */	\
										|	(LOW << 13)	/* PF13 */	\
										|	(LOW << 14)	/* PF14 */	\
										|	(LOW << 15)	/* PF15 */	\
										)

#define DIO_CFG_PORTF_PULL_UP_DOWN_CONFIG	(	(DIO_PULL_NONE << 0)	/* PF00 */	\
											|	(DIO_PULL_NONE << 1)	/* PF01 */	\
											|	(DIO_PULL_NONE << 2)	/* PF02 */	\
											|	(DIO_PULL_NONE << 3)	/* PF03 */	\
											|	(DIO_PULL_NONE << 4)	/* PF04 */	\
											|	(DIO_PULL_NONE << 5)	/* PF05 */	\
											|	(DIO_PULL_NONE << 6)	/* PF06 */	\
											|	(DIO_PULL_NONE << 7)	/* PF07 */	\
											|	(DIO_PULL_NONE << 8)	/* PF08 */	\
											|	(DIO_PULL_NONE << 9)	/* PF09 */	\
											|	(DIO_PULL_NONE << 10) 	/* PF10 */	\
											|	(DIO_PULL_NONE << 11) 	/* PF11 */	\
											|	(DIO_PULL_NONE << 12) 	/* PF12 */	\
											|	(DIO_PULL_NONE << 13) 	/* PF13 */	\
											|	(DIO_PULL_NONE << 14) 	/* PF14 */	\
											|	(DIO_PULL_NONE << 15) 	/* PF15 */	\
											)

/*-------------------------------------------------------------------------------------------------
 * PORT G CONFIGURATION ---------------------------------------------------------------------------
 *------------------------------------------------------------------------------------------------- */

#define DIO_CFG_PORTG_CONFIG_HIGH	(	(DIO_FLOATING_IN << 0)	/* PG08:	Start/stop tracking */	\
									|	(DIO_FLOATING_IN << 4)	/* PG09 */	\
									|	(DIO_FLOATING_IN << 8)	/* PG10 */	\
									|	(DIO_FLOATING_IN << 12)	/* PG11 */	\
									|	(DIO_FLOATING_IN << 16)	/* PG12 */	\
									|	(DIO_FLOATING_IN << 20)	/* PG13 */	\
									|	(DIO_FLOATING_IN << 24)	/* PG14 */	\
									|	(DIO_FLOATING_IN << 28)	/* PG15 */	\
									)

#define DIO_CFG_PORTG_CONFIG_LOW	(	(DIO_FLOATING_IN << 0)	/* PG00 */	\
									|	(DIO_FLOATING_IN << 4)	/* PG01 */	\
									|	(DIO_FLOATING_IN << 8)	/* PG02 */	\
									|	(DIO_FLOATING_IN << 12)	/* PG03 */	\
									|	(DIO_FLOATING_IN << 16)	/* PG04 */	\
									|	(DIO_FLOATING_IN << 20)	/* PG05 */	\
									|	(DIO_FLOATING_IN << 24)	/* PG06 */	\
									|	(DIO_FLOATING_IN << 28)	/* PG07 */	\
									)

#define DIO_CFG_PORTG_INITIAL_OUTPUT	(	(LOW << 0)	/* PG00 */	\
										|	(LOW << 1)	/* PG01 */	\
										|	(LOW << 2)	/* PG02 */	\
										|	(LOW << 3)	/* PG03 */	\
										|	(LOW << 4)	/* PG04 */	\
										|	(LOW << 5)	/* PG05 */	\
										|	(LOW << 6)	/* PG06 */	\
										|	(LOW << 7)	/* PG07 */	\
										|	(LOW << 8)	/* PG08 */	\
										|	(LOW << 9)	/* PG09 */	\
										|	(LOW << 10)	/* PG10 */	\
										|	(LOW << 11)	/* PG11 */	\
										|	(LOW << 12)	/* PG12 */	\
										|	(LOW << 13)	/* PG13 */	\
										|	(LOW << 14)	/* PG14 */	\
										|	(LOW << 15)	/* PG15 */	\
										)

#define DIO_CFG_PORTG_PULL_UP_DOWN_CONFIG	(	(DIO_PULL_NONE << 0)	/* PG00 */	\
											|	(DIO_PULL_NONE << 1)	/* PG01 */	\
											|	(DIO_PULL_NONE << 2)	/* PG02 */	\
											|	(DIO_PULL_NONE << 3)	/* PG03 */	\
											|	(DIO_PULL_NONE << 4)	/* PG04 */	\
											|	(DIO_PULL_NONE << 5)	/* PG05 */	\
											|	(DIO_PULL_NONE << 6)	/* PG06 */	\
											|	(DIO_PULL_NONE << 7)	/* PG07 */	\
											|	(DIO_PULL_NONE << 8)	/* PG08 */	\
											|	(DIO_PULL_NONE << 9)	/* PG09 */	\
											|	(DIO_PULL_NONE << 10)	/* PG10 */	\
											|	(DIO_PULL_NONE << 11) 	/* PG11 */	\
											|	(DIO_PULL_NONE << 12) 	/* PG12 */	\
											|	(DIO_PULL_NONE << 13) 	/* PG13 */	\
											|	(DIO_PULL_NONE << 14) 	/* PG14 */	\
											|	(DIO_PULL_NONE << 15) 	/* PG15 */	\
											)

/*
*********************************************************************************************************
*							LOCAL CONSTANTS
*********************************************************************************************************
*/

const TDioConfig DIO_atIoPortConfig[] = {
	{	GPIOA_ENABLE,						/* IO port A configuration */
		GPIOA,
		DIO_CFG_PORTA_CONFIG_HIGH,
		DIO_CFG_PORTA_CONFIG_LOW,
		DIO_CFG_PORTA_INITIAL_OUTPUT,
		DIO_CFG_PORTA_PULL_UP_DOWN_CONFIG},
	{	GPIOB_ENABLE,						/* IO port B configuration */
		GPIOB,
		DIO_CFG_PORTB_CONFIG_HIGH,
		DIO_CFG_PORTB_CONFIG_LOW,
		DIO_CFG_PORTB_INITIAL_OUTPUT,
		DIO_CFG_PORTB_PULL_UP_DOWN_CONFIG},
	{	GPIOC_ENABLE,						/* IO port C configuration */
		GPIOC,
		DIO_CFG_PORTC_CONFIG_HIGH,
		DIO_CFG_PORTC_CONFIG_LOW,
		DIO_CFG_PORTC_INITIAL_OUTPUT,
		DIO_CFG_PORTC_PULL_UP_DOWN_CONFIG},
	{	GPIOD_ENABLE,						/* IO port D configuration */
		GPIOD,
		DIO_CFG_PORTD_CONFIG_HIGH,
		DIO_CFG_PORTD_CONFIG_LOW,
		DIO_CFG_PORTD_INITIAL_OUTPUT,
		DIO_CFG_PORTD_PULL_UP_DOWN_CONFIG},
	{	GPIOE_DISABLE,						/* IO port E configuration */
		GPIOE,
		DIO_CFG_PORTE_CONFIG_HIGH,
		DIO_CFG_PORTE_CONFIG_LOW,
		DIO_CFG_PORTE_INITIAL_OUTPUT,
		DIO_CFG_PORTE_PULL_UP_DOWN_CONFIG},
	{	GPIOF_DISABLE, 						/* IO port F configuration */
		GPIOF,
		DIO_CFG_PORTF_CONFIG_HIGH,
		DIO_CFG_PORTF_CONFIG_LOW,
		DIO_CFG_PORTF_INITIAL_OUTPUT,
		DIO_CFG_PORTF_PULL_UP_DOWN_CONFIG},
	{	GPIOG_ENABLE, 						/* IO port G configuration */
		GPIOG,
		DIO_CFG_PORTG_CONFIG_HIGH,
		DIO_CFG_PORTG_CONFIG_LOW,
		DIO_CFG_PORTG_INITIAL_OUTPUT,
		DIO_CFG_PORTG_PULL_UP_DOWN_CONFIG},
};

const uint32	DIO_ulConfigSize	=	(uint32)(sizeof(DIO_atIoPortConfig)/sizeof(TDioConfig));
