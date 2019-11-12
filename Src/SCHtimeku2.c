/*
 * SCHtimeku2.c
 *
 *  Created on: Nov 11, 2019
 *      Author: izzat
 */
#include "SCHtimeku2.h"
#include "Taskku.h"

void TIM3_IRQHandler(void)
{
	Task_Run_Main();
}
void SCH_Init2(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	TIM3->PSC = 0;
	TIM3->ARR = 144;
	TIM3->CR1 |= TIM_CR1_URS;
	TIM3->DIER |= TIM_DIER_UIE;
	TIM3->EGR |= TIM_EGR_UG;
	//TIM3->CR1 |= TIM_CR1_CEN;

	NVIC_EnableIRQ(TIM3_IRQn);
}
