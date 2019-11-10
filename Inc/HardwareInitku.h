/*
 * HardwareInitku.h
 *
 *  Created on: Nov 10, 2019
 *      Author: izzat
 */

#ifndef INC_HARDWAREINITKU_H_
#define INC_HARDWAREINITKU_H_

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_ADC1_Init(void);
void MX_USART2_UART_Init(void);

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
UART_HandleTypeDef huart2;



#endif /* INC_HARDWAREINITKU_H_ */
