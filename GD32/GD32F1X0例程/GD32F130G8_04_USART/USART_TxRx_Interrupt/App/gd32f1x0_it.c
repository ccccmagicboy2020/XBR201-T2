/*!
    \file  gd32f1x0_it.c
    \brief interrupt service routines
*/

/*
    Copyright (C) 2017 GigaDevice

    2014-12-26, V1.0.0, platform GD32F1x0(x=3,5)
    2016-01-15, V2.0.0, platform GD32F1x0(x=3,5,7,9)
    2016-04-30, V3.0.0, firmware update for GD32F1x0(x=3,5,7,9)
    2017-06-19, V3.1.0, firmware update for GD32F1x0(x=3,5,7,9)
*/

#include "gd32f1x0_it.h"
#include "systick.h"
#include "usart.h"

extern uint8_t transfersize;
extern uint8_t receivesize;
extern __IO uint8_t txcount; 
extern __IO uint16_t rxcount; 
extern uint8_t receiver_buffer[32];
extern uint8_t transmitter_buffer[];


/*!
    \brief      this function handles NMI exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void NMI_Handler(void)
{
}

/*!
    \brief      this function handles HardFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void HardFault_Handler(void)
{
    /* if Hard Fault exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief      this function handles MemManage exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void MemManage_Handler(void)
{
    /* if Memory Manage exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief      this function handles BusFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void BusFault_Handler(void)
{
    /* if Bus Fault exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief      this function handles UsageFault exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void UsageFault_Handler(void)
{
    /* if Usage Fault exception occurs, go to infinite loop */
    while (1);
}

/*!
    \brief      this function handles SVC exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SVC_Handler(void)
{
}

/*!
    \brief      this function handles DebugMon exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void DebugMon_Handler(void)
{
}

/*!
    \brief      this function handles PendSV exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void PendSV_Handler(void)
{
}

/*!
    \brief      this function handles SysTick exception
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SysTick_Handler(void)
{
    delay_decrement();
}

/*!
    \brief      this function handles USART RBNE interrupt request and TBE interrupt request
    \param[in]  none
    \param[out] none
    \retval     none
*/
void USART0_IRQHandler(void)
{
	/* 串口接收中断 */
	if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE))
		{
			/* 保存接收的数据 */
			receiver_buffer[rxcount++] = usart_data_receive(USART0);
			if(rxcount == receivesize)	//如果接收的数据量 = 32，关闭接收中断
				usart_interrupt_disable(USART0, USART_INT_RBNE);
    }

	/* 串口发送中断 */
	if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_TBE))
		{
			/* 发送 transmitter_buffer 数据 */
			usart_data_transmit(USART0, transmitter_buffer[txcount++]);
			if(txcount == transfersize)	//数据全部发送完毕，关闭发送中断
				usart_interrupt_disable(USART0, USART_INT_TBE);
        
    }
}
