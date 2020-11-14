/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无 & 璨,                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Task_CAN.c                                              
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
#include "Task_CAN.h" 

#include "Task_Control.h"
#include "Driver_Analysis.h"
#include "Driver_Flash.h"

/* ====================== CAN_ReceiverTask of begin =========================== */
/*CAN接受报文任务控制句柄*/
static TaskHandle_t CAN_ReceiveHandler = NULL;

/*CAN接受报文任务队列*/
QueueHandle_t xCanReciver = NULL;

/*任务函数*/
void CAN_ReceiveTask(void *pvParameters);
/* ====================== CAN_ReceiverTask of end =========================== */

/* =========================== CAN_SendTask of begin =========================== */
/*CAN发送报文任务控制句柄*/
static TaskHandle_t CAN_SendHandler = NULL;

/*CAN发送报文任务队列*/
QueueHandle_t xCanSender = NULL;

/*任务函数*/
void CAN_SendTask(void *pvParameters);
/* =========================== CAN_SendTask of end =========================== */


/**
  * @Data    2019-03-23 15:48
  * @brief   CAN任务创建
  * @param   void
  * @retval  void
  */
void CAN_TaskCreate(void)
{
    /*CAN接受队列创建*/
    xCanReciver = xQueueCreate(40,sizeof(CAN_RXPrarm_t));
	
		/*发送队列创建*/
		xCanSender = xQueueCreate(40,sizeof(CAN_TXPrarm_t));
	
		/*CAN接受任务创建*/
    xTaskCreate(CAN_ReceiveTask,           /* 任务函数  */        
								"CAN_ReceiveTask",         /* 任务名    */      
								128,       			      /* 任务栈大小*/  
								NULL,                 /* 任务参数  */    
									4,       			        /* 任务优先级*/
								&CAN_ReceiveHandler);   /* 任务句柄  */
	
		xTaskCreate(CAN_SendTask,           /* 任务函数  */        
								"CAN_ReceiveTask",         /* 任务名    */      
								128,       			      /* 任务栈大小*/  
								NULL,                 /* 任务参数  */    
									4,       			        /* 任务优先级*/
								&CAN_SendHandler);   /* 任务句柄  */
	
		
}

/**
  * @Data    2019-03-23 15:56
  * @brief   CAN接受任务函数
  * @param   void *pvParameters
  * @retval  void
  */
void CAN_ReceiveTask(void *pvParameters)
{
		CAN_RXPrarm_t RxMessagePrarm;
    while(1)
    {
				/*无论是CAN1还是CAN2的数据都发到这里去*/
        xQueueReceive(xCanReciver,&RxMessagePrarm,portMAX_DELAY);
			
				TaskState.CANRecevie_State++;
				/*流水灯提示*/
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
  * @brief   CAN发送任务函数
  * @param   void *pvParameters
  * @retval  void
  */
/*如果要使用CAN2的话另外开队列*/
void CAN_SendTask(void *pvParameters)
{
		CAN_TXPrarm_t TxMessagePrarm;
    while(1)
    {
			
			xQueueReceive(xCanSender,&TxMessagePrarm,portMAX_DELAY);
			TaskState.CANSender_State++;
			/*流水灯提示*/
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


