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
  * ����Ч��       �ϵ紮�ڴ�ӡ��USART DMA TEST!
	*								 USART DMA receive and transmit example, please input 10 bytes:
	*								 �ڴ��ڵ��������������ڷ���10Byte�����ڻᷢ�ͻ���10Byte
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


uint8_t rxbuffer[10];	//�������ݻ���
/* �������ݻ��� */
uint8_t txbuffer[]="\n\rUSART DMA receive and transmit example, please input 10 bytes:\n\r";

#define ARRAYNUM(arr_nanme)      (uint32_t)(sizeof(arr_nanme) / sizeof(*(arr_nanme)))
#define USART0_TDATA_ADDRESS      ((uint32_t)0x40013828)	//USART0�ķ������ݼĴ�����ַ
#define USART0_RDATA_ADDRESS      ((uint32_t)0x40013824)	//USART0�Ľ������ݼĴ�����ַ



/**
  * @������       main
  * @��  ��       ���������
  * @��  ��       ��
  * @����ֵ       ��
  */
int main(void)
{
	/* ����DMA��ʼ���ṹ�� */
	dma_parameter_struct dma_init_struct;

	/* ʹ��DMA����ʱ�� */
	rcu_periph_clock_enable(RCU_DMA);
	
	LED_Init();	//LED��ʼ��
	USART0_Init();	//����0��ʼ��
	
	/* ��ӡ��Ϣ */
	printf("USART DMA TEST!\n\r");
	LED1_ON();	//LED1��
	
	/* ��ʼ��DMA_CH1 */
	dma_deinit(DMA_CH1);	//����DMA_CH1��ؼĴ���
	dma_init_struct.direction = DMA_MEMORY_TO_PERIPHERAL;	//�ڴ浽����ģʽ
	dma_init_struct.memory_addr = (uint32_t)txbuffer;	//�ڴ����ַ
	dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;	//�ڴ��ַ����
	dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;	//���ݿ��8λ
	dma_init_struct.number = ARRAYNUM(txbuffer);	//������
	dma_init_struct.periph_addr = USART0_TDATA_ADDRESS;	//�������ַ
	dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;	//�����ַ������
	dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;	//���ݿ��8λ
	dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;	//���ȼ�����
	dma_init(DMA_CH1, dma_init_struct);	//��ʼ������
	
	/* ����ѭ��ģʽ */
	dma_circulation_disable(DMA_CH1);
	
	/* �����ڴ浽�ڴ�ģʽ */
	dma_memory_to_memory_disable(DMA_CH1);
	
	/* ʹ��DMA_CH1 */
	dma_channel_enable(DMA_CH1);
	
	/* ʹ��USART0��DMA���� */
	usart_dma_transmit_config(USART0, USART_DENT_ENABLE);
    
	/* �ȴ�DMA������� */
	while (RESET == dma_flag_get(DMA_CH1, DMA_FLAG_FTF));
	
	while(1){
		/* ��ʼ��DMA_CH2 */
		dma_deinit(DMA_CH2);	//����DMA_CH2��ؼĴ���
		dma_init_struct.direction = DMA_PERIPHERAL_TO_MEMORY;	//���赽�ڴ�ģʽ
		dma_init_struct.memory_addr = (uint32_t)rxbuffer;	//�ڴ����ַ
		dma_init_struct.memory_inc = DMA_MEMORY_INCREASE_ENABLE;	//�ڴ��ַ����
		dma_init_struct.memory_width = DMA_MEMORY_WIDTH_8BIT;	//���ݿ��8λ
		dma_init_struct.number = 10;	//������10
		dma_init_struct.periph_addr = USART0_RDATA_ADDRESS;	//�������ַ
		dma_init_struct.periph_inc = DMA_PERIPH_INCREASE_DISABLE;	//�����ַ������
		dma_init_struct.periph_width = DMA_PERIPHERAL_WIDTH_8BIT;	//���ݿ��8λ
		dma_init_struct.priority = DMA_PRIORITY_ULTRA_HIGH;	//���ȼ�����
		dma_init(DMA_CH2, dma_init_struct);		//��ʼ������
        
		/* ����ѭ��ģʽ */
		dma_circulation_disable(DMA_CH2);
		
		/* �����ڴ浽�ڴ�ģʽ */
		dma_memory_to_memory_disable(DMA_CH2);

		/* ʹ��DMA_CH2 */
		dma_channel_enable(DMA_CH2);
		
		/* ʹ��USART��DMA���� */
		usart_dma_receive_config(USART0, USART_DENR_ENABLE);
		
		/* �ȴ�DMA������� */
		while (RESET == dma_flag_get(DMA_CH2, DMA_FLAG_FTF));
		
		/* ��ӡDMA���յ���Ϣ */
		printf("\n\r%s\n\r",rxbuffer);
		LED2_Toggle();	//LED2״̬�ı�
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



