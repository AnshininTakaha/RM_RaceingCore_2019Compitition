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
  |--FileName    : Driver_SCCM.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无 & 璨                                                     
  |--Date        : 2019-04-20             
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
#include "Driver_SCCM.h" 

#include "BSP_Init.h"

SCCM_t SCCM;


/**
  * @brief  超级电容管理状态
  * @param  UseToCharge 	使用底盘功率充电占用大小，单位：W ,范围 0-70W
  *         ChargeSet     是否使能充电
  *         CapOutputSet  是否切换成为电容供电
  * @retval None
  */
void SCCM_StateSetting(float UseToCharge, uint8_t ChargeSet, uint8_t CapOutputSet)
{
		/*防止超过充电功率*/
		if(UseToCharge > SCCM_Charge_MAX)
		{
				UseToCharge = SCCM_Charge_MAX;
		}
		
		/*防止负电压*/
		if(UseToCharge <0.0f)
		{
				UseToCharge = 0;
		}
		
		/*防止直接计算的时候充电爆功率*/
		if(UseToCharge > 80.0f)
		{
				UseToCharge = 79.0f;
		}
		
		SCCM.sendData.charge_power = UseToCharge;
		SCCM.sendData.charge_enable = ChargeSet;
		SCCM.sendData.is_cap_output = CapOutputSet;
		
		CAN_sendData(CAN1,CAN_ID_STD,0x601,SCCM.sendData.data);
}
/*-----------------------------------file of end------------------------------*/


