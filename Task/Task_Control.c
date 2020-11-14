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
  |--FileName    : Task_Control.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ���� & �                                                     
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
/*Aiming������ƾ��*/
static TaskHandle_t Aiming_Handler = NULL;

/*������ƶ���*/
QueueHandle_t AimingRxQueue = NULL;

/*������ƺ���*/
void Aiming_Task(void *pvParameters);
/* =========================== Aiming of end =========================== */

/* =========================== ANO of begin =========================== */
/*ANO������ƾ��*/
static TaskHandle_t ANO_Handler = NULL;

/*ANO������ƺ���*/
void ANO_Task(void *pvParameters);

/*DS������ƾ��*/
static TaskHandle_t DS_Handler = NULL;

/*DS������ƺ���*/
extern void DataScopeTask(void *Parameters);
/* =========================== ANO of end =========================== */

/* =========================== DeviceFlash of begin =========================== */
/*֡��ˢ�¿��ƾ��*/
static TaskHandle_t Device_FlashHandler = NULL;

/*֡��ˢ�¿��ƺ���*/
void Devices_Task(void *pvParameters);
/* =========================== DeviceFlash of end =========================== */

/* =========================== DeviceFlash of begin =========================== */
/*֡��ˢ�¿��ƾ��*/
static TaskHandle_t Control_Handler = NULL;

/*֡��ˢ�¿��ƺ���*/
void Control_Task(void *pvParameters);
/* =========================== DeviceFlash of end =========================== */

/* =========================== PCControl of begin =========================== */
/*��λ�任���*/
static TaskHandle_t PC_Handler = NULL;

/*��λ�任���ƺ������ƺ���*/
void PC_ControlTask(void *pvParameters);
/* =========================== PCControl of end =========================== */

/* =========================== Judgement of begin =========================== */
/*���������ݷ���*/
static TaskHandle_t Judgement_Handler = NULL;

/*���������ݷ��Ϳ��ƺ���*/
void Judgement_Task(void *pvParameters);
/* =========================== Judgement of end =========================== */

/* =========================== Judgement of begin =========================== */
/*���������ݷ���*/
static TaskHandle_t Single_Handler = NULL;

/*���������ݷ��Ϳ��ƺ���*/
void Single_Task(void *pvParameters);
/* =========================== Judgement of end =========================== */
/**
  * @Data    2019-03-24 13:07
  * @brief   ���������ʼ��
  * @param   void
  * @retval  void
  */
float TimeCounter = 0;
void Control_TaskCreate(void)
{
		
    /*������д������д���*/
    AimingRxQueue = xQueueCreate(VISION_BUFFSIZE,(VISION_BUFFSIZE)*sizeof(uint8_t));
//		AimingRxQueue = xQueueCreate(VISION_NEW_BUFFERSIZE,(VISION_NEW_BUFFERSIZE)*sizeof(uint8_t));
    /*�������ݴ�������*/
    xTaskCreate(Aiming_Task,           /* ������  */        
                "Devices_Task",         /* ������    */      
                300,       			      /* ����ջ��С*/  
                NULL,                 /* �������  */    
                3,       			        /* �������ȼ�*/
                &Aiming_Handler);   /* ������  */
    #if ANOUse
    /*ANO�����������*/
//    xTaskCreate(ANO_Task,           /* ������  */        
//		 						"ANO_Task",         /* ������    */      
//		 						128,       			      /* ����ջ��С*/  
//		 						NULL,                 /* �������  */    
//		 						2,       			        /* �������ȼ�*/
//		 						&ANO_Handler);   /* ������  */
    #endif
	
		xTaskCreate(DataScopeTask,           /* ������  */        
		 						"DataScopeTask",         /* ������    */      
		 						300,       			      /* ����ջ��С*/  
		 						NULL,                 /* �������  */    
		 						2,       			        /* �������ȼ�*/
		 						&DS_Handler);   /* ������  */
								
    /*֡��ˢ�¿�������*/
    xTaskCreate(Devices_Task,           /* ������  */        
				        "Devices_Task",         /* ������    */      
				        300,       			      /* ����ջ��С*/  
				        NULL,                 /* �������  */    
				        4,       			        /* �������ȼ�*/
				        &Device_FlashHandler);   /* ������  */

		/*��������������*/
		xTaskCreate(Control_Task,           /* ������  */        
				        "Control_Task",         /* ������    */      
				        5000,       			      /* ����ջ��С*/  
				        NULL,                 /* �������  */    
				        3,       			        /* �������ȼ�*/
				        &Control_Handler);   /* ������  */
		/*��λ�任����*/
		xTaskCreate(PC_ControlTask,           /* ������  */        
				        "PC_ControlTask",         /* ������    */      
				        300,       			      /* ����ջ��С*/  
				        NULL,                 /* �������  */    
				        3,       			        /* �������ȼ�*/
				        &PC_Handler);   /* ������  */
								
		xTaskCreate(Judgement_Task,           /* ������  */        
				        "Judgement_Task",         /* ������    */      
				        300,       			      /* ����ջ��С*/  
				        NULL,                 /* �������  */    
				        3,       			        /* �������ȼ�*/
				        &Judgement_Handler);   /* ������  */
								
		xTaskCreate(Single_Task,           /* ������  */        
				        "Single_Task",         /* ������    */      
				        300,       			      /* ����ջ��С*/  
				        NULL,                 /* �������  */    
				        3,       			        /* �������ȼ�*/
				        &Single_Handler);   /* ������  */

}

/**
  * @Data    2019-03-26 17:44
  * @brief   ����������
  * @param   void *pvParameters
  * @retval  void
  */


void Aiming_Task(void *pvParameters)
{
  /*Aim���ݴ�����*/
  uint8_t AimingRxBuffer[VISION_BUFFSIZE];
	uint8_t NewRxBuffer[VISION_NEW_BUFFERSIZE];
  /*����ʱ��Ƭ�������*/
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
  * @brief   ANO������
  * @param   void *pvParameters
  * @retval  void
  */

void ANO_Task(void *pvParameters)
{
  /*����ʱ��Ƭ�������*/
  portTickType CurrentControlTick = 0;
  while(1)
	{
      ANO_Send_Data_V1(0,ext_power_heat_data.chassis_power_buffer,0,0);
      vTaskDelayUntil(&CurrentControlTick,10 / portTICK_RATE_MS);
	}

}


/**
  * @Data    2019-03-26 21:20
  * @brief   ֡��ˢ�¿���������
  * @param   void *pvParameters
  * @retval  void
  */
void Devices_Task(void *pvParameters)
{
  /*����ʱ��Ƭ�������*/
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
  * @brief   ������ƺ���
  * @param   void *pvParameters
  * @retval  void
  */
void Control_Task(void *pvParameters)
{
	 /*����ʱ��Ƭ�������*/
  portTickType CurrentControlTick = 0;
  while(1)
  {

			/*���еĿ��Ƶĳ���д������*/
			TaskState.TaskControl_State++;
			/*��ˮ����ʾ*/
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
  * @brief   ��λ�жϿ��ƺ���
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
	* @brief   �������ݷ��ͺ���
  * @param   void *pvParameters
  * @retval  void
  */

uint16_t BulletNumberOutput = 0;
void Judgement_Task(void *pvParameters)
{
		portTickType CurrentControlTick = 0;
		/*״̬��־λ*/
		int Search_Type = 0;
		/*�ӵ���������*/
		uint16_t BulletNumber = 0;
		while(1)
		{
				/*״̬λ�ñ��*/
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
				
				
				/*�����ϵͳ��������*/
				/*����ӵ���ʣ��*/
				/*����ʣ��*/
				/*Ŀǰ״̬��־λ*/
				Judge_sendPC(BulletNumberOutput,\
										SCCM.receiveData.cap_level,\
										Search_Type);
				
				vTaskDelayUntil(&CurrentControlTick,150 / portTICK_RATE_MS);
		}
}


/**
  * @Data    2019-03-27 10:37
	* @brief   �źŵ���ʾ����
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


