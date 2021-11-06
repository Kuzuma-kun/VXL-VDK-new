/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RUNNING_Pin GPIO_PIN_5
#define RUNNING_GPIO_Port GPIOA
#define BTN0_Pin GPIO_PIN_6
#define BTN0_GPIO_Port GPIOA
#define BTN1_Pin GPIO_PIN_7
#define BTN1_GPIO_Port GPIOA
#define T0_Pin GPIO_PIN_0
#define T0_GPIO_Port GPIOB
#define T1_Pin GPIO_PIN_1
#define T1_GPIO_Port GPIOB
#define T2_Pin GPIO_PIN_2
#define T2_GPIO_Port GPIOB
#define T10_Pin GPIO_PIN_10
#define T10_GPIO_Port GPIOB
#define T11_Pin GPIO_PIN_11
#define T11_GPIO_Port GPIOB
#define BTN2_Pin GPIO_PIN_8
#define BTN2_GPIO_Port GPIOA
#define T3_Pin GPIO_PIN_3
#define T3_GPIO_Port GPIOB
#define T4_Pin GPIO_PIN_4
#define T4_GPIO_Port GPIOB
#define T5_Pin GPIO_PIN_5
#define T5_GPIO_Port GPIOB
#define T6_Pin GPIO_PIN_6
#define T6_GPIO_Port GPIOB
#define T7_Pin GPIO_PIN_7
#define T7_GPIO_Port GPIOB
#define T8_Pin GPIO_PIN_8
#define T8_GPIO_Port GPIOB
#define T9_Pin GPIO_PIN_9
#define T9_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
