/**
  ******************************************************************************
  * @�ļ�         ck_out.c
  * @����         LGG
  * @�汾         V1.0.0
  * @����         2018-3-16
  * @ժҪ         ck_outԴ�ļ�
  ******************************************************************************
*/ 


/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "ck_out.h"


/**
  * @������       CK_OUT_Config
  * @��  ��       ����CK_OUT
  * @��  ��       ��
  * @����ֵ       ��
  */
void CK_OUT_Config(uint32_t ckout_src, uint32_t ckout_div)
{
	/* ʹ��CK_OUT�������ڵ�GPIO����ʱ�� */
	rcu_periph_clock_enable(CK_OUT_CLOCK);
	
	/* ����PA8(CK_OUT) ������ģʽ */
	gpio_mode_set(CK_OUT_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, CK_OUT_PIN);
	
	/* ����PA8(CK_OUT) Ϊ������� */
	gpio_output_options_set(CK_OUT_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,CK_OUT_PIN);
	
	/* ����PA8(CK_OUT) �������ù��� */
	gpio_af_set(CK_OUT_PORT, GPIO_AF_0, CK_OUT_PIN);
	
	/* ����PA8(CK_OUT) ���ʱ��Դ�����ϵ�� */
	rcu_ckout_config(ckout_src, ckout_div);
}


/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/



