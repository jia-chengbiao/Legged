/**
  ******************************************************************************
  * @file           : bsp_pca9685.h
  * @brief          : Header for bsp_pca9685.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __PCA9685_H
#define __PCA9685_H
#include "math.h"
#include "bsp_IIC.h"

#define PCA9685_adrr 0x80
#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE


#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

void PCA9685_Init(uint8_t freq);
void setPWMFreq(uint8_t freq);

void PCA_MG90(uint8_t num,uint8_t angle);
void setPWM(uint8_t num, uint16_t on, uint16_t off);
uint16_t calculate_PWM(uint8_t angle);

void PCA9685_write(unsigned char reg,unsigned char data);
uint8_t PCA9685_read(unsigned char reg);

void Median_Setting(void);

#endif
