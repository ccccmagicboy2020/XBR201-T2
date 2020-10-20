/**
  ******************************************************************************
  * @文件         DAC.c
  * @作者         CCCC
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         DAC源文件
  ******************************************************************************
*/

/* 包含头文件 ----------------------------------------------------------------*/
#include "DAC.h"
#include "systick.h"

/**
  * @函数名       DAC_Config
  * @功  能       DAC配置
  * @参  数       无
  * @返回值       无
  */
void DAC_Config(void)
{
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_DAC);
	
	  gpio_mode_set(GPIOA,GPIO_MODE_ANALOG,GPIO_PUPD_NONE,GPIO_PIN_4);

    dac0_trigger_source_config(DAC_TRIGGER_SOFTWARE);
    dac0_output_buffer_disable();
    /* set data left 12b alignment */
    dac0_data_set(DAC_ALIGN_12B_R, 0x0000);
    /* enable DAC0 */
    dac0_enable();
    dac0_software_trigger_enable();
}

void DAC_voltage_output(float value)
{
  uint32_t raw;

  raw = value/3.3*4096;

  dac0_data_set(DAC_ALIGN_12B_R, raw);
}
/************************ Copyright (C)2018 LGG. All Rights Reserved *****END OF FILE****/
