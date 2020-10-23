/**
  ******************************************************************************
  * @�ļ�         key.c
  * @����         LGG
  * @�汾         V1.0.0
  * @����         2018-3-16
  * @ժҪ         keyԴ�ļ�
  ******************************************************************************
*/ 


/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "key.h"
#include "systick.h"


/**
  * @������       KEY_Init
  * @��  ��       ����KEY ��IO��
  * @��  ��       ��
  * @����ֵ       ��
  */
void KEY_Init(void)
{
	/* ʹ��KEY����GPIO����ʱ�� */
	rcu_periph_clock_enable(KEY_CLOCK);
	
	/* ����KEY������ģʽΪ����ģʽ������������ */
	gpio_mode_set(KEY_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, KEY_PIN);
}


/**
  * @������       KEY_Scan
  * @��  ��       ����ɨ�躯��
  * @��  ��       ��
  * @����ֵ       KEY���·��أ�KEY_PRES�����򷵻أ�0
  */
uint8_t KEY_Scan(void)
{
	if(KEY_READ == 0)
	{
		delay_1ms(10);	//����
		if(KEY_READ == 0)
		{
			while(KEY_READ == 0);	//���ּ��
			return KEY_PRES;
		}
	}
	
	return 0;
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



