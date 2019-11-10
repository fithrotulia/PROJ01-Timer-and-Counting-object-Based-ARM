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
#include "Counterku.h"
#include "SCHtimeku.h";

uint16_t Dark[3];
uint16_t Light[3]={4096, 4096, 4096};
uint16_t Thrs[3];
uint32_t lapA_milis, lapA_Sec, lapA_minute;
uint8_t LAP_A, LAP_B, LAP_C;
uint16_t refreshDisplay;
uint64_t timeOut1, timeOut2, timeOut3, timeOut4, timeOut5, timeOutVal = 500000;
unsigned char bouncing1=0xFF;
unsigned char bouncing2=0xFF;
unsigned char bouncing3=0xFF;
unsigned char bouncing4=0xFF;
unsigned char bouncing5=0xFF;
_Bool error;
_Bool stopwatchEnable;

void Task_Init(void)
{
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
		bouncing1=bouncing1<<1;
	}
	if(bouncing1==3){
		stopwatchEnable = !stopwatchEnable;
	}

	/*	Reset Button */
	if(Reset_On){
		if(timeOut2++ > timeOutVal)
		{
			UART_Println("PUSH BUTTON RESET ERROR!");
			HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_SET);
		}else{
			bouncing2 = (bouncing2<<1)|1;
		}
	}else{
		timeOut2=0;
		bouncing2=bouncing2<<1;
	}
	if(bouncing2==3){
		LCD_Clear();
		HAL_GPIO_WritePin(Buzzer_GPIO_Port, Buzzer_Pin, GPIO_PIN_RESET);
	}

	/*	Calibrate Sensor	*/
	Task_Calibrate(!stopwatchEnable);

	if(stopwatchEnable){
		if(value[0] < Thrs[0]){
			if(timeOut3++ > timeOutVal){
				stopwatchEnable=0;
				LCD_Clear();
				UART_Println("SENS1 ERROR!");
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
			lapA_milis=milisec;
			lapA_Sec=sec;
			lapA_minute=min;
			Task_Display(stopwatchEnable);
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
	LCD_SetCursor(0, 1);
	LCD_PrintNum(LAP_A);
	LCD_SetCursor(0, 2);
	LCD_PrintNum(lapA_minute);LCD_Print(":");LCD_PrintNum(lapA_Sec);LCD_Print(":");LCD_PrintNum(lapA_milis);
	show_timer();
}

