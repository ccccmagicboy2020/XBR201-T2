/**
  ******************************************************************************
  * @�ļ�         led.c
  * @����         LGG
  * @�汾         V1.0.0
  * @����         2018-3-16
  * @ժҪ         ledԴ�ļ�
  ******************************************************************************
*/ 


/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "led.h"


/**
  * @������       LED_Init
  * @��  ��       ����LED ��IO��
  * @��  ��       ��
  * @����ֵ       ��
  */
void LED_Init(void)
{
	/* ʹ��LED1��LED2����GPIO����ʱ�� */
	rcu_periph_clock_enable(LED1_CLOCK);
	rcu_periph_clock_enable(LED2_CLOCK);
	
	/* ����LED1��LED2������ģʽΪ���ģʽ���������� */
	gpio_mode_set(LED1_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED1_PIN);
	gpio_mode_set(LED2_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED2_PIN);
	
	/* ����LED1��LED2��������ͣ�����������ٶȣ����50MHz */
	gpio_output_options_set(LED1_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LED1_PIN);
	gpio_output_options_set(LED2_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, LED2_PIN);
	
	/* ����LED1��LED2���������ͣ��ر�LED1&LED2�� */
	gpio_bit_set(LED1_PORT, LED1_PIN);
	gpio_bit_set(LED2_PORT, LED2_PIN);
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



