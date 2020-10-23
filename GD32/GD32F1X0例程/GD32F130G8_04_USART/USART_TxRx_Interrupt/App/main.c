/**
  ******************************************************************************
  * @�ļ�         main.c
  * @����         LGG
  * @�汾         V1.0.0
  * @����         2018-3-16
  * @ժҪ         USART����
  ******************************************************************************
  * @attention
  * ������         www.jixin.pro
  * Ӳ��ƽ̨       ����GD32F130G8U6���İ�
  * ����Ч��       �ϵ紮�ڴ�ӡ��USART interrupt test��LED1���������ж��аѷ����жϽ��ܣ�
	*								 �����ڽ��յ����ڵ���32Byte������ʱ�����ڴ�ӡUSART receive successfully!��LED2�������ж��аѽ����жϽ��ܣ�
	*									- BaudRate = 115200 baud��������115200��
	*									- Word Length = 8 Bits�����ݳ���8λ��
	*									- One Stop Bit��ֹͣλ1λ��
	*									- No parity������żУ�飩
	*									- Hardware flow control disabled (RTS and CTS signals)������Ӳ�����أ�
	*									- Receive and transmit enabled�����������ʹ�ܣ�
  ******************************************************************************
  */


/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "gd32f1x0.h"
#include "gd32f1x0_libopt.h"
#include "systick.h"
#include "led.h"
#include "usart.h"
#include <stdio.h>


#define ARRAYNUM(arr_nanme)      (uint32_t)(sizeof(arr_nanme) / sizeof(*(arr_nanme)))
#define TRANSMIT_SIZE   				 (ARRAYNUM(transmitter_buffer) - 1)	//���㷢�����ݵĴ�С

uint8_t transmitter_buffer[] = "USART interrupt test\n\r";	//Ҫ���͵�����
uint8_t receiver_buffer[32];	//����������ݵĻ���
uint8_t transfersize = TRANSMIT_SIZE;	//���巢�����ݵĴ�С
uint8_t receivesize = 32;	//����������ݴ�С
__IO uint8_t txcount = 0; 	//���巢����������
__IO uint16_t rxcount = 0; 	//���������������


/**
  * @������       main
  * @��  ��       ���������
  * @��  ��       ��
  * @����ֵ       ��
  */
int main(void)
{
	LED_Init();	//LED��ʼ��
	USART0_Init();	//����0��ʼ��
	
	/* USART0���ж����� */
	nvic_irq_enable(USART0_IRQn, 0, 0);
	
	/* ʹ�� USART0 TBE�����ڷ��ͣ� �ж� */  
	usart_interrupt_enable(USART0, USART_INT_TBE);
	
	/* �ȴ������жϷ��� transmitter_buffer ���� */
	while(txcount < transfersize);
	
	/* �ȴ����ڷ������ */
	while (RESET == usart_flag_get(USART0, USART_FLAG_TC));
	LED1_ON();	//LED1��
	
	/* ʹ��RBNE�����ڽ��գ��ж� */
	usart_interrupt_enable(USART0, USART_INT_RBNE);
	
	/* �ȴ��������ݣ��������ݴ��ڵ���32Byteʱ��ӡ���������Ϣ */
	while(rxcount < receivesize);
	if(rxcount == receivesize)
        printf("USART receive successfully!\n\r");
	LED2_ON();	//LED2��
	
	while(1)
	{
		;
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



