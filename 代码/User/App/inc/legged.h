/**
  ******************************************************************************
  * @file           : legged.h
  * @brief          : Header for legged.c file.
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
#ifndef _LEGGED_H
#define _LEGGED_H

/* 用户App头文件引用 */
#include "trajectory.h"
/* 核心头文件引用 */
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "tim.h"
#include "math.h"

/** 定义四足各腿长度的宏
 *  L1_length /L4_length 为与舵机直接相连的主动杆
 *  L2_length /L3_length 为从动杆 
 *  bracket_length 为舵机旋转中心的距离（如过小可忽略不计）
 *  具体仿真分析查看MATLAB中。MLX文件
 */
#define L1_length 35.f                      //L1为BC
#define L2_length 80.f                      //L2为CD
#define L3_length L2_length               	//L3为DE
#define L4_length L1_length               	//L4为EA
#define L5_length 15.f                      //L5为脚脖子
#define L2_Front L2_length + L5_length     	//L2_Front总长
#define L3_Front L3_length + L5_length     	//L3_Front总长
#define bracket_length 15.f                 //bracket为AB

/**定义设置舵机中位时存在的误差
 * 在舵机控制时进行补偿
 */
#define COMPENSATE_ANGLE1 90 //舵机角度与计算角度的补偿值
#define COMPENSATE_ANGLE4 270 //舵机角度与计算角度的补偿值

#define SERVO_ERR1 2
#define SERVO_ERR2 1
#define SERVO_ERR3 -1
#define SERVO_ERR4 8
#define SERVO_ERR5 -5
#define SERVO_ERR6 -9
#define SERVO_ERR7 -6
#define SERVO_ERR8 8
/*
 * Crank 连杆角度 
 */
typedef struct 
{
  float crank_L1;
  float crank_L4;
}Crank_typedef;

/*
 * Link 连杆
 */
typedef struct 
{
  /* 实际足端点坐标 */
  Point_typedef point_P;
  /* 铰链坐标（从动杆L2与从动杆L3交点） */
  Point_typedef point_D;
  /* 机座bracket始端坐标 */
  Point_typedef point_A;
  /* 机座bracket末端坐标 */
  Point_typedef point_B;
  /* 连杆旋转角度 */
  Crank_typedef crank;
}Link_typedef;
/*
 * Inverse 逆解算
 */
typedef struct 
{
  /* 逆解算连杆数据 */
  Link_typedef link;
  /* 逆解算足端轨迹相关数据 */
  Trajectory_typedef trajectory;

}Inverse_typedef;

extern void Inverse_Init(Inverse_typedef* inverse_init);
extern void Trajectory_Coordinate_Converter(Inverse_typedef* inverse,float body_h,float pitch_value,float rall_value);
extern void Inverse_Solution(uint8_t LegNum,Link_typedef* link);
#endif

