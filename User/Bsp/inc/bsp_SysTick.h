#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f1xx.h"

typedef uint32_t  u32;

void SysTick_Init(void);
void delay_us(__IO u32 nTime);
void delay_ms(u32 Time);
#define delay_ms(x) delay_us(1000*x)	 //��λms

#endif /* __SYSTICK_H */
