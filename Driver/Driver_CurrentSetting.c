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
  |--FileName    : Driver_CurrentSetting.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无 & 璨                                                     
  |--Date        : 2019-03-28             
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
#include "Driver_CurrentSetting.h" 


#include "Task_CAN.h"

/**
  * @Data    2019-02-28 21:39
  * @brief   底盘电流值发送
  * @param   int16_t I1,int16_t I2,int16_t I3,int16_t I4
  * @retval  void
  */
void Chassis_CurrentSetting(int16_t I1,int16_t I2,int16_t I3,int16_t I4)
{
		CAN_TXPrarm_t SendCanTxMsgPrarm;
//    uint8_t RM3508_Sending[8];
//	
//    RM3508_Sending[0] = I1 >> 8;
//    RM3508_Sending[1] = I1;

//    RM3508_Sending[2] = I2 >> 8;
//    RM3508_Sending[3] = I2;

//    RM3508_Sending[4] = I3 >> 8;
//    RM3508_Sending[5] = I3;

//    RM3508_Sending[6] = I4 >> 8;
//    RM3508_Sending[7] = I4;
	
		SendCanTxMsgPrarm.TxMessage.DLC = 8;
		SendCanTxMsgPrarm.TxMessage.IDE = CAN_ID_STD;
		SendCanTxMsgPrarm.TxMessage.RTR = CAN_RTR_Data;
		SendCanTxMsgPrarm.TxMessage.StdId = 0x200;
	
		SendCanTxMsgPrarm.TxMessage.Data[0] = I1 >> 8;
		SendCanTxMsgPrarm.TxMessage.Data[1] = I1;
		SendCanTxMsgPrarm.TxMessage.Data[2] = I2 >> 8;
		SendCanTxMsgPrarm.TxMessage.Data[3] = I2;
		SendCanTxMsgPrarm.TxMessage.Data[4] = I3 >> 8;
		SendCanTxMsgPrarm.TxMessage.Data[5] = I3;
		SendCanTxMsgPrarm.TxMessage.Data[6] = I4 >> 8;
		SendCanTxMsgPrarm.TxMessage.Data[7] = I4;
		SendCanTxMsgPrarm.CANSet = 1;
		
		xQueueSend(xCanSender,&SendCanTxMsgPrarm,portMAX_DELAY);
//    CAN_sendData(CAN1,CAN_ID_STD,0x200,RM3508_Sending);
}












/**
  * @Data    2019-02-28 21:40
  * @brief   云台电流和拨弹电流值发送
  * @param   int16_t I_Yaw, int16_t I_Pitch, \
	int16_t I_Emitter, int16_t OVER
  * @retval  void
  */
void Cloud_And_Emitter_CurrentSetting(int16_t I_Yaw, int16_t I_Pitch, \
int16_t I_Emitter, int16_t OVER)
{
		CanTxMsg SendCanTxMsg;

	
		SendCanTxMsg.DLC = 8;
		SendCanTxMsg.IDE = CAN_ID_STD;
		SendCanTxMsg.RTR = CAN_RTR_Data;
		SendCanTxMsg.StdId = 0x1FF;
		
		SendCanTxMsg.Data[0] = I_Yaw >> 8;
		SendCanTxMsg.Data[1] = I_Yaw;
		SendCanTxMsg.Data[2] = I_Pitch >> 8;
		SendCanTxMsg.Data[3] = I_Pitch;
		SendCanTxMsg.Data[4] = I_Emitter >> 8;
		SendCanTxMsg.Data[5] = I_Emitter;
		SendCanTxMsg.Data[6] = OVER >> 8;
		SendCanTxMsg.Data[7] = OVER;
		
		xQueueSend(xCanSender,&SendCanTxMsg,portMAX_DELAY);
//    CAN_sendData(CAN1,CAN_ID_STD,0x1FF,Cloud_Sending);
}


/**
  * @Data    2019-03-06 19:42
  * @brief   云台电流值发送
  * @param   int16_t I_Yaw, int16_t I_Pitch,
  * @retval  void
  */
void Cloud_CurrentSetting(int16_t I_Yaw, int16_t I_Pitch)
{
  uint8_t Cloud_Sending[8];
	CanTxMsg SendCanTxMsg;
	
	SendCanTxMsg.DLC = 8;
	SendCanTxMsg.IDE = CAN_ID_STD;
	SendCanTxMsg.RTR = CAN_RTR_Data;
	SendCanTxMsg.StdId = 0x1FF;
	
	Cloud_Sending[0] = I_Yaw >> 8;
	Cloud_Sending[1] = I_Yaw;
	Cloud_Sending[2] = I_Pitch >> 8;
  Cloud_Sending[3] = I_Pitch;
	
	SendCanTxMsg.Data[0] = Cloud_Sending[0];
	SendCanTxMsg.Data[1] = Cloud_Sending[1];
	SendCanTxMsg.Data[2] = Cloud_Sending[2];
	SendCanTxMsg.Data[3] = Cloud_Sending[3];
	SendCanTxMsg.Data[4] = Cloud_Sending[4];
	SendCanTxMsg.Data[5] = Cloud_Sending[5];
	SendCanTxMsg.Data[6] = Cloud_Sending[6];
	SendCanTxMsg.Data[7] = Cloud_Sending[7];
	
  xQueueSend(xCanSender,&SendCanTxMsg,portMAX_DELAY);
}

void Cloud_CurrentSettingOnlyYaw(int16_t I_Yaw)
{
  uint8_t Cloud_Sending[8];
	CAN_TXPrarm_t SendCanTxMsgPrarm;
	
	SendCanTxMsgPrarm.TxMessage.DLC = 8;
	SendCanTxMsgPrarm.TxMessage.IDE = CAN_ID_STD;
	SendCanTxMsgPrarm.TxMessage.RTR = CAN_RTR_Data;
	SendCanTxMsgPrarm.TxMessage.StdId = 0x1FF;
	
	Cloud_Sending[0] = I_Yaw >> 8;
	Cloud_Sending[1] = I_Yaw;
	
	SendCanTxMsgPrarm.TxMessage.Data[0] = Cloud_Sending[0];
	SendCanTxMsgPrarm.TxMessage.Data[1] = Cloud_Sending[1];
	SendCanTxMsgPrarm.TxMessage.Data[2] = Cloud_Sending[2];
	SendCanTxMsgPrarm.TxMessage.Data[3] = Cloud_Sending[3];
	SendCanTxMsgPrarm.TxMessage.Data[4] = Cloud_Sending[4];
	SendCanTxMsgPrarm.TxMessage.Data[5] = Cloud_Sending[5];
	SendCanTxMsgPrarm.TxMessage.Data[6] = Cloud_Sending[6];
	SendCanTxMsgPrarm.TxMessage.Data[7] = Cloud_Sending[7];
	SendCanTxMsgPrarm.CANSet = 1;
	
  xQueueSend(xCanSender,&SendCanTxMsgPrarm,portMAX_DELAY);
}

void Cloud_CurrentSettingOnlyPitchANDCarr(int16_t I_Pitch,int16_t I_Emitter)
{
  uint8_t Cloud_Sending[8];
	CAN_TXPrarm_t SendCanTxMsgPrarm;
	
	SendCanTxMsgPrarm.TxMessage.DLC = 8;
	SendCanTxMsgPrarm.TxMessage.IDE = CAN_ID_STD;
	SendCanTxMsgPrarm.TxMessage.RTR = CAN_RTR_Data;
	SendCanTxMsgPrarm.TxMessage.StdId = 0x1FF;
	
	Cloud_Sending[2] = I_Pitch >> 8;
  Cloud_Sending[3] = I_Pitch;
	Cloud_Sending[4] = I_Emitter >> 8;
  Cloud_Sending[5] = I_Emitter;
	
	SendCanTxMsgPrarm.TxMessage.Data[0] = Cloud_Sending[0];
	SendCanTxMsgPrarm.TxMessage.Data[1] = Cloud_Sending[1];
	SendCanTxMsgPrarm.TxMessage.Data[2] = Cloud_Sending[2];
	SendCanTxMsgPrarm.TxMessage.Data[3] = Cloud_Sending[3];
	SendCanTxMsgPrarm.TxMessage.Data[4] = Cloud_Sending[4];
	SendCanTxMsgPrarm.TxMessage.Data[5] = Cloud_Sending[5];
	SendCanTxMsgPrarm.TxMessage.Data[6] = Cloud_Sending[6];
	SendCanTxMsgPrarm.TxMessage.Data[7] = Cloud_Sending[7];
	SendCanTxMsgPrarm.CANSet = 2;
	
  xQueueSend(xCanSender,&SendCanTxMsgPrarm,portMAX_DELAY);
}



/**
  * @Data    2019-03-06 19:50
  * @brief   拨弹电机电流值发送
  * @param   int16_t I_Emitter
  * @retval  void
  */
void Cartridge_CurrentSetting(int16_t I_Emitter)
{
  uint8_t Cloud_Sending[8];
	CAN_TXPrarm_t SendCanTxMsgPrarm;
	
	SendCanTxMsgPrarm.TxMessage.DLC = 8;
	SendCanTxMsgPrarm.TxMessage.IDE = CAN_ID_STD;
	SendCanTxMsgPrarm.TxMessage.RTR = CAN_RTR_Data;
	SendCanTxMsgPrarm.TxMessage.StdId = 0x1FF;

  Cloud_Sending[4] = I_Emitter >> 8;
  Cloud_Sending[5] = I_Emitter;
	
	SendCanTxMsgPrarm.TxMessage.Data[0] = Cloud_Sending[0];
	SendCanTxMsgPrarm.TxMessage.Data[1] = Cloud_Sending[1];
	SendCanTxMsgPrarm.TxMessage.Data[2] = Cloud_Sending[2];
	SendCanTxMsgPrarm.TxMessage.Data[3] = Cloud_Sending[3];
	SendCanTxMsgPrarm.TxMessage.Data[4] = Cloud_Sending[4];
	SendCanTxMsgPrarm.TxMessage.Data[5] = Cloud_Sending[5];
	SendCanTxMsgPrarm.TxMessage.Data[6] = Cloud_Sending[6];
	SendCanTxMsgPrarm.TxMessage.Data[7] = Cloud_Sending[7];
	SendCanTxMsgPrarm.CANSet = 2;

	xQueueSend(xCanSender,&SendCanTxMsgPrarm,portMAX_DELAY);
//  CAN_sendData(CAN1,CAN_ID_STD,0x1FF,Cloud_Sending);
}

/*-----------------------------------file of end------------------------------*/


