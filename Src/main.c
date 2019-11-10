/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include "LCDku.h"
#include "HardwareInitku.h"
#include "SCHtimeku.h"
#include "SCHtimeku2.h"
#include "Sensorku.h"
#include "Counterku.h"
/* USER CODE END Includes */
/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	HAL_Init();
	SystemClock_Config();
	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_ADC1_Init();
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */
	Open_ADC_Init();
	LCD_Init();
	LCD_Clear();
	HAL_GPIO_WritePin(LCD_Katoda_GPIO_Port, LCD_Katoda_Pin, GPIO_PIN_SET);
	LCD_SetCursor(0, 0);
	LCD_Print("BISMILLAH.");
	SCH_Init();
	SCH_Init2();
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}
/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{ 
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
