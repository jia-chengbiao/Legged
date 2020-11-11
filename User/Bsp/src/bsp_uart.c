/**
  ******************************************************************************
  * @file           : bsp_uart.c
  * @brief          : 
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
  *******************************************************************************
  */
#include "bsp_uart.h"

extern uint8_t ControlBuffer;			//接收中断缓冲
extern void Get_ControlData(uint8_t data);

/**
  * @brief  串口中断回调
  * @param  huart
  * @retval 
  * @attention  
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* 
    NOTE: This function Should not be modified, when the callback is needed,
    the HAL_UART_TxCpltCallback could be implemented in the user file
   */
  UNUSED(huart);
	if(huart == (&huart1))
	{
		Get_ControlData(ControlBuffer);
		HAL_UART_Receive_IT(&huart1, (uint8_t *)&ControlBuffer, 1);   //再开启接收中断
	}
}


