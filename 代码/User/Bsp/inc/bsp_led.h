/**
  ******************************************************************************
  * @file           : bsp_led.h
  * @brief          : Header for bsp_led.c file.
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
#ifndef __LED_H
#define	__LED_H

#include "main.h"


/** 控制LED灯亮灭的宏
	* LED低电平亮，设置ON=0，OFF=1
	* 若LED高电平亮，设置ON=1，OFF=0
	*/
#define ON  GPIO_PIN_RESET
#define OFF GPIO_PIN_SET

/* 带参宏，可当内联函数一样使用 */
#define LED(a)	HAL_GPIO_WritePin(LED_GPIO_PORT,LED_PIN,a)


/* 定义控制IO的宏 */
#define LED_TOGGLE  HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin)
#define LED_OFF		HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,OFF)
#define LED_ON		HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin,ON)


#endif /* __LED_H */
