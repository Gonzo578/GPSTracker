/**
 * \file systime.c
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

#include "includes.h"

#include "systime.h"

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
static	TSystemTime	SYST_tActualSystemTime;			/**< Timer overflow counter which is used to compute the actual system time */

/*
*********************************************************************************************************
*							LOCAL FUNCTIONS
*********************************************************************************************************
*/

/**
 *
 * */
void TIM6_IRQHandler(void) {
	/*
	 * Reset interrupt request flag of the peripheral.
	 * This is not automatically done by hardware!
	 * */
	TIM6->SR &= 0xFFFE;

	SYST_tActualSystemTime += (TSystemTime)0x10000;
}

/*
*********************************************************************************************************
*							GLOBAL FUNCTIONS
*********************************************************************************************************
*/

TSystemTime SYST_tGetSystemTime(void) {

	OS_CPU_SR		cpu_sr;
	TSystemTime		tActTime;

	OS_ENTER_CRITICAL();
	tActTime = (TIM6->CNT + SYST_tActualSystemTime);
	OS_EXIT_CRITICAL();

	return tActTime;
}

void SYST_vInitSystemTimeBase(void) {
	TIM6->ARR	= 0xFFFF;
	TIM6->PSC	= 72-1;					/* 1us tick */
	TIM6->DIER	|= TIM_DIER_UIE;		/* Enable update event */
	TIM6->CR1	|= (TIM_CR1_URS | TIM_CR1_CEN);

	NVIC_EnableIRQ(TIM6_IRQn);
}
