	/**
  ******************************************************************************
  * @file           : PCA9685.c
  * @brief          : PCA9685模块的设置与舵机驱动
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
#include "bsp_pca9685.h"

///**
//  * @brief   舵机中位设置
//  * @param   
//  * @retval  
//	* @attention  
//  */
//void Median_Setting(void)
//{
//  static float i = 110;
//  static float p = 70;
//  float err1,err2;
//	PCA_MG90(4,88);
//  PCA_MG90(5,91);
//	PCA_MG90(6,91);
//  PCA_MG90(7,98);
//	PCA_MG90(8,95);
//  PCA_MG90(9,81);
//  PCA_MG90(10,96);
//  PCA_MG90(11,98);
//  //i--;
//	p++;
//}
/**
  * @brief   PCA9685初始化
  * @param   PWM频率：freq:一般取50ms
  * @retval  无
	* @attention  
  */
void PCA9685_Init(uint8_t freq)
{
		PCA9685_write(PCA9685_MODE1,0x00);
		setPWMFreq(freq);
}
/**
  * @brief   PCA9685控制函数
  * @param   舵机编号（0-15）
	*					 角度（0-180）
  * @retval  无
	* @attention  
  */
void PCA_MG90(uint8_t num,uint8_t angle)
{
		uint16_t pwm;
	
		pwm = calculate_PWM(angle);
		setPWM(num,0,pwm);
}

/**
  * @brief   PCA9685写入
  * @param   
  * @retval  无
	* @attention  用IIC向指定寄存器写入数据
  */
void PCA9685_write(unsigned char reg,unsigned char data)
{
    IIC_Start();//开启IIC传输
		IIC_Send_Byte(PCA9685_adrr);//发送数据（参数为从机地址）
    IIC_Wait_Ack();
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();
    IIC_Send_Byte(data);
    IIC_Wait_Ack();
    IIC_Stop();
}
/**
  * @brief   PCA9685读
  * @param   
  * @retval  
	* @attention  从指定寄存器地址读取数据
  */
uint8_t PCA9685_read(unsigned char reg)
{
    uint8_t res;
    IIC_Start();
    IIC_Send_Byte(PCA9685_adrr);
    IIC_Wait_Ack();
    IIC_Send_Byte(reg);
    IIC_Wait_Ack();    
    IIC_Start();                
    IIC_Send_Byte(PCA9685_adrr|0X01);
    IIC_Wait_Ack();
    res=IIC_Read_Byte(0);       
    IIC_Stop();             
    return res;  
}
/**
  * @brief  设置PWM频率
  * @param   freq
  * @retval  无
	* @attention  
  */
void setPWMFreq(uint8_t freq)
{
   uint8_t prescale,oldmode,newmode;
   double prescaleval;
	
   prescaleval = 25000000.0/(4096*freq*0.915);
   prescale = (uint8_t)floor(prescaleval+0.5)-1;

   oldmode = PCA9685_read(PCA9685_MODE1);
   newmode = (oldmode&0x7F) | 0x10; // sleep
   PCA9685_write(PCA9685_MODE1, newmode); // go to sleep
   PCA9685_write(PCA9685_PRESCALE, prescale); // set the prescaler
   PCA9685_write(PCA9685_MODE1, oldmode);
   HAL_Delay(5);
   PCA9685_write(PCA9685_MODE1, oldmode | 0xa1); 
}
/**
  * @brief  	角度与PWM转换函数
  * @param  	angle：角度 范围（0-180）
  * @retval   输出转换后的PWMֵ值
	* @attention  
  */
uint16_t calculate_PWM(uint8_t angle)
{
	return (int)(204.8*(0.5+angle/90.));
}

/**
  * @brief  	舵机PWM控制
  * @param  	1.num：舵机板编号
	*						2.on：PWM上升计数值0-4096
	*	  				3.off：PWM下降计数值
  * @retval   	
	* @attention  一个PWM周期分成4096份，从0开始+1计数，记到on时跳变为高电平
  *             计数到off时跳变为低电平，直到计满4096重新开始。
  *             所以当on不为0时可作为延时，on为0时作为PWM输出
  */
void setPWM(uint8_t num, uint16_t on, uint16_t off) 
{
    PCA9685_write(LED0_ON_L+4*num,on);
    PCA9685_write(LED0_ON_H+4*num,on>>8);
    PCA9685_write(LED0_OFF_L+4*num,off);
    PCA9685_write(LED0_OFF_H+4*num,off>>8);
}





