/**
  ******************************************************************************
  * File Name          : remote.h
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

#ifndef REMOTE_H
#define REMOTE_H

/* 用户App头文件引用 */

/* 核心头文件引用 */
#include "main.h"

#define FORWARD 1
#define BACK 2
#define TURNRIGHT 3
#define TURNLEFT 4
#define STOP 0


extern uint8_t Remote_control(void);
#endif




