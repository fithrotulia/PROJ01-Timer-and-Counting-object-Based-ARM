/*
 * Sensorku.c
 *
 *  Created on: Nov 10, 2019
 *      Author: izzat
 */

#include "main.h"
#include "HardwareInitku.h"
#include "Sensorku.h"


void Open_ADC_Init(void)
{
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)value, 4);
}
void Sensor_ADC_One(void)
{

}
void Sensor_ADC_Two(void)
{

}
void Sensor_ADC_Three(void)
{

}
