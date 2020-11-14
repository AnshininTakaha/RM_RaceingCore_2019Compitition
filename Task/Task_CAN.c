/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,���� & �,                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Task_CAN.c                                              
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
#include "Task_CAN.h" 

#include "Task_Control.h"
#include "Driver_Analysis.h"
#include "Driver_Flash.h"

/* ====================== CAN_ReceiverTask of begin =========================== */
/*CAN���ܱ���������ƾ��*/
static TaskHandle_t CAN_ReceiveHandler = NULL;

/*CAN���ܱ����������*/
QueueHandle_t xCanReciver = NULL;

/*������*/
void CAN_ReceiveTask(void *pvParameters);
/* ====================== CAN_ReceiverTask of end =========================== */

/* =========================== CAN_SendTask of begin =========================== */
/*CAN���ͱ���������ƾ��*/
static TaskHandle_t CAN_SendHandler = NULL;

/*CAN���ͱ����������*/
QueueHandle_t xCanSender = NULL;

/*������*/
void CAN_SendTask(void *pvParameters);
/* =========================== CAN_SendTask of end =========================== */


/**
  * @Data    2019-03-23 15:48
  * @brief   CAN���񴴽�
  * @param   void
  * @retval  void
  */
void CAN_TaskCreate(void)
{
    /*CAN���ܶ��д���*/
    xCanReciver = xQueueCreate(40,sizeof(CAN_RXPrarm_t));
	
		/*���Ͷ��д���*/
		xCanSender = xQueueCreate(40,sizeof(CAN_TXPrarm_t));
	
		/*CAN�������񴴽�*/
    xTaskCreate(CAN_ReceiveTask,           /* ������  */        
								"CAN_ReceiveTask",         /* ������    */      
								128,       			      /* ����ջ��С*/  
								NULL,                 /* �������  */    
									4,       			        /* �������ȼ�*/
								&CAN_ReceiveHandler);   /* ������  */
	
		xTaskCreate(CAN_SendTask,           /* ������  */        
								"CAN_ReceiveTask",         /* ������    */      
								128,       			      /* ����ջ��С*/  
								NULL,                 /* �������  */    
									4,       			        /* �������ȼ�*/
								&CAN_SendHandler);   /* ������  */
	
		
}

/**
  * @Data    2019-03-23 15:56
  * @brief   CAN����������
  * @param   void *pvParameters
  * @retval  void
  */
void CAN_ReceiveTask(void *pvParameters)
{
		CAN_RXPrarm_t RxMessagePrarm;
    while(1)
    {
				/*������CAN1����CAN2�����ݶ���������ȥ*/
        xQueueReceive(xCanReciver,&RxMessagePrarm,portMAX_DELAY);
			
				TaskState.CANRecevie_State++;
				/*��ˮ����ʾ*/
				if(TaskState.CANRecevie_State % 20 == 0)
				{
						GPIO_ToggleBits(GPIOE,GPIO_Pin_10);
				}
				
				
				if(RxMessagePrarm.CANSet == 1)
				{
						CAN_Analysis(RxMessagePrarm.RxMessage);
				}
				if(RxMessagePrarm.CANSet == 2)
				{
						CAN_Analysis(RxMessagePrarm.RxMessage);
				}				
    }
}

/**
  * @Data    2019-03-23 15:56
  * @brief   CAN����������
  * @param   void *pvParameters
  * @retval  void
  */
/*���Ҫʹ��CAN2�Ļ����⿪����*/
void CAN_SendTask(void *pvParameters)
{
		CAN_TXPrarm_t TxMessagePrarm;
    while(1)
    {
			
			xQueueReceive(xCanSender,&TxMessagePrarm,portMAX_DELAY);
			TaskState.CANSender_State++;
			/*��ˮ����ʾ*/
			if(TaskState.CANSender_State % 10 == 0)
			{
					GPIO_ToggleBits(GPIOE,GPIO_Pin_11);
			}
			
			if(TxMessagePrarm.CANSet == 1)
			{
					CAN_Transmit(CAN1,&TxMessagePrarm.TxMessage);
			}
			if(TxMessagePrarm.CANSet == 2)
			{
					CAN_Transmit(CAN2,&TxMessagePrarm.TxMessage);
			}
			
    }
}
/*-----------------------------------file of end------------------------------*/


