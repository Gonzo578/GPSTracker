/**
 * \file app_cfg.h	Application configuration file
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
*
*                                      APPLICATION CONFIGURATION
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   STM3210E-EVAL Evaluation Board
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : BAN
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           CLOCK CONFIGURATION
*********************************************************************************************************
*/

#define HSI_CLOCK_MHZ					8		/**< [MHz] Clock frequency of the ext. high speed clock */

/*
*********************************************************************************************************
*                                              TASKS NAMES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define	APP_TASK_START_PRIO				3			/**< Initialization task priority */
#define GPS_DEVICE_TASK_PRIO			4			/**< GPS device task priority */
#define BTN_SAMPLING_TASK_PRIO			5			/**< Button sampling task priority */
#define MMI_TASK_PRIO					6			/**< MMI (man machine interface) task priority */
#define TRK_TASK_PRIO					7			/**< Tracker task priority */
#define	SOL_TASK_PRIO					8			/**< Sign of life task priority */
#define OS_TASK_TMR_PRIO				9			/**< OS timer task priority */

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

#define	APP_TASK_START_STK_SIZE			128		/**< Start task stack size */
#define	GPS_DEVICE_TASK_STK_SIZE		128		/**< GPS device task stack size */
#define BTN_TASK_STK_SIZE				128		/**< Button sampling task stack size */
#define	MMI_TASK_STK_SIZE				128		/**< MMI task stack size */
#define TRK_TASK_STACK_SIZE				256		/**< Tracker task stack size */
#define	APP_TASK_SOL_STK_SIZE			128		/**< Sign of life task stack size */

/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/

#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_ENABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED

#endif
