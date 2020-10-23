/**
  ******************************************************************************
  * @文件         main.c
  * @作者         LGG
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         USART例程
  ******************************************************************************
  * @attention
  * 技新网         www.jixin.pro
  * 硬件平台       技新GD32F130G8U6核心板
  * 程序效果       上电串口打印：USART interrupt test；LED1亮；（在中断中把发送中断禁能）
	*								 当串口接收到大于等于32Byte的数据时，串口打印USART receive successfully!；LED2亮（在中断中把接收中断禁能）
	*									- BaudRate = 115200 baud（波特率115200）
	*									- Word Length = 8 Bits（数据长度8位）
	*									- One Stop Bit（停止位1位）
	*									- No parity（无奇偶校验）
	*									- Hardware flow control disabled (RTS and CTS signals)（禁能硬件流控）
	*									- Receive and transmit enabled（发送与接收使能）
  ******************************************************************************
  */


/* 包含头文件 ----------------------------------------------------------------*/
#include "gd32f1x0.h"
#include "gd32f1x0_libopt.h"
#include "systick.h"
#include "led.h"
#include "usart.h"
#include <stdio.h>


#define ARRAYNUM(arr_nanme)      (uint32_t)(sizeof(arr_nanme) / sizeof(*(arr_nanme)))
#define TRANSMIT_SIZE   				 (ARRAYNUM(transmitter_buffer) - 1)	//计算发送数据的大小

uint8_t transmitter_buffer[] = "USART interrupt test\n\r";	//要发送的数据
uint8_t receiver_buffer[32];	//定义接收数据的缓存
uint8_t transfersize = TRANSMIT_SIZE;	//定义发送数据的大小
uint8_t receivesize = 32;	//定义接收数据大小
__IO uint8_t txcount = 0; 	//定义发送数量变量
__IO uint16_t rxcount = 0; 	//定义接收数量变量


/**
  * @函数名       main
  * @功  能       主函数入口
  * @参  数       无
  * @返回值       无
  */
int main(void)
{
	LED_Init();	//LED初始化
	USART0_Init();	//串口0初始化
	
	/* USART0的中断配置 */
	nvic_irq_enable(USART0_IRQn, 0, 0);
	
	/* 使能 USART0 TBE（串口发送） 中断 */  
	usart_interrupt_enable(USART0, USART_INT_TBE);
	
	/* 等待串口中断发送 transmitter_buffer 数据 */
	while(txcount < transfersize);
	
	/* 等待串口发送完成 */
	while (RESET == usart_flag_get(USART0, USART_FLAG_TC));
	LED1_ON();	//LED1亮
	
	/* 使能RBNE（串口接收）中断 */
	usart_interrupt_enable(USART0, USART_INT_RBNE);
	
	/* 等待接收数据，接收数据大于等于32Byte时打印接收完成信息 */
	while(rxcount < receivesize);
	if(rxcount == receivesize)
        printf("USART receive successfully!\n\r");
	LED2_ON();	//LED2亮
	
	while(1)
	{
		;
	}
}


/* 重定向C库中的printf函数 */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t)ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    return ch;
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



