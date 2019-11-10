/*
 * Counterku.c
 *
 *  Created on: Nov 10, 2019
 *      Author: izzat
 */

#include "main.h"
#include "HardwareInitku.h"
#include "stm32f1xx_hal.h"
#include "Sensorku.h"
#include "LCDku.h"
#include "SCHtimeku.h"


uint8_t counting_One=0;
uint8_t counting_Two=0;
uint8_t counting_Three=0;

uint32_t time_sens1_milis=0;
uint32_t time_sens1_sec=0;
uint32_t time_sens1_minute=0;

uint32_t time_sens2_milis=0;
uint32_t time_sens2_sec=0;
uint32_t time_sens2_minute=0;

uint32_t time_sens3_milis=0;
uint32_t time_sens3_sec=0;
uint32_t time_sens3_minute=0;

void Count_Sens_One(void)
{
	counting_One++;

	time_sens1_milis=milisec;
	time_sens1_sec=sec;
	time_sens1_minute=min;
}
void Count_Sens_Two(void)
{
	counting_Two++;

	time_sens2_milis=milisec;
	time_sens2_sec=sec;
	time_sens2_minute=min;
}
void Count_Sens_Three(void)
{
	counting_Three++;

	time_sens3_milis=milisec;
	time_sens3_sec=sec;
	time_sens3_minute=min;
}
void Show_Counter(void)
{
	if(counting_One<5){

		LCD_SetCursor(0, 0);
		LCD_Print("S1");
		LCD_SetCursor(3, 0);
		LCD_PrintNum(counting_One);

		LCD_SetCursor(8, 0);
		LCD_PrintNum(time_sens1_minute);LCD_Print(":");
		LCD_PrintNum(time_sens1_sec);LCD_Print(":");
		LCD_PrintNum(time_sens1_milis);

	}else{
		LCD_SetCursor(0, 0);
		LCD_Print("S1");
		LCD_SetCursor(3, 0);
		LCD_Print("FIN");
	}

	if(counting_Two<5){

		LCD_SetCursor(0, 1);
		LCD_Print("S2");
		LCD_SetCursor(3, 1);
		LCD_PrintNum(counting_Two);

		LCD_SetCursor(8, 1);
		LCD_PrintNum(time_sens2_minute);LCD_Print(":");
		LCD_PrintNum(time_sens2_sec);LCD_Print(":");
		LCD_PrintNum(time_sens2_milis);

	}else{
		LCD_SetCursor(0, 1);
		LCD_Print("S2");
		LCD_SetCursor(3, 1);
		LCD_Print("FIN");
	}

	if(counting_Three<5){

		LCD_SetCursor(0, 2);
		LCD_Print("S3");
		LCD_SetCursor(3, 2);
		LCD_PrintNum(counting_Three);

		LCD_SetCursor(8, 2);
		LCD_PrintNum(time_sens3_minute);LCD_Print(":");
		LCD_PrintNum(time_sens3_sec);LCD_Print(":");
		LCD_PrintNum(time_sens3_milis);

	}else{

		LCD_SetCursor(0, 2);
		LCD_Print("S3");
		LCD_SetCursor(3, 2);
		LCD_Print("FIN");
	}

}
