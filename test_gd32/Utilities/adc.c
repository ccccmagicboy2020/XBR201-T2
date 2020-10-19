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
	rcu_periph_clock_enable(RCU_GPIOA);
	
	/* 使能 ADC 时钟 */
	rcu_periph_clock_enable(RCU_ADC);
	
	/* 配置 ADC 时钟 */
	rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);
	
	/* 配置ADC通道所在GPIO为模拟模式 */
	gpio_mode_set(LIGHT_ADC_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, LIGHT_ADC_GPIO_PIN);
	
	/* ADC 连续模式使能 */
	adc_special_function_config(ADC_CONTINUOUS_MODE, ENABLE);
	
	/* ADC 触发器配置：软件触发 */
	adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_SWRCST);

	/* ADC 数据对齐配置：右对齐 */
	adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
	
	/* ADC 通道长度配置：1 */
	adc_channel_length_config(ADC_REGULAR_CHANNEL, 1);
	
	/* ADC 规则通道配置：规则组0、ADC通道8、采样时间55.5ADC时钟周期、使能规则通道 */
	adc_regular_channel_config(0, LIGHT_ADC_CHANNEL, ADC_SAMPLETIME_55POINT5);
	adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);
	
	adc_enable();	//使能ADC
	
	adc_calibration_enable();	//使能ADC校准
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



