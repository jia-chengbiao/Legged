/**
  ******************************************************************************
  * @file           : bsp_iic.c
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

#include "bsp_IIC.h"

static void i2c_Delay(void)
{
	uint8_t i;
	/*	
	 *	下面时间是通过逻辑分析仪测试得到
	 *	CPU主频72HZ时，在内部Flash运行，MDK工程不优化
	 *	循环次数为10，SCL频率 = 205HZ
	 *	循环次数为7，SCL频率 = 347HZ，SCL高电平时间1.5us，SCL低电平时间2.87us
	 *	循环次数为5，SCL频率 = 421HZ，SCL高电平时间1.25us，SCL低电平时间2.375us
	 *	IAR工程编译效率高，不能设置为7
	 *	（参考安富莱IIC程序）
	 */
	for (i = 0; i < 10; i++);
}
/**
  * @brief  产生IIC的起始信号
  * @param  无
  * @retval 无
  * @attention
  */
void IIC_Start(void)
{
		SDA_OUT();     //sda线输出
		IIC_SDA=1;	  	  
		IIC_SCL=1;
		i2c_Delay();
		IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
		i2c_Delay();
		IIC_SCL=0;//钳住IIC总线，准备发送或接收数据
}	  
/**
  * @brief  产生IIC停止信号
  * @param  无
  * @retval 无
  * @attention
  */
void IIC_Stop(void)
{
		SDA_OUT();//sda线输出
		IIC_SCL=0;
		IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
		i2c_Delay();
		IIC_SCL=1; 
		IIC_SDA=1;//发送IIC总线结束信号
		i2c_Delay();							   	
}
/**
  * @brief  等待应答信号到来
  * @param  无
  * @retval 返回1：接收应答失败
  *			返回0：接收应答成功
  * @attention  
  */
uint8_t IIC_Wait_Ack(void)
{
		uint8_t ucErrTime=0;
		SDA_IN();      //SDA设置为输入
		IIC_SDA=1;i2c_Delay();
		IIC_SCL=1;i2c_Delay();
		while(READ_SDA)
		{
			ucErrTime++;
			if(ucErrTime>250)
			{
				IIC_Stop();
				return 1;
			}
		}
		IIC_SCL=0;//时钟输出0
		return 0;  
} 
/**
  * @brief  产生ACK应答
  * @param  无
  * @retval 
  * @attention  
  */
void IIC_Ack(void)
{
		IIC_SCL=0;
		SDA_OUT();
		IIC_SDA=0;
		i2c_Delay();
		IIC_SCL=1;
		i2c_Delay();
		IIC_SCL=0;
}
/**
  * @brief  不产生ACK应答	
  * @param  无
  * @retval 
  * @attention  
  */    
void IIC_NAck(void)
{
		IIC_SCL=0;
		SDA_OUT();
		IIC_SDA=1;
		i2c_Delay();
		IIC_SCL=1;
		i2c_Delay();
		IIC_SCL=0;
}					
/**
  * @brief  IIC发送一个字节
  * @param  无
  * @retval 返回从机有无应答
	*		返回1：接收应答失败
	*		返回0：接收应答成功	
  * @attention  
  */   	  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
		SDA_OUT(); //传输方向设置为输出
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1;
				i2c_Delay();   //延时是必要的
				IIC_SCL=1;
				i2c_Delay(); 
				IIC_SCL=0;	
				i2c_Delay();
    }	 
} 	    
/**
  * @brief  IIC读取一个字节（8位）
  * @param  无
  * @retval ack=1：发送ACK
	* 		ack=0：发送nACK  
  * @attention   
  */ 
uint8_t IIC_Read_Byte(unsigned char ack)
{
		unsigned char i,receive=0;
		SDA_IN();//SDA设置为输入
		for(i=0;i<8;i++ )
		{
					IIC_SCL=0; 
					i2c_Delay();
					IIC_SCL=1;
					receive<<=1;
					if(READ_SDA)receive++;   
					i2c_Delay(); 
			}					 
			if (!ack)
					IIC_NAck();//发送nACK
			else
					IIC_Ack(); //发送ACK   
			return receive;
}
/*********************************************END OF FILE**********************/


























