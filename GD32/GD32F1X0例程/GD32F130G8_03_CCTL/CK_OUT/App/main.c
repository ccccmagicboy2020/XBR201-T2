/**
  ******************************************************************************
  * @文件         main.c
  * @作者         LGG
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         CLK例程
  ******************************************************************************
  * @attention
  * 技新网         www.jixin.pro
  * 硬件平台       技新GD32F130G8U6核心板
  * 程序效果       LED1闪烁，PA8（CK_OUT）输出内部40KHz时钟频率（实测36KHz左右）
  ******************************************************************************
  */


/* 包含头文件 ----------------------------------------------------------------*/
#include "gd32f1x0.h"
#include "gd32f1x0_libopt.h"
#include "systick.h"
#include "led.h"
#include "ck_out.h"


/**
  * @函数名       main
  * @功  能       主函数入口
  * @参  数       无
  * @返回值       无
  */
int main(void)
{
	rcu_osci_on(RCU_IRC40K);	//打开内部40KHz时钟
	while(rcu_osci_stab_wait(RCU_IRC40K) == ERROR);	//等待时钟稳定
	CK_OUT_Config(RCU_CKOUTSRC_IRC40K, RCU_CKOUT_DIV1);	//输出内部40KHz、1分频时钟
	
	systick_config();	//初始化滴答定时器
	LED_Init();	//LED初始化
	
	
	while(1)
	{
		LED1_Toggle();	//改变LED1状态
		delay_1ms(500);
	}
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



