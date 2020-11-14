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
  |--FileName    : Driver_Analysis.c                                              
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
#include "Driver_Analysis.h" 


#include "Driver_Galvanoment.h"
#include "Driver_PID.h"
#include "Driver_SCCM.h"
#include "Driver_IMU.h"

/* =========================== WHELLSTRUCT of begin =========================== */
/*��Ӧ���ĸ�����*/
RM3508_t RM3508s[4];
/*��Ӧ��������̨*/
RM6020_t RM6020s[2];
/*��Ӧ�Ĳ������*/
RM2006_t RM2006s[1];
/* =========================== WHELLSTRUCT of end =========================== */

/**
  * @Data    2019-03-23 16:13
  * @brief   CAN�����������ݽ���
  * @param   void
  * @retval  void
  */
void CAN_Analysis(CanRxMsg RxMessage)
{
		
    switch(RxMessage.StdId)
		{
				case Receive_MotorLeftFront://��Ӧ��Ϊ0������
        RM3508s[0].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
        RM3508s[0].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
        RM3508s[0].realCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
        RM3508s[0].realTempeture = (RxMessage.Data[6]);
        RM3508s[0].UpdateFlag = 1;
        RM3508s[0].UpdateFrame++;
        break;

    case Receive_MotorRightFront://��Ӧ��Ϊ1������
        RM3508s[1].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
        RM3508s[1].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
        RM3508s[1].realCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
        RM3508s[1].realTempeture = (RxMessage.Data[6]);
        RM3508s[1].UpdateFlag = 1;
        RM3508s[1].UpdateFrame++;
        break;

    case Receive_MotorRightBack://��ӦΪ2������
        RM3508s[2].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
        RM3508s[2].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
        RM3508s[2].realCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
        RM3508s[2].realTempeture = (RxMessage.Data[6]);
        RM3508s[2].UpdateFlag = 1;
        RM3508s[2].UpdateFrame++;
        break;

    case Receive_MotorLeftBack://��ӦΪ3������
        RM3508s[3].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
        RM3508s[3].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
        RM3508s[3].realCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
        RM3508s[3].realTempeture = (RxMessage.Data[6]);
        RM3508s[3].UpdateFlag = 1;
        RM3508s[3].UpdateFrame++;
        break;

    //platform
    case Receive_CloudYAW://��Ӧ��Yaw����̨
        RM6020s[0].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
        RM6020s[0].realCurrent = (RxMessage.Data[2]<<8|RxMessage.Data[3]);/*��ʵ��ת��*/
				RM6020s[0].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
				RM6020s[0].realTorque = (RxMessage.Data[4]<<8 | RxMessage.Data[5]);
				RM6020s[0].realTempeture = RxMessage.Data[6];
//			RM6020s[0].feedbackCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
				M6623_ZeroDealing_platform(0);
        RM6020s[0].totalAngle = RM6020s[0].realAngle +(PLATFORM_A_TURN*\
				RM6020s[0].turnCount);
        RM6020s[0].UpdateFlag = 1;
        RM6020s[0].UpdateFrame++;
        break;

    case Receive_CloudPITCH://��Ӧ��Pitch����̨
				RM6020s[1].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
        RM6020s[1].realCurrent = (RxMessage.Data[2]<<8|RxMessage.Data[3]);/*��ʵ��ת��*/
				RM6020s[1].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
				RM6020s[1].realTorque = (RxMessage.Data[4]<<8 | RxMessage.Data[5]);
				RM6020s[1].realTempeture = RxMessage.Data[6];
//			RM6020s[1].feedbackCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
        M6623_ZeroDealing_platform(1);
        RM6020s[1].totalAngle = RM6020s[1].realAngle +(PLATFORM_A_TURN*\
				RM6020s[1].turnCount);
        RM6020s[1].UpdateFlag = 1;
        RM6020s[1].UpdateFrame++;
        break;

    case Receive_Carriage://��Ӧ�������
        RM2006s[0].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
        RM2006s[0].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
        RM2006s[0].realTorque = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
        M2006_ZeroDealing_platform(0);
        RM2006s[0].totalAngle = RM2006s[0].realAngle +(UNDULATION_A_TURN*RM2006s[0].turnCount);
        RM2006s[0].UpdateFlag = 1;
        RM2006s[0].UpdateFrame++;
        break;

    case Receive_Galvanoment:
       Galvanometer.data.chassisVolt = (uint16_t)(RxMessage.Data[1]<<8 | \
       RxMessage.Data[0]) / 100.0f;
       Galvanometer.data.chassisCurrent = (uint16_t)(RxMessage.Data[3]<<8 | \
       RxMessage.Data[2]) / 100.0f;
       Galvanometer.data.chassisPower = (uint16_t)(RxMessage.Data[5]<<8 | \
       RxMessage.Data[4]) / 100.0f;
       Galvanometer.data.chassisPowerBuffer = (uint16_t)(RxMessage.Data[7]<<8 |\
       RxMessage.Data[6]) / 100.0f;
       Galvanometer_Calculation(&Galvanometer);
       Galvanometer.UpdateFrame++;
       Galvanometer.UpdateFlag = 1;
        break;
		
		case Receive_SCCM:
			memcpy(SCCM.receiveData.data, RxMessage.Data, sizeof(uint8_t[8]));
			SCCM.UpdateFrame++;
			SCCM.UpdateFlag = 1;
			break;
		
		case Recrive_CloudIMU:
			memcpy(IMU_Cloud.data.dataBuff,RxMessage.Data,sizeof(uint8_t[8]));
			IMU_Cloud.data.euler_yaw = (float)IMU_Cloud.data.euler_yaw / 100.0f/ 360.0f * 8191;
//			IMU_Cloud.data.euler_yaw = IMU_Cloud.data.euler_yaw ;
//			IMU_Cloud.data.euler_yaw = (int16_t)IMU_Cloud.data.euler_yaw * 8191;

			
			IMU_Cloud.data.euler_pitch = IMU_Cloud.data.euler_pitch / 100.0f *RATIO;
			IMU_Cloud.data.gyro_x = IMU_Cloud.data.gyro_x / 100.0f;
			IMU_Cloud.data.gyro_z = IMU_Cloud.data.gyro_z / 100.0f;
			
			/*���㴦��*/
			if(IMU_Cloud.data.euler_yaw - IMU_Cloud.lastYaw < -4000)
			{
					IMU_Cloud.turnCount++;
			}
			if(IMU_Cloud.lastYaw - IMU_Cloud.data.euler_yaw < -4000)
			{
					IMU_Cloud.turnCount--;
			}
			IMU_Cloud.lastYaw = IMU_Cloud.data.euler_yaw;
			IMU_Cloud.totalYaw = IMU_Cloud.data.euler_yaw + (8192 * IMU_Cloud.turnCount);
			IMU_Cloud.UpdateFrame++;
			
			break;
			
		case Receive_ChassisIMU:
			/*��Ҫ����ŷ�����ٶȣ����Բ�����eular���������㴦��*/
			memcpy(IMU_Chassis.data.dataBuff,RxMessage.Data,sizeof(uint8_t[8]));
			IMU_Chassis.data.euler_yaw = IMU_Chassis.data.euler_yaw / 100.0f * RATIO;
			IMU_Chassis.data.euler_pitch = IMU_Chassis.data.euler_pitch / 100.0f *RATIO;
			IMU_Chassis.data.gyro_x = IMU_Chassis.data.gyro_x / 16.0f;
			IMU_Chassis.data.gyro_z = IMU_Chassis.data.gyro_z / 16.0f;
			IMU_Chassis.UpdateFrame++;
			break;

		}
}

/**
  * @Data    2019-02-19 18:39
  * @brief   RM6623��̨������㴦��
  * @param   int8_t id ��Ҫ���㴦��ĵ����Ӧ��ID
  * @retval  void
  */
void M6623_ZeroDealing_platform(int8_t id)
{
    if(RM6020s[id].realAngle - RM6020s[id].lastAngle < -6000)
    {
        RM6020s[id].turnCount++;
    }

    if(RM6020s[id].lastAngle - RM6020s[id].realAngle < -6000)
    {
        RM6020s[id].turnCount--;
    }
    RM6020s[id].lastAngle =  RM6020s[id].realAngle;

}

/**
  * @Data    2019-02-19 18:41
  * @brief   RM2006���㴦��
  * @param   int8_t id  ��Ҫ���㴦��ĵ����Ӧ��ID
  * @retval  void
  */
void M2006_ZeroDealing_platform(int8_t id)
{
    if(RM2006s[id].realAngle - RM2006s[id].lastAngle < -6000)
    {
        RM2006s[id].turnCount++;
    }
    if(RM2006s[id].lastAngle - RM2006s[id].realAngle < -6000)
    {
        RM2006s[id].turnCount--;
    }
    RM2006s[id].lastAngle =  RM2006s[id].realAngle;
}
/*-----------------------------------file of end------------------------------*/


