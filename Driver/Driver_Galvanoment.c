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
  |--FileName    : Driver_Galvanoment.c                                              
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
#include "Driver_Galvanoment.h" 


#include "Driver_Judge.h"

/*电流计的基本数值储存体*/
Galvanometer_t Galvanometer;

/**
  * @Data    2019-03-11 20:04
  * @brief   超功率限制算法
  * @param   GalvanometerData_t* Galvanometer
  * @retval  void
  */
void Galvanometer_Calculation(Galvanometer_t* Galvanometer)
{
	/*预测判断*/

	/*斜率计算*/
	Galvanometer->data.Growthslope = (Galvanometer->data.chassisPowerBuffer - \
    Galvanometer->data.LastchassisPowerBuffer) / (10 / portTICK_RATE_MS);
		
	/*预测功率计算*/
	Galvanometer->data.ForecastPower = (Galvanometer->data.Growthslope * \
    (2*(10 / portTICK_RATE_MS))) + Galvanometer->data.LastchassisPowerBuffer;
		
	/*缓冲功率（测试）*/
  Galvanometer->data.ExpectPowerTiring = 60 - \
	((Galvanometer->data.chassisPowerBuffer + Galvanometer->data.ForecastPower)\
	/ 2);
	
	if(Galvanometer->OFFLINE_SET != 1 && Judgement_Check.OFFLINE_SET != 1)
	{
			/*直接通过裁判系统判断*/
	}
	else if(Galvanometer->OFFLINE_SET != 1 && Judgement_Check.OFFLINE_SET == 1)
	{
			if(Galvanometer->data.ForecastPower < 40)
			{
					Galvanometer->data.PreOverPowerState = 1;
			}
			if(Galvanometer->data.PreOverPowerState == 1)
			{
					if(Galvanometer->data.chassisPowerBuffer < 40)
					{
							Galvanometer->data.OverPowerState = 1;
					}
					else
					{
							Galvanometer->data.OverPowerState = 0;
					}
			}
			
			if(Galvanometer->data.ForecastPower > 50 && \
				Galvanometer->data.chassisPowerBuffer > 50)
			{
					Galvanometer->data.PreOverPowerState = 0;
					Galvanometer->data.OverPowerState = 0;
			}
			
			
	}
	else if(Galvanometer->OFFLINE_SET == 1 && Judgement_Check.OFFLINE_SET != 1)
	{
			/*直接通过裁判系统判断*/
	}
	else if(Galvanometer->OFFLINE_SET == 1 && Judgement_Check.OFFLINE_SET == 1)
	{
			Galvanometer->data.PreOverPowerState = 1;
			Galvanometer->data.OverPowerState = 1;
			ChassPowerStatus = OverPower_Many;
	}
	
	
		
//	if((Galvanometer->data.ForecastPower < 40 && \
//		Galvanometer->data.ForecastPower != 0) || \
//		(ext_power_heat_data.chassis_power_buffer < 50 && \
//		Judgement_Check.OFFLINE_SET == 0))
//	{
//		Galvanometer->data.PreOverPowerState = 1;
//	}
//		
//	if(Galvanometer->data.PreOverPowerState == 1)
//	{
//		if(Galvanometer->data.chassisPowerBuffer < 40 || \
//			(ext_power_heat_data.chassis_power_buffer < 40 && \
//			Judgement_Check.OFFLINE_SET == 0))
//		{
//			Galvanometer->data.OverPowerState = 1;
//		}
//	}
//		
//	if(Galvanometer->data.ForecastPower >50 ||\
//		(ext_power_heat_data.chassis_power_buffer > 55 && \
//		Judgement_Check.OFFLINE_SET == 0))
//	{
//		Galvanometer->data.PreOverPowerState = 0;
//	}
//		
//	if(Galvanometer->data.OverPowerState == 1)
//	{
//		if(Galvanometer->data.chassisPowerBuffer > 50 ||\
//			(ext_power_heat_data.chassis_power_buffer > 50 && \
//			Judgement_Check.OFFLINE_SET == 0))
//		{
//			Galvanometer->data.OverPowerState = 0;
//		}
//	}
		
		
	Galvanometer->data.LastchassisPowerBuffer = Galvanometer->data.chassisPowerBuffer;
		
}


/*-----------------------------------file of end------------------------------*/


