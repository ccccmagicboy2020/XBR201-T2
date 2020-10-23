/**
  ******************************************************************************
  * @�ļ�         led.h
  * @����         LGG
  * @�汾         V1.0.0
  * @����         2018-3-16
  * @ժҪ         ledͷ�ļ�
  ******************************************************************************
*/ 


/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef __LED__H
#define __LED__H


/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "gd32f1x0.h"


/* �궨�� --------------------------------------------------------------------*/
/* ����LED IO PORT��PIN */
#define LED1_CLOCK			RCU_GPIOB
#define	LED1_PORT				GPIOB
#define LED1_PIN				GPIO_PIN_3

#define LED2_CLOCK			RCU_GPIOB
#define	LED2_PORT				GPIOB
#define LED2_PIN				GPIO_PIN_4

/* ����LED ����� */
#define LED1_ON()				gpio_bit_reset(LED1_PORT, LED1_PIN)
#define LED2_ON()				gpio_bit_reset(LED2_PORT, LED2_PIN)
#define LED1_OFF()			gpio_bit_set(LED1_PORT, LED1_PIN)
#define LED2_OFF()			gpio_bit_set(LED2_PORT, LED2_PIN)
#define LED1_Toggle()		(GPIO_OCTL(LED1_PORT) ^= LED1_PIN)
#define LED2_Toggle()		(GPIO_OCTL(LED2_PORT) ^= LED2_PIN)


/* ��������-------------------------------------------------------------------*/
void LED_Init(void);

#endif



/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/


