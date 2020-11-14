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
  |--FileName    : Driver_PID.c                                              
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
#include "Control_Chassis.h"
#include "Control_Cloud.h"
#include "Control_PC.h"
#include "Driver_Aiming.h" 
#include "power_buffer_pool.h"
//#include "Driver_Power.h"
#include "Driver_Galvanoment.h"
#include "Driver_Judge.h"
#include "Driver_Filter.h"
#include "Driver_DR16.h"
#include "Driver_CurrentSetting.h"
#include "Driver_IMU.h"
#include "Driver_slope.h"
#include "Driver_SCCM.h"

Chassis_t Chassis;

incrementalpid_t PID_Wheel0 = IncInit_Wheel;
incrementalpid_t PID_Wheel1 = IncInit_Wheel;
incrementalpid_t PID_Wheel2 = IncInit_Wheel;
incrementalpid_t PID_Wheel3 = IncInit_Wheel;
positionpid_t PID_Follow  = PosInit_Follow;
positionpid_t PID_FollowSwing  = PosInit_Follow;
/**
  * @Data    2019-02-19 15:46
  * @brief   �������ݸ�ֵ
  * @param   uint8_t switchmode
  * @retval  void
  */
float LastChassis_Vx= 0.0f;
void Chassis_Judgement(uint8_t switchmode)
{
		/*��ʼ����ֵ�ı���*/
		float Chassis_Vx = 0.0f,Chassis_Vy = 0.0f,Chassis_VOmega = 0.0f;
		float RadRaw = 0.0f;
		float temp_Vx = 0.0f;
		Chassis.Filter_LPFfactor = Fif_Factor;
		
		/*ѡ��ֵģʽ*/
  switch(switchmode)
  {
		/**********************************���Կ���********************************/
    case PC_Controling_ON:
		/*����WASDQE��λ���Ʒ�����ƶ�*/
				switch(PC.PCMode)
				{
						/***********��̨����ģʽ***********/
						case PC_CloudPlatfrom:
						Chassis_Vx = PCRocket.PC_x;
						Chassis_Vy = PCRocket.PC_y;
						
//						/*���Ӽ��ٻ���*/
//						if(ABS(Chassis_Vx) < ABS(LastChassis_Vx))
//						{
//								/*������ٵ����������ڼ����ƶ�������*/
//								if(LastChassis_Vx > 0)
//								{
//										Chassis_Vx = LastChassis_Vx - 300.0f;
//										if(Chassis_Vx < 0)
//										{
//												Chassis_Vx = 0;
//										}
//								}
//								if(LastChassis_Vx < 0)
//								{
//										Chassis_Vx = LastChassis_Vx + 300.0f;
//										if(Chassis_Vx > 0)
//										{
//												Chassis_Vx = 0;
//										}
//								}
//						}
//						LastChassis_Vx = Chassis_Vx;
						
						/*��������*/
						if(PC.ShiftState == 1)
						{
								if(SCCM.OFFLINE_SET == 0)
								{
										SCCM_StateSetting(UseTo_Charge - ext_power_heat_data.chassis_power,1,1);
								}
						}
						
						
						temp_Vx = Chassis_Vx;
						RadRaw = GetYAW_withCenter()*DEG_TO_RAD;
						Chassis_Vx = Chassis_Vx*cos(RadRaw) - Chassis_Vy*sin(RadRaw);
						Chassis_Vy = Chassis_Vy*cos(RadRaw) + temp_Vx*sin(RadRaw);
						
						break;
				
						
						
						/***********��ͷ��תģʽ***********/
						case PC_NoneHead:
						Chassis_Vx = PCRocket.PC_x;
						Chassis_Vy = PCRocket.PC_y;
						
						
						/*��ת�ٶȸı�*/
						if(PCRocket.PC_x == 0 && PCRocket.PC_y == 0)
						{
								Chassis_VOmega = 6000;
						}
						else
						{
								Chassis_VOmega = 4000;
						}
						
						
						/*��������*/
						if(PC.ShiftState == 1)
						{
								if(SCCM.OFFLINE_SET == 0)
								{
										SCCM_StateSetting(60 - ext_power_heat_data.chassis_power,1,1);
								}
						}
							
						/*�ٶȷֽ�*/
						temp_Vx = Chassis_Vx;
						RadRaw = GetYAW_withCenter()*DEG_TO_RAD;
						Chassis_Vx = Chassis_Vx*cos(RadRaw) - Chassis_Vy*sin(RadRaw);
						Chassis_Vy = Chassis_Vy*cos(RadRaw) + temp_Vx*sin(RadRaw);
						
						
						
						break;
						
						/***********��е�Ƕ�ģʽ***********/
						case PC_Sevrel:
						Chassis_Vx = PCRocket.PC_x;
						Chassis_Vy = PCRocket.PC_y;
						Chassis_VOmega = PCRocket.PC_degrees;
						
						/*��������*/
						if(PC.ShiftState == 1)
						{
								if(SCCM.OFFLINE_SET == 0)
								{
										SCCM_StateSetting(60 - ext_power_heat_data.chassis_power,1,1);
								}
						}
						break;
						
						default:
						break;
				}
				
    break;
		
				
		/**********************************ң�ؿ���********************************/
    case RC_Controling_ON:
				/*PCģʽ����*/
				PC.PCMode = PC_CloudPlatfrom;
				Chassis_Vx = (RCRocket.Left_x / 660 * Chassis_MaxSpeed_X);
				Chassis_Vy = (RCRocket.Left_y / 660 * Chassis_MaxSpeed_Y);
		
				/*��������*/
				if(SCCM.OFFLINE_SET == 0)
				{
						SCCM_StateSetting(60 - ext_power_heat_data.chassis_power,1,1);
				}

				
				/*�����ƶ���ʽ*/
				temp_Vx = Chassis_Vx;
				RadRaw = GetYAW_withCenter()*DEG_TO_RAD;
				Chassis_Vx = Chassis_Vx*cos(RadRaw) - Chassis_Vy*sin(RadRaw);
				Chassis_Vy = Chassis_Vy*cos(RadRaw) + temp_Vx*sin(RadRaw);
				break;
		
				
		/**********************************ʧ�ܿ���********************************/
    case None_Controling_ON:
    /*ֹͣģʽ��ֱ��ȫ�̳��*/
		if(SCCM.OFFLINE_SET == 0)
		{
				SCCM_StateSetting(78,1,0);
		}
		
    Chassis_Process(0,0,0,switchmode);
		return;
    break;
		
		
		
    default:
		Chassis_Process(0,0,0,switchmode);
    break;
  }
	
	/*�������ݴ���*/
  Chassis_Process(Chassis_Vx,Chassis_Vy,Chassis_VOmega,switchmode);
	
}




/**
  * @Data    2019-02-19 15:46
  * @brief   float Input_Vx, float Input_Vy, float Input_VOmega, uint8_t switchmode
  * @param   uint8_t switchmode
  * @retval  void
  */
float TC = Cloud_Yaw_Center;
float angle;
static float const add_time_step = PI / 150.0f;
float swing_angle_set,swing_time;
int16_t SpeedCount[4] = {0,0,0,0};
void Chassis_Process(float Input_Vx, float Input_Vy, float Input_VOmega, \
uint8_t switchmode)
{
		/*�ĸ������ٶȷֽ�*/
		int16_t speed[4];

		/*��ת�ٶȻ���*/
		float tempVOmega = 0.0f;

	/*��һ���ֹ��ը*/
	if(DR16.OFFLINE_SET == 1 || \
		 switchmode == None_Controling_ON || \
		 Judgement_Check.OFFLINE_SET == 1)
	{
		Chassis_CurrentSetting(0,0,0,0);
    return;
	}
		
  /*�˲�����*/
  Filter_IIRLPF(&Input_Vx,&Chassis.xPF,Chassis.Filter_LPFfactor);
  Filter_IIRLPF(&Input_Vy,&Chassis.yPF,Chassis.Filter_LPFfactor);
  Filter_IIRLPF(&Input_VOmega,&Chassis.zPF,Chassis.Filter_LPFfactor);
	
	
	
	switch(switchmode)
  {
		/**********************************���Կ���********************************/
    case PC_Controling_ON:
    /*���������ж�ģʽ*/
		if(PC.PCMode == PC_NoneHead || PC.PCMode == PC_Sevrel)
		{
				MecanumCalculation(Chassis.xPF,Chassis.yPF,Chassis.zPF,speed);
		}
		else
		{
				Chassis.FollowYawRaw = 0.0f;
				
				/*angleΪ������*/
				/*���ĵ���λ*/
				angle = RM6020s[0].totalAngle - TC;
				if(angle > 4096)
				{
						TC = TC + 8192;
						angle = RM6020s[0].totalAngle - TC;
				}
				if(angle < -4096)
				{
						TC = TC - 8192;
						angle = RM6020s[0].totalAngle - TC;
				}
				angle = angle / (float)22.75;
				angle = angle * (PI/180);	
				
			
				if(SEDV_Swing == 1)
				{
						//�������Ŀ��Ƕ�
						swing_angle_set = 70.0f*PI/180.0f * arm_sin_f32(swing_time);
					
						//ÿ�����ӵĽǶ�
						swing_time += add_time_step;
						
						/*�����ֹ�Ƕȿ��Ƴ���*/
						if(swing_time > 2 * PI)
						{  
							 swing_time -= 2 * PI;
						}
						
						PID_Follow.Pos_Calc(&PID_Follow,swing_angle_set,angle);
						Chassis.FollowYawRaw = PID_Follow.PWM;
						Filter_IIRLPF(&Chassis.FollowYawRaw, &Chassis.FollowYawLPF, Filter_LowFilter);
						tempVOmega = Chassis.zPF + Chassis.FollowYawLPF;
				}
				else
				{
						if(ABS(RM6020s[0].totalAngle - TC) > 5 && SEDV_BIGER == 0)
							{
									PID_Follow.Pos_Calc(&PID_Follow,0,angle);
									tempVOmega = Chassis.zPF + PID_Follow.PWM;
							}
							else if(SEDV_BIGER == 1)
							{
									tempVOmega = 0;
							}
							else
							{
									tempVOmega = Chassis.zPF;
							}
				}
				MecanumCalculation(Chassis.xPF,Chassis.yPF,tempVOmega,speed);
		}

    break;
		
		
		/**********************************ң�ؿ���********************************/
    case RC_Controling_ON:
			
			if(RM6020s[0].OFFLINE_SET == 0  && IMU_Cloud.OFFLINE_SET == 0)
			{
				Chassis.FollowYawRaw = 0.0f;
				angle = RM6020s[0].totalAngle - TC;
				if(angle > 4096)
				{
						TC = TC + 8192;
						angle = RM6020s[0].totalAngle - TC;
				}
				if(angle < -4096)
				{
						TC = TC - 8192;
						angle = RM6020s[0].totalAngle - TC;
				}
				angle = angle / (float)22.75;
				angle = angle * (PI/180);

							if(ABS(RM6020s[0].totalAngle - TC) > 20 )
							{
									PID_Follow.Pos_Calc(&PID_Follow,0,angle);
									tempVOmega = Chassis.zPF + PID_Follow.PWM;
							}
							else
							{
									tempVOmega = Chassis.zPF;
							}
				MecanumCalculation(Chassis.xPF,Chassis.yPF,tempVOmega,speed);
			}
			else
			{
					
			}
    break;
		
		
		/**********************************ʧ�ܿ���********************************/	
    case None_Controling_ON:
		/*���ط�ֹ��ը*/
    Chassis_CurrentSetting(0,0,0,0);
    return;

    break;

    default:
    break;
  }
	
	RM3508s[0].targetSpeed = speed[0];
	RM3508s[1].targetSpeed = speed[1];
	RM3508s[2].targetSpeed = speed[2];
	RM3508s[3].targetSpeed = speed[3];
	
	PID_Wheel0.Inc_Calc(&PID_Wheel0,RM3508s[0].targetSpeed, RM3508s[0].realSpeed);
	PID_Wheel1.Inc_Calc(&PID_Wheel1,RM3508s[1].targetSpeed, RM3508s[1].realSpeed);
	PID_Wheel2.Inc_Calc(&PID_Wheel2,RM3508s[2].targetSpeed, RM3508s[2].realSpeed);
	PID_Wheel3.Inc_Calc(&PID_Wheel3,RM3508s[3].targetSpeed, RM3508s[3].realSpeed);
	
	/*������ֵ*/
	Power_Limited();
	
	/*���������ֵ*/
	RM3508s[0].outCurrent = PID_Wheel0.PWM;
	RM3508s[1].outCurrent = PID_Wheel1.PWM;
	RM3508s[2].outCurrent = PID_Wheel2.PWM;
	RM3508s[3].outCurrent = PID_Wheel3.PWM;
	
	#ifndef ChassisDebugMode
	Chassis_CurrentSetting(RM3508s[0].outCurrent, RM3508s[1].outCurrent, \
   RM3508s[2].outCurrent, RM3508s[3].outCurrent);
	#endif
}


/**
  * @Data    2019-02-28 21:27
  * @brief   ���ֽ���
  * @param   float Vx, float Vy, float VOmega, int16_t *Speed
  * @retval  void
  */
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed)
{
		float tempSpeed[4];
    float Param = 1;
    float MaxSpeed = 0;

    VAL_LIMIT(Vx, -Chassis_MaxSpeed_X, Chassis_MaxSpeed_X);
    VAL_LIMIT(Vy, -Chassis_MaxSpeed_Y, Chassis_MaxSpeed_Y);
    VAL_LIMIT(VOmega, -Chassis_MaxSpeed_W, Chassis_MaxSpeed_W);

    tempSpeed[0] = Vx - Vy + VOmega;
    tempSpeed[1] = -Vx - Vy + VOmega;
    tempSpeed[2] = -Vx + Vy + VOmega;
    tempSpeed[3] = Vx + Vy + VOmega;

    for(uint8_t i = 0, MaxSpeed = 0; i < 4; i++)//�����ĸ������ٶȵ����ֵ
    {
        if(ABS(tempSpeed[i]) > MaxSpeed)//abs()Ϊ����ֵ����
        {
            MaxSpeed = ABS(tempSpeed[i]);
        }
    }

    /*�ٶȷ���*/
    /*�е����������ٶȵ����ã����ٶ�������3500*/
    if(MaxSpeed > 3500)//WheelMaxSpeed ��������ٶ�
    {
        Param = (float)3500 / MaxSpeed;
    }

    Speed[0] = tempSpeed[0] * Param;
    Speed[1] = tempSpeed[1] * Param;
    Speed[2] = tempSpeed[2] * Param;
    Speed[3] = tempSpeed[3] * Param;
}


/**
  * @Data    2019-02-28 21:27
  * @brief   ������ֵ
  * @param   float Vx, float Vy, float VOmega, int16_t *Speed
  * @retval  void
  */
void Power_Limited(void)
{
	/*��PWM���ֵ*/
	float PWMBUFFER = 1;
		
	/*�ܵ���ӳ��ֵ*/
	float TOCurBUFFER = 1;
		
	/*ӳ�����ֵϵ��(��λΪ��)*/
	float PWM_TO_CUR = 0.00122;
	
	/*�������ӳ�����*/
	float MAX_CurBUFFER = 1;
	
	/*�µĹ��������㷨*/
	/*�����ܵ�PWM���*/
	PWMBUFFER = ABS(PID_Wheel0.PWM) + ABS(PID_Wheel1.PWM) + ABS(PID_Wheel2.PWM) + ABS(PID_Wheel3.PWM);

	
	/*��ӳ�����*/
	TOCurBUFFER = PWMBUFFER * PWM_TO_CUR;

	
	/*�жϵ�ǰ��Ӧ�����ӳ�����(�Թ��ʼ�����)*/
	/*������̫����û�е�����ֵ������Ҫ�޸�*/
	/*�ײ�����̫������Ҫ�޸�*/
	if(Galvanometer.OFFLINE_SET == 0)
	{
			if(Galvanometer.data.chassisPowerBuffer < 14)
			{    
					MAX_CurBUFFER = 3000.0f;
			}
			else if(Galvanometer.data.chassisPowerBuffer < 20)
			{
					MAX_CurBUFFER = 3500.0f;
			}
			else if(Galvanometer.data.chassisPowerBuffer < 26)
			{
					MAX_CurBUFFER = 4000.0f;
			}
			else
			{
					MAX_CurBUFFER = (300000.0f * CurrentUnit) / ext_power_heat_data.chassis_volt;
			}
	}
	else if(Judgement_Check.OFFLINE_SET == 0)
	{
			if(ext_power_heat_data.chassis_power_buffer < 14)
			{
					MAX_CurBUFFER = 3000.0f;
			}
			else if(ext_power_heat_data.chassis_power_buffer < 20)
			{
					MAX_CurBUFFER = 3500.0f;
			}
			else if(ext_power_heat_data.chassis_power_buffer < 26)
			{
					MAX_CurBUFFER = 4000.0f;
			}
			else
			{
					MAX_CurBUFFER = (300000.0f * CurrentUnit) / ext_power_heat_data.chassis_volt;
			}
	}
	else
	{
			MAX_CurBUFFER = 3000.0f;
	}

//	LOOK_PWM = MAX_CurBUFFER;
	if(TOCurBUFFER * 1000 > MAX_CurBUFFER)
	{
			PID_Wheel0.PWM = MAX_CurBUFFER * PID_Wheel0.PWM / PWMBUFFER;
			PID_Wheel1.PWM = MAX_CurBUFFER * PID_Wheel1.PWM / PWMBUFFER;
			PID_Wheel2.PWM = MAX_CurBUFFER * PID_Wheel2.PWM / PWMBUFFER;
			PID_Wheel3.PWM = MAX_CurBUFFER * PID_Wheel3.PWM / PWMBUFFER;
	}
	else
	{
		 
	}
}

/*
case AutoTrace_Mode://�Զ�׷��ģʽ
    
     Chassis.TargetVX = CalcTargetValue.Left_Right_Value;
     
     if (ABS(CalcRealCompare(GetCloudMotorAngle(Yaw),CHASSIS_CENTER_ANGLE)) > 30)
     {
      //���̸���pid����
      ChassisAngle_PID.Calc(&ChassisAngle_PID, 0.0f, angle);
      
      Chassis.TargetOmega = ChassisAngle_PID.Output;
     }
     else
     {
      Chassis.TargetOmega = 0;
     }
     
     if((GetVisionDepth() == 0) || CalcTargetValue.Forward_Back_Value)
     {
      Chassis.TargetVY = -CalcTargetValue.Forward_Back_Value;
     }
     else
     {
      if(GetVisionDepth() > 100)
      {
       Chassis.TargetVY = -ABS(GetVisionDepth() - 100) * 80;
      }
      else
      {
       Chassis.TargetVY = 0;
      }
     }
     swing_time = 0.0f;
     LIMIT(Chassis.TargetVY, 5000);//���Ƹ����ٶ�  
     LIMIT(Chassis.TargetOmega, 5000);//���Ƹ����ٶ�       
     break;

*/




/*
if(GetAttackMode() == AutoAim_Mode)		//�Ƿ�Ϊ�Զ���׼
		{			
			Vision_x_OPID.Calc(&Vision_x_OPID, 
													 vision_offset_x, 
													  GetCoordx(VISION_X));
			Vision_x_IPID.Calc(&Vision_x_IPID, 
													 Vision_x_OPID.Output, 
														GetCorrdxDiff(VISION_X));
			
			Vision_y_OPID.Calc(&Vision_y_OPID, 
													 vision_offset_y, 
														GetCoordx(VISION_Y));			
			Vision_y_IPID.Calc(&Vision_y_IPID, 
													Vision_y_OPID.Output, 
													 GetCorrdxDiff(VISION_Y));
			
			//�ж��Ƿ񵽴﷢������
			if(auto_shoot_enable)
			{
				if((ABS(Vision_x_OPID.Error) < 80) 
						&& (ABS(Vision_y_OPID.Error) < 80))
				{
					auto_shoot_flag = 1;
				}
				else
				{
					auto_shoot_flag = 0;
				}
			}
			else
			{
				auto_shoot_flag = 0;
			}
							
			//�Ӿ����ֿص��л�
			//Yaw
			if (CalcTargetValue.Yaw_Value != 0)
			{
				vision_x = 0;
				CloudParam.Axis[Yaw].ImuTargetAngle += 
							CalcTargetValue.Yaw_Value * 0.05; 
			}
			else
			{  
				if(GetCoordx(VISION_X))
				{
					CloudParam.Axis[Yaw].ImuTargetAngle = GetImuYaw(GY955);
				}
				vision_x = Vision_x_IPID.Output 
								 + GetImuGry_Z(GY955) * vision_temp1;
			}
			
			
			//Pitch
			if (CalcTargetValue.Pitch_Value != 0)
			{
				vision_y = 0;
				CloudParam.Axis[Pitch].TargetAngle -= 
						CalcTargetValue.Pitch_Value * 0.05;
			}
			else
			{				
				if(GetCoordx(VISION_Y))
				{
					CloudParam.Axis[Pitch].TargetAngle = GetCloudMotorAngle(Pitch);
				}	
				vision_y = Vision_y_IPID.Output 
								 + GetImuGry_X(GY955) * vision_temp2;
			}
			
			//û��ʶ��Ŀ��
			if (!ABS(GetCoordx(VISION_X)) 
					&& !ABS(GetCoordx(VISION_Y)))
			{
				auto_shoot_flag = 0;			
				vision_x = 0;
				vision_y = 0;
			}	
		
		}
*/



/*
//�����������Ƿ����
				if(LostCounterCheck(ERROR_CHASSISIMU) == 0)
				{
					Cloud_Chassis_speed_offset = ChassisNDOF055_data.data.gyro_z*16.0f
																			 /ABS(CloudYaw_IPID.Kp);
				}
				else
				{
					Cloud_Chassis_speed_offset = 0;
				}
				
				//yaw��pid���㣨imu��
				CloudYaw_OPID.Calc(&CloudYaw_OPID,
														 CloudParam.Axis[Yaw].ImuTargetAngle,
															GetImuYaw(GY955) + vision_x);
				CloudYaw_IPID.Calc(&CloudYaw_IPID, 
														 CloudYaw_OPID.Output,
															GetImuGry_Z(GY955)+Cloud_Chassis_speed_offset);
															
				//pitch��pid���㣨��е�Ƕȣ�
				CloudPitch_MACHOPID.Calc(&CloudPitch_MACHOPID, 
															 CloudParam.Axis[Pitch].TargetAngle,
																GetCloudMotorAngle(Pitch) + vision_y);
				CloudPitch_MACHIPID.Calc(&CloudPitch_MACHIPID, 
															 CloudPitch_MACHOPID.Output,  
																GetCloudMotorRotate(Pitch));
							
				if(angle > 0)
				{
					Chassis_speed_offset = 1000.0f * (0.1415f*angle*angle - 0.8226f*angle + 1.5) - 1000;
				}
				else
				{
					Chassis_speed_offset = 1000.0f * (0.1015f*angle*angle - 0.8226f*angle + 1.5) - 1000;
				}
				
				//Ť��ģʽ��ӵ���ֵ
				if (GetChassisWorkMode() == Twister_Mode)
				{
					CloudParam.YawCurrentOutPut = CloudYaw_IPID.Output 
																			+ Chassis_speed_offset;
				}
				else
				{
					CloudParam.YawCurrentOutPut = CloudYaw_IPID.Output;
				}
				
				CloudParam.PitchCurrentOutPut = CloudPitch_MACHIPID.Output;
				CloudParam.Axis[Yaw].TargetAngle = GetCloudMotorAngle(Yaw);		
*/

/*-----------------------------------file of end------------------------------*/

