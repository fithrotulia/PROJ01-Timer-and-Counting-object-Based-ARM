/*
 * SCHtimeku.c
 *
 *  Created on: Nov 10, 2019
 *      Author: izzat
 */
#include "main.h"
#include "SCHtimeku.h"
#include "stm32f1xx_hal.h"

void TIM4_IRQHandler(void){

}
void SCH_Init(void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	TIM4->PSC = 0;
	TIM4->ARR = 72;
	TIM4->CR1 |= TIM_CR1_URS;
	TIM4->DIER |= TIM_DIER_UIE;
	TIM4->EGR |= TIM_EGR_UG;

	NVIC_EnableIRQ(TIM4_IRQn);

	SysTick_Config(SystemCoreClock/1000);
}
void task_Init(void){
	milisec=0;
	sec=0;
	min=0;
}
void task_run(void)
{
	milisec++;
	if(milisec>999){
		sec++;
		milisec=0;
	}
	if(sec>59){
		min++;
		sec=0;
	}
}
