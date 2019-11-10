/*
 * Sensorku.h
 *
 *  Created on: Nov 10, 2019
 *      Author: izzat
 */

#ifndef INC_SENSORKU_H_
#define INC_SENSORKU_H_

void Open_ADC_Init(void);
void Sensor_ADC_One(void);
void Sensor_ADC_Two(void);
void Sensor_ADC_Three(void);

uint32_t value[3];



#endif /* INC_SENSORKU_H_ */
