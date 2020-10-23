/**
  ******************************************************************************
  * @文件         usart.h
  * @作者         LGG
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         usart头文件
  ******************************************************************************
*/ 


/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef __USART__H
#define __USART__H


/* 包含头文件 ----------------------------------------------------------------*/
#include "gd32f1x0.h"


/* 宏定义 --------------------------------------------------------------------*/


/* 定义USARTx IO PORT与PIN */
#define USART0_CLOCK				RCU_USART0
#define	USART0_PORT					GPIOA
#define USART0_TX_PIN				GPIO_PIN_9
#define USART0_RX_PIN				GPIO_PIN_10

#define USART1_CLOCK				RCU_USART1
#define	USART1_PORT					GPIOA
#define USART1_TX_PIN				GPIO_PIN_2
#define USART1_RX_PIN				GPIO_PIN_3


/* 函数声明-------------------------------------------------------------------*/
void USART0_Init(void);
void USART1_Init(void);

#endif



/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/


