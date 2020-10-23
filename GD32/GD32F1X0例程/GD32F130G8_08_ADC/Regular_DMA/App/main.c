/**
  ******************************************************************************
  * @文件         main.c
  * @作者         LGG
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         ADC例程
  ******************************************************************************
  * @attention
  * 技新网         www.jixin.pro
  * 硬件平台       技新GD32F130G8U6核心板
  * 程序效果       LED1闪烁，把PB0口接一个电位器，通过USB转TTL模块连接到核心板的USART0（PA9、PA10），
	*								 调节电位器可以看到串口输出的ADC值和电压值产生变化
  ******************************************************************************
  */


/* 包含头文件 ----------------------------------------------------------------*/
#include "gd32f1x0.h"
#include "gd32f1x0_libopt.h"
#include <stdio.h>
#include "systick.h"
#include "led.h"
#include "usart.h"
#include "adc.h"


/* 变量定义-------------------------------------------------------------------*/
uint16_t adc_value;	//定义内存地址，用于保存ADC值
float vol_value;	//定义保存转换电压值


/**
  * @函数名       main
  * @功  能       主函数入口
  * @参  数       无
  * @返回值       无
  */
int main(void)
{
	systick_config();	//初始化滴答定时器
	
	LED_Init();	//LED初始化
	USART0_Init();	//USART0初始化
	ADC_Config();	//ADC初始化
	ADC_DMA_Config();	//ADC的DMA配置初始化
	
	/* 软件触发使能 */
	adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
	while(1)
	{
		/* 等待DMA发送完成 */
		while (RESET == dma_flag_get(DMA_CH0, DMA_FLAG_FTF));

		vol_value = (float)adc_value/4096 * 3.3;	//转换为电压值
		
		printf("the adc_value1 is %d\r\n", adc_value);	//打印ADC值
		printf("the vol_valuel is %f\r\n", vol_value);	//打印电压值
		
		LED1_Toggle();
		delay_1ms(500);
	}
}


/* 重定向printf函数 */
int fputc(int ch, FILE *f)
{
	usart_data_transmit(USART0, (uint8_t)ch);
	while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));

	return ch;
}



/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



