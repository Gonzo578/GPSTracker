/**
 * \file nmeadll.c
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

#include "huart.h"				/* Include UART HAL interface */
#include "utility.h"			/* Include generic utilities */

#include "nmeadll.h"			/* Include own interface declaration */

/*
*********************************************************************************************************
*							LOCAL DEFINITIONS
*********************************************************************************************************
*/
#define NMEAD_UART_INTERFACE		HUART_3		/**< NMEA interface mapping definition */
#define NMEAD_UART_COM_SPEED		57600		/**< NMEA interface communication speed */
#define NMEAD_UART_INT_SOURCE		USART3_IRQn	/**< NMEA interface interrupt source */

#define NMEAD_FRAME_BUFFER_SIZE		5			/**< No. of frames that can be stored within the frame buffer */

#define NMEAD_MAX_FRAME_LENGTH		82			/**< The max. NMEA frame length is 82 characters incl. the
 	 	 	 	 	 	 	 	 	 	 	 	 	 leading '$' and the CR/LF characters at the end */

#define NMEAD_ASCII_CR				0x0D		/**< ASCII code for "carriage return" */
#define NMEAD_ASCII_LF				0x0A		/**< ASCII code for "line feed" */
#define NMEAD_START_OF_FRAME		'$'			/**< Definition of the NMEA start of frame character */
#define NMEAD_CHECKSUM_DELIMITER	'*'			/**< Definition of the NMEA checksum delimiter character */

/*
*********************************************************************************************************
*							LOCAL TYPES
*********************************************************************************************************
*/

/**
 *	\brief	Type definition of the NMEA protocol handler states
 *
 *			There is one state function implemented for each state that is defined
 *			herewith.
 * */
typedef enum _TNMEADProtocolState {
	NMEAD_STATE_SYNCH,		/**< Protocol handler is out of synch */
	NMEAD_STATE_IDLE,		/**< Protocol handler is waiting for a new frame */
	NMEAD_STATE_READ_FRAME,	/**< Protocol handler is reading a frame */
	NMEAD_STATE_WAIT_EOF,	/**< Protocol handler is waiting for the end of the current frame */
	NMEAD_NO_OF_STATES		/**< Number of protocol handler states; used for plausibility checks */
}TNMEADProtocolState;

/**
 *	\brief	NMEA protocol statistics object
 *
 * 			All statistical data that is collected by the NMEA dll layer is collected
 * 			in this structure.
 * */
typedef struct _TNMEAProtocolStatistics {
	uint32			ulReceivedValidFrames;			/**< No. of received valid NMEA frames */
	uint32			ulProcessedFrames;				/**< No. of processed frames */
	uint32			ulReceivedInvalidFrames;		/**< No. of received invalid NMEA frames */
	uint32			ulFrameFormatError;				/**< No. of received frames with invalid frame format */
	uint32			ulFrameChecksumError;			/**< No. of received frames with invalid checksum */
	uint32			ulFrameLengthExceededError;		/**< No. of received frames which exceeded the max. frame length */
	uint32			ulBufferOverrunError;			/**< No. of buffer overrun errors */
	uint32			ulUnknownStateError;			/**< No. of unknown state errors */
	uint32			ulTimeoutError;					/**< No. of timeout errors */
}TNMEAProtocolStatistics;

/**
 * 	\brief	Type definition of the NMEA data object
 *
 * 			All required data to handle the incoming NMEA frames is collected
 * 			within this structure.
 * */
typedef struct _TNMEAObj {
	uchar8					aucNMEAFrameBuffer[NMEAD_FRAME_BUFFER_SIZE][NMEAD_MAX_FRAME_LENGTH];		/**< NMEA frame buffer */
	uchar8					ucFrameWrIdx;				/**< NMEA frame index which points to the next free frame buffer */
	uchar8					ucFrameRdIdx;				/**< NMEA frame index which points to the next NMEA frame to be processed */
	uchar8					ucActChecksum;				/**< Actually computed checksum of the incoming NMEA frame */
	uchar8*					pucBufWrPtr;				/**< Data write pointer which is used to store incoming data bytes in the frame buffer */
	uint32					ulActFrameLength;			/**< No. of bytes received from the incoming frame */
	uint32					ulFramesInBuffer;			/**< No. of received NMEA data frames in buffer */
	TNMEADProtocolState		tProtState;					/**< Actual state the NMEA protocol handler */
	TNMEAProtocolStatistics	tStatistics;				/**< NMEA dll statistics object */
	OS_EVENT*				tFrameSem;					/**< Counting semaphore used for higher layer application interface */
}TNMEAObj;

/*
*********************************************************************************************************
*							FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static BOOL NMEAD_bCheckFrameFormat(void);
static void NMEAD_vHandleProtStateSynch(uchar8 ucRxData);
static void NMEAD_vHandleProtStateIdle(uchar8 ucRxData);
static void NMEAD_vHandleProtStateReadDataFrame(uchar8 ucRxData);
static void NMEAD_vHandleProtStateWaitForEOF(uchar8 ucRxData);

/*
*********************************************************************************************************
*							LOCAL CONSTANTS
*********************************************************************************************************
*/
/**
 * \brief	NMEA Protocol handler state table
 *
 * \remark	Refer to the state enumeration for further description of the states
 * */
void (*NMEAD_afpProtocolStateHandler[])(uchar8 ucRxData) = {
	NMEAD_vHandleProtStateSynch,			/**< State function: Synchronize to protocol */
	NMEAD_vHandleProtStateIdle,				/**< State function: Idle, i.e. no frame is currently received */
	NMEAD_vHandleProtStateReadDataFrame,	/**< State function: Read incoming NMEA data frame */
	NMEAD_vHandleProtStateWaitForEOF		/**< State function: Wait for end of frame delimiter of incoming data frame */
};

/**
 *	\brief	NMEA protocol interface configuration
 *
 *			The NMEA protocol uses UART communication with the format 8N1. The baud rate
 *			can  differ between different receivers.
 * */
const TUARTCfg NMEAD_tUARTInterfaceCfg = {
	NMEAD_UART_COM_SPEED,			/**< UART baud rate */
	UART_PARITY_NONE,				/**< no parity */
	UART_STOPBITS_1,				/**< 1 stopbit */
	UART_DATASIZE_8					/**< 8 data bits */
};

/*
*********************************************************************************************************
*							LOCAL VARIABLES
*********************************************************************************************************
*/

static TNMEAObj NMEAD_tObj = {0};

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/

/**
 * 	\brief	Function checks the NMEA frame format for validity
 *
 * 			In detail the function checks the following attributes of an incoming
 * 			NMEA frame:
 *
 * 			\li The end of the frame must have a "CR" character (0x0D)
 * 			\li There must be a checksum delimiting character '*'
 * 			\li The computed checksum from the incoming data must match with the
 * 				one that is included in the frame.
 *
 * 	\return	TRUE => The frame format is valid; else FALSE
 *
 * */
static BOOL NMEAD_bCheckFrameFormat(void) {
	if(		(*(NMEAD_tObj.pucBufWrPtr - 2) != NMEAD_ASCII_CR)
		|| 	(*(NMEAD_tObj.pucBufWrPtr - 5) != NMEAD_CHECKSUM_DELIMITER)) {
		/*
		 * ERROR: The frame format is invalid
		 *
		 * There was no CR character at the end of the frame or the checksum delimiter
		 * is not correct or missing.
		 * */
		NMEAD_tObj.tStatistics.ulFrameFormatError++;
		return FALSE;
	} else if ( (*(NMEAD_tObj.pucBufWrPtr - 3) != UTI_ucHexToAscii(NMEAD_tObj.ucActChecksum & 0x0F))
			||	(*(NMEAD_tObj.pucBufWrPtr - 4) != UTI_ucHexToAscii(NMEAD_tObj.ucActChecksum >> 4)) ) {
		/*
		 * ERROR: 	The computed checksum from the incoming data does not match with the one
		 * 			in the frame.
		 * */
		NMEAD_tObj.tStatistics.ulFrameChecksumError++;
		return FALSE;
	} else {
		return TRUE;
	}
}

/**
 *	\brief	NMEA synchronization state handler
 *
 *			This state function waits for a 'LF' = 0x0A character for synchronization
 *			purposes. That means the state machine is synchronized when the end of frame
 *			character of one frame is received. This is the first state of the state machine.
 *			If the LF character is received, the state machine changes to IDLE state.
 *
 *	\return	void
 * */
static void NMEAD_vHandleProtStateSynch(uchar8 ucRxData) {
	if (ucRxData == NMEAD_ASCII_LF) {
		/*
		 * STATE TRANSITION:
		 * Line feed character has been received
		 * => Protocol handler is in synch now
		 * => Wait for the next start of frame character
		 *  */
		NMEAD_tObj.tProtState = NMEAD_STATE_IDLE;
	}
}

/**
 * 	\brief	NMEA protocol IDLE state handler
 *
 * 			This function waits for the start of NMEA frame character '$' to begin with the
 * 			reception of any NMEA frame. If this character is received, the state machine
 * 			moves to the read frame state. At this point the internal checksum is initialized.
 *
 * 	\return	void
 * */
static void NMEAD_vHandleProtStateIdle(uchar8 ucRxData) {
	if(ucRxData == NMEAD_START_OF_FRAME) {
		/*
		 * Start of frame character has been received
		 * => store the first character '$'
		 * => reset checksum
		 * => continue with reception of the frame
		 * */
		*NMEAD_tObj.pucBufWrPtr	= ucRxData;
		NMEAD_tObj.pucBufWrPtr++;
		NMEAD_tObj.ulActFrameLength = 1;
		NMEAD_tObj.ucActChecksum    = 0;

		NMEAD_tObj.tProtState	= NMEAD_STATE_READ_FRAME;
	}
}

/**
 * 	\brief	NMEA protocol READ frame state handler
 *
 * 			This state function read the actually incoming frame in the frame buffer.
 * 			Additionally it updates the internal checksum to be able to make a validity
 * 			check of the data after the complete frame has been received.
 * 			If the checksum delimiter is received, the state machine moves to the state
 * 			for waiting for the end of frame characters CR+LF.
 * 			If the frame exceeds the maximum frame length NMEAD_MAX_FRAME_LENGTH an error
 * 			is counted and the state machine re-synchronizes to the protocol. The actual
 * 			frame is refused, i.e means the already stored data is overwritten with the
 * 			next incoming frame.
 *
 * 	\return	void
 * */
static void NMEAD_vHandleProtStateReadDataFrame(uchar8 ucRxData) {
	/*
	 * Store received character and check if the checksum delimiter has been received
	 * */
	*NMEAD_tObj.pucBufWrPtr	= ucRxData;
	NMEAD_tObj.pucBufWrPtr++;
	NMEAD_tObj.ulActFrameLength++;

	if(NMEAD_tObj.ulActFrameLength >= NMEAD_MAX_FRAME_LENGTH) {
		/*
		 * Max. frame length has been reached
		 * => The received frame is invalid
		 * => Discard actually incoming frame and re-synch to protocol
		 * */
		NMEAD_tObj.pucBufWrPtr 	= (uchar8*)(&NMEAD_tObj.aucNMEAFrameBuffer[NMEAD_tObj.ucFrameWrIdx][0]);
		NMEAD_tObj.tStatistics.ulFrameLengthExceededError++;

		NMEAD_tObj.tProtState	= NMEAD_STATE_SYNCH;

	} else if(ucRxData == NMEAD_CHECKSUM_DELIMITER) {
		NMEAD_tObj.tProtState = NMEAD_STATE_WAIT_EOF;
	} else {
		/*
		 * Add byte to checksum
		 * Note: The checksum delimiter does not belong to the checksum!
		 * */
		NMEAD_tObj.ucActChecksum ^= ucRxData;
	}
}

/**
 *	\brief	NMEA protocol EOF state handler
 *
 *			This function waits for the reception of the end of frame character 'LF'.
 *			If this character is received, the actual frame is checked for validity
 *			and possibly accepted as a valid frame for further processing by a higher
 *			level software. Valid frame are handled with a counting semaphore, i.e.
 *			a higher level software can block until a new frame is received.
 *			Additionally the max. frame length is checked. If it is exceeded, the
 *			state machine is resynchronized to the protocol.
 *
 *	\return	void
 * */
static void NMEAD_vHandleProtStateWaitForEOF(uchar8 ucRxData) {
	*NMEAD_tObj.pucBufWrPtr	= ucRxData;
	NMEAD_tObj.pucBufWrPtr++;
	NMEAD_tObj.ulActFrameLength++;

	if (ucRxData == NMEAD_ASCII_LF) {
		/*
		 * EOF has been reached => check format
		 * */
		if(NMEAD_bCheckFrameFormat() != FALSE) {
			/*
			 * The received frame was valid => accept the frame
			 * */
			NMEAD_tObj.ulFramesInBuffer++;
			NMEAD_tObj.ucFrameWrIdx++;
			if(NMEAD_tObj.ucFrameWrIdx >= NMEAD_FRAME_BUFFER_SIZE) {
				/* Wrap around */
				NMEAD_tObj.ucFrameWrIdx = 0;
			}
			NMEAD_tObj.tStatistics.ulReceivedValidFrames++;
			OSSemPost(NMEAD_tObj.tFrameSem);
		} else {
			/*
			 * The received frame was invalid => discard this frame
			 * */
			NMEAD_tObj.tStatistics.ulReceivedInvalidFrames++;
		}

		NMEAD_tObj.pucBufWrPtr = (uchar8*)(&NMEAD_tObj.aucNMEAFrameBuffer[NMEAD_tObj.ucFrameWrIdx][0]);

		NMEAD_tObj.tProtState = NMEAD_STATE_IDLE;
	} else if (NMEAD_tObj.ulActFrameLength >= NMEAD_MAX_FRAME_LENGTH) {
		/*
		 * Max. frame length has been reached
		 * => The received frame is invalid
		 * => Discard actually incoming frame and re-synch to protocol
		 * */
		NMEAD_tObj.pucBufWrPtr 	= (uchar8*)(&NMEAD_tObj.aucNMEAFrameBuffer[NMEAD_tObj.ucFrameWrIdx][0]);
		NMEAD_tObj.tStatistics.ulFrameLengthExceededError++;

		NMEAD_tObj.tProtState	= NMEAD_STATE_SYNCH;
	}else {
		/*
		 * Wait for EOF
		 * */
	}
}

/**
 *	\brief	NMEA Protocol interrupt handler
 *
 * 			This function is called by the USART receive interrupt whenever a new by is
 * 			received from the GPS receiver module. The function calls the actual state
 * 			function depending on the current reception state or handles errors in case
 * 			of unknown internal states.
 *
 * 	\param	ucRxData Received byte from USART resource
 *
 * 	\return	void
 * */
void NMEAD_vNMEAProtocolRxEvent(uint8 ucRxData) {
	if(NMEAD_tObj.tProtState < NMEAD_NO_OF_STATES) {
		/*
		 * State variable is valid => call state handler function
		 * */
		NMEAD_afpProtocolStateHandler[NMEAD_tObj.tProtState](ucRxData);
	} else {
		/*
		 * ERROR: Unknown state
		 * => Reset state machine
		 * => \todo Implement further error handling
		 * => throw ERROR
		 *  */
		NMEAD_tObj.tStatistics.ulUnknownStateError++;

		/* Reset state machine to synch mode */
		NMEAD_tObj.tProtState = NMEAD_STATE_SYNCH;
	}
}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

/* ------------------------------------------------------------------------------------------------
 * uchar8* NMEAD_pucGetNMEAFrame(void)
 * ------------------------------------------------------------------------------------------------ */
uchar8* NMEAD_pucGetNMEAFrame(void) {
	INT8U err;

	OSSemPend(NMEAD_tObj.tFrameSem, 0, &err);

	return (uchar8*)(&NMEAD_tObj.aucNMEAFrameBuffer[NMEAD_tObj.ucFrameRdIdx][0]);
}

/* ------------------------------------------------------------------------------------------------
 * void NMEAD_vReleaseFrame(void)
 * ------------------------------------------------------------------------------------------------ */
void NMEAD_vReleaseFrame(void) {
	NMEAD_tObj.ulFramesInBuffer--;
	NMEAD_tObj.ucFrameRdIdx++;

	if(NMEAD_tObj.ucFrameRdIdx >= NMEAD_FRAME_BUFFER_SIZE) {
		/* Wrap around */
		NMEAD_tObj.ucFrameRdIdx = 0;
	}
	NMEAD_tObj.tStatistics.ulProcessedFrames++;
}

/* ------------------------------------------------------------------------------------------------
 * void NMEAD_vInitNMEADll(void)
 * ------------------------------------------------------------------------------------------------ */
void NMEAD_vInitNMEADll(void) {
	INT8U	tError;

	/* Initialize protocol data object */
	NMEAD_tObj.ucFrameWrIdx	 		= 0;
	NMEAD_tObj.ucFrameRdIdx	 		= 0;
	NMEAD_tObj.pucBufWrPtr 			= (uchar8*)(&NMEAD_tObj.aucNMEAFrameBuffer);
	NMEAD_tObj.ulFramesInBuffer		= 0;
	NMEAD_tObj.tProtState			= NMEAD_STATE_SYNCH;
	NMEAD_tObj.tFrameSem			= OSSemCreate((INT16U)0);

	/* First configure the UART where the GPS receiver is connected to */
	HUART_vInit (NMEAD_UART_INTERFACE, &NMEAD_tUARTInterfaceCfg);

	/*
	 * Configure the receive interrupt event, i.e. connect the handler function to the event and
	 * enable the interrupt
	 *  */
	HUART_tEnableRxEvent(NMEAD_UART_INTERFACE, (TUARTRxEvent)NMEAD_vNMEAProtocolRxEvent);

	/*
	 * Enable the event in the interrupt controller
	 * */
	NVIC_EnableIRQ(NMEAD_UART_INT_SOURCE);

	/*
	 * Enable the receiver to allow reception of the GPS NMEA data frames
	 * */
	HUART_vEnableReceiver(NMEAD_UART_INTERFACE);
}
