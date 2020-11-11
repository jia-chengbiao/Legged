/**
  ******************************************************************************
  * File Name          : trajectory.c
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
#include "trajectory.h"

/**
  * @brief  足端轨迹生成
  * @param  
  * @retval 无
  * @attention
  */
void Trajectory_Planning(Trajectory_typedef* trajectory)
{
    /* 临时参数 */
		float t,Tm,Stride,lift_h;
    Point_typedef point_s;
    Point_typedef point_f;

    t = trajectory->cycle.t;
    Tm = trajectory->cycle.Tm;
    Stride = trajectory->cycle.stride;
    lift_h = trajectory->cycle.lift_h;

    point_s.x = 0;
    point_f.x = point_s.x + Stride;
    point_s.z = 0;
    point_f.z = 0;


    if(t < Tm){
        trajectory->point_out.x = Stride * (t / Tm - sin(2 * pi * t / Tm)        \
                    / (2 * pi)) + point_s.x;
        trajectory->point_out.z = lift_h * (0.5f - cos(2 * pi * t/Tm) / 2)         \
                    + point_s.z;
    }
    else{
        trajectory->point_out.x = -Stride * ((t - Tm) / Tm) + point_f.x;
        trajectory->point_out.z = point_s.z;
    }
}



