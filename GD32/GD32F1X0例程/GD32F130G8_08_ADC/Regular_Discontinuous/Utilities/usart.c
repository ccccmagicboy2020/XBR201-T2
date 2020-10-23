/**
  ******************************************************************************
  * @�ļ�         usart.c
  * @����         LGG
  * @�汾         V1.0.0
  * @����         2018-3-16
  * @ժҪ         usartԴ�ļ�
  ******************************************************************************
*/ 


/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "usart.h"


/**
  * @������       USART0_Init
  * @��  ��       ��ʼ��USART0
  * @��  ��       ��
  * @����ֵ       ��
  */
void USART0_Init(void)
{
	/* ʹ��GPIOA����ʱ�� */
	rcu_periph_clock_enable( RCU_GPIOA);
	
	/* ʹ��USART0����ʱ�� */
	rcu_periph_clock_enable(USART0_CLOCK);
	
	/* ����USART��ص�RX��TX������Ϊ���ù��� */
	gpio_af_set(USART0_PORT, GPIO_AF_1, USART0_TX_PIN);
	gpio_af_set(USART0_PORT, GPIO_AF_1, USART0_RX_PIN);
	
	gpio_mode_set(USART0_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART0_TX_PIN);
	gpio_output_options_set(USART0_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, USART0_TX_PIN);
	
	gpio_mode_set(USART0_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART0_RX_PIN);
	gpio_output_options_set(USART0_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, USART0_RX_PIN);
	
	/* ����USART */
	usart_deinit(USART0);	//�˿ں�
	usart_baudrate_set(USART0,115200U);	//������115200
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);	//ʹ�ܷ���
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);	//ʹ�ܽ���
	usart_enable(USART0);	//ʹ��USART0
	
}


/**
  * @������       USART1_Init
  * @��  ��       ��ʼ��USART1
  * @��  ��       ��
  * @����ֵ       ��
  */
void USART1_Init(void)
{
	/* ʹ��GPIOA����ʱ�� */
	rcu_periph_clock_enable( RCU_GPIOA);
	
	/* ʹ��USART1����ʱ�� */
	rcu_periph_clock_enable(USART1_CLOCK);
	
	/* ����USART��ص�RX��TX������Ϊ���ù��� */
	gpio_af_set(USART1_PORT, GPIO_AF_1, USART1_TX_PIN);
	gpio_af_set(USART1_PORT, GPIO_AF_1, USART1_RX_PIN);
	
	gpio_mode_set(USART1_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART1_TX_PIN);
	gpio_output_options_set(USART1_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, USART1_TX_PIN);
	
	gpio_mode_set(USART1_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART1_RX_PIN);
	gpio_output_options_set(USART1_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, USART1_RX_PIN);
	
	/* ����USART */
	usart_deinit(USART1);	//�˿ں�
	usart_baudrate_set(USART1,115200U);	//������115200
	usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);	//ʹ�ܷ���
	usart_receive_config(USART1, USART_RECEIVE_ENABLE);	//ʹ�ܽ���
	usart_enable(USART1);	//ʹ��USART1
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



