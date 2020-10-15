/**
  ******************************************************************************
  * @文件         led.c
  * @作者         LGG
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         led源文件
  ******************************************************************************
*/ 


/* 包含头文件 ----------------------------------------------------------------*/
#include "led.h"


/**
  * @函数名       LED_Init
  * @功  能       配置LED 的IO口
  * @参  数       无
  * @返回值       无
  */
void LED_Init(void)
{
	/* 使能LED1与LED2所在GPIO外设时钟 */
	rcu_periph_clock_enable(LED1_CLOCK);
	rcu_periph_clock_enable(LED2_CLOCK);
	
	/* 设置LED1与LED2的引脚模式为输出模式，无上下拉 */
	gpio_mode_set(LED1_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED1_PIN);
	gpio_mode_set(LED2_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED2_PIN);
	
	/* 设置LED1与LED2的输出类型：推挽输出；速度：最大50MHz */
	gpio_output_options_set(LED1_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LED1_PIN);
	gpio_output_options_set(LED2_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LED2_PIN);
	
	/* 设置LED1与LED2的输出输出低（关闭LED1&LED2） */
	gpio_bit_set(LED1_PORT, LED1_PIN);
	gpio_bit_set(LED2_PORT, LED2_PIN);
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



