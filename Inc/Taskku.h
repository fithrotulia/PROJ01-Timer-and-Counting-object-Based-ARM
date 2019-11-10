/*
 * Taskku.h
 *
 *  Created on: Nov 10, 2019
 *      Author: izzat
 */

#ifndef INC_TASKKU_H_
#define INC_TASKKU_H_

#include "HardwareInitku.h"
#include "string.h"
#include "stdio.h"

void Task_Init(void);
void Task_Run_Main(void);
void Task_Error_Handler(_Bool, char *);
void Task_Refresh(void);
void Task_Display(_Bool);
void Task_Calibrate(_Bool);


#endif /* INC_TASKKU_H_ */
