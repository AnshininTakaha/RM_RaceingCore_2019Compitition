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
  |--FileName    : Task_CAN.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ���� & �                                                       
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

/*CAN���񴴽�*/
void CAN_TaskCreate(void);

/* ====================== CAN_ReceiverTask of begin =========================== */
/*CAN���ܱ���������ƾ��*/
extern TaskHandle_t CAN_ReceiveHandler;

/*CAN���ܱ����������*/
extern QueueHandle_t xCanReciver;

/*������*/
void CAN_ReceiveTask(void *pvParameters);
/* ====================== CAN_ReceiverTask of end =========================== */

/* =========================== CAN_SendTask of begin =========================== */
/*CAN���ͱ���������ƾ��*/
extern TaskHandle_t CAN_SendHandler;

/*CAN���ͱ����������*/
extern QueueHandle_t xCanSender;

/*������*/
void CAN_SendTask(void *pvParameters);
/* =========================== CAN_SendTask of end =========================== */



#endif	// __TASK_CAN_H
/*-----------------------------------file of end------------------------------*/


