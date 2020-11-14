/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无 & 璨，                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : BSP_USART.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无 & 璨                                                       
  |--Date        : 2019-03-22               
  |--Libsupports : 
  |--Description :                                                       
  |--FunctionList                                                       
  |-------1. ....                                                       
  |          <version>:                                                       
  |     <modify staff>:                                                       
  |             <data>:                                                       
  |      <description>:                                                        
  |-------2. ...                                                       
  |-----------------------------declaration of end-----------------------------|
 **/
#ifndef __BSP_USART_H 
#define __BSP_USART_H 

#include "Switch.h"
#include "stm32f4xx.h" 
#include "stdio.h"	


/*发送一个字符*/
void USART_SendByte(USART_TypeDef*USARTx,uint8_t ch);

/*发送一串字符串*/
void USART_SendString(USART_TypeDef*USARTx,char*str);

	
/* =========================== USART1 & DMA of begin =========================== */
#define USART1_TX_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define USART1_TX_GPIO_PORT         GPIOB
#define USART1_TX_Pin          	 	GPIO_Pin_6
#define USART1_TX_PINSOURCE			GPIO_PinSource6

#define USART1_RX_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define USART1_RX_GPIO_PORT         GPIOB
#define USART1_RX_Pin           	GPIO_Pin_7
#define USART1_RX_PINSOURCE			GPIO_PinSource7    

#define USART1_RX_ADDR						(uint32_t)(&USART1->DR)	
#define USART1_RX_DMA_CHANNEL           	DMA_Channel_4		
#define USART1_RX_DMA_STREAM           		DMA2_Stream2		

/* USART1(DR16)初始化*/
void USART1_QuickInit(uint32_t USART_BaudRate);

/*USART1_DMA初始化*/
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);
/* =========================== USART1 & DMA of end =========================== */

/* =========================== USART2 & DMA of begin =========================== */
#define USART2_TX_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define USART2_TX_GPIO_PORT         GPIOD
#define USART2_TX_Pin          	 	GPIO_Pin_5
#define USART2_TX_PINSOURCE			GPIO_PinSource5

#define USART2_RX_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define USART2_RX_GPIO_PORT         GPIOD
#define USART2_RX_Pin           	GPIO_Pin_6
#define USART2_RX_PINSOURCE			GPIO_PinSource6

#define USART2_RX_ADDR						(uint32_t)(&USART2->DR)	//串口1数据寄存器地址
#define USART2_RX_DMA_CHANNEL           	DMA_Channel_4		//DMA通道号
#define USART2_RX_DMA_STREAM           		DMA1_Stream5		//DMA数据流

/*USART2快速初始化*/
void USART2_QuickInit(uint32_t USART_BaudRate);

/*USART2_DMA初始化*/
void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize);
/* =========================== USART2 & DMA of end =========================== */

/* =========================== USART3 & DMA of begin =========================== */
#define USART3_TX_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define USART3_TX_GPIO_PORT         GPIOD
#define USART3_TX_Pin          	 	GPIO_Pin_8
#define USART3_TX_PINSOURCE			GPIO_PinSource8

#define USART3_RX_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define USART3_RX_GPIO_PORT         GPIOD
#define USART3_RX_Pin           	GPIO_Pin_9
#define USART3_RX_PINSOURCE			GPIO_PinSource9

#define USART3_RX_ADDR						(uint32_t)(&USART3->DR)	//串口3数据寄存器地址
#define USART3_RX_DMA_CHANNEL           	DMA_Channel_4		//DMA通道号
#define USART3_RX_DMA_STREAM           		DMA1_Stream1		//DMA数据流

/*USART3快速初始化*/
void USART3_QuickInit(uint32_t USART_BaudRate);

/*USART3_DMA初始化*/
void USART3_RXDMA_Config(uint32_t USART3_DMABuff_addr, uint32_t buffsize);
/* =========================== USART3 & DMA of end =========================== */

/* =========================== USART6 & DMA of begin =========================== */
#ifdef RMOfficialBoardA
#define USART6_TX_GPIO_CLK          RCC_AHB1Periph_GPIOG
#define USART6_TX_GPIO_PORT         GPIOG
#define USART6_TX_Pin          	 	GPIO_Pin_9
#define USART6_TX_PINSOURCE			GPIO_PinSource9

#define USART6_RX_GPIO_CLK          RCC_AHB1Periph_GPIOG
#define USART6_RX_GPIO_PORT         GPIOG
#define USART6_RX_Pin           	GPIO_Pin_14
#define USART6_RX_PINSOURCE			GPIO_PinSource14

#define USART6_RX_ADDR						(uint32_t)(&USART6->DR)	
#define USART6_RX_DMA_CHANNEL           	DMA_Channel_5		
#define USART6_RX_DMA_STREAM           		DMA2_Stream1	
#endif

#ifdef WildWolfOfficialBoard_F
#define USART6_TX_GPIO_CLK          RCC_AHB1Periph_GPIOC
#define USART6_TX_GPIO_PORT         GPIOC
#define USART6_TX_Pin          	 	GPIO_Pin_6
#define USART6_TX_PINSOURCE			GPIO_PinSource6

#define USART6_RX_GPIO_CLK          RCC_AHB1Periph_GPIOC
#define USART6_RX_GPIO_PORT         GPIOC
#define USART6_RX_Pin           	GPIO_Pin_7
#define USART6_RX_PINSOURCE			GPIO_PinSource7

#define USART6_RX_ADDR						(uint32_t)(&USART6->DR)	
#define USART6_RX_DMA_CHANNEL           	DMA_Channel_5		
#define USART6_RX_DMA_STREAM           		DMA2_Stream1	
#endif

/*USART6初始化*/
void USART6_QuickInit(uint32_t USART_BaudRate);

/*USART6_DMA初始化*/
void USART6_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize);
/* =========================== USART6 & DMA of end =========================== */


/* =========================== USART7 & DMA of begin =========================== */

/*USART7初始化*/
void USART7_QuickInit(uint32_t USART_BaudRate);

/*USART7_DMA初始化*/
void USART7_RXDMA_Config(uint32_t USART7_DMABuff_addr, uint32_t buffsize);

/* =========================== USART7 & DMA of end =========================== */


/* =========================== USART8 & DMA of begin =========================== */
#define USART8_TX_GPIO_CLK          RCC_AHB1Periph_GPIOE
#define USART8_TX_GPIO_PORT         GPIOE
#define USART8_TX_Pin          	 	GPIO_Pin_1
#define USART8_TX_PINSOURCE			GPIO_PinSource1

#define USART8_RX_GPIO_CLK          RCC_AHB1Periph_GPIOE
#define USART8_RX_GPIO_PORT         GPIOE
#define USART8_RX_Pin           	GPIO_Pin_0
#define USART8_RX_PINSOURCE			GPIO_PinSource0

#define USART8_RX_ADDR						(uint32_t)(&UART8->DR)
#define USART8_RX_DMA_CHANNEL           	DMA_Channel_5		
#define USART8_RX_DMA_STREAM           		DMA1_Stream6	
/* =========================== USART8 & DMA of end =========================== */


/*USART8初始化*/
void USART8_QuickInit(uint32_t USART_BaudRate);
/*USART8 DMA初始化*/
void USART8_RXDMA_Config(uint32_t USART8_DMABuff_addr, uint32_t buffsize);


/*ANO专用接收函数*/
void ANO_SendChar(USART_TypeDef* USARTx,char ch);

/*裁判系统发送函数*/
void USART_sendChar(USART_TypeDef* USARTx,char ch);

void USART3_sendChar(USART_TypeDef* USARTx,char ch);

void USART_ALLFSendChar(USART_TypeDef* USARTx,char*str);

#endif	// __BSP_USART_H
/*-----------------------------------file of end------------------------------*/


