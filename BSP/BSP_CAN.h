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
  |--FileName    : BSP_CAN.h                                                
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
#ifndef __BSP_CAN_H 
#define __BSP_CAN_H 

#include "stm32f4xx.h"

/* =========================== CAN1 of begin =========================== */
#define CAN1_RX_GPIO_CLK          	RCC_AHB1Periph_GPIOD
#define CAN1_RX_GPIO_PORT           GPIOD
#define CAN1_RX_Pin           		GPIO_Pin_0
#define CAN1_RX_PINSOURCE			GPIO_PinSource0

#define CAN1_TX_GPIO_CLK          	RCC_AHB1Periph_GPIOD
#define CAN1_TX_GPIO_PORT           GPIOD
#define CAN1_TX_Pin          	 	GPIO_Pin_1
#define CAN1_TX_PINSOURCE			GPIO_PinSource1


#define CAN1_SJW		CAN_SJW_1tq
#define CAN1_BS1		CAN_BS1_3tq
#define CAN1_BS2		CAN_BS2_5tq
#define CAN1_Prescaler	5
/* =========================== CAN1 of end =========================== */

///* =========================== CAN2 of begin =========================== */
//#define CAN2_RX_GPIO_CLK          	RCC_AHB1Periph_GPIOB
//#define CAN2_RX_GPIO_PORT           GPIOB
//#define CAN2_RX_Pin           		GPIO_Pin_12
//#define CAN2_RX_PINSOURCE			GPIO_PinSource12

//#define CAN2_TX_GPIO_CLK          	RCC_AHB1Periph_GPIOB
//#define CAN2_TX_GPIO_PORT           GPIOB
//#define CAN2_TX_Pin          	 	GPIO_Pin_13
//#define CAN2_TX_PINSOURCE			GPIO_PinSource13


//#define CAN2_SJW		CAN_SJW_1tq
//#define CAN2_BS1		CAN_BS1_3tq
//#define CAN2_BS2		CAN_BS2_5tq
//#define CAN2_Prescaler	6
///* =========================== CAN2 of end =========================== */


/* =========================== functions of begin =========================== */
/*CAN1初始化*/
void CAN1_QuickInit(void);

/*CAN2初始化*/
void CAN2_QuickInit(void);

/*把CAN的东西发送到对应的ID上*/
void CAN_sendData(CAN_TypeDef* CANx, uint8_t id_type, uint32_t id, \
uint8_t data[8]);
/* =========================== functions of end =========================== */


#endif	// __BSP_CAN_H
/*-----------------------------------file of end------------------------------*/


