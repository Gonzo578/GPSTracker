/**
 * \file main.c	Main file => Entry of the MySportTracker project
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

#include "includes.h"		/* Include global header file */
#include "dio.h"			/* Include digital IO interface */
#include "sol.h"			/* Include sign of life interface */
#include "gps.h"			/* Include GPS positioning interface */
#include "systime.h"		/* Include system time base interface */
#include "tracker.h"		/* Include tracker task interface */
#include "button.h"			/* Include button interface */
#include "mmi.h"			/* Include MMI interface */

/*
*********************************************************************************************************
*							FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void MAI_vConfigurePeripheralClocks(void);
static	void  App_TaskStart (void *p_arg);

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
static OS_STK App_TaskStartStk[APP_TASK_START_STK_SIZE];

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/

/**
 * \brief	Function configures all peripheral clocks as required by the application
 * */
static void MAI_vConfigurePeripheralClocks(void) {
	/* APB1 Peripheral clock configuration */
	RCC->APB1ENR |= (
						RCC_APB1ENR_USART2EN	/* USART2 Enable PC communication */
					|	RCC_APB1ENR_USART3EN	/* USART2 Enable NMEA interface */
					|	RCC_APB1ENR_TIM6EN		/* TIM6 Enable system time base */
					);
}

/**
 * \brief Application start task
 *
 * This task function is started at the very beginning after starting the RTOS kernel.
 * The task is used to setup the application itself. First it initializes the system
 * time tick which is required by the RTOS. After this the other application tasks
 * are created.
 * Finally the task terminates itself because it is no longer needed because it has
 * done its work.
 *
 * \param p_arg Standard parameter of an RTOS task. Not needed by this task function.
 *
 * \return void
 * */
static  void  App_TaskStart (void *p_arg) {
	(void)p_arg;		/* Prevent compiler warnings */

	/* First initialize the OS tick event */
	OS_CPU_SysTickInit();

	/* Initialize the statistic task */
	OSStatInit();

	/* Configure digital IO ports */
	DIO_vInitPorts(DIO_atIoPortConfig, DIO_ulConfigSize);

	/* Enable the peripheral clocks of the required units */
	MAI_vConfigurePeripheralClocks();

	SYST_vInitSystemTimeBase();

	/* Set up other application tasks */
	BTN_vInitButtonTask();				/* Button interface */
	SOL_vInitSignOfLifeTask();			/* Sign of life */
	GPS_vInitGPSDeviceTask();			/* GPS position */
	TRK_vInitTask();					/* GPS tracker */
	MMI_vInitTask();					/* MMI task */

	/* Finally delete the initialization task */
	OSTaskDel(APP_TASK_START_PRIO);

	/* Code will never get here */
	while(1) {

	}
}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

/**
 * \brief Main Function => Application entry point
 *
 * This function first initializes the RTOS kernel and the creates justr one task
 * before starting the RTOS. This task is used to setup the application itself.
 *
 * \return int	Always (int)0
 *
 * \note At this point the system time tick which is required by the RTOS is not
 * 			running!
*/
int main(void)
{
	INT8U  os_err;

    OSInit();                                                   /* Initialize "uC/OS-II, The Real-Time Kernel".         */

    os_err = OSTaskCreate (	(void (*)(void *)) App_TaskStart,  /* Create the start task.                               */
                            (void          * ) 0,
                            (OS_STK        * )&App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],
                            (INT8U           ) APP_TASK_START_PRIO);

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II).  */

    /* Code will never get here because OSStart usually never returns */
	return ((int)0);
}

/**
 * \brief Function returns the system clock frequency
 *
 * \todo Move this function to another file
 * */
INT32U OS_CPU_SysTickClkFreq(void) {
	return SystemCoreClock;
}
