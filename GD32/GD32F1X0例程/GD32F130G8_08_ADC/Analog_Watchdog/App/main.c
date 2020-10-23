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
  * ����Ч��       LED1��˸����PB0(ADC_IN8)�ڽ�һ����λ�����ڲɼ��ĵ�ѹ����ֵ(0x0400,0x0A00)֮�ڣ�
	*								 LED2�����,���ɼ��ĵ�ѹ���ڻ�С����ֵ��LED2��
  ******************************************************************************
  */


/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "gd32f1x0.h"
#include "gd32f1x0_libopt.h"
#include "systick.h"
#include "led.h"
#include "adc.h"


/* ��������-------------------------------------------------------------------*/
uint8_t Analog_Watchdog_Flag = 0;


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
	ADC_Config();	//ADC��ʼ��
	
	/* �������ADC */
	adc_software_trigger_enable(ADC_REGULAR_CHANNEL);
	
	while(1)
	{
		if(Analog_Watchdog_Flag != 0)	//�жϱ�־λ
		{
			Analog_Watchdog_Flag = 0;	//��־λ����
			LED2_ON();	//����LED2
		}
		else
			LED2_OFF();	//�ر�LED2

		LED1_Toggle();
		delay_1ms(500);
	}
}



/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



