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
  * 程序效果       上电串口打印：USART DMA TEST!
	*								 USART DMA receive and transmit example, please input 10 bytes:
	*								 在串口调试助手上往串口发送10Byte，串口会发送回来10Byte
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


uint8_t rxbuffer[10];	//接收数据缓存
/* 发送数据缓存 */
uint8_t txbuffer[]="\n\rUSART DMA receive and transmit example, please input 10 bytes:\n\r";

#define ARRAYNUM(arr_nanme)      (uint32_t)(sizeof(arr_nanme) / sizeof(*(arr_nanme)))
#define USART0_TDATA_ADDRESS      ((uint32_t)0x40013828)	//USART0的发送数据寄存器地址
#define USART0_RDATA_ADDRESS      ((uint32_t)0x40013824)	//USART0的接收数据寄存器地址



/**
  * @函数名       main
  * @功  能       主函数入口
  * @参  数       无
  * @返回值       无
  */
int main(void)
{
	/* 定义DMA初始化结构体 */
	dma_parameter_struct dma_init_struct;

	/* 使能DMA外设时钟 */
	rcu_periph_clock_enable(RCU_DMA);
	
	LED_Init();	//LED初始化
	USART0_Init();	//串口0初始化
	
	/* 打印信息 */
	printf("USART DMA TEST!\n\r");
	LED1_ON();	//LED1亮
	
	/* 初始化DMA_CH1 */
	dma_deinit(DMA_CH1);	//重置DMA_CH1相关寄存器
	dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;	//内存到外设模式
	dma_init_struct.memory_addr = (uint32_t)txbuffer;	//内存基地址
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;	//内存地址递增
	dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;	//数据宽度8位
	dma_init_struct.number = ARRAYNUM(txbuffer);	//数据量
	dma_init_struct.periph_addr = USART0_TDATA_ADDRESS;	//外设基地址
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;	//外设地址不递增
	dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;	//数据宽度8位
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;	//优先级超高
	dma_init(DMA_CH1, dma_init_struct);	//初始化配置
	
	/* 禁能循环模式 */
	dma_circulation_disable(DMA_CH1);
	
	/* 禁能内存到内存模式 */
	dma_memory_to_memory_disable(DMA_CH1);
	
	/* 使能DMA_CH1 */
	dma_channel_enable(DMA_CH1);
	
	/* 使能USART0的DMA发送 */
	usart_dma_transmit_config(USART0, USART_DENT_ENABLE);
    
	/* 等待DMA传输完成 */
	while (RESET == dma_flag_get(DMA_CH1, DMA_FLAG_FTF));
	
	while(1){
		/* 初始化DMA_CH2 */
		dma_deinit(DMA_CH2);	//重置DMA_CH2相关寄存器
		dma_init_struct.direction = DMA_PERIPHERAL_TO_MEMORY;	//外设到内存模式
		dma_init_struct.memory_addr = (uint32_t)rxbuffer;	//内存基地址
		dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;	//内存地址递增
		dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;	//数据宽度8位
		dma_init_struct.number = 10;	//数据量10
		dma_init_struct.periph_addr = USART0_RDATA_ADDRESS;	//外设基地址
		dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;	//外设地址不递增
		dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;	//数据宽度8位
		dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;	//优先级超高
		dma_init(DMA_CH2, dma_init_struct);		//初始化配置
        
		/* 禁能循环模式 */
		dma_circulation_disable(DMA_CH2);
		
		/* 禁能内存到内存模式 */
		dma_memory_to_memory_disable(DMA_CH2);

		/* 使能DMA_CH2 */
		dma_channel_enable(DMA_CH2);
		
		/* 使能USART的DMA接收 */
		usart_dma_receive_config(USART0, USART_DENR_ENABLE);
		
		/* 等待DMA传输完成 */
		while (RESET == dma_flag_get(DMA_CH2, DMA_FLAG_FTF));
		
		/* 打印DMA接收的信息 */
		printf("\n\r%s\n\r",rxbuffer);
		LED2_Toggle();	//LED2状态改变
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



