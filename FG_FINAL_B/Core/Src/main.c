/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "AD9833.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
uint8_t F_PLUS;
uint8_t F_MINUS;
uint8_t SinWave;
uint8_t TriWave;
uint8_t SqrWave;
uint8_t Wave = SIN;
int status[2];
int prev_status[2]={SIN,1000};
long freq=1000;

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
	  SinWave = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_9);
	  if(SinWave == RESET && Wave != SIN){
		  Wave = SIN;
		  goto change;
	  }
	  TriWave = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_8);
	  if(TriWave == RESET && Wave != TRI){
		  Wave = TRI;
		  goto change;
	  }
	  SqrWave = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7);
	  if(SqrWave == RESET && Wave != TRI){
		  Wave = TRI;
		  goto change;
	  }

	  //F_PLUS
	  F_PLUS = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6);
	  if(F_PLUS==0)
	  {
		  F_PLUS = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6);
		  while(F_PLUS==0){
			  F_PLUS = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_6);
				if(freq<1000){
					freq = freq + 25;
					HAL_Delay(300);
				}
				if(freq>=1000 && freq<10000){
					freq = freq + 250;
					HAL_Delay(300);
				}
				if(freq>=10000 && freq<100000){
					freq = freq + 2500;
					HAL_Delay(300);
				}
				if(freq>=100000 && freq<1000000){
					freq = freq + 2500;
					HAL_Delay(300);
				}
				if(freq==1000000){
					freq = 1000000;
					HAL_Delay(300);
				}
		  }
			  if(F_PLUS==1){

					if(freq<1000){
						freq = freq + 25;
						HAL_Delay(300);
						goto change;
					}
					if(freq>=1000 && freq<10000){
						freq = freq + 250;
						HAL_Delay(300);
						goto change;
					}
					if(freq>=10000 && freq<100000){
						freq = freq + 2500;
						HAL_Delay(300);
						goto change;
					}
					if(freq>=100000 && freq<1000000){
						freq = freq + 2500;
						HAL_Delay(300);
						goto change;
					}
					if(freq==1000000){
						freq = 1000000;
						HAL_Delay(300);
						goto change;
					}
				  }

	  }

	  //F_MINUS
	  F_MINUS = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5);
	  if(F_MINUS==0)
	  {
		  F_MINUS = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5);
		  while(F_MINUS==0){
			  F_MINUS = HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5);
			  if(freq<1000){
					freq = freq - 25;
					HAL_Delay(300);
				}
				if(freq>=1000 && freq<10000){
					freq = freq - 250;
					HAL_Delay(300);
				}
				if(freq>=10000 && freq<100000){
					freq = freq - 2500;
					HAL_Delay(300);
				}
				if(freq>=100000 && freq<=1000000){
					freq = freq - 2500;
					HAL_Delay(300);
				}
				if(freq==0){
					freq = 1;
					HAL_Delay(300);
				}
		  }
			  if(F_MINUS==1){

				  if(freq<1000){
						freq = freq - 25;
						HAL_Delay(300);
						goto change;
					}
					if(freq>=1000 && freq<10000){
						freq = freq - 250;
						HAL_Delay(300);
						goto change;
					}
					if(freq>=10000 && freq<100000){
						freq = freq - 2500;
						HAL_Delay(300);
						goto change;
					}
					if(freq>=100000 && freq<=1000000){
						freq = freq - 2500;
						HAL_Delay(300);
						goto change;
					}
					if(freq==0){
						freq = 1;
						HAL_Delay(300);
						goto change;
					}
				  }

	  }

	  change:
	  status[0] = Wave;
	  status[1] = freq;
	  if(prev_status[0]== status[0] && prev_status[1]== status[1])
	  	{

	  	}
	  else{
		  AD9833_Init(Wave,freq,0);
		  prev_status[0] = status[0];
		  prev_status[1] = status[1];
	  }
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL13;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA5 PA6 PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB5 PB6 PB7 PB8
                           PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
