/**
  ******************************************************************************
  * @file           : gait.h
  * @brief          : Header fro gait.c file.
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

#ifndef _GAIT_H
#define _GAIT_H

/* 用户App头文件引用 */
#include "start_task.h"
#include "legged.h"
#include "remote.h"
/* 核心头文件引用 */
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tim.h"
#include "math.h"
/* 步态模式宏 */
#define TROT 1
/* 步态摆动相占空比宏 */
#define TROT_FAI 0.5f

/* 运动模式宏 */
#define FORWARD 1
#define BACK    2
#define RIGHT   3
#define LEFT    4
/* 计时器标志宏 */
#define TIME_BEGIN 0
#define TIME_START 1
#define TIME_CLEAR 2
#define TIME_STOP 3

#define TIME_S 100.f

typedef struct 
{
  /* 四足步态模式 */
  uint8_t GaitMode;
  /* 计时器标志位 */ 
  uint8_t TimeFlag;
  /* 足端轨迹用户指令 */
  float stride;
  float lift_h; 
  /* 机体控制用户指令 */
  float speed;
  float body_h;

  float pitch_control;
  float pitch_value[4];//俯仰
  float yaw_control;  //航向
  float roll_control;
  float roll_value[4];//横滚

}Control_Typedef;

/* 步态数据结构体 */
typedef struct 
{
  /* 逆解算数据 */
  Inverse_typedef inverse[4];
  
  Control_Typedef control;

}Gait_Typedef;

extern Gait_Typedef Trot;
extern void Gait_Task(void const * argument);

#endif

