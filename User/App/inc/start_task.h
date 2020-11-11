/**
  ******************************************************************************
  * @file           : start_task.h
  * @brief          : Header fro start_task.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.rog/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
#ifndef _START_TASK_H
#define _START_TASK_H

/* 用户App头文件引用 */
#include "legged.h"
#include "trajectory.h"
#include "gait_task.h"
/* 核心头文件引用 */
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/*
 *运行时间结构体
 */
typedef struct
{
	uint16_t cur_time;
	uint16_t runtime;
	uint16_t lasttime;
}TaskRunTime;

/* 
* 任务控制块 
*/
/* led任务相应宏  */
#define LED_STACK_SIZE    80             //任务堆栈大小
extern osThreadId LedTask_Handler;        //任务句柄（身份证）

/* key任务相应宏 */
#define KEY_STACK_SIZE    80             //任务堆栈大小
extern osThreadId KeyTask_Handler;        //任务句柄（身份证）

/* 轨迹生成任务相应宏 */
#define TRAJECTORY_STACK_SIZE 128         //任务堆栈大小
extern osThreadId TrajectoryTask_Handler; //任务句柄（身份证）

/* 查询任务相应宏 */
#define QUERY_STACK_SIZE 128         //任务堆栈大小
extern osThreadId QueryTask_Handler; //任务句柄（身份证）

/* legged任务相应宏 */
#define LEGGED_STACK_SIZE 256         //任务堆栈大小
extern osThreadId LeggedTask_Handler; //任务句柄（身份证）

/* gait任务相应宏 */
#define GAIT_STACK_SIZE 512         //任务堆栈大小
extern osThreadId GaitTask_Handler; //任务句柄（身份证）

/* 空闲任务 */
extern osThreadId defaultTaskHandle;      //任务句柄（身份证）

/* functions prototypes */
extern void getRunTime(TaskRunTime* time);
extern void StartTest(void);
#endif


