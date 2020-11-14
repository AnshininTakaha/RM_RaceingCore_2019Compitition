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
  |--FileName    : Task_Control.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无 & 璨                                                     
  |--Date        : 2019-03-24             
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
#include "Task_Control.h" 


#include "Control_Chassis.h"
#include "Control_Cloud.h"
#include "Control_Shoot.h"
#include "Control_PC.h"

#include "Driver_SCCM.h"
#include "Driver_Judge.h"
#include "Driver_ANO.h"
#include "Driver_IMU.h"
#include "Driver_Filter.h"
#include "Driver_Aiming.h"
#include "Driver_Flash.h"
#include "Driver_Aiming.h"
#include "Driver_CRC.h"
#include "Driver_MiniBalanceShowData.h"

#include "BSP_Init.h"

/* =========================== Aiming of begin =========================== */
/*Aiming自瞄控制句柄*/
static TaskHandle_t Aiming_Handler = NULL;

/*自瞄控制队列*/
QueueHandle_t AimingRxQueue = NULL;

/*自瞄控制函数*/
void Aiming_Task(void *pvParameters);
/* =========================== Aiming of end =========================== */

/* =========================== ANO of begin =========================== */
/*ANO任务控制句柄*/
static TaskHandle_t ANO_Handler = NULL;

/*ANO任务控制函数*/
void ANO_Task(void *pvParameters);

/*DS任务控制句柄*/
static TaskHandle_t DS_Handler = NULL;

/*DS任务控制函数*/
extern void DataScopeTask(void *Parameters);
/* =========================== ANO of end =========================== */

/* =========================== DeviceFlash of begin =========================== */
/*帧率刷新控制句柄*/
static TaskHandle_t Device_FlashHandler = NULL;

/*帧率刷新控制函数*/
void Devices_Task(void *pvParameters);
/* =========================== DeviceFlash of end =========================== */

/* =========================== DeviceFlash of begin =========================== */
/*帧率刷新控制句柄*/
static TaskHandle_t Control_Handler = NULL;

/*帧率刷新控制函数*/
void Control_Task(void *pvParameters);
/* =========================== DeviceFlash of end =========================== */

/* =========================== PCControl of begin =========================== */
/*键位变换句柄*/
static TaskHandle_t PC_Handler = NULL;

/*键位变换控制函数控制函数*/
void PC_ControlTask(void *pvParameters);
/* =========================== PCControl of end =========================== */

/* =========================== Judgement of begin =========================== */
/*服务器数据发送*/
static TaskHandle_t Judgement_Handler = NULL;

/*服务器数据发送控制函数*/
void Judgement_Task(void *pvParameters);
/* =========================== Judgement of end =========================== */

/* =========================== Judgement of begin =========================== */
/*服务器数据发送*/
static TaskHandle_t Single_Handler = NULL;

/*服务器数据发送控制函数*/
void Single_Task(void *pvParameters);
/* =========================== Judgement of end =========================== */
/**
  * @Data    2019-03-24 13:07
  * @brief   控制任务初始化
  * @param   void
  * @retval  void
  */
float TimeCounter = 0;
void Control_TaskCreate(void)
{
		
    /*自瞄队列创建队列创建*/
    AimingRxQueue = xQueueCreate(VISION_BUFFSIZE,(VISION_BUFFSIZE)*sizeof(uint8_t));
//		AimingRxQueue = xQueueCreate(VISION_NEW_BUFFERSIZE,(VISION_NEW_BUFFERSIZE)*sizeof(uint8_t));
    /*自瞄数据处理任务*/
    xTaskCreate(Aiming_Task,           /* 任务函数  */        
                "Devices_Task",         /* 任务名    */      
                300,       			      /* 任务栈大小*/  
                NULL,                 /* 任务参数  */    
                3,       			        /* 任务优先级*/
                &Aiming_Handler);   /* 任务句柄  */
    #if ANOUse
    /*ANO检测数据任务*/
//    xTaskCreate(ANO_Task,           /* 任务函数  */        
//		 						"ANO_Task",         /* 任务名    */      
//		 						128,       			      /* 任务栈大小*/  
//		 						NULL,                 /* 任务参数  */    
//		 						2,       			        /* 任务优先级*/
//		 						&ANO_Handler);   /* 任务句柄  */
    #endif
	
		xTaskCreate(DataScopeTask,           /* 任务函数  */        
		 						"DataScopeTask",         /* 任务名    */      
		 						300,       			      /* 任务栈大小*/  
		 						NULL,                 /* 任务参数  */    
		 						2,       			        /* 任务优先级*/
		 						&DS_Handler);   /* 任务句柄  */
								
    /*帧率刷新控制任务*/
    xTaskCreate(Devices_Task,           /* 任务函数  */        
				        "Devices_Task",         /* 任务名    */      
				        300,       			      /* 任务栈大小*/  
				        NULL,                 /* 任务参数  */    
				        4,       			        /* 任务优先级*/
				        &Device_FlashHandler);   /* 任务句柄  */

		/*控制任务处理任务*/
		xTaskCreate(Control_Task,           /* 任务函数  */        
				        "Control_Task",         /* 任务名    */      
				        5000,       			      /* 任务栈大小*/  
				        NULL,                 /* 任务参数  */    
				        3,       			        /* 任务优先级*/
				        &Control_Handler);   /* 任务句柄  */
		/*键位变换任务*/
		xTaskCreate(PC_ControlTask,           /* 任务函数  */        
				        "PC_ControlTask",         /* 任务名    */      
				        300,       			      /* 任务栈大小*/  
				        NULL,                 /* 任务参数  */    
				        3,       			        /* 任务优先级*/
				        &PC_Handler);   /* 任务句柄  */
								
		xTaskCreate(Judgement_Task,           /* 任务函数  */        
				        "Judgement_Task",         /* 任务名    */      
				        300,       			      /* 任务栈大小*/  
				        NULL,                 /* 任务参数  */    
				        3,       			        /* 任务优先级*/
				        &Judgement_Handler);   /* 任务句柄  */
								
		xTaskCreate(Single_Task,           /* 任务函数  */        
				        "Single_Task",         /* 任务名    */      
				        300,       			      /* 任务栈大小*/  
				        NULL,                 /* 任务参数  */    
				        3,       			        /* 任务优先级*/
				        &Single_Handler);   /* 任务句柄  */

}

/**
  * @Data    2019-03-26 17:44
  * @brief   自瞄任务函数
  * @param   void *pvParameters
  * @retval  void
  */


void Aiming_Task(void *pvParameters)
{
  /*Aim数据储存体*/
  uint8_t AimingRxBuffer[VISION_BUFFSIZE];
	uint8_t NewRxBuffer[VISION_NEW_BUFFERSIZE];
  /*创建时间片计算变量*/
  portTickType CurrentControlTick = 0;
	while(1)
	{
      xQueueReceive(AimingRxQueue,&AimingRxBuffer,portMAX_DELAY);
			AimingControl(AimingRxBuffer);
//			xQueueReceive(AimingRxQueue,&NewRxBuffer,portMAX_DELAY);
//			NEWAimingControl(NewRxBuffer);
      
	}
}


/**
  * @Data    2019-03-26 17:45
  * @brief   ANO任务函数
  * @param   void *pvParameters
  * @retval  void
  */

void ANO_Task(void *pvParameters)
{
  /*创建时间片计算变量*/
  portTickType CurrentControlTick = 0;
  while(1)
	{
      ANO_Send_Data_V1(0,ext_power_heat_data.chassis_power_buffer,0,0);
      vTaskDelayUntil(&CurrentControlTick,10 / portTICK_RATE_MS);
	}

}


/**
  * @Data    2019-03-26 21:20
  * @brief   帧率刷新控制任务函数
  * @param   void *pvParameters
  * @retval  void
  */
void Devices_Task(void *pvParameters)
{
  /*创建时间片计算变量*/
  portTickType CurrentControlTick = 0;
  while(1)
  {
			DeviceFlash();
//			TimeCounter++;
			vTaskDelayUntil(&CurrentControlTick,200 / portTICK_RATE_MS);
  }
}

/**
  * @Data    2019-03-27 10:37
  * @brief   任务控制函数
  * @param   void *pvParameters
  * @retval  void
  */
void Control_Task(void *pvParameters)
{
	 /*创建时间片计算变量*/
  portTickType CurrentControlTick = 0;
  while(1)
  {

			/*所有的控制的程序都写在这里*/
			TaskState.TaskControl_State++;
			/*流水灯提示*/
			if(TaskState.TaskControl_State % 3 == 0)
			{
					GPIO_ToggleBits(GPIOE,GPIO_Pin_9);
			}
			
			Chassis_Judgement(DR16.rc.s_left);
			Cloud_Judgement(DR16.rc.s_left);
			Shoot_Judgement(DR16.rc.s_left);
//			Judge_sendPC(10,\
//										0,\
//										0);
			vTaskDelayUntil(&CurrentControlTick,10 / portTICK_RATE_MS);
	}
}


/**
  * @Data    2019-03-27 10:37
  * @brief   键位判断控制函数
  * @param   void *pvParameters
  * @retval  void
  */
float AUTO = 0;
float BIG = 0; 
void PC_ControlTask(void *pvParameters)
{
		portTickType CurrentControlTick = 0;
		while(1)
		{
				if(DR16.rc.s_left == 1)
				{
						PCControl_Process();
				}
				else
				{
						if(DR16.rc.s_right == 2)
						{
								USART_ALLFSendChar(USART6,"S211E");
						}
						if(DR16.rc.s_right == 3)
						{
								USART_ALLFSendChar(USART6,"S111E");
						}
				}
				TimeCounter++;
				vTaskDelayUntil(&CurrentControlTick,5 / portTICK_RATE_MS);
		}
}


/**
  * @Data    2019-03-27 10:37
	* @brief   裁判数据发送函数
  * @param   void *pvParameters
  * @retval  void
  */

uint16_t BulletNumberOutput = 0;
void Judgement_Task(void *pvParameters)
{
		portTickType CurrentControlTick = 0;
		/*状态标志位*/
		int Search_Type = 0;
		/*子弹数量计算*/
		uint16_t BulletNumber = 0;
		while(1)
		{
				/*状态位置变更*/
				if(SEDV_BIGER == 0 && SECV_BIGModule == 0)
				{
						Search_Type = 0;
				}
				else if(SEDV_BIGER == 1 && SECV_BIGModule == 0)
				{
						Search_Type = 1;
				}
				else if(SEDV_BIGER == 0 && SECV_BIGModule == 1)
				{
						Search_Type = 2;		
				}
				else
				{
						
				}
				
				
				/*向裁判系统发送数据*/
				/*射击子弹数剩余*/
				/*电容剩余*/
				/*目前状态标志位*/
				Judge_sendPC(BulletNumberOutput,\
										SCCM.receiveData.cap_level,\
										Search_Type);
				
				vTaskDelayUntil(&CurrentControlTick,150 / portTICK_RATE_MS);
		}
}


/**
  * @Data    2019-03-27 10:37
	* @brief   信号灯提示处理
  * @param   void *pvParameters
  * @retval  void
  */
void Single_Task(void *pvParameters)
{
		portTickType CurrentControlTick = 0;
		while(1)
		{
				SetLedSingle();
				vTaskDelayUntil(&CurrentControlTick,10 / portTICK_RATE_MS);
		}
}



/*-----------------------------------file of end------------------------------*/


