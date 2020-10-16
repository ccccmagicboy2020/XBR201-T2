/**
  ******************************************************************************
  * @�ļ�         main.c
  * @����         LGG
  * @�汾         V1.0.0
  * @����         2018-3-16
  * @ժҪ         LED����
  ******************************************************************************
  * @attention
  * ������         www.jixin.pro
  * Ӳ��ƽ̨       ����GD32F130G8U6���İ�
  * ����Ч��       LED1��˸
  ******************************************************************************
  */


/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "gd32f1x0.h"
#include "gd32f1x0_libopt.h"
#include "systick.h"

#include "led.h"
#include "usart.h"
#include <stdio.h>  //printf��


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
  USART0_Init();	//����0��ʼ��
	
	while(1)
	{
    printf("Hello World!\r\n");	//���ڴ�ӡ��Hello World!
		LED1_Toggle();	//��LED1��״̬����ȡ��
		delay_1ms(500);
	}
}

/* �ض���C���е�printf���� */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t)ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    return ch;
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



