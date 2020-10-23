/**
  ******************************************************************************
  * @文件         key.c
  * @作者         LGG
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         key源文件
  ******************************************************************************
*/ 


/* 包含头文件 ----------------------------------------------------------------*/
#include "key.h"
#include "systick.h"


/**
  * @函数名       KEY_Init
  * @功  能       配置KEY 的IO口
  * @参  数       无
  * @返回值       无
  */
void KEY_Init(void)
{
	/* 使能KEY所在GPIO外设时钟 */
	rcu_periph_clock_enable(KEY_CLOCK);
	
	/* 设置KEY的引脚模式为输入模式，带上拉电阻 */
	gpio_mode_set(KEY_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, KEY_PIN);
}


/**
  * @函数名       KEY_Scan
  * @功  能       按键扫描函数
  * @参  数       无
  * @返回值       KEY按下返回：KEY_PRES；否则返回：0
  */
uint8_t KEY_Scan(void)
{
	if(KEY_READ == 0)
	{
		delay_1ms(10);	//消抖
		if(KEY_READ == 0)
		{
			while(KEY_READ == 0);	//松手检测
			return KEY_PRES;
		}
	}
	
	return 0;
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



