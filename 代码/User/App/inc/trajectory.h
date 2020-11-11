/**
  ******************************************************************************
  * @file           : trajectory.h
  * @brief          : Header for trajectory.c file.
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
#ifndef _TRAJECTORY_H
#define _TRAJECTORY_H

/* 用户App头文件引用 */

/* 核心头文件引用 */
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tim.h"
#include "math.h"

#define STRAIGHT_TEST 0

/*
 * 定义坐标结构体
 */
typedef struct
{
  /* data */
  float x;
  float z;
}Point_typedef;

typedef struct 
{
  /* 计时器 */
  const float *clock_t;
  float t;
  /* 步态周期: Ts */
  float Ts;
  /* 支撑相占空比 */
  float fai;
  /* 摆动相周期 */
  float Tm;
  /*  步幅：Stride */
  float* control_stride;
	float stride;
  /*  抬腿高度：h */
  float* control_lift_h;
  float lift_h;
}Cycle_typedef;

/*
 * 定义轨迹的结构体
 */
typedef struct
{
  Cycle_typedef cycle;

  Point_typedef point_out;
  
}Trajectory_typedef;

extern void Trajectory_Planning(Trajectory_typedef* trajectory);
#endif

