/*
 * Taskku.c
 *
 *  Created on: Nov 10, 2019
 *      Author: izzat
 */

#include "main.h"
#include "HardwareInitku.h"
#include "LCDku.h"
#include "Taskku.h"
#include "Sensorku.h"
#include "UARTku.h"
#include "SCHtimeku.h"

uint16_t Dark[3];
uint16_t Light[3]={4096, 4096, 4096};
uint16_t Thrs[3];

uint16_t milisecond, second, minute;
uint64_t counter_gap=0;
uint16_t lapA_milis, lapA_Sec, lapA_minute;
uint16_t lapB_milis, lapB_Sec, lapA_minute;
uint16_t lapC_milis, lapC_Sec, lapC_minute;
uint8_t LAP_A, LAP_B, LAP_C;

uint16_t refreshDisplay;
uint16_t timeOut1, timeOut2, timeOut3, timeOut4, timeOut5, timeOutVal = 1000;
unsigned char bouncing1=0xFF;
unsigned char bouncing2=0xFF;
unsigned char bouncing3=0xFF;
unsigned char bouncing4=0xFF;
unsigned char bouncing5=0xFF;
_Bool error;
_Bool stopwatchEnable;

void Task_Init(void)
{
	milisecond=0;
	second=0;
	minute=0;
	LCD_Init();
}
void Task_Calibrate(_Bool state)
{
	if(state)
	{
		for(uint8_t i=0; i<3; i++){
			if(value[i] < Light[i])
			{
				Light[i] = value[i];
			}
			if(value[i] > Dark[i])
			{
				Dark[i] = value[i];
			}
			Thrs[i] = ((Light[i]+Dark[i])/2)-200;
		}
	}
}

void Task_Run_Main(void)
{
	/* Start Button */
	if(Start_On){
		if(timeOut1++ > timeOutVal){
			stopwatchEnable=0;
			UART_Println("PUSH BUTTON RESET ERROR!");
			HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
		}else{
			bouncing1 = (bouncing1<<1)|1;

		}
	}else{
		timeOut1=0;
		bouncing1=(bouncing1<<1);
	}
	if(bouncing1==3){
		stopwatchEnable = !(stopwatchEnable);
		Task_Display(stopwatchEnable);
		TIM4->CR1 |= TIM_CR1_CEN;
	}

	/*	Reset Button */
	if(Reset_On){
		if(timeOut2++ > timeOutVal)
		{
			stopwatchEnable=0;
			UART_Println("PUSH BUTTON RESET ERROR!");
			HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
		}else{
			bouncing2 = (bouncing2<<1)|1;
		}
	}else{
		timeOut2=0;
		bouncing2=(bouncing2<<1);
	}
	if(bouncing2==3){
		LCD_Clear();
		LAP_A=0;
		HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET);
	}

	/*	Calibrate Sensor	*/
	Task_Calibrate(!stopwatchEnable);
	Task_Calibrate(!stopwatchEnable);

	if(stopwatchEnable){
		/*Sensor 1*/
		if(value[0] < Thrs[0]){
			if(timeOut3++ > timeOutVal){
				stopwatchEnable=0;
				LCD_Clear();
				UART_Println("SENS1 ERROR!");
				HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
			}else{
				bouncing3=(bouncing3<<1)|1;
			}
		}else{
			timeOut3=0;
			bouncing3=bouncing3<<1;
		}
		if(bouncing3==3){
			LAP_A++;
			if(LAP_A > 5) LAP_A = 4;
			lapA_milis=milisecond;
			lapA_Sec=second;
			lapA_minute=minute;
			Task_Display(stopwatchEnable);
		}
	}
}
void Task_Run_Stopwatch(void)
{
	if(stopwatchEnable)
	{
		milisecond++;
		counter_gap++;
		if(milisecond>99)
		{
			milisecond=0;
			second++;
			if(second>59)
			{
				second=0;
				minute++;
			}
		}
		if(!error)
		{
			LCD_SetCursor(0, 0);LCD_Print("STOPWATCH:");
			LCD_SetCursor(11, 0);
			LCD_PrintNum(minute);LCD_Print(":");LCD_PrintNum(second);LCD_Print(":");LCD_PrintNum(milisecond);
		}
	}
}
void Task_Error_Handler(_Bool state, char *pData)
{

}
void Task_Refresh(void)
{

}
void Task_Display(_Bool state)
{
	if(state)
	{
		LCD_SetCursor(0, 1);LCD_PrintNum(LAP_A);LCD_SetCursor(5, 1);
		LCD_PrintNum(lapA_minute);LCD_Print(":");LCD_PrintNum(lapA_Sec);LCD_Print(":");LCD_PrintNum(lapA_milis);
	}
}

