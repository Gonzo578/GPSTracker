/**
 * \file huart.h
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

#ifndef __HUART_H_
#define __HUART_H_

/*
*********************************************************************************************************
*							INCLUDES
*********************************************************************************************************
*/
#include "types.h"

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

/**
 * \brief Type definition of the UART resources
 * */
typedef enum _TUART {
	HUART_1,		/**< UART1 => Mapped to USART1 peripheral */
	HUART_2,		/**< UART2 => Mapped to USART2 peripheral */
	HUART_3,		/**< UART3 => Mapped to USART3 peripheral */
	HUART_4,		/**< UART4 => Mapped to UART4 peripheral */
	HUART_5,		/**< UART5 => Mapped to UART5 peripheral */
	HUART_CHANNELS	/**< Number of UART channels */
}TUART;

/**
 * \brief Type definition of the returned UART error codes
 * */
typedef enum TUARTError {
	UART_OK,						/**< No error */
	UART_ERROR,						/**< Generic error */
	UART_ERROR_UNKNOWN_UART,		/**< Unknown UART resource */
	UART_ERROR_UART_NOT_SUPPORTED	/**< Not supported UART */
}TUARTError;

/*
 * ------------------------------------------------------------------------------------------------------
 * UART configuration types
 * ------------------------------------------------------------------------------------------------------
 * */

/**
 * \brief Type definition of the different parity mode configurations
 * */
typedef enum _TParity {
	UART_PARITY_NONE,		/**< No parity */
	UART_PARITY_EVEN,		/**< Even parity  */
	UART_PARITY_ODD			/**< Odd parity */
}TParity;

/**
 * \brief Type definition of the different numbers of stop bit configurations
 * */
typedef enum _TStopBits {
	UART_STOPBITS_0_5,		/**< 0.5 Stop bits */
	UART_STOPBITS_1,		/**< 1 Stop bit */
	UART_STOPBITS_1_5,		/**< 1.5 Stop bits */
	UART_STOPBITS_2,		/**< 2 Stop bits */
}TStopBits;

/**
 * \brief Type defintion of the different data site configurations
 * */
typedef enum _TDataSize {
	UART_DATASIZE_8,		/**< 8 Data bits */
	UART_DATASIZE_9			/**< 9 Data bits */
}TDataSize;

/**
 * \brief Type definition of the UART configuration object
 * */
typedef struct _TUARTCfg {
	uint32		ulBaudrate;		/**< Baud rate used for communication */
	TParity		tParity;		/**< Parity setting */
	TStopBits	tStopbits;		/**< No. of stop bits */
	TDataSize	tDataSize;		/**< No. of data bits */
}TUARTCfg;

/*
 * ------------------------------------------------------------------------------------------------------
 * UART call-back function types
 * ------------------------------------------------------------------------------------------------------
 * */

/**
 * \brief Type definition of the UART receive event call-back function
 * */
typedef void (*TUARTRxEvent)(uint8 ucRxData);

/**
 * \brief Type definition of the UART transmit complete event call-back function
 * */
typedef void (*TUARTTxCompleteEvent)(void);

/**
 * \brief Type definition of the UART transmit buffer empty event call-back function
 * */
typedef void (*TUARTTxBufferEmptyEvent)(void);

/**
 * \brief Type definition of the UART error event call-back function
 * */
typedef void (*TUARTErrorEvent)(void);

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
 * \brief
 * */
TUARTError HUART_tEnableRxEvent(TUART tUART, TUARTRxEvent fpRxEvent);

/**
 * \brief
 * */
TUARTError HUART_tDisableRxEvent(TUART tUART);

/**
 * \brief
 * */
BOOL HUART_bIsDataReceived(TUART tUART);

/**
 * \brief
 * */
uint8 HUART_ucReceiveData(TUART tUART);

/**
 * \brief
 * */
void HUART_vTransmitData(TUART tUART, uint8 ucData);

/**
 * \brief	Function enables the transmitter of the passed UART
 *
 * \param	tUART UART resource identifier
 * */
void HUART_vEnableTransmitter (TUART tUART);

/**
 * \brief	Function enables the receiver of the passed UART
 *
 * \param	tUART UART resource identifier
 * */
void HUART_vEnableReceiver (TUART tUART);

/**
 * \brief
 * */
TUARTError HUART_vInit (TUART tUART, const TUARTCfg* ptCfg);


#endif /* __HUART_H_ */
