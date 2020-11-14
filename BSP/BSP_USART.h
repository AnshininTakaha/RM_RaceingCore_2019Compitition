/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,���� & 貣�                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : BSP_USART.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ���� & �                                                       
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


/*����һ���ַ�*/
void USART_SendByte(USART_TypeDef*USARTx,uint8_t ch);

/*����һ���ַ���*/
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

/* USART1(DR16)��ʼ��*/
void USART1_QuickInit(uint32_t USART_BaudRate);

/*USART1_DMA��ʼ��*/
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

#define USART2_RX_ADDR						(uint32_t)(&USART2->DR)	//����1���ݼĴ�����ַ
#define USART2_RX_DMA_CHANNEL           	DMA_Channel_4		//DMAͨ����
#define USART2_RX_DMA_STREAM           		DMA1_Stream5		//DMA������

/*USART2���ٳ�ʼ��*/
void USART2_QuickInit(uint32_t USART_BaudRate);

/*USART2_DMA��ʼ��*/
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

#define USART3_RX_ADDR						(uint32_t)(&USART3->DR)	//����3���ݼĴ�����ַ
#define USART3_RX_DMA_CHANNEL           	DMA_Channel_4		//DMAͨ����
#define USART3_RX_DMA_STREAM           		DMA1_Stream1		//DMA������

/*USART3���ٳ�ʼ��*/
void USART3_QuickInit(uint32_t USART_BaudRate);

/*USART3_DMA��ʼ��*/
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

/*USART6��ʼ��*/
void USART6_QuickInit(uint32_t USART_BaudRate);

/*USART6_DMA��ʼ��*/
void USART6_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize);
/* =========================== USART6 & DMA of end =========================== */


/* =========================== USART7 & DMA of begin =========================== */

/*USART7��ʼ��*/
void USART7_QuickInit(uint32_t USART_BaudRate);

/*USART7_DMA��ʼ��*/
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


/*USART8��ʼ��*/
void USART8_QuickInit(uint32_t USART_BaudRate);
/*USART8 DMA��ʼ��*/
void USART8_RXDMA_Config(uint32_t USART8_DMABuff_addr, uint32_t buffsize);


/*ANOר�ý��պ���*/
void ANO_SendChar(USART_TypeDef* USARTx,char ch);

/*����ϵͳ���ͺ���*/
void USART_sendChar(USART_TypeDef* USARTx,char ch);

void USART3_sendChar(USART_TypeDef* USARTx,char ch);

void USART_ALLFSendChar(USART_TypeDef* USARTx,char*str);

#endif	// __BSP_USART_H
/*-----------------------------------file of end------------------------------*/


