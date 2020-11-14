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
  |--FileName    : Task_CAN.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无 & 璨                                                       
  |--Date        : 2019-03-23               
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
#ifndef __TASK_CAN_H 
#define __TASK_CAN_H 


#include "stm32f4xx.h"
#include "RTOSinclude.h"

typedef struct
{
		uint8_t CANSet;
		CanTxMsg TxMessage;
}CAN_TXPrarm_t;

typedef struct
{
		uint8_t CANSet;
		CanRxMsg RxMessage;
}CAN_RXPrarm_t;

/*CAN任务创建*/
void CAN_TaskCreate(void);

/* ====================== CAN_ReceiverTask of begin =========================== */
/*CAN接受报文任务控制句柄*/
extern TaskHandle_t CAN_ReceiveHandler;

/*CAN接受报文任务队列*/
extern QueueHandle_t xCanReciver;

/*任务函数*/
void CAN_ReceiveTask(void *pvParameters);
/* ====================== CAN_ReceiverTask of end =========================== */

/* =========================== CAN_SendTask of begin =========================== */
/*CAN发送报文任务控制句柄*/
extern TaskHandle_t CAN_SendHandler;

/*CAN发送报文任务队列*/
extern QueueHandle_t xCanSender;

/*任务函数*/
void CAN_SendTask(void *pvParameters);
/* =========================== CAN_SendTask of end =========================== */



#endif	// __TASK_CAN_H
/*-----------------------------------file of end------------------------------*/


