/**
  ******************************************************************************
  * @文件         adc.h
  * @作者         LGG
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         adc头文件
  ******************************************************************************
*/

/* 定义防止递归包含 ----------------------------------------------------------*/
#ifndef __ADC__H
#define __ADC__H

/* 包含头文件 ----------------------------------------------------------------*/
#include "gd32f1x0.h"

extern uint16_t adc_value[2];

/* 宏定义 --------------------------------------------------------------------*/
/* 定义ADC相关端口 */

#define LIGHT_ADC_CHANNEL ADC_CHANNEL_8 //采集光敏PB0
#define LIGHT_ADC_GPIO_PORT GPIOB
#define LIGHT_ADC_GPIO_PIN GPIO_PIN_0

#define IF_ADC_CHANNEL ADC_CHANNEL_5 //采集雷达中频PA5
#define IF_ADC_GPIO_PORT GPIOA
#define IF_ADC_GPIO_PIN GPIO_PIN_5

/* 函数声明-------------------------------------------------------------------*/
void ADC_Config(void);
void ADC_DMA_Config(void);

#endif

/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/
