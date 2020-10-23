/**
  ******************************************************************************
  * @作者         LGG
  * @版本         V1.0.0
  * @日期         2018-3-16
  * @摘要         USART例程
  ******************************************************************************
  */ 

一、开发说明
	1、开发环境：	MDK5.24a
	2、标准外设库：	GD32F1x0_Firmware_Library_v3.1.0
	3、硬件：		技新GD32F130G8U6核心板 & GD-LINK下载调试器

二、例程说明
	例程主要内容是：	配置USART0，重定向printf函数，通过DMA功能实现数据收发
					例程主要在USART_Printf例程上添加了DMA部分的内容，添加的内容在主函数中。
					其中DMA_CH1用于USART0_TX，DMA_CH2用于USART0_RX。主函数处理过程如下：
					1、定义DMA初始化结构体
					2、使能DMA外设时钟
					3、初始化LED、初始化USART0
					4、串扣打印信息：USART DMA TEST!，LED1亮
					5、初始化DMA_CH1（用于串口发送）：
						a.内存到外设模式、内存地址、内存地址递增、内存数据宽度8位、数据量、外设地址、外设地址不递增、外设数据宽度8位、优先级超高
						b.禁能循环模式
						c.禁能内存到内存模式
						d.使能DMA_CH1
						e.使能USART0的DMA发送
						f.等待DMA传输完成，完成后串口显示：rUSART DMA receive and transmit example, please input 10 bytes:
					6、初始化DMA_CH2（用于串口接收）：
						a.外设到内存模式、内存地址、内存地址递增、内存数据宽度8位、数据量10、外设地址、外设地址不递增、外设数据宽度8位、优先级超高
						b.禁能循环模式
						c.禁能内存到内存模式
						d.使能DMA_CH2
						e.使能USART0的DMA接收
						f.等待DMA传输完成（DMA等待接收10Byte数据），完成后串口打印串口发送过来的10Byte消息，LED2状态改变
					
					注意：首先需要重定向printf函数，然后‘在魔术棒’中的target栏下把Use MicroLIB（使用微库）勾上才能使用
						  例程需要一个USB转TTL模块，把核心板与电脑连接，然后在电脑上位机（串口调试软件）实现效果
						  上位机的设置应该跟USART0的（波特率115200）、（数据长度8位）、（停止位1位）、（无奇偶校验）、（禁能硬件流控）一致

三、使用说明
	1、打开工程
	2、编译：Project--->	Rebuild all target files
	3、下载：Flash--->Download（快捷键F8）
	4、效果：上电串口打印：USART DMA TEST!
			 USART DMA receive and transmit example, please input 10 bytes:
			 在串口调试助手上往串口发送10Byte，串口会发送回来10Byte（超过10Byte,只会发送前10Byte）

四、其他&帮助
	1、技新售前支持（QQ群）：612394941
	2、技新官网：www.jixin.pro
	3、联系方式：18320813408(加微信联系)
	



