/**
 * \file huart.c
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

#include "includes.h"			/* Include generic header */
#include "HUART.h"				/* Include own header */

/*
*********************************************************************************************************
*							FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void HUART_vDefaultRxEvent(uint8 ucRxData);
static void HUART_vDefaultTxCompletexEvent(void);
static void HUART_vDefaultTxBufferEmptyEvent(void);
static void HUART_vDefaultErrorEvent(void);
static void HUART_vHandleEvent(TUART tUART);

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

/**
 * \brief Definition of the UART register mapping table
 *
 * \note This constant is used together with the interface type TUART. That means the first
 * 			enumeration value in TUART is mapped to the first entry in this table. The 2nd
 * 			enum value is mapped to the 2nd entry and so on.
 * */
USART_TypeDef* const HUART_ptMapping[] = {
	USART1,			/**< mapped to HUART_1 */
	USART2,			/**< mapped to HUART_2 */
	USART3,			/**< mapped to HUART_3 */
	UART4,			/**< mapped to HUART_4 */
	UART5			/**< mapped to HUART_5 */
};

/*
*********************************************************************************************************
*							LOCAL VARIABLES
*********************************************************************************************************
*/

/**
 * \brief Rx Event handler array
 *
 * The event handler array is initialized with the default handler implementation.
 * */
static TUARTRxEvent				HUART_afpRxEvents[HUART_CHANNELS] = {
		HUART_vDefaultRxEvent,
		HUART_vDefaultRxEvent,
		HUART_vDefaultRxEvent,
		HUART_vDefaultRxEvent,
		HUART_vDefaultRxEvent
};

/**
 * \brief Tx complete event handler array
 *
 * The event handler array is initialized with the default handler implementation.
 * */
static TUARTTxCompleteEvent		HUART_afpTxCompleteEvents[HUART_CHANNELS] = {
		HUART_vDefaultTxCompletexEvent,
		HUART_vDefaultTxCompletexEvent,
		HUART_vDefaultTxCompletexEvent,
		HUART_vDefaultTxCompletexEvent,
		HUART_vDefaultTxCompletexEvent
};

/**
 * \brief Tx buffer empty event handler array
 *
 * The event handler array is initialized with the default handler implementation.
 * */
static TUARTTxBufferEmptyEvent	HUART_afpTxBufferEmptyEvents[HUART_CHANNELS] = {
		HUART_vDefaultTxBufferEmptyEvent,
		HUART_vDefaultTxBufferEmptyEvent,
		HUART_vDefaultTxBufferEmptyEvent,
		HUART_vDefaultTxBufferEmptyEvent,
		HUART_vDefaultTxBufferEmptyEvent
};

/**
 * \brief Error event handler array
 *
 * The event handler array is initialized with the default handler implementation.
 * */
static TUARTErrorEvent			HUART_afpErrorEvents[HUART_CHANNELS] = {
		HUART_vDefaultErrorEvent,
		HUART_vDefaultErrorEvent,
		HUART_vDefaultErrorEvent,
		HUART_vDefaultErrorEvent,
		HUART_vDefaultErrorEvent
};

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/

/**
 * \brief Default implementation of the Rx event handler
 * */
static void HUART_vDefaultRxEvent(uint8 ucRxData) {
	(void)ucRxData;		/* Prevent compiler warning */
}

/**
 * \brief Default implementation of the Tx complete event handler
 * */
static void HUART_vDefaultTxCompletexEvent(void) {

}

/**
 * \brief Default implementation of the Tx buffer empty event handler
 * */
static void HUART_vDefaultTxBufferEmptyEvent(void) {

}

/**
 * \brief Default implementation of the error event handler
 * */
static void HUART_vDefaultErrorEvent(void) {

}

static void HUART_vHandleEvent(TUART tUART) {
	if((HUART_ptMapping[tUART]->SR & USART_SR_RXNE) != 0) {
		HUART_afpRxEvents[tUART]((uint8)HUART_ptMapping[tUART]->DR);
	} else if ((HUART_ptMapping[tUART]->SR & USART_SR_TC) != 0) {
		HUART_afpTxCompleteEvents[tUART]();
	} else if ((HUART_ptMapping[tUART]->SR & USART_SR_TXE) != 0) {
		HUART_afpTxBufferEmptyEvents[tUART]();
	} else if ((HUART_ptMapping[tUART]->SR & (USART_SR_PE | USART_SR_FE | USART_SR_NE | USART_SR_ORE)) != 0) {
		HUART_afpErrorEvents[tUART]();
	}
}

/*
*********************************************************************************************************
*							INTERRUPT FUNCTIONS
*********************************************************************************************************
*/

void USART1_IRQHandler(void) {
	OSIntEnter();
	HUART_vHandleEvent(HUART_1);
	OSIntExit();
}

void USART2_IRQHandler(void) {
	OSIntEnter();
	HUART_vHandleEvent(HUART_2);
	OSIntExit();
}

void USART3_IRQHandler(void) {
	OSIntEnter();
	HUART_vHandleEvent(HUART_3);
	OSIntExit();
}

void UART4_IRQHandler(void) {
	OSIntEnter();
	HUART_vHandleEvent(HUART_4);
	OSIntExit();
}

void UART5_IRQHandler(void) {
	OSIntEnter();
	HUART_vHandleEvent(HUART_5);
	OSIntExit();
}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

/*
 * ------------------------------------------------------------------------------------------------------
 * TUARTError HUART_tEnableRxEvent(TUART tUART, TUARTRxEvent fpRxEvent)
 * ------------------------------------------------------------------------------------------------------
 * */
TUARTError HUART_tEnableRxEvent(TUART tUART, TUARTRxEvent fpRxEvent) {
	if (tUART < HUART_CHANNELS) {
		HUART_afpRxEvents[tUART] = fpRxEvent;
		HUART_ptMapping[tUART]->CR1 |= USART_CR1_RXNEIE;
		return UART_OK;
	} else {
		return UART_ERROR_UNKNOWN_UART;
	}
}

/*
 * ------------------------------------------------------------------------------------------------------
 * TUARTError HUART_tDisableRxEvent(TUART tUART)
 * ------------------------------------------------------------------------------------------------------
 * */
TUARTError HUART_tDisableRxEvent(TUART tUART) {
	if (tUART < HUART_CHANNELS) {
		HUART_ptMapping[tUART]->CR1 &= ~USART_CR1_RXNEIE;
		HUART_afpRxEvents[tUART] = (TUARTRxEvent)HUART_vDefaultRxEvent;
		return UART_OK;
	} else {
		return UART_ERROR_UNKNOWN_UART;
	}
}

/*
 * ------------------------------------------------------------------------------------------------------
 * BOOL HUART_bIsDataReceived(TUART tUART)
 * ------------------------------------------------------------------------------------------------------
 * */
BOOL HUART_bIsDataReceived(TUART tUART) {
	if((HUART_ptMapping[tUART]->SR & USART_SR_RXNE) != 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
 * ------------------------------------------------------------------------------------------------------
 * uint8 HUART_ucReceiveData(TUART tUART)
 * ------------------------------------------------------------------------------------------------------
 * */
uint8 HUART_ucReceiveData(TUART tUART) {
	return (uint8)HUART_ptMapping[tUART]->DR;
}

/*
 * ------------------------------------------------------------------------------------------------------
 * void HUART_vTransmitData(TUART tUART, uint8 ucData)
 * ------------------------------------------------------------------------------------------------------
 * */
void HUART_vTransmitData(TUART tUART, uint8 ucData) {
	HUART_ptMapping[tUART]->DR = ucData;
}

/*
 * ------------------------------------------------------------------------------------------------------
 * void HUART_vEnableTransmitter (TUART tUART)
 * ------------------------------------------------------------------------------------------------------
 * */
void HUART_vEnableTransmitter (TUART tUART) {
	HUART_ptMapping[tUART]->CR1 |= USART_CR1_TE;
}

/*
 * ------------------------------------------------------------------------------------------------------
 * void HUART_vEnableReceiver (TUART tUART)
 * ------------------------------------------------------------------------------------------------------
 * */
void HUART_vEnableReceiver (TUART tUART) {
	HUART_ptMapping[tUART]->CR1 |= USART_CR1_RE;
}

/*
 * ------------------------------------------------------------------------------------------------------
 * TUARTError HUART_vInit (TUART tUART, const TUARTCfg* ptCfg)
 * ------------------------------------------------------------------------------------------------------
 * */
TUARTError HUART_vInit (TUART tUART, const TUARTCfg* ptCfg) {
	uint32		ulPrescaler;
	uint16_t	uiReg;


	switch(tUART) {
	case HUART_1:
		return UART_ERROR_UART_NOT_SUPPORTED;
		break;

	case HUART_2:
		break;

	case HUART_3:
		break;

	case HUART_4:
		return UART_ERROR_UART_NOT_SUPPORTED;
		break;

	case HUART_5:
		return UART_ERROR_UART_NOT_SUPPORTED;
		break;

	default:
		return UART_ERROR_UNKNOWN_UART;
		break;	/* CPU will never reach this position */
	}

	/* Configure baud rate prescaler */
	/*
	 * \todo Remove number by function which returns APB clock frequency
	 * */
	ulPrescaler  = 36000000;				/* Set to peripheral clock */
	ulPrescaler /= ptCfg->ulBaudrate;
	HUART_ptMapping[tUART]->BRR = (uint16_t)ulPrescaler;

	uiReg = 0x0000;

	/* Configure parity */
	if(ptCfg->tParity != UART_PARITY_NONE) {
		uiReg |= USART_CR1_PCE;
		if(ptCfg->tParity == UART_PARITY_EVEN) {
			/* Even parity */
		} else {
			/* Odd parity */
			uiReg |= USART_CR1_PS;
		}
	}

	if(ptCfg->tDataSize == UART_DATASIZE_9) {
		/* Select 9 data bits */
		uiReg |= USART_CR1_M;
	}

	HUART_ptMapping[tUART]->CR1 |= uiReg;

	switch(ptCfg->tStopbits) {
	case UART_STOPBITS_0_5:
		HUART_ptMapping[tUART]->CR2 |= USART_CR2_STOP_0;
		break;
	case UART_STOPBITS_1:
		break;
	case UART_STOPBITS_1_5:
		HUART_ptMapping[tUART]->CR2 |= USART_CR2_STOP_0 | USART_CR2_STOP_1;
		break;
	case UART_STOPBITS_2:
		HUART_ptMapping[tUART]->CR2 |= USART_CR2_STOP_1;
		break;
	}

	HUART_ptMapping[tUART]->CR1 |= USART_CR1_UE;

	return UART_OK;
}
