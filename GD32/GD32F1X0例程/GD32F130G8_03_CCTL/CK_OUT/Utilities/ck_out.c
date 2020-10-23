/**
  ******************************************************************************
  * @文件         ck_out.c
  * @作者         LGG
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         ck_out源文件
  ******************************************************************************
*/ 


/* 包含头文件 ----------------------------------------------------------------*/
#include "ck_out.h"


/**
  * @函数名       CK_OUT_Config
  * @功  能       配置CK_OUT
  * @参  数       无
  * @返回值       无
  */
void CK_OUT_Config(uint32_t ckout_src, uint32_t ckout_div)
{
	/* 使能CK_OUT引脚所在的GPIO外设时钟 */
	rcu_periph_clock_enable(CK_OUT_CLOCK);
	
	/* 配置PA8(CK_OUT) 用作复模式 */
	gpio_mode_set(CK_OUT_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, CK_OUT_PIN);
	
	/* 配置PA8(CK_OUT) 为推挽输出 */
	gpio_output_options_set(CK_OUT_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,CK_OUT_PIN);
	
	/* 配置PA8(CK_OUT) 用作复用功能 */
	gpio_af_set(CK_OUT_PORT, GPIO_AF_0, CK_OUT_PIN);
	
	/* 配置PA8(CK_OUT) 输出时钟源与分配系数 */
	rcu_ckout_config(ckout_src, ckout_div);
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



