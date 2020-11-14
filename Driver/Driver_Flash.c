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
  |--FileName    : Driver_Flash.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无 & 璨                                                     
  |--Date        : 2019-03-26             
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
#include "Driver_Flash.h" 


#include "Driver_Galvanoment.h"
#include "Driver_Analysis.h"
#include "Driver_DR16.h"
#include "Driver_IMU.h"
#include "Driver_Aiming.h"
#include "Driver_Judge.h"
#include "Driver_SCCM.h"
#include "Switch.h"
TaskState_t TaskState;
/**
  * @Data    2019-02-20 19:54
  * @brief   帧率刷新
  * @param   void
  * @retval  void
  */
	/*新版LED灯处理*/
	//PB4：当所有的底盘轮子链接正常的时候闪灯
	//PB5: 当所有的云台轮子链接正常的时候闪灯
	//PE9：当所有的拨弹电机正常的时候闪灯
	//PE10：当DR16遥控器正常的时候闪灯
	//PE11：当IMU陀螺仪正常的时候闪灯
	//PE12：当电流计正常的时候闪灯
	//PE13：当超级电容正常运行的时候闪灯
	//PE14：
	//PE15：当裁判系统正常的时候闪灯


void DeviceFlash(void)
{		

    /* =========================== RM3508 of begin =========================== */
    for(int i =0;i<4;i++)
		{
			if(RM3508s[i].UpdateFrame < 5)
			{
				RM3508s[i].OFFLINE_SET = 1;
				
			}
			else
			{
				RM3508s[i].OFFLINE_SET = 0;
			}
			
			RM3508s[i].UpdateFrame = 0;
		}
		

    /* =========================== RM3508 of end =========================== */
    
	/* =========================== RM6623 of begin =========================== */
    for(int j = 0;j<2;j++)
		{
			if(RM6020s[j].UpdateFrame < 5)
			{
				RM6020s[j].OFFLINE_SET = 1;
		
			}
			else
			{
					RM6020s[j].OFFLINE_SET = 0;
			}
			RM6020s[j].UpdateFrame = 0;
		}
		
    /* =========================== RM6623 of end =========================== */
    
    /* =========================== RM2006 of begin =========================== */
    for(int k = 0;k < 1;k++)
		{
			if(RM2006s[k].UpdateFrame < 5)
			{
				RM2006s[k].OFFLINE_SET = 1;
			}
			else
			{
				RM2006s[k].OFFLINE_SET = 0;
			}
			RM2006s[k].UpdateFrame =0;
		}
		
    /* =========================== RM2006 of end =========================== */
    
    /* =========================== DR16 of begin =========================== */
    if(DR16.UpdateFrame < 5)
		{
			DR16.OFFLINE_SET = 1;
		}
		else
		{
			DR16.OFFLINE_SET = 0;
		}
		DR16.UpdateFrame = 0;
    /* =========================== DR16 of end =========================== */
    
    /* =========================== IMU of begin =========================== */
    /*云台陀螺仪*/
		 if(IMU_Cloud.UpdateFrame < 5)
		 {
				IMU_Cloud.OFFLINE_SET = 1;
		 }
		 else
		 {
				IMU_Cloud.OFFLINE_SET = 0;
		 }
		 IMU_Cloud.UpdateFrame = 0;
			
		 
			/*底盘陀螺仪*/
		if(IMU_Chassis.UpdateFrame < 5)
		{
				IMU_Chassis.OFFLINE_SET = 1;
				
		}
		else
		{
				IMU_Chassis.OFFLINE_SET = 0;
		}
		IMU_Chassis.UpdateFrame =0;
    /* =========================== IMU of end =========================== */

		/* =========================== Galvanometer of begin =========================== */
		//电流计
		if(Galvanometer.UpdateFrame < 1)
		{
			Galvanometer.OFFLINE_SET = 1;
//			GPIO_SetBits(GPIOE,GPIO_Pin_12);
		}
		else
		{
			Galvanometer.OFFLINE_SET = 0;
		}
		Galvanometer.UpdateFrame = 0;
		/* =========================== Galvanometer of end =========================== */
	
		/* =========================== Judge of begin =========================== */
		if(Judgement_Check.UpdateFrame < 2)
		{
				Judgement_Check.OFFLINE_SET = 1;
		}
		else
		{
				Judgement_Check.OFFLINE_SET = 0;
		}
		
		Judgement_Check.UpdateFrame = 0;
		/* =========================== Judge of end =========================== */
		
		/* =========================== SCCM of begin =========================== */
		if(SCCM.UpdateFrame < 5)
		{
				SCCM.OFFLINE_SET = 1;

		}
		else
		{
				SCCM.OFFLINE_SET = 0;

		}
		SCCM.UpdateFrame = 0;
		/* =========================== SCCM of end =========================== */
		
		/* =========================== CV of begin =========================== */
		/*帧率非常非常非常的低*/
		if(CV.UpdateFrame <= 0)
		{
				CV.OFFLINE_SET = 1;

		}
		else
		{
				CV.OFFLINE_SET = 0;

		}
		CV.UpdateFrame = 0;
		/* =========================== CV of end =========================== */
		if(TaskState.TaskControl_State < 2)
		{
				TaskState.TaskControl_OfflineSet = 1;
		}
		else
		{
				TaskState.TaskControl_OfflineSet = 0;
		}
		TaskState.TaskControl_State = 0;
		
		
		if(TaskState.CANRecevie_State < 5)
		{
				TaskState.CANRecevie_OfflineSet = 1;
		}
		else
		{
				TaskState.CANRecevie_OfflineSet = 0;
		}
		TaskState.CANRecevie_State = 0;
		
		
		if(TaskState.CANSender_State < 5)
		{
				TaskState.CANSender_OfflineSet = 1;
		}
		else
		{
				TaskState.CANSender_OfflineSet = 0;
		}
		TaskState.CANSender_State = 0;
}

/**
  * @Data    2019-02-20 19:54
  * @brief   新LED灯闪烁提示
  * @param   void
  * @retval  void
  */
void SetLedSingle(void)
{
		static int TimeSearch = 0;
		TimeSearch++;
		if (TimeSearch > 100)
		{
				TimeSearch = 1;
		}
		
		/*掉线判断*/
		if(DR16.OFFLINE_SET == 1 && Judgement_Check.OFFLINE_SET == 0)
		{
				LEDSingleLight(GPIOB,GPIO_Pin_4,1,TimeSearch);
		}
		else if(DR16.OFFLINE_SET == 0 && Judgement_Check.OFFLINE_SET == 1)
		{
				LEDSingleLight(GPIOB,GPIO_Pin_4,2,TimeSearch);
		}
		else if(DR16.OFFLINE_SET == 1 && Judgement_Check.OFFLINE_SET == 1)
		{
				LEDSingleLight(GPIOB,GPIO_Pin_4,3,TimeSearch);
		}
		else
		{
				GPIO_SetBits(GPIOE,GPIO_Pin_9);
		}	
		
		
		if(IMU_Chassis.OFFLINE_SET == 1 && IMU_Cloud.OFFLINE_SET == 0)
		{
				LEDSingleLight(GPIOB,GPIO_Pin_5,1,TimeSearch);
		}
		else if(IMU_Chassis.OFFLINE_SET == 0 && IMU_Cloud.OFFLINE_SET == 1)
		{
				LEDSingleLight(GPIOB,GPIO_Pin_5,2,TimeSearch);
		}
		else if(IMU_Chassis.OFFLINE_SET == 1 && IMU_Cloud.OFFLINE_SET == 1)
		{
				LEDSingleLight(GPIOB,GPIO_Pin_5,3,TimeSearch);
		}
//		else
//		{
//				GPIO_ResetBits(GPIOE,GPIO_Pin_10);
//		}
		
		
//		if(TaskState.TaskControl_OfflineSet == 0)
//		{	
//				LEDSingleLight(GPIOE,GPIO_Pin_9,1,TimeSearch);
//		}
//		else
//		{
//				GPIO_SetBits(GPIOE,GPIO_Pin_9);
//		}
//		
//		
//		if(TaskState.CANRecevie_OfflineSet == 0)
//		{
//				LEDSingleLight(GPIOE,GPIO_Pin_10,1,TimeSearch);
//		}
//		else
//		{
//				GPIO_SetBits(GPIOE,GPIO_Pin_10);
//		}
//		
//		
//		if(TaskState.CANSender_OfflineSet == 0)
//		{
//				LEDSingleLight(GPIOE,GPIO_Pin_11,1,TimeSearch);
//		}
//		else
//		{
//				GPIO_SetBits(GPIOE,GPIO_Pin_11);
//		}
		
		
		if((RM3508s[0].OFFLINE_SET == 1 || RM3508s[1].OFFLINE_SET == 1) 
			&&(RM3508s[2].OFFLINE_SET == 0 && RM3508s[3].OFFLINE_SET == 0))
		{
				LEDSingleLight(GPIOE,GPIO_Pin_12,1,TimeSearch);
		}
		else if((RM3508s[2].OFFLINE_SET == 1 || RM3508s[3].OFFLINE_SET == 1)
			&& (RM3508s[0].OFFLINE_SET == 0 && RM3508s[1].OFFLINE_SET == 0))
		{
				LEDSingleLight(GPIOE,GPIO_Pin_12,2,TimeSearch);
		}
		else if((RM3508s[0].OFFLINE_SET == 1 || RM3508s[1].OFFLINE_SET == 1)
				&& (RM3508s[2].OFFLINE_SET == 1 || RM3508s[3].OFFLINE_SET == 1))
		{
				LEDSingleLight(GPIOE,GPIO_Pin_12,3,TimeSearch);
		}
		else
		{
				GPIO_SetBits(GPIOE,GPIO_Pin_12);
		}
		
		
		if(RM6020s[0].OFFLINE_SET == 1 && RM6020s[1].OFFLINE_SET == 0)
		{
				LEDSingleLight(GPIOE,GPIO_Pin_13,1,TimeSearch);
		}
		else if(RM6020s[0].OFFLINE_SET == 0 && RM6020s[1].OFFLINE_SET == 1)
		{
				LEDSingleLight(GPIOE,GPIO_Pin_13,2,TimeSearch);
		}
		else if(RM6020s[0].OFFLINE_SET == 1 && RM6020s[1].OFFLINE_SET == 1) 
		{
				LEDSingleLight(GPIOE,GPIO_Pin_13,3,TimeSearch);
		}
		else
		{	
				GPIO_SetBits(GPIOE,GPIO_Pin_13);	
		}
		
		
		if(RM2006s[0].OFFLINE_SET == 1 && CV.OFFLINE_SET == 0)
		{
				LEDSingleLight(GPIOE,GPIO_Pin_14,1,TimeSearch);
		}
		else if(RM2006s[0].OFFLINE_SET == 0 && CV.OFFLINE_SET == 1)
		{
				LEDSingleLight(GPIOE,GPIO_Pin_14,2,TimeSearch);
		}
		else if(RM2006s[0].OFFLINE_SET == 1 && CV.OFFLINE_SET == 1)
		{
				LEDSingleLight(GPIOE,GPIO_Pin_14,3,TimeSearch);
		}
		else
		{
				GPIO_SetBits(GPIOE,GPIO_Pin_14);	
		}
		
		if(SCCM.OFFLINE_SET == 1)
		{
				LEDSingleLight(GPIOE,GPIO_Pin_15,1,TimeSearch);
		}
		else
		{
				GPIO_SetBits(GPIOE,GPIO_Pin_15);
		}
		
		

}


void LEDSingleLight(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,uint8_t single, int TimeNow)
{
		if(single > 0)
		{
				if(TimeNow <= 50)
				{
						if(TimeNow %(50/single) == 0)
						{
							  
								GPIO_ToggleBits(GPIOx,GPIO_Pin);
						}
						else
						{	
								;
						}
				}
				else
				{
						;
				}
		}
		else
		{
				;
		}
}


/*-----------------------------------file of end------------------------------*/


