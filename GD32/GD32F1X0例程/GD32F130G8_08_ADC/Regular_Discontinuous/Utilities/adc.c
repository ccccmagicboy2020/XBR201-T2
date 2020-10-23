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
#include "systick.h"


/**
  * @函数名       ADC_Config
  * @功  能       ADC配置
  * @参  数       无
  * @返回值       无
  */
void ADC_Config(void)
{
	/* 使能ADC通道所在GPIO外设时钟 */
	rcu_periph_clock_enable(RCU_GPIOA);
	
	/* 使能 ADC 时钟 */
	rcu_periph_clock_enable(RCU_ADC);
	
	/* 配置 ADC 时钟 */
	rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);
	
	/* 配置ADC_IN0,ADC_IN1,ADC_IN2,ADC_IN3在GPIO为模拟模式 */
	gpio_mode_set(GPIOA,GPIO_MODE_ANALOG,GPIO_PUPD_NONE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	
	
	/* ADC 通道长度配置：规则通道，数量4 */
	adc_channel_length_config(ADC_REGULAR_CHANNEL, 4);
	
	/* ADC 规则通道配置 */
	adc_regular_channel_config(0,ADC_CHANNEL_0,ADC_SAMPLETIME_239POINT5);
	adc_regular_channel_config(1,ADC_CHANNEL_1,ADC_SAMPLETIME_239POINT5);
	adc_regular_channel_config(2,ADC_CHANNEL_2,ADC_SAMPLETIME_239POINT5);
	adc_regular_channel_config(3,ADC_CHANNEL_3,ADC_SAMPLETIME_239POINT5);
	
	/* ADC 外部触发使能 */
	adc_external_trigger_config(ADC_REGULAR_CHANNEL,ENABLE);
	
	/* ADC 外部触发源配置：软件触发 */
	adc_external_trigger_source_config(ADC_REGULAR_CHANNEL,ADC_EXTTRIG_REGULAR_SWRCST);
	
	/* ADC 数据对齐配置：右对齐 */
	adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
	
	/* ADC 不连续模式，每次转换4个通道 */
	adc_discontinuous_mode_config(ADC_REGULAR_CHANNEL,4);
	
	adc_enable();	//使能ADC
	
	adc_calibration_enable();	//使能ADC校准
}


void ADC_DMA_Config(void)
{
	/* 使能 DMA 外设时钟 */
	rcu_periph_clock_enable(RCU_DMA);
	
	/* ADC_DMA_channel 配置 */
	dma_deinit(DMA_CH0);	//重置DMA_CHO相关寄存器
	dma_periph_address_config(DMA_CH0,(uint32_t)(&ADC_RDATA));	//外设地址
	dma_memory_address_config(DMA_CH0,(uint32_t)(&adc_value));	//内存地址
	dma_transfer_direction_config(DMA_CH0,DMA_PERIPHERAL_TO_MEMORY);	//外设到内存
	dma_memory_width_config(DMA_CH0,DMA_MEMORY_WIDTH_16BIT);	//内存数据宽度16Bit
	dma_periph_width_config(DMA_CH0,DMA_PERIPHERAL_WIDTH_16BIT);	//外设数据宽度16Bit
	dma_priority_config(DMA_CH0,DMA_PRIORITY_HIGH);	//优先级高
	dma_transfer_number_config(DMA_CH0,4);	//数据量4
	dma_periph_increase_disable(DMA_CH0);	//外设地址地址禁能
	dma_memory_increase_enable(DMA_CH0);	//内存地址递增使能
	dma_circulation_enable(DMA_CH0);	//使能循环模式
	dma_channel_enable(DMA_CH0);	//使能DMA_CH0
	
	adc_dma_mode_enable();	//使能ADC的DMA模式
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



