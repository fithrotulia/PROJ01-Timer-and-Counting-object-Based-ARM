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

uint64_t start_sens1=0;
uint64_t start_sens2=0;
uint64_t start_sens3=0;

uint64_t finish_sens1=0;
uint64_t finish_sens2=0;
uint64_t finish_sens3=0;

uint64_t elapse_time_sens1;
uint64_t elapse_time_sens2;
uint64_t elapse_time_sens3;

uint16_t sec_sens1, milisec_sens1;
uint16_t sec_sens2, milisec_sens2;
uint16_t sec_sens3, milisec_sens3;

void Count_Sens_One(void)
{
	counting_One++;

	sec_sens1 =0;
	milisec_sens1=0;

	elapse_time_sens1=0;

	finish_sens1 = counter_stop;

	elapse_time_sens1=finish_sens1-start_sens1;
	milisec_sens1=elapse_time_sens1;
	sec_sens1=milisec_sens1/999;
	milisec_sens1=milisec_sens1-(999*sec_sens1);

	start_sens1 = finish_sens1;


	time_sens1_milis=milisec;
	time_sens1_sec=sec;
	time_sens1_minute=min;
}
void Count_Sens_Two(void)
{
	counting_Two++;

	sec_sens2 =0;
	milisec_sens2=0;

	elapse_time_sens2=0;

	finish_sens2 = counter_stop;

	elapse_time_sens2=finish_sens2-start_sens2;
	milisec_sens2=elapse_time_sens2;
	sec_sens2=milisec_sens2/999;
	milisec_sens2=milisec_sens2-(999*sec_sens2);

	start_sens2 = finish_sens2;

	time_sens2_milis=milisec;
	time_sens2_sec=sec;
	time_sens2_minute=min;
}
void Count_Sens_Three(void)
{
	counting_Three++;

	sec_sens3 =0;
	milisec_sens3=0;

	elapse_time_sens3=0;

	finish_sens3 = counter_stop;

	elapse_time_sens3=finish_sens3-start_sens3;
	milisec_sens3=elapse_time_sens3;
	sec_sens3=milisec_sens3/999;
	milisec_sens3=milisec_sens3-(999*sec_sens3);

	start_sens3 = finish_sens3;

	time_sens3_milis=milisec;
	time_sens3_sec=sec;
	time_sens3_minute=min;
}
void PbStop_ON(void)
{

}
void PbReset_ON(void)
{
	LCD_Clear();
	counting_One=0;
	counting_Two=0;
	counting_Three=0;

	time_sens1_milis=0;
	time_sens1_sec=0;
	time_sens1_minute=0;

	time_sens2_milis=0;
	time_sens2_sec=0;
	time_sens2_minute=0;

	time_sens3_milis=0;
	time_sens3_sec=0;
	time_sens3_minute=0;

	time_milisec=0;
	time_sec=0;
	time_minute=0;

	sec_sens1=0;
	milisec_sens1=0;
	sec_sens2=0;
	milisec_sens2=0;
	sec_sens3=0;
	milisec_sens3=0;


}
void Show_Counter(void)
{
	if(counting_One<5){

		LCD_SetCursor(0, 0);
		LCD_Print("S1");
		LCD_SetCursor(3, 0);
		LCD_PrintNum(counting_One);

		LCD_SetCursor(5, 0);
		LCD_PrintNum(time_sens1_minute);LCD_Print(":");
		LCD_PrintNum(time_sens1_sec);LCD_Print(":");
		LCD_PrintNum(time_sens1_milis);

		LCD_SetCursor(14, 0);
		LCD_PrintNum(sec_sens1);LCD_Print(":");
		LCD_PrintNum(milisec_sens1);

	}else{
		LCD_SetCursor(0, 0);
		LCD_Print("S1");
		LCD_SetCursor(3, 0);
		LCD_Print("FINISH           ");
	}

	if(counting_Two<5){

		LCD_SetCursor(0, 1);
		LCD_Print("S2");
		LCD_SetCursor(3, 1);
		LCD_PrintNum(counting_Two);

		LCD_SetCursor(5, 1);
		LCD_PrintNum(time_sens2_minute);LCD_Print(":");
		LCD_PrintNum(time_sens2_sec);LCD_Print(":");
		LCD_PrintNum(time_sens2_milis);

		LCD_SetCursor(14, 1);
		LCD_PrintNum(sec_sens2);LCD_Print(":");
		LCD_PrintNum(milisec_sens2);

	}else{
		LCD_SetCursor(0, 1);
		LCD_Print("S2");
		LCD_SetCursor(3, 1);
		LCD_Print("FINISH           ");
	}

	if(counting_Three<5){

		LCD_SetCursor(0, 2);
		LCD_Print("S3");
		LCD_SetCursor(3, 2);
		LCD_PrintNum(counting_Three);

		LCD_SetCursor(5, 2);
		LCD_PrintNum(time_sens3_minute);LCD_Print(":");
		LCD_PrintNum(time_sens3_sec);LCD_Print(":");
		LCD_PrintNum(time_sens3_milis);

		LCD_SetCursor(14, 2);
		LCD_PrintNum(sec_sens3);LCD_Print(":");
		LCD_PrintNum(milisec_sens3);

	}else{

		LCD_SetCursor(0, 2);
		LCD_Print("S3");
		LCD_SetCursor(3, 2);
		LCD_Print("FINISH           ");
	}

}
