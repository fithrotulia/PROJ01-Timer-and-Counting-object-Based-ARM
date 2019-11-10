/*
 * Sensorku.c
 *
 *  Created on: Nov 10, 2019
 *      Author: izzat
 */

#include "main.h"
#include "HardwareInitku.h"
#include "Sensorku.h"

UART_HandleTypeDef huart2;

uint64_t timeout_Value = 3000000;
uint64_t timeout_Loop = 0;

void Open_ADC_Init(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)value, 4);
}

uint32_t Sensor_ADC_One(void)
{
	uint8_t flagDetected=0;
	timeout_Loop=0;
	if(value[0]<4095){
		HAL_Delay(20);
		if(value[0]<4095){
			while(value[0]<4095 && timeout_Loop++ < timeout_Value);
			if(timeout_Loop>=timeout_Value){
				while(value[0]<4095){
					HAL_UART_Transmit(&huart2, (uint8_t *)&"SENS1 ERROR!\n\r", 20, 10);
					Error_Sensor_Hendler();
				}
			}else{
				flagDetected=1;
			}
		}
	}

	return flagDetected;
}

uint32_t Sensor_ADC_Two(void)
{
	uint8_t flagDetected=0;
	timeout_Loop=0;
	if(value[1]<4095){
		HAL_Delay(20);
		if(value[1]<4095){
			while(value[1]<4095 && timeout_Loop++ < timeout_Value);
			if(timeout_Loop>=timeout_Value){
				while(value[1]<4095){
					HAL_UART_Transmit(&huart2, (uint8_t *)&"SENS2 ERROR!\n\r", 20, 10);
					Error_Sensor_Hendler();
				}
			}else{
				flagDetected=1;
			}
		}
	}

	return flagDetected;
}

uint32_t Sensor_ADC_Three(void)
{
	uint8_t flagDetected=0;
	timeout_Loop=0;
	if(value[2]<4095){
		HAL_Delay(20);
		if(value[2]<4095){
			while(value[2]<4095 && timeout_Loop++ < timeout_Value);
			if(timeout_Loop>=timeout_Value){
				while(value[2]<4095){
					HAL_UART_Transmit(&huart2, (uint8_t *)&"SENS3 ERROR!\n\r", 20, 10);
					Error_Sensor_Hendler();
				}
			}else{
				flagDetected=1;
			}
		}
	}

	return flagDetected;

}


uint8_t PbSTOP_Handler(void)
{
	uint8_t flagDetected=0;
	if(HAL_GPIO_ReadPin(Pb_SS_GPIO_Port, Pb_SS_Pin)==GPIO_PIN_RESET){
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(Pb_SS_GPIO_Port, Pb_SS_Pin)==GPIO_PIN_RESET){
			while(HAL_GPIO_ReadPin(Pb_SS_GPIO_Port, Pb_SS_Pin)==GPIO_PIN_RESET);
			flagDetected=1;
		}
	}

	return flagDetected;
}

uint8_t pbReset_Handler(void)
{
	uint8_t flagDetected=0;
	if(HAL_GPIO_ReadPin(Pb_Reset_GPIO_Port, Pb_Reset_Pin)==GPIO_PIN_RESET){
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(Pb_Reset_GPIO_Port, Pb_Reset_Pin)==GPIO_PIN_RESET){
			while(HAL_GPIO_ReadPin(Pb_Reset_GPIO_Port, Pb_Reset_Pin)==GPIO_PIN_RESET);
			flagDetected=1;
		}
	}

	return flagDetected;
}

void Error_Sensor_Hendler(void)
{
	HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_Katoda_GPIO_Port, LCD_Katoda_Pin, GPIO_PIN_RESET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_Katoda_GPIO_Port, LCD_Katoda_Pin, GPIO_PIN_SET);
	HAL_Delay(200);
}
