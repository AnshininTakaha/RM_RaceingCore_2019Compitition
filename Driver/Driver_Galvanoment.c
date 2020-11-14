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
  |--FileName    : Driver_Galvanoment.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ���� & �                                                     
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

/*�����ƵĻ�����ֵ������*/
Galvanometer_t Galvanometer;

/**
  * @Data    2019-03-11 20:04
  * @brief   �����������㷨
  * @param   GalvanometerData_t* Galvanometer
  * @retval  void
  */
void Galvanometer_Calculation(Galvanometer_t* Galvanometer)
{
	/*Ԥ���ж�*/

	/*б�ʼ���*/
	Galvanometer->data.Growthslope = (Galvanometer->data.chassisPowerBuffer - \
    Galvanometer->data.LastchassisPowerBuffer) / (10 / portTICK_RATE_MS);
		
	/*Ԥ�⹦�ʼ���*/
	Galvanometer->data.ForecastPower = (Galvanometer->data.Growthslope * \
    (2*(10 / portTICK_RATE_MS))) + Galvanometer->data.LastchassisPowerBuffer;
		
	/*���幦�ʣ����ԣ�*/
  Galvanometer->data.ExpectPowerTiring = 60 - \
	((Galvanometer->data.chassisPowerBuffer + Galvanometer->data.ForecastPower)\
	/ 2);
	
	if(Galvanometer->OFFLINE_SET != 1 && Judgement_Check.OFFLINE_SET != 1)
	{
			/*ֱ��ͨ������ϵͳ�ж�*/
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
			/*ֱ��ͨ������ϵͳ�ж�*/
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


