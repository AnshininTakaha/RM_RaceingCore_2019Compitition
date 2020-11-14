/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,���� & �,                         |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)      |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Task_Init.c                                              
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
#include "Task_Init.h" 

#include "Task_CAN.h"
#include "Task_Control.h"

#include "Control_Cloud.h"
#include "Control_PC.h"

//#include "Driver_Power.h"

#include "BSP_Init.h"

/*��ʼ������*/
TaskHandle_t StartTaskHandler = NULL;

/**
  * @Data    2019-02-18 20:50
  * @brief   ��ʼ������
  * @param   void *pvParameters
  * @retval  void
  */
void TaskStart(void *pvParameters)
{
	/*�����ٽ���*/
	taskENTER_CRITICAL();
	
	/*�ײ����ݳ�ʼ��*/
	Devices_Init();
	
	/*PC���Ƴ�ʼ��*/
	PC_Init();
	
	/*��ʱ��֤IMU�����ȶ�*/
  vTaskDelay(2000 / portTICK_RATE_MS);
	
	/*����CAN����*/
	CAN_TaskCreate();
	
	/*������������*/
	Control_TaskCreate();
	
	/*�����ʼ����ʱ�򲻶�*/
	LIDSwitch(1);
	/*���ʳ�ʼ��*/
	
	
	/*ɾ����ʼ������*/
  vTaskDelete(StartTaskHandler);
	
	/*�˳��ٽ���*/
  taskEXIT_CRITICAL();
	
	
	
	
	
}

/*-----------------------------------file of end------------------------------*/


