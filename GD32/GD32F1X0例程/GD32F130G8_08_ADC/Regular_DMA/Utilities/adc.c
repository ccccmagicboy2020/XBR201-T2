/**
  ******************************************************************************
  * @�ļ�         adc.c
  * @����         LGG
  * @�汾         V1.0.0
  * @����         2018-3-16
  * @ժҪ         adcԴ�ļ�
  ******************************************************************************
*/ 


/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "adc.h"


/**
  * @������       ADC_Config
  * @��  ��       ADC����
  * @��  ��       ��
  * @����ֵ       ��
  */
void ADC_Config(void)
{
	/* ʹ��ADCͨ������GPIO����ʱ�� */
	rcu_periph_clock_enable(RCU_GPIOB);
	
	/* ʹ�� ADC ʱ�� */
	rcu_periph_clock_enable(RCU_ADC);
	
	/* ���� ADC ʱ�� */
	rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);
	
	/* ����ADCͨ������GPIOΪģ��ģʽ */
	gpio_mode_set(ADC_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, ADC_GPIO_PIN);
	
	/* ADC ����ģʽʹ�� */
	adc_special_function_config(ADC_CONTINUOUS_MODE, ENABLE);
	
	/* ADC ���������ã�������� */
	adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_SWRCST);

	/* ADC ���ݶ������ã��Ҷ��� */
	adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
	
	/* ADC ͨ���������ã�1 */
	adc_channel_length_config(ADC_REGULAR_CHANNEL, 1);
	
	/* ADC ����ͨ�����ã�������0��ADCͨ��8������ʱ��55.5ADCʱ�����ڡ�ʹ�ܹ���ͨ�� */
	adc_regular_channel_config(0, ADC_CHANNEL_8, ADC_SAMPLETIME_55POINT5);
	adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);
	
	adc_enable();	//ʹ��ADC
	
	adc_calibration_enable();	//ʹ��ADCУ׼
}


void ADC_DMA_Config(void)
{
	/* ʹ�� DMA ����ʱ�� */
	rcu_periph_clock_enable(RCU_DMA);
	
	/* ADC_DMA_channel ���� */
	dma_deinit(DMA_CH0);	//����DMA_CHO��ؼĴ���
	dma_periph_address_config(DMA_CH0,(uint32_t)(&ADC_RDATA));	//�����ַ
	dma_memory_address_config(DMA_CH0,(uint32_t)(&adc_value));	//�ڴ��ַ
	dma_transfer_direction_config(DMA_CH0,DMA_PERIPHERAL_TO_MEMORY);	//���赽�ڴ�
	dma_memory_width_config(DMA_CH0,DMA_MEMORY_WIDTH_16BIT);	//�ڴ����ݿ��16Bit
	dma_periph_width_config(DMA_CH0,DMA_PERIPHERAL_WIDTH_16BIT);	//�������ݿ��16Bit
	dma_priority_config(DMA_CH0,DMA_PRIORITY_HIGH);	//���ȼ���
	dma_transfer_number_config(DMA_CH0,1);	//������1
	dma_periph_increase_disable(DMA_CH0);	//�����ַ��������
	dma_memory_increase_disable(DMA_CH0);	//�ڴ��ַ��������
	dma_circulation_enable(DMA_CH0);	//ʹ��ѭ��ģʽ
	dma_channel_enable(DMA_CH0);	//ʹ��DMA_CH0
	
	adc_dma_mode_enable();	//ʹ��ADC��DMAģʽ
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



