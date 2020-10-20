/**
  ******************************************************************************
  * @�ļ�         adc.h
  * @����         LGG
  * @�汾         V1.0.0
  * @����         2018-3-16
  * @ժҪ         adcͷ�ļ�
  ******************************************************************************
*/

/* �����ֹ�ݹ���� ----------------------------------------------------------*/
#ifndef __ADC__H
#define __ADC__H

/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "gd32f1x0.h"

extern uint16_t adc_value[2];

/* �궨�� --------------------------------------------------------------------*/
/* ����ADC��ض˿� */

#define LIGHT_ADC_CHANNEL ADC_CHANNEL_8 //�ɼ�����PB0
#define LIGHT_ADC_GPIO_PORT GPIOB
#define LIGHT_ADC_GPIO_PIN GPIO_PIN_0

#define IF_ADC_CHANNEL ADC_CHANNEL_5 //�ɼ��״���ƵPA5
#define IF_ADC_GPIO_PORT GPIOA
#define IF_ADC_GPIO_PIN GPIO_PIN_5

/* ��������-------------------------------------------------------------------*/
void ADC_Config(void);
void ADC_DMA_Config(void);

#endif

/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/
