/**
  ******************************************************************************
  * @�ļ�         main.c
  * @����         LGG
  * @�汾         V1.0.0
  * @����         2018-3-16
  * @ժҪ         ADC����
  ******************************************************************************
  * @attention
  * ������         www.jixin.pro
  * Ӳ��ƽ̨       ����GD32F130G8U6���İ�
  * ����Ч��       LED1��˸����PB0�ڽ�һ����λ����ͨ��USBתTTLģ�����ӵ����İ��USART0��PA9��PA10����
	*								 ���ڵ�λ�����Կ������������ADCֵ�͵�ѹֵ�����仯
  ******************************************************************************
  */


/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "gd32f1x0.h"
#include "gd32f1x0_libopt.h"
#include <stdio.h>
#include "systick.h"
#include "led.h"
#include "usart.h"
#include "adc.h"


/* ��������-------------------------------------------------------------------*/
uint16_t adc_value;	//�����ڴ��ַ�����ڱ���ADCֵ
float vol_value;	//���屣��ת����ѹֵ


/**
  * @������       main
  * @��  ��       ���������
  * @��  ��       ��
  * @����ֵ       ��
  */
int main(void)
{
	systick_config();	//��ʼ���δ�ʱ��
	
	LED_Init();	//LED��ʼ��
	USART0_Init();	//USART0��ʼ��
	ADC_Config();	//ADC��ʼ��
	ADC_DMA_Config();	//ADC��DMA���ó�ʼ��
	
	/* �������ʹ�� */
	adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
	while(1)
	{
		/* �ȴ�DMA������� */
		while (RESET == dma_flag_get(DMA_CH0, DMA_FLAG_FTF));

		vol_value = (float)adc_value/4096 * 3.3;	//ת��Ϊ��ѹֵ
		
		printf("the adc_value1 is %d\r\n", adc_value);	//��ӡADCֵ
		printf("the vol_valuel is %f\r\n", vol_value);	//��ӡ��ѹֵ
		
		LED1_Toggle();
		delay_1ms(500);
	}
}


/* �ض���printf���� */
int fputc(int ch, FILE *f)
{
	usart_data_transmit(USART0, (uint8_t)ch);
	while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));

	return ch;
}



/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



