/**
 * \file dio.c
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

#include "includes.h"		/* Include generic header */

#include "dio.h"			/* Include own header */

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

void DIO_vSetPort(TIoPort* ptIoPort, uint16_t uiPortMask) {
	ptIoPort->BSRR	= uiPortMask;
}

void DIO_vResetPort(TIoPort* ptIoPort, uint16_t uiPortMask) {
	ptIoPort->BRR	= uiPortMask;
}

uint16_t DIO_uiReadPort(TIoPort* ptIoPort) {
	return (uint16_t)ptIoPort->IDR;
}

BOOL DIO_bReadPortPin(TIoPort* ptIoPort, uint16_t uiPortMask) {
	if((ptIoPort->IDR & uiPortMask) == uiPortMask) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void DIO_vInitPorts(const TDioConfig* ptCfg, const uint32 ulCfgSize) {
	uint32	ulIdx;

	for(ulIdx = 0; ulIdx < ulCfgSize; ulIdx++) {
		if(ptCfg->ulPortActivation != 0) {
			/*
			 * IO port shall be activated
			 * => Enable clock via RCC register
			 * => GPIOs are located on APB2
			 * */
			RCC->APB2ENR |= ptCfg->ulPortActivation;
			ptCfg->tIoPort->ODR = ptCfg->ulInitialOutputState | ptCfg->uiPullUpDownConfig;
			ptCfg->tIoPort->CRH = ptCfg->ulPortConfigHigh;
			ptCfg->tIoPort->CRL = ptCfg->ulPortConfigLow;
		}
		ptCfg++;
	}
}
