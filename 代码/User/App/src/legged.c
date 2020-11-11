/**
  ******************************************************************************
  * File Name          : legged.c
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

#include "legged.h"

/* 逆解算数据初始化 */
void Inverse_Init(Inverse_typedef* inverse_init);
static void Link_Init(Link_typedef* link_init);
/* 逆解算执行 */
void Inverse_Solution(uint8_t LegNum,Link_typedef* link);
static void Crank_Angle_Control(uint8_t LegNum,Crank_typedef crank);


/**
  * @brief  逆解算相关数据初始化
  * @param  LegNum：腿的编号{0，1，2，3}代表1，2，3，4号腿
  *         腿的编号规则为 Z 型编号
  * @retval 无
  * @attention
  */
void Inverse_Init(Inverse_typedef* inverse_init)
{
    /* 连杆数据初始化 */
    Link_Init(&inverse_init->link);
}

/**
  * @brief  逆解算相关连杆数据初始化
  * @param  
  * @retval 无
  * @attention
  */
static void Link_Init(Link_typedef* link_init)
{
    link_init->point_A.x = -bracket_length/2;
    link_init->point_A.z = 0;

    link_init->point_B.x = link_init->point_A.x + bracket_length;
    link_init->point_B.z = link_init->point_A.z;
}

/**
  * @brief  单腿坐标系设置
  * @param  
  * @retval 无
  * @attention
  */
void Trajectory_Coordinate_Converter(Inverse_typedef* inverse,float body_h,float pitch_value,float rall_value)
{
    inverse->trajectory.point_out.x += (-(inverse->trajectory.cycle.stride) / 2);
    inverse->trajectory.point_out.z += -(body_h + pitch_value + rall_value);

    inverse->link.point_P = inverse->trajectory.point_out;
}

/**
  * @brief  逆解算函数
  * @param  
  * @retval 无
  * @attention
  */
void Inverse_Solution(uint8_t LegNum,Link_typedef* link)
{   
    /* 临时变量 */
    float Temp_AD,Temp_BD;
    float Temp_BP,Temp_AP;
    /*  */
    float angle_L1_a,angle_L1_b;
    float angle_L4_a,angle_L4_b;
    float angle_Temp_a,angle_Temp_b,angle_Temp;
    
    /* 逆解算 */
     switch(LegNum){
        case 0:
        case 3:
          Temp_BP = sqrt(pow(link->point_B.x - link->point_P.x,2.) + pow(link->point_B.z - link->point_P.z,2.));
          angle_Temp_a = acos((pow(L2_Front,2.) + pow(Temp_BP,2.) - pow(L1_length,2.)) / (2 * L2_Front * Temp_BP));
          angle_Temp_b = acos((link->point_B.x - link->point_P.x) / Temp_BP);
          angle_Temp  = angle_Temp_b - angle_Temp_a;
          link->point_D.x = link->point_P.x + L5_length * cos(angle_Temp);
          link->point_D.z = link->point_P.z + L5_length * sin(angle_Temp);
          break;
          
        default:
          Temp_AP = sqrt(pow(link->point_A.x - link->point_P.x,2.) + pow(link->point_A.z - link->point_P.z,2.));
          angle_Temp_a = acos((pow(L3_Front,2.) + pow(Temp_AP,2.) - pow(L4_length,2.)) / (2 * L3_Front * Temp_AP));
          angle_Temp_b = acos((link->point_P.x - link->point_A.x) / Temp_AP);
          angle_Temp  = angle_Temp_b - angle_Temp_a;
          link->point_D.x = link->point_P.x - L5_length * cos(angle_Temp);
          link->point_D.z = link->point_P.z + L5_length * sin(angle_Temp);
					break;
    }

    Temp_AD = sqrt(pow(link->point_A.x - link->point_D.x,2.) + pow(link->point_A.z - link->point_D.z,2.));
    Temp_BD = sqrt(pow(link->point_B.x - link->point_D.x,2.) + pow(link->point_B.z - link->point_D.z,2.));

    angle_L1_a = acos((pow(L1_length,2.) + pow(Temp_BD,2.) - pow(L2_length,2.)) / (2 * L1_length * Temp_BD));
    angle_L1_b = acos((pow(bracket_length,2.) + pow(Temp_BD,2.) - pow(Temp_AD,2.)) / (2 * bracket_length * Temp_BD));

    angle_L4_a = acos((pow(L4_length,2.) + pow(Temp_AD,2.) - pow(L3_length,2.)) / (2 * L4_length * Temp_AD));
    angle_L4_b = acos((pow(bracket_length,2.) + pow(Temp_AD,2.) - pow(Temp_BD,2.)) / (2 * bracket_length * Temp_AD));

    link->crank.crank_L1 = (angle_L1_a + angle_L1_b - pi) * Rad_To_Angle;
    link->crank.crank_L4 = -(angle_L4_a + angle_L4_b) * Rad_To_Angle;

    Crank_Angle_Control(LegNum,link->crank);

 }

/**
  * @brief   驱动杆件角度控制
  * @param   
  * @retval  
	* @attention  设置舵机实际角度为90度时为逆解算角度0度
  */
static void Crank_Angle_Control(uint8_t LegNum,Crank_typedef crank)
{
    float crank_angle1,crank_angle4;


   switch(LegNum)
    {
        case 0:
					crank_angle1 = crank.crank_L1 + COMPENSATE_ANGLE1 - SERVO_ERR1;
					crank_angle4 = crank.crank_L4 + COMPENSATE_ANGLE4 + SERVO_ERR2;
					
					if(crank_angle1 >= 180)crank_angle1 = 180;
					if(crank_angle1 <= 0)crank_angle1 = 0;
					if(crank_angle4 >= 180)crank_angle4 = 180;
					if(crank_angle4 <= 0)crank_angle4 = 0;
				
          PCA_MG90(4,crank_angle1);
          PCA_MG90(5,crank_angle4);
          break;
        case 1:
					crank_angle1 = crank.crank_L1 + COMPENSATE_ANGLE1 - SERVO_ERR3;
					crank_angle4 = crank.crank_L4 + COMPENSATE_ANGLE4 + SERVO_ERR4;
					
					if(crank_angle1 >= 180)crank_angle1 = 180;
					if(crank_angle1 <= 0)crank_angle1 = 0;
					if(crank_angle4 >= 180)crank_angle4 = 180;
					if(crank_angle4 <= 0)crank_angle4 = 0;
				
          PCA_MG90(6,crank_angle1);
          PCA_MG90(7,crank_angle4);
          break;
        case 2:
					crank_angle1 = crank.crank_L1 + COMPENSATE_ANGLE1 - SERVO_ERR5;
					crank_angle4 = crank.crank_L4 + COMPENSATE_ANGLE4 + SERVO_ERR6;
					
					if(crank_angle1 >= 180)crank_angle1 = 180;
					if(crank_angle1 <= 0)crank_angle1 = 0;
					if(crank_angle4 >= 180)crank_angle4 = 180;
					if(crank_angle4 <= 0)crank_angle4 = 0;
				
          PCA_MG90(8,crank_angle1);
          PCA_MG90(9,crank_angle4);
          break;
        case 3:
					crank_angle1 = crank.crank_L1 + COMPENSATE_ANGLE1 - SERVO_ERR7;
					crank_angle4 = crank.crank_L4 + COMPENSATE_ANGLE4 + SERVO_ERR8;
					
					if(crank_angle1 >= 180)crank_angle1 = 180;
					if(crank_angle1 <= 0)crank_angle1 = 0;
					if(crank_angle4 >= 180)crank_angle4 = 180;
					if(crank_angle4 <= 0)crank_angle4 = 0;
				
          PCA_MG90(10,crank_angle1);
          PCA_MG90(11,crank_angle4 );
          break;
    }
          
}

	








