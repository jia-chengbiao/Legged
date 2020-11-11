/**
  ******************************************************************************
  * File Name          : start_task.c
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
/* 用户App头文件引用 */
#include "start_task.h"

osThreadId GaitTask_Handler;      //Gait任务句柄

/**
  * @brief   开始函数
  * @param   
  * @retval  无
	* @attention  用于创建开始任务
  *             对于cubemx所定义的的任务优先级一共只有7个
  *             在枚举结构体osPriority中有说明，最低的空闲任务优先级为0
  */
void StartTest(void)
{
	/* 创建legged任务 */
  osThreadDef(gait_task,          			//任务名称
							Gait_Task,          			//任务函数
							osPriorityNormal,         //任务优先级
							NULL,                     //任务参数
							GAIT_STACK_SIZE);   			//任务堆栈大小
	GaitTask_Handler = osThreadCreate(osThread(gait_task), NULL);
}
/**
  * @brief  检测程序周期运行时间长度
  * @param  
  * @retval 无
  * @attention
  */
void getRunTime(TaskRunTime* time)
{
		time->cur_time = HAL_GetTick();
		time->runtime = time->cur_time - time->lasttime;
		time->lasttime = time->cur_time;
}

