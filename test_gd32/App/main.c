/**
  ******************************************************************************
  * @文件         main.c
  * @作者         LGG
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         LED例程
  ******************************************************************************
  * @attention
  * 技新网         www.jixin.pro
  * 硬件平台       技新GD32F130G8U6核心板
  * 程序效果       LED1闪烁
  ******************************************************************************
  */


/* 包含头文件 ----------------------------------------------------------------*/
#include "gd32f1x0.h"
#include "gd32f1x0_libopt.h"
#include "systick.h"

#include "led.h"
#include "usart.h"
#include <stdio.h>  //printf等


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
  USART0_Init();	//串口0初始化
	
	while(1)
	{
    printf("Hello World!\r\n");	//串口打印：Hello World!
		LED1_Toggle();	//对LED1的状态进行取反
		delay_1ms(500);
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



