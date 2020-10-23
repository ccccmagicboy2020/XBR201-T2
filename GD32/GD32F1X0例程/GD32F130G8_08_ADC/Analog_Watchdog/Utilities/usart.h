/**
  ******************************************************************************
  * @�ļ�         usart.h
  * @����         LGG
  * @�汾         V1.0.0
  * @����         2018-3-16
  * @ժҪ         usartͷ�ļ�
  ******************************************************************************
*/ 


/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef __USART__H
#define __USART__H


/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "gd32f1x0.h"


/* �궨�� --------------------------------------------------------------------*/


/* ����USARTx IO PORT��PIN */
#define USART0_CLOCK				RCU_USART0
#define	USART0_PORT					GPIOA
#define USART0_TX_PIN				GPIO_PIN_9
#define USART0_RX_PIN				GPIO_PIN_10

#define USART1_CLOCK				RCU_USART1
#define	USART1_PORT					GPIOA
#define USART1_TX_PIN				GPIO_PIN_2
#define USART1_RX_PIN				GPIO_PIN_3


/* ��������-------------------------------------------------------------------*/
void USART0_Init(void);
void USART1_Init(void);

#endif



/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/


