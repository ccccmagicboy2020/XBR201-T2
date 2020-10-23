/**
  ******************************************************************************
  * @文件         adc.c
  * @作者         LGG
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         adc源文件
  ******************************************************************************
*/ 


/* 包含头文件 ----------------------------------------------------------------*/
#include "adc.h"


/**
  * @函数名       ADC_Config
  * @功  能       ADC配置
  * @参  数       无
  * @返回值       无
  */
void ADC_Config(void)
{
	/* 使能ADC通道所在GPIO外设时钟 */
	rcu_periph_clock_enable(RCU_GPIOB);
	
	/* 使能 ADC 时钟 */
	rcu_periph_clock_enable(RCU_ADC);
	
	/* 配置 ADC 时钟 */
	rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);
	
	/* 配置ADC通道所在GPIO为模拟模式 */
	gpio_mode_set(ADC_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, ADC_GPIO_PIN);
	
	
	/* ADC 连续模式使能 */
	adc_special_function_config(ADC_CONTINUOUS_MODE, ENABLE);
	
	/* ADC 触发器配置：软件触发 */
	adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_SWRCST);

	/* ADC 数据对齐配置：右对齐 */
	adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
	
	/* ADC 通道长度配置：1 */
	adc_channel_length_config(ADC_REGULAR_CHANNEL, 1);
	
	/* ADC 规则通道配置：规则组0、ADC通道8、采样时间239.5ADC时钟周期、使能规则通道 */
	adc_regular_channel_config(0, ADC_CHANNEL_8, ADC_SAMPLETIME_239POINT5);
	adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);
	
	adc_enable();	//使能ADC
	
	adc_calibration_enable();	//使能ADC校准
	
	/* 配置看门狗中断向量以及优先级 */
	nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);
	nvic_irq_enable(ADC_CMP_IRQn, 0, 0);
	
	/* ADC 模拟看门狗阈值配置 */
	adc_watchdog_threshold_config(0x0400,0x0A00);
	
	/* ADC 模拟看门狗单通道配置 */
	adc_watchdog_single_channel_enable(ADC_CHANNEL);
	
	/* ADC 中断配置：使能模拟看门狗中断 */
	adc_interrupt_enable(ADC_INT_WDE);
	
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



