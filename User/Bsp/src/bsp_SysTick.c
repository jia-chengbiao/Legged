	/**
  ******************************************************************************
  * @file           : bsp_SysTick.c
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
#include "bsp_SysTick.h"

__IO static u32 TimingDelay;
 
/**
  * @brief  启动滴答计时器 SysTick
  * @param  无
  * @retval 无
  */
void SysTick_Init(void)
{
	/* SystemFrequency / 1000    1ms中断一次
	 * SystemFrequency / 100000	 10us中断一次
	 * SystemFrequency / 1000000 1us中断一次
	 */
	if (HAL_SYSTICK_Config(SystemCoreClock / 1000000))
	{ 
		/* Capture error */ 
		while (1);
	}
}

/**
  * @brief   us延时程序,1us为一个单位
  * @param  
  *	@arg nTime: delay_us( 1 ) 实现延时 1 * 1us = 1us
  * @retval  无
  */
void delay_us(__IO u32 nTime)
{ 
	TimingDelay = nTime;	

	while(TimingDelay != 0);
}
/**
  * @brief  获取节拍程序
  * @param  无
  * @retval 无
  * @attention  在 SysTick 中断函数SysTick_Handler()调用
  */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}
/*********************************************END OF FILE**********************/
