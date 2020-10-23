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
#include "systick.h"


/**
  * @������       ADC_Config
  * @��  ��       ADC����
  * @��  ��       ��
  * @����ֵ       ��
  */
void ADC_Config(void)
{
	/* ʹ��ADCͨ������GPIO����ʱ�� */
	rcu_periph_clock_enable(RCU_GPIOA);
	
	/* ʹ�� ADC ʱ�� */
	rcu_periph_clock_enable(RCU_ADC);
	
	/* ���� ADC ʱ�� */
	rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);
	
	/* ����ADC_IN0,ADC_IN1,ADC_IN2,ADC_IN3��GPIOΪģ��ģʽ */
	gpio_mode_set(GPIOA,GPIO_MODE_ANALOG,GPIO_PUPD_NONE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	
	
	/* ADC ͨ���������ã�����ͨ��������4 */
	adc_channel_length_config(ADC_REGULAR_CHANNEL, 4);
	
	/* ADC ����ͨ������ */
	adc_regular_channel_config(0,ADC_CHANNEL_0,ADC_SAMPLETIME_239POINT5);
	adc_regular_channel_config(1,ADC_CHANNEL_1,ADC_SAMPLETIME_239POINT5);
	adc_regular_channel_config(2,ADC_CHANNEL_2,ADC_SAMPLETIME_239POINT5);
	adc_regular_channel_config(3,ADC_CHANNEL_3,ADC_SAMPLETIME_239POINT5);
	
	/* ADC �ⲿ����ʹ�� */
	adc_external_trigger_config(ADC_REGULAR_CHANNEL,ENABLE);
	
	/* ADC �ⲿ����Դ���ã�������� */
	adc_external_trigger_source_config(ADC_REGULAR_CHANNEL,ADC_EXTTRIG_REGULAR_SWRCST);
	
	/* ADC ���ݶ������ã��Ҷ��� */
	adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
	
	/* ADC ������ģʽ��ÿ��ת��4��ͨ�� */
	adc_discontinuous_mode_config(ADC_REGULAR_CHANNEL,4);
	
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
	dma_transfer_number_config(DMA_CH0,4);	//������4
	dma_periph_increase_disable(DMA_CH0);	//�����ַ��ַ����
	dma_memory_increase_enable(DMA_CH0);	//�ڴ��ַ����ʹ��
	dma_circulation_enable(DMA_CH0);	//ʹ��ѭ��ģʽ
	dma_channel_enable(DMA_CH0);	//ʹ��DMA_CH0
	
	adc_dma_mode_enable();	//ʹ��ADC��DMAģʽ
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



