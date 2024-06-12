/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define Start_Button_Pin GPIO_PIN_1
#define Start_Button_GPIO_Port GPIOC
#define Ready_to_Drive_Sound_Pin GPIO_PIN_2
#define Ready_to_Drive_Sound_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define Drive_Enable_Output_Pin GPIO_PIN_5
#define Drive_Enable_Output_GPIO_Port GPIOC
#define APPS_1_SW_Pin GPIO_PIN_6
#define APPS_1_SW_GPIO_Port GPIOC
#define APPS_2_SW_Pin GPIO_PIN_8
#define APPS_2_SW_GPIO_Port GPIOC
#define HV_Present_Pin GPIO_PIN_9
#define HV_Present_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define BRAKE_SIGNAL_BUFFER 50 // this value is used in APPS_Brake_Pedal_Plausibility_Test() to ensure that function doesn't become true in error due to signal noise
#define APPS_MINIMUM_THRESHOLD 400 // this is the minimum 12 bit value that the apps sensor must produce in order to go forward.
#define APPS_FLOOR_THRESHOLD 65 // this is the value that must be produced in addition to the APPS_n_MIN value in order for the car to register a pedal press
#define BPS_MINIMUM_THRESHOLD 200

// TODO: These values must be calibrated when the VCU is integrated with the sensors.
#define BPS_MIN 800  //Below range ADC value for BPS
#define BPS_MAX 3000 //Above range ADC value for BPS
#define BPS_PERCENT_THRESHOLD 1
#define APPS_0_MIN 667 //Below range ADC value for APPS_0
#define APPS_0_MAX 3050 //Above range ADC value for APPS_0
#define APPS_1_SIGNAL_MIN 1210
#define APPS_1_SIGNAL_MAX 3600
#define APPS_1_MIN 1200 //Below range ADC value for APPS_1
#define APPS_1_MAX 3600
// #define APPS_1_MAX (APPS_1_SIGNAL_MAX - APPS_1_SIGNAL_MIN) //Above range ADC value for APPS_1

#define MIN_DAC_VAL 0;
#define MAX_DAC_VAL 4095;

//#define LOOP_TIME_INTERVAL  0.001 //loop time in counts x milliseconds, 0.001 x 0.001 == 0.001s -> 10000Hz
#define LOOP_TIME_INTERVAL 100 //loop time in counts x milliseconds, 100 x 0.001 == 0.1s -> 10Hz
#define SQRT_2 1.4142
#define DEBUG
// #define TESTING
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
