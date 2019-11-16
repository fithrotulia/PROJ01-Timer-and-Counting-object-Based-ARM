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

uint16_t Dark[3]={0, 0, 0};
uint16_t Light[3]={4096, 4096, 4096};
uint16_t Thrs[3]={0, 0, 0};

uint16_t milisecond=0;
uint16_t second=0;
uint16_t minute=0;
uint64_t counter_gap=0;

uint16_t lapA_milis=0;
uint16_t lapA_Sec=0;
uint16_t lapA_minute=0;
uint16_t lapB_milis=0;
uint16_t lapB_Sec=0;
uint16_t lapB_minute=0;
uint16_t lapC_milis=0;
uint16_t lapC_Sec=0;
uint16_t lapC_minute=0;
uint8_t LAP_A=0;
uint8_t LAP_B=0;
uint8_t LAP_C=0;

uint16_t refreshDisplay = 0;
uint16_t timeOut1=0;
uint16_t timeOut2=0;
uint16_t timeOut3=0;
uint16_t timeOut4=0;
uint16_t timeOut5=0;
uint16_t timeOutVal = 700;
unsigned char bouncing1=0xFF;
unsigned char bouncing2=0xFF;
unsigned char bouncing3=0xFF;
unsigned char bouncing4=0xFF;
unsigned char bouncing5=0xFF;
_Bool error = 0;
_Bool stopwatchEnable = 0;

void Task_Init(void)
{
	milisecond=0;
	second=0;
	minute=0;
	counter_gap=0;
	timeOut1=0;
	timeOut2=0;
	timeOut3=0;
	timeOut4=0;
	timeOut5=0;
	lapA_milis=0;
	lapA_Sec=0;
	lapA_minute=0;
	lapB_milis=0;
	lapB_Sec=0;
	lapB_minute=0;
	lapC_milis=0;
	lapC_Sec=0;
	lapC_minute=0;
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
	}

	/*	Reset Button */
	if(Reset_On){
		if(timeOut2 > timeOutVal)
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
		LAP_B=0;
		LAP_C=0;
		milisecond=0;
		second=0;
		minute=0;
		HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET);
	}

	/*	Calibrate Sensor	*/
	Task_Calibrate(!stopwatchEnable);

	if(stopwatchEnable){
		/*Sensor 1*/
		if(value[0] > Thrs[0]){
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
			if(LAP_A >= 5) LAP_A = 4;
			lapA_milis=milisecond;
			lapA_Sec=second;
			lapA_minute=minute;
			Task_Display(stopwatchEnable);
		}

		/*Sensor 2*/
		if(value[1] < Thrs[1]){
			if(timeOut4++ > timeOutVal){
				stopwatchEnable=0;
				LCD_Clear();
				UART_Println("SENS2 ERROR!");
				HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
			}else{
				bouncing4=(bouncing4<<1)|1;
			}
		}else{
			timeOut4=0;
			bouncing4=bouncing4<<1;
		}
		if(bouncing4==3){
			LAP_B++;
			if(LAP_B >= 5) LAP_B = 4;
			lapB_milis=milisecond;
			lapB_Sec=second;
			lapB_minute=minute;
			Task_Display(stopwatchEnable);
		}

		/*Sensor 3*/
		if(value[2] < Thrs[2]){
			if(timeOut5++ > timeOutVal){
				stopwatchEnable=0;
				LCD_Clear();
				UART_Println("SENS3 ERROR!");
				HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
			}else{
				bouncing5=(bouncing5<<1)|1;
			}
		}else{
			timeOut5=0;
			bouncing5=bouncing5<<1;
		}
		if(bouncing5==3){
			LAP_C++;
			if(LAP_C >= 5) LAP_C = 4;
			lapC_milis=milisecond;
			lapC_Sec=second;
			lapC_minute=minute;
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
		if(milisecond>49)
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
		LCD_SetCursor(0, 1);LCD_Print("TR A");LCD_SetCursor(4, 1);LCD_PrintNum(LAP_A);LCD_SetCursor(6, 1);
		LCD_PrintNum(lapA_minute);LCD_Print(":");LCD_PrintNum(lapA_Sec);LCD_Print(":");LCD_PrintNum(lapA_milis);

		LCD_SetCursor(0, 2);LCD_Print("TR B");LCD_SetCursor(4, 2);LCD_PrintNum(LAP_B);LCD_SetCursor(6, 2);
		LCD_PrintNum(lapB_minute);LCD_Print(":");LCD_PrintNum(lapB_Sec);LCD_Print(":");LCD_PrintNum(lapB_milis);

		LCD_SetCursor(0, 3);LCD_Print("TR C");LCD_SetCursor(4, 3);LCD_PrintNum(LAP_C);LCD_SetCursor(6, 3);
		LCD_PrintNum(lapC_minute);LCD_Print(":");LCD_PrintNum(lapC_Sec);LCD_Print(":");LCD_PrintNum(lapC_milis);
	}
}

