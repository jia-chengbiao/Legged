/**
  ******************************************************************************
  * File Name          : remote.c
  * Description        : 
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

#include "remote.h"

/* 用于四足运动控制 */
extern char control_data[2];
/* 串口数据接收 */
#define CONTROLBUFFERSIZE  6     //最大接收字节数
char RxBuffer[CONTROLBUFFERSIZE];   //接收数据
uint8_t ControlBuffer;			//接收中断缓冲
uint8_t ControlBuffer_Cnt;		//接收缓冲计数



/**
  * @brief  用户指令控制
  * @param  
  * @retval 无
  * @attention
  */
uint8_t Remote_control(void)
{
    if(strncmp(control_data,"01",2) == 0)//前进
			return 1;
    else if(strncmp(control_data,"02",2) == 0)//后退
			return 2;
		else if(strncmp(control_data,"03",2) == 0)//原地转向
			return 3;
		else if(strncmp(control_data,"04",2) == 0)//原地转向
			return 4;
		else if(strncmp(control_data,"00",2) == 0)//停止
			return 0;
		else 
			return 5;
}




/**
  * @brief  串口遥控数据获取
  * @param  data
  * @retval 
  * @attention  
  */
void Get_ControlData(uint8_t data)
{
	if(ControlBuffer_Cnt < CONTROLBUFFERSIZE)
	{
		RxBuffer[ControlBuffer_Cnt++] = data;   //接收数据转存
		if(RxBuffer[0] != 'M')//判断包头
		{
			ControlBuffer_Cnt = 0;
			memset(RxBuffer,0x00,sizeof(RxBuffer)); //清空数组
		}
	}
	if(RxBuffer[ControlBuffer_Cnt-2] == 'O' &&RxBuffer[ControlBuffer_Cnt-1] == 'K')//判断包尾
	{
		if(ControlBuffer_Cnt > 2 && strncmp(RxBuffer,"M1",2) == 0)
		{
			for(uint8_t i = 0;i < 2;i++)
				control_data[i] = RxBuffer[i+2];
			ControlBuffer_Cnt = 0;
			memset(RxBuffer,0x00,sizeof(RxBuffer)); //清空数组
		}
	}
	if(ControlBuffer_Cnt >= CONTROLBUFFERSIZE)
	{
		ControlBuffer_Cnt = 0;
		memset(RxBuffer,0x00,sizeof(RxBuffer)); //清空数组
	}
}

