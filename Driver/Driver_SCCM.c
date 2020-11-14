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
  |--FileName    : Driver_SCCM.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ���� & �                                                     
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
  * @brief  �������ݹ���״̬
  * @param  UseToCharge 	ʹ�õ��̹��ʳ��ռ�ô�С����λ��W ,��Χ 0-70W
  *         ChargeSet     �Ƿ�ʹ�ܳ��
  *         CapOutputSet  �Ƿ��л���Ϊ���ݹ���
  * @retval None
  */
void SCCM_StateSetting(float UseToCharge, uint8_t ChargeSet, uint8_t CapOutputSet)
{
		/*��ֹ������繦��*/
		if(UseToCharge > SCCM_Charge_MAX)
		{
				UseToCharge = SCCM_Charge_MAX;
		}
		
		/*��ֹ����ѹ*/
		if(UseToCharge <0.0f)
		{
				UseToCharge = 0;
		}
		
		/*��ֱֹ�Ӽ����ʱ���籬����*/
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


