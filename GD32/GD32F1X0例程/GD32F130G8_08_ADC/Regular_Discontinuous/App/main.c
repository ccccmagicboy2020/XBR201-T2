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
  * ����Ч��       LED1��˸��PA0(ADC_IN0),PA1(ADC_IN1),PA2(ADC_IN2),PA3(ADC_IN3)��·ADC����
	*								 ��������ͨ��DMA���ͣ����ڴ��ڴ�ӡ����
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
uint16_t adc_value[4];
float vol_value[4];


/**
  * @������       main
  * @��  ��       ���������
  * @��  ��       ��
  * @����ֵ       ��
  */
int main(void)
{
	uint8_t i;
	
	systick_config();	//��ʼ���δ�ʱ��
	
	LED_Init();	//LED��ʼ��
	USART0_Init();	//USART0��ʼ��
	ADC_Config();	//ADC��ʼ��
	ADC_DMA_Config();	//ADC��DMA���ó�ʼ��
	
	while(1)
	{
		/* �������ʹ�� */
		adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
		
		/* �ȴ�DMA������� */
		while (RESET == dma_flag_get(DMA_CH0, DMA_FLAG_FTF));

		for(i = 0; i<4; i++)
		{
			vol_value[i] = (float)adc_value[i]/4096 * 3.3;	//ת��Ϊ��ѹֵ
		
			printf("the adc_value1[%d] is %d\r\n", i,adc_value[i]);	//��ӡADCֵ
			printf("the vol_valuel[%d] is %f\r\n", i,vol_value[i]);	//��ӡ��ѹֵ
		}
		
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



