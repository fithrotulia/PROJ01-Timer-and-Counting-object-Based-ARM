/*
 * Sensorku.h
 *
 *  Created on: Nov 10, 2019
 *      Author: izzat
 */

#ifndef INC_SENSORKU_H_
#define INC_SENSORKU_H_

void Open_ADC_Init(void);
void Error_Sensor_Hendler(void);
uint8_t PbSTOP_Handler(void);
uint8_t pbReset_Handler(void);
uint32_t Sensor_ADC_One(void);
uint32_t Sensor_ADC_Two(void);
uint32_t Sensor_ADC_Three(void);

uint32_t value[3];



#endif /* INC_SENSORKU_H_ */
