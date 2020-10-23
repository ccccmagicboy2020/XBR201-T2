/**
  ******************************************************************************
  * @�ļ�         main.c
  * @����         LGG
  * @�汾         V1.0.0
  * @����         2018-3-16
  * @ժҪ         CLK����
  ******************************************************************************
  * @attention
  * ������         www.jixin.pro
  * Ӳ��ƽ̨       ����GD32F130G8U6���İ�
  * ����Ч��       LED1��˸��PA8��CK_OUT������ڲ�40KHzʱ��Ƶ�ʣ�ʵ��36KHz���ң�
  ******************************************************************************
  */


/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "gd32f1x0.h"
#include "gd32f1x0_libopt.h"
#include "systick.h"
#include "led.h"
#include "ck_out.h"


/**
  * @������       main
  * @��  ��       ���������
  * @��  ��       ��
  * @����ֵ       ��
  */
int main(void)
{
	rcu_osci_on(RCU_IRC40K);	//���ڲ�40KHzʱ��
	while(rcu_osci_stab_wait(RCU_IRC40K) == ERROR);	//�ȴ�ʱ���ȶ�
	CK_OUT_Config(RCU_CKOUTSRC_IRC40K, RCU_CKOUT_DIV1);	//����ڲ�40KHz��1��Ƶʱ��
	
	systick_config();	//��ʼ���δ�ʱ��
	LED_Init();	//LED��ʼ��
	
	
	while(1)
	{
		LED1_Toggle();	//�ı�LED1״̬
		delay_1ms(500);
	}
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



