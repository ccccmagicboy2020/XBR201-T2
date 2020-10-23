/**
  ******************************************************************************
  * @文件         led.h
  * @作者         LGG
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         led头文件
  ******************************************************************************
*/ 


/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef __LED__H
#define __LED__H


/* 包含头文件 ----------------------------------------------------------------*/
#include "gd32f1x0.h"


/* 宏定义 --------------------------------------------------------------------*/
/* 定义LED IO PORT与PIN */
#define LED1_CLOCK			RCU_GPIOB
#define	LED1_PORT				GPIOB
#define LED1_PIN				GPIO_PIN_3

#define LED2_CLOCK			RCU_GPIOB
#define	LED2_PORT				GPIOB
#define LED2_PIN				GPIO_PIN_4

/* 定义LED 开或关 */
#define LED1_ON()				gpio_bit_reset(LED1_PORT, LED1_PIN)
#define LED2_ON()				gpio_bit_reset(LED2_PORT, LED2_PIN)
#define LED1_OFF()			gpio_bit_set(LED1_PORT, LED1_PIN)
#define LED2_OFF()			gpio_bit_set(LED2_PORT, LED2_PIN)
#define LED1_Toggle()		(GPIO_OCTL(LED1_PORT) ^= LED1_PIN)
#define LED2_Toggle()		(GPIO_OCTL(LED2_PORT) ^= LED2_PIN)


/* 函数声明-------------------------------------------------------------------*/
void LED_Init(void);

#endif



/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/


