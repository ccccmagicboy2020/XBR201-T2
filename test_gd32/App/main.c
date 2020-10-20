/**
  ******************************************************************************
  * @文件         main.c
  * @作者         LGG
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         LED例程
  ******************************************************************************
  * @attention
  * 技新网         www.jixin.pro
  * 硬件平台       技新GD32F130G8U6核心板
  * 程序效果       LED1闪烁
  ******************************************************************************
  */

/* 包含头文件 ----------------------------------------------------------------*/
#include "gd32f1x0.h"
#include "gd32f1x0_libopt.h"
#include "systick.h"

#include "led.h"
#include "usart.h"
#include "adc.h"
#include "dac.h"
#include <stdio.h> //printf等

uint16_t adc_value[2];
float vol_value[2];
uint16_t Get_JTAG_ID(void);
/**
  * @函数名       main
  * @功  能       主函数入口
  * @参  数       无
  * @返回值       无
  */
int main(void)
{
  uint32_t MCUid;

  systick_config(); //初始化滴答定时器
  LED_Init();       //LED初始化
  USART0_Init();    //串口0初始化
  ADC_Config();     //ADC初始化
  ADC_DMA_Config(); //ADC的DMA配置初始化
  DAC_Config();     //DAC的初始化

  MCUid = Get_JTAG_ID(); //启动芯片之前判断芯片
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
    LED1_Toggle(); //对LED1的状态进行取反
    delay_1ms(1000);
  }
}

/* 重定向C库中的printf函数 */
int fputc(int ch, FILE *f)
{
  usart_data_transmit(USART0, (uint8_t)ch);
  while (RESET == usart_flag_get(USART0, USART_FLAG_TBE))
    ;
  return ch;
}

//返回  0x041 是 ST （ST手册 Doc ID 13902 Rev 14 的 1055页    31.6.2 和 31.6.4 ） ，
//返回  0x7A3 是 GD 。
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
