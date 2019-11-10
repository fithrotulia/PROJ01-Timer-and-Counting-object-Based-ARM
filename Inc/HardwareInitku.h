/*
 * HardwareInitku.h
 *
 *  Created on: Nov 10, 2019
 *      Author: izzat
 */

#ifndef INC_HARDWAREINITKU_H_
#define INC_HARDWAREINITKU_H_

#include "stm32f1xx_hal.h"

#define Reset_On 	HAL_GPIO_ReadPin(Pb_Reset_GPIO_Port, Pb_Reset_Pin)==GPIO_PIN_RESET
#define Start_On	HAL_GPIO_ReadPin(Pb_SS_GPIO_Port, Pb_SS_Pin)==GPIO_PIN_RESET
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_ADC1_Init(void);
void MX_USART2_UART_Init(void);

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
UART_HandleTypeDef huart2;



#endif /* INC_HARDWAREINITKU_H_ */
