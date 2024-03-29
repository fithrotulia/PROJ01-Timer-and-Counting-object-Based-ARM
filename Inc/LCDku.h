/*
 * LCDku.h
 *
 *  Created on: Nov 10, 2019
 *      Author: izzat
 */

#ifndef INC_LCDKU_H_
#define INC_LCDKU_H_


#define LCD_EN()			{ HAL_GPIO_WritePin(LCD_Enable_GPIO_Port, LCD_Enable_Pin, GPIO_PIN_SET);\
							  HAL_Delay(1);\
							  HAL_GPIO_WritePin(LCD_Enable_GPIO_Port, LCD_Enable_Pin, GPIO_PIN_RESET);\
							  HAL_Delay(1);}

#define LCD_RW(state)		{HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, (state)? GPIO_PIN_SET : GPIO_PIN_RESET);}
#define LCD_RS(state)		{HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, (state)? GPIO_PIN_SET : GPIO_PIN_RESET);}
#define LCD_Command(data)	{LCD_Send(0,data);}
#define LCD_Data(data)		{LCD_Send(1,data);}

void LCD_Write4Bit(uint8_t);
void LCD_Send(_Bool, uint8_t);
void LCD_Init(void);
void LCD_Print(char *);
void LCD_PrintNum(uint16_t);
void LCD_SetCursor(uint8_t, uint8_t);
void LCD_Clear(void);


#endif /* INC_LCDKU_H_ */
