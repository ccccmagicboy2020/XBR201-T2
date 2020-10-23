/**
  ******************************************************************************
  * @文件         usart.c
  * @作者         LGG
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         usart源文件
  ******************************************************************************
*/ 


/* 包含头文件 ----------------------------------------------------------------*/
#include "usart.h"


/**
  * @函数名       USART0_Init
  * @功  能       初始化USART0
  * @参  数       无
  * @返回值       无
  */
void USART0_Init(void)
{
	/* 使能GPIOA外设时钟 */
	rcu_periph_clock_enable( RCU_GPIOA);
	
	/* 使能USART0外设时钟 */
	rcu_periph_clock_enable(USART0_CLOCK);
	
	/* 配置USART相关的RX、TX引脚作为复用功能 */
	gpio_af_set(USART0_PORT, GPIO_AF_1, USART0_TX_PIN);
	gpio_af_set(USART0_PORT, GPIO_AF_1, USART0_RX_PIN);
	
	gpio_mode_set(USART0_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART0_TX_PIN);
	gpio_output_options_set(USART0_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, USART0_TX_PIN);
	
	gpio_mode_set(USART0_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART0_RX_PIN);
	gpio_output_options_set(USART0_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, USART0_RX_PIN);
	
	/* 配置USART */
	usart_deinit(USART0);	//端口号
	usart_baudrate_set(USART0,115200U);	//波特率115200
	usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);	//使能发送
	usart_receive_config(USART0, USART_RECEIVE_ENABLE);	//使能接收
	usart_enable(USART0);	//使能USART0
	
}


/**
  * @函数名       USART1_Init
  * @功  能       初始化USART1
  * @参  数       无
  * @返回值       无
  */
void USART1_Init(void)
{
	/* 使能GPIOA外设时钟 */
	rcu_periph_clock_enable( RCU_GPIOA);
	
	/* 使能USART1外设时钟 */
	rcu_periph_clock_enable(USART1_CLOCK);
	
	/* 配置USART相关的RX、TX引脚作为复用功能 */
	gpio_af_set(USART1_PORT, GPIO_AF_1, USART1_TX_PIN);
	gpio_af_set(USART1_PORT, GPIO_AF_1, USART1_RX_PIN);
	
	gpio_mode_set(USART1_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART1_TX_PIN);
	gpio_output_options_set(USART1_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, USART1_TX_PIN);
	
	gpio_mode_set(USART1_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, USART1_RX_PIN);
	gpio_output_options_set(USART1_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_10MHZ, USART1_RX_PIN);
	
	/* 配置USART */
	usart_deinit(USART1);	//端口号
	usart_baudrate_set(USART1,115200U);	//波特率115200
	usart_transmit_config(USART1, USART_TRANSMIT_ENABLE);	//使能发送
	usart_receive_config(USART1, USART_RECEIVE_ENABLE);	//使能接收
	usart_enable(USART1);	//使能USART1
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



