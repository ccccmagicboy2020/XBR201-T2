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
  * 程序效果       LED1闪烁，把PB0(ADC_IN8)口接一个电位器，在采集的电压在阈值(0x0400,0x0A00)之内，
	*								 LED2是灭的,当采集的电压大于或小于阈值，LED2亮
  ******************************************************************************
  */


/* 包含头文件 ----------------------------------------------------------------*/
#include "gd32f1x0.h"
#include "gd32f1x0_libopt.h"
#include "systick.h"
#include "led.h"
#include "adc.h"


/* 变量定义-------------------------------------------------------------------*/
uint8_t Analog_Watchdog_Flag = 0;


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
	ADC_Config();	//ADC初始化
	
	/* 软件触发ADC */
	adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
	
	while(1)
	{
		if(Analog_Watchdog_Flag != 0)	//判断标志位
		{
			Analog_Watchdog_Flag = 0;	//标志位清零
			LED2_ON();	//点亮LED2
		}
		else
			LED2_OFF();	//关闭LED2

		LED1_Toggle();
		delay_1ms(500);
	}
}



/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



