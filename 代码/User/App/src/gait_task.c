/**
  ******************************************************************************
  * File Name          : gait.c
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

#include "gait_task.h"

Gait_Typedef Trot;
/* 步态数据初始化 */
void Gait_Init(Gait_Typedef* gait_init);
static void Trot_Cycle_Init(Cycle_typedef* cycle_init,float* stride,float* lift_h);
/* 步态控制循环 */
static void Gait_Loop(void);
/* 腿的坐标系/相位转换 */
static void Legged_Converter(uint8_t LegNum,Cycle_typedef* Converter,float yaw_value);

static void Control(Control_Typedef* control);

/**
  * @brief  Gait任务
  * @param  
  * @retval 无
  * @attention
  */
void Gait_Task(void const * argument)
{
	Gait_Init(&Trot);
		/* 打开定时器 计数器开始计数 */
    Trot.control.TimeFlag = TIME_START;
    while(1)
    {
		  Gait_Loop();
			vTaskDelay(1);
    }
}

/**
  * @brief  Gait任务控制循环
  * @param  
  * @retval 无
  * @attention
  */
static void Gait_Loop(void)
{
    /* 用户指令输入 */
		Control(&Trot.control);
		
    for(uint8_t i = 0;i < 4;i++){
        /* 腿坐标系/相位转换 */
        Legged_Converter(i,&Trot.inverse[i].trajectory.cycle,Trot.control.yaw_control);
        /* 足端轨迹生成 */
        Trajectory_Planning(&Trot.inverse[i].trajectory);
        /* 足端在单腿坐标系下的坐标转换 */
        Trajectory_Coordinate_Converter(&Trot.inverse[i],
                                        Trot.control.body_h,
                                        Trot.control.pitch_value[i],
                                        Trot.control.roll_value[i]);
        /* 逆解算执行 */
        Inverse_Solution(i,&Trot.inverse[i].link);
    }

}

/**
  * @brief  Gait任务参数初始化
  * @param  
  * @retval 无
  * @attention
  */
static void Gait_Init(Gait_Typedef* gait_init)
{
    /* 各腿数据初始化 */
    for(uint8_t i = 0;i < 4;i++){

        Inverse_Init(&gait_init->inverse[i]);
        
        Trot_Cycle_Init(&gait_init->inverse[i].trajectory.cycle,&gait_init->control.stride,&gait_init->control.lift_h);
    }

}
/** 
  * @brief  Gait步态周期参数初始化
  * @param  
  * @retval 无
  * @attention
  */
static void Trot_Cycle_Init(Cycle_typedef* cycle_init,float* stride,float* lift_h)
{
    cycle_init->clock_t = Clock_t();
    cycle_init->Ts = TIME_S;
    cycle_init->fai = TROT_FAI;
	  cycle_init->Tm = cycle_init->Ts * cycle_init->fai;
    
    cycle_init->control_lift_h = lift_h;
    cycle_init->control_stride = stride;
}
/**
  * @brief  腿坐标系/相位转换
  * @param  
  * @retval 无
  * @attention
  */
static void Legged_Converter(uint8_t LegNum,Cycle_typedef* Converter,float yaw_value)
{
    /* 腿坐标系方向修改 */
    switch(LegNum)
    {
     
      case 0:
      case 2: Converter->stride = -(*Converter->control_stride - yaw_value);
							Converter->lift_h = *Converter->control_lift_h;break;
      default:Converter->stride = (*Converter->control_stride + yaw_value);
							Converter->lift_h = *Converter->control_lift_h;break;
    }

    /* 相位设置 */
    Converter->t = *Converter->clock_t;
    switch(LegNum)
    {
      case 0:
      case 3: Converter->t += Converter->Tm;
              if(Converter->t >= Converter->Ts)
                Converter->t -= Converter->Ts;break;
      default:Converter->t = Converter->t;break;
    }
}
/**
  * @brief  用户指令控制
  * @param  
  * @retval 无
  * @attention
  */
char control_data[2] = {0};

static void Control(Control_Typedef* control)
{
		switch(Remote_control())
		{
			case FORWARD:
				control->TimeFlag = TIME_START;control->stride = 60.f;control->pitch_control = -5.f;control->roll_control = 0.f;control->yaw_control = 0.f;
				break;
			case BACK:
				control->TimeFlag = TIME_START;control->stride = -60.f;	control->pitch_control = 5.f;control->roll_control = 0.f;control->yaw_control = 0.f;
				break;
			case TURNRIGHT:
				control->TimeFlag = TIME_START;control->stride = 0.f;control->pitch_control = 0.f;control->roll_control = 0.f;control->yaw_control = -10.f;
				break;
			case TURNLEFT:
				control->TimeFlag = TIME_START;control->stride = 0.f;control->pitch_control = 0.f;control->roll_control = 0.f;control->yaw_control = 10.f;
				break;
			case STOP:
				control->TimeFlag = TIME_CLEAR;control->stride = 0.f;control->pitch_control = 0.f;control->roll_control = 0.f;control->yaw_control = 0.f;
				break;
			default:
				control->TimeFlag = TIME_CLEAR;
				control->stride = 0.f;
				control->lift_h = 6.f;
				control->speed = 5.f;
				control->body_h = 90.f;
				control->pitch_control = 0.f;
				control->roll_control = 0.f;
				control->yaw_control = 0.f;
				break;
		}
		for(uint8_t i = 0;i < 4;i++){
      switch(i)
      {
          case 0: control->pitch_value[i] = control->pitch_control;
                  control->roll_value[i] = control->roll_control;
            break;
          case 1: control->pitch_value[i] = control->pitch_control;
                  control->roll_value[i] = -control->roll_control;
            break;
          case 2: control->pitch_value[i] = -control->pitch_control;
                  control->roll_value[i] = control->roll_control;
            break;
          case 3: control->pitch_value[i] = -control->pitch_control;
                  control->roll_value[i] = -control->roll_control;
            break;
      }
		}
}
    
