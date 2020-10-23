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
  * 程序效果       LED1闪烁，PA0(ADC_IN0),PA1(ADC_IN1),PA2(ADC_IN2),PA3(ADC_IN3)四路ADC采用
	*								 采样数据通过DMA传送，并在串口打印出来
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
uint16_t adc_value[4];
float vol_value[4];


/**
  * @函数名       main
  * @功  能       主函数入口
  * @参  数       无
  * @返回值       无
  */
int main(void)
{
	uint8_t i;
	
	systick_config();	//初始化滴答定时器
	
	LED_Init();	//LED初始化
	USART0_Init();	//USART0初始化
	ADC_Config();	//ADC初始化
	ADC_DMA_Config();	//ADC的DMA配置初始化
	
	while(1)
	{
		/* 软件触发使能 */
		adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
		
		/* 等待DMA发送完成 */
		while (RESET == dma_flag_get(DMA_CH0, DMA_FLAG_FTF));

		for(i = 0; i<4; i++)
		{
			vol_value[i] = (float)adc_value[i]/4096 * 3.3;	//转换为电压值
		
			printf("the adc_value1[%d] is %d\r\n", i,adc_value[i]);	//打印ADC值
			printf("the vol_valuel[%d] is %f\r\n", i,vol_value[i]);	//打印电压值
		}
		
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



