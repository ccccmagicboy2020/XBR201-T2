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
	rcu_periph_clock_enable(RCU_GPIOA);
	
	/* ʹ�� ADC ʱ�� */
	rcu_periph_clock_enable(RCU_ADC);
	
	/* ���� ADC ʱ�� */
	rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);
	
	/* ����ADCͨ������GPIOΪģ��ģʽ */
	gpio_mode_set(LIGHT_ADC_GPIO_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, LIGHT_ADC_GPIO_PIN);
	
	/* ADC ����ģʽʹ�� */
	adc_special_function_config(ADC_CONTINUOUS_MODE, ENABLE);
	
	/* ADC ���������ã�������� */
	adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_SWRCST);

	/* ADC ���ݶ������ã��Ҷ��� */
	adc_data_alignment_config(ADC_DATAALIGN_RIGHT);
	
	/* ADC ͨ���������ã�1 */
	adc_channel_length_config(ADC_REGULAR_CHANNEL, 1);
	
	/* ADC ����ͨ�����ã�������0��ADCͨ��8������ʱ��55.5ADCʱ�����ڡ�ʹ�ܹ���ͨ�� */
	adc_regular_channel_config(0, LIGHT_ADC_CHANNEL, ADC_SAMPLETIME_55POINT5);
	adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);
	
	adc_enable();	//ʹ��ADC
	
	adc_calibration_enable();	//ʹ��ADCУ׼
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



