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
#include "adc.h"
#include "dac.h"
#include <stdio.h> //printf��

uint16_t adc_value[2];
float vol_value[2];
uint16_t Get_JTAG_ID(void);
/**
  * @������       main
  * @��  ��       ���������
  * @��  ��       ��
  * @����ֵ       ��
  */
int main(void)
{
  uint32_t MCUid;

  systick_config(); //��ʼ���δ�ʱ��
  LED_Init();       //LED��ʼ��
  USART0_Init();    //����0��ʼ��
  ADC_Config();     //ADC��ʼ��
  ADC_DMA_Config(); //ADC��DMA���ó�ʼ��
  DAC_Config();     //DAC�ĳ�ʼ��

  MCUid = Get_JTAG_ID(); //����оƬ֮ǰ�ж�оƬ
  printf("mcu id is: 0x%04x\r\n", MCUid);

  while (1)
  {
    char i;

    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
    while (RESET == dma_flag_get(DMA_CH0, DMA_FLAG_FTF))
      ;

    for (i = 0; i < 2; i++)
    {
      vol_value[i] = (float)adc_value[i] / 4096 * 3.3; //

      printf("the adc_value1[%d] is %d\r\n", i, adc_value[i]); //
      printf("the vol_valuel[%d] is %f\r\n", i, vol_value[i]); //
    }

    DAC_voltage_output(1.2);
    LED1_Toggle(); //��LED1��״̬����ȡ��
    delay_1ms(1000);
  }
}

/* �ض���C���е�printf���� */
int fputc(int ch, FILE *f)
{
  usart_data_transmit(USART0, (uint8_t)ch);
  while (RESET == usart_flag_get(USART0, USART_FLAG_TBE))
    ;
  return ch;
}

//����  0x041 �� ST ��ST�ֲ� Doc ID 13902 Rev 14 �� 1055ҳ    31.6.2 �� 31.6.4 �� ��
//����  0x7A3 �� GD ��
uint16_t Get_JTAG_ID(void)
{
  if (*(uint8_t *)(0xE00FFFE8) & 0x08)
  {
    return ((*(uint8_t *)(0xE00FFFD0) & 0x0F) << 8) |
           ((*(uint8_t *)(0xE00FFFE4) & 0xFF) >> 3) |
           ((*(uint8_t *)(0xE00FFFE8) & 0x07) << 5) + 1;
  }
  return 0;
}

/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/
