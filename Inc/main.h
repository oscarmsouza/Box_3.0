/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sigfox.h"
#include "encoder.h"
#include "gprs.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */


struct{
	float
	temperature,
	battery;
}st_stm_adc_variables;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
__IO ITStatus UartReady;// = RESET;

uint32_t value[3];  // to store the adc values
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void blink(uint8_t times);
void fn_fprint(char *data);
float get_temp (uint32_t variable);
void fn_get_stm32_temperature();
void fn_get_stm32_volts();
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define WISOL_LED_CPU_Pin GPIO_PIN_13
#define WISOL_LED_CPU_GPIO_Port GPIOC
#define BLE_RX_Pin GPIO_PIN_0
#define BLE_RX_GPIO_Port GPIOA
#define BLE_TX_Pin GPIO_PIN_1
#define BLE_TX_GPIO_Port GPIOA
#define US_RX_Pin GPIO_PIN_2
#define US_RX_GPIO_Port GPIOA
#define US_TX_Pin GPIO_PIN_3
#define US_TX_GPIO_Port GPIOA
#define V_BAT_FB_Pin GPIO_PIN_4
#define V_BAT_FB_GPIO_Port GPIOA
#define US_AN_Pin GPIO_PIN_5
#define US_AN_GPIO_Port GPIOA
#define HC_SR04_TRG_Pin GPIO_PIN_6
#define HC_SR04_TRG_GPIO_Port GPIOA
#define HC_SR04_PULSE_Pin GPIO_PIN_7
#define HC_SR04_PULSE_GPIO_Port GPIOA
#define EXT_INT1_XL_Pin GPIO_PIN_0
#define EXT_INT1_XL_GPIO_Port GPIOB
#define EXT_INT_MAG_Pin GPIO_PIN_1
#define EXT_INT_MAG_GPIO_Port GPIOB
#define GPRS_RST_Pin GPIO_PIN_2
#define GPRS_RST_GPIO_Port GPIOB
#define PC_DEBUG_RX_Pin GPIO_PIN_10
#define PC_DEBUG_RX_GPIO_Port GPIOB
#define GPS_TX_Pin GPIO_PIN_11
#define GPS_TX_GPIO_Port GPIOB
#define GPS_EXTI_Pin GPIO_PIN_12
#define GPS_EXTI_GPIO_Port GPIOB
#define GPS_TIMEPULSE_Pin GPIO_PIN_13
#define GPS_TIMEPULSE_GPIO_Port GPIOB
#define WISOL_WKP_Pin GPIO_PIN_14
#define WISOL_WKP_GPIO_Port GPIOB
#define WISOL_RST_Pin GPIO_PIN_15
#define WISOL_RST_GPIO_Port GPIOB
#define GPIO_LED_Pin GPIO_PIN_8
#define GPIO_LED_GPIO_Port GPIOA
#define EN_US_Pin GPIO_PIN_9
#define EN_US_GPIO_Port GPIOA
#define EN_GPRS_Pin GPIO_PIN_10
#define EN_GPRS_GPIO_Port GPIOA
#define EN_GPS_Pin GPIO_PIN_11
#define EN_GPS_GPIO_Port GPIOA
#define EN_BLE_Pin GPIO_PIN_12
#define EN_BLE_GPIO_Port GPIOA
#define EN_SFOX_Pin GPIO_PIN_15
#define EN_SFOX_GPIO_Port GPIOA
#define GPRS_RX_Pin GPIO_PIN_3
#define GPRS_RX_GPIO_Port GPIOB
#define GPRS_TX_Pin GPIO_PIN_4
#define GPRS_TX_GPIO_Port GPIOB
#define GPRS_PWR_ON_Pin GPIO_PIN_5
#define GPRS_PWR_ON_GPIO_Port GPIOB
#define SFOX_RX_Pin GPIO_PIN_6
#define SFOX_RX_GPIO_Port GPIOB
#define SFOX_TX_Pin GPIO_PIN_7
#define SFOX_TX_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define LED_ON               	HAL_GPIO_WritePin(GPIO_LED_GPIO_Port,GPIO_LED_Pin,0);
#define LED_OFF              	HAL_GPIO_WritePin(GPIO_LED_GPIO_Port,GPIO_LED_Pin,1);
#define LED_CHANGE           	HAL_GPIO_TogglePin(GPIO_LED_GPIO_Port,GPIO_LED_Pin);

#define GPRS_RESET_ON        	HAL_GPIO_WritePin(GPRS_RST_GPIO_Port,GPRS_RST_Pin,0);
#define GPRS_RESET_OFF       	HAL_GPIO_WritePin(GPRS_RST_GPIO_Port,GPRS_RST_Pin,1);
#define GPRS_ON              	HAL_GPIO_WritePin(EN_GPRS_GPIO_Port,EN_GPRS_Pin,1);
#define GPRS_OFF             	HAL_GPIO_WritePin(EN_GPRS_GPIO_Port,EN_GPRS_Pin,0);
#define GPRS_PWR_ON          	HAL_GPIO_WritePin(GPRS_PWR_ON_GPIO_Port,GPRS_PWR_ON_Pin,1);
#define GPRS_PWR_OFF         	HAL_GPIO_WritePin(GPRS_PWR_ON_GPIO_Port,GPRS_PWR_ON_Pin,0);

#define SIGFOX_ON			 	HAL_GPIO_WritePin(EN_SFOX_GPIO_Port,EN_SFOX_Pin,1);
#define SIGFOX_OFF				HAL_GPIO_WritePin(EN_SFOX_GPIO_Port,EN_SFOX_Pin,0);
#define SIGFOX_RESET_ON			HAL_GPIO_WritePin(EN_SFOX_GPIO_Port,EN_SFOX_Pin,0);
#define SIGFOX_RESET_OFF		HAL_GPIO_WritePin(EN_SFOX_GPIO_Port,EN_SFOX_Pin,1);
#define SIGFOX_WAKEUP_ON		HAL_GPIO_WritePin(EN_SFOX_GPIO_Port,EN_SFOX_Pin,0);
#define SIGFOX_WAKEUP_OFF		HAL_GPIO_WritePin(EN_SFOX_GPIO_Port,EN_SFOX_Pin,1);



// for get battery volts and stm32 temperature let's get the values from the datasheet
#define V25  1.43
#define Avg_Slope .0043
#define VSENSE 3.3/4096   // 3.3 v and 12 bits so 4096





/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
