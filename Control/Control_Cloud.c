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
  |--FileName    : Control_Cloud.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无 & 璨                                                     
  |--Date        : 2019-03-27             
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
#include "Control_Cloud.h" 
#include "Control_PC.h"
#include "Control_Chassis.h"
#include "Control_Shoot.h"

#include "Driver_Judge.h"
#include "Driver_Analysis.h"
#include "Driver_CurrentSetting.h"
#include "Driver_Filter.h"
#include "Driver_DR16.h"
#include "Driver_IMU.h"
#include "Driver_Aiming.h"

/*云台储存结构体*/
Cloud_t Cloud;

/*YAW PITCH轴对应PID*/
positionpid_t Yaw_OuterRing = PosInit_Cloud_YAWOuterRing;
positionpid_t Yaw_InnerRing = PosInit_Cloud_YAWInnerRing;

positionpid_t Pitch_OuterRing = PosInit_Cloud_PitchOuterRing;
positionpid_t Pitch_InnerRing = PosInit_Cloud_PitchInnerRing;

/*IMU异常状态时候的机械控制*/
positionpid_t Yaw_Ring_NIMU = PosInit_Cloud_YAWRing_NIMU;
positionpid_t Yaw_Ring_SIMU = PosInit_Cloud_YAWRing_SIMU;
positionpid_t Pitch_Ring_NIMU = PosInit_Cloud_PITCHRing_NIMU;
positionpid_t Pitch_Ring_SIMU = PosInit_Cloud_PITCHRing_SIMU;

/*自瞄对应PID(定点)*/
positionpid_t Yaw_AimimgRing = PosInit_Cloud_AimingYaw;
positionpid_t Yaw_AimingSeconrdRing = PosInit_Cloud_AimingYawSeconrd;
positionpid_t Pitch_AimingRing = PosInit_Cloud_AimingPitch;
positionpid_t Pitch_AimingSeconrdRing = PosInit_Cloud_AimingPitchSeconrd;

/*自瞄对应PID(跟随)*/
positionpid_t Yaw_AimingFollowRing = PosInit_Cloud_AimingFollowYaw;
positionpid_t Yaw_AimingFollowSeconrdRing = PosInit_Cloud_AimingFollowYawSeconrd;
positionpid_t Pitch_AimingFollowRing = PosInit_Cloud_AimingFollowPitch;
positionpid_t Pitch_AimingFollowSeconrdRing = PosInit_Cloud_AimingFollowPitchSeconrd;


positionpid_t Yaw_AimingFollowRingJZ = PosInit_Cloud_AimingFollowYawJZ;
positionpid_t Yaw_AimingFollowSeconrdRingJZ = PosInit_Cloud_AimingFollowYawSeconrdJZ;
positionpid_t Pitch_AimingFollowRingJZ = PosInit_Cloud_AimingFollowPitchJZ;
positionpid_t Pitch_AimingFollowSeconrdRingJZ = PosInit_Cloud_AimingFollowPitchSeconrdJZ;
/**
  * @Data    2019-03-29 11:19
  * @brief   云台处理赋值
  * @param   uint8_t switchmode
  * @retval  void
  */ 

/*视觉计算出来的补偿值*/
float vision_x,vision_y;
/*X,Y偏差数值*/
float Tempx = 13;
float Tempy  = 3;
float TempxFollow = 9;
float TempyFollow = 20;
void Cloud_Judgement(uint8_t switchmode)
{
		/*云台储存数据变量*/
		float Cloud_delta_Yaw = 0.0f,Cloud_delta_Pitch = 0.0f;
		/*启动自瞄限位开关*/
		int8_t AUTO_shoot_enable = 1;
		
		
		/*是否可以开始自瞄*/
		int8_t AUTO_shoot_flag;
		
		switch(switchmode)
    {
		/**********************************电脑控制********************************/
        case PC_Controling_ON:
					/*鼠标操作的速度可以通过灵敏度来调整*/
					/*补给站模式要微调（多写一种模式）*/

						Cloud_delta_Yaw = DR16.mouse.x*15.0f;
						Cloud_delta_Pitch = -DR16.mouse.y*1.2f;
					
					/*开启自瞄而且自瞄处于激活状态*/
					if(PC.AimingState == 1 && SEDV_BIGER == 0)
					{
//							//君竹版本
//							/*Yaw轴偏差*/
//							/*跟随*/
//							Yaw_AimingFollowRingJZ.Pos_Calc(&Yaw_AimingFollowRingJZ,
//																									vision_offset_x,
//																											VisionData.vision_x);
//							Yaw_AimingFollowSeconrdRingJZ.Pos_Calc(&Yaw_AimingFollowSeconrdRingJZ,
//																												Yaw_AimingFollowRingJZ.PWM,
//																														VisionData.vision_diff_x);
//							/*Pitch轴偏差*/
//							/*跟随*/
//							Pitch_AimingFollowRingJZ.Pos_Calc(&Pitch_AimingFollowRingJZ,
//																						vision_offset_y,
//																								VisionData.vision_y);
//							Pitch_AimingFollowSeconrdRingJZ.Pos_Calc(&Pitch_AimingFollowSeconrdRingJZ,
//																									Pitch_AimingFollowRingJZ.PWM,
//																											VisionData.vision_diff_y);
//							/*跟随*/
//							vision_x = Yaw_AimingFollowSeconrdRingJZ.PWM + IMU_Cloud.data.gyro_z * TempxFollow;
//							vision_y = Pitch_AimingFollowSeconrdRingJZ.PWM + IMU_Cloud.data.gyro_x * TempyFollow;

						
							//创新版本
							/*Yaw轴*/
							Yaw_AimingFollowRing.Pos_Calc(&Yaw_AimingFollowRing,
																								0,
																									CV.Input_x);
							Yaw_AimingFollowSeconrdRing.Pos_Calc(&Yaw_AimingFollowSeconrdRing,
																											Yaw_AimingFollowRing.PWM,
																													CV.ErrorC_x);
						
							/*Pitch轴*/
							Pitch_AimingFollowRing.Pos_Calc(&Pitch_AimingFollowRing,
																						CVOffset_y,
																								CV.Input_y);
							Pitch_AimingFollowSeconrdRing.Pos_Calc(&Pitch_AimingFollowSeconrdRing,
																									Pitch_AimingFollowRing.PWM,
																											CV.ErrorC_y);
						
							vision_x = Yaw_AimingFollowSeconrdRing.PWM + IMU_Cloud.data.gyro_z * TempxFollow;
							vision_y = Pitch_AimingFollowSeconrdRing.PWM + IMU_Cloud.data.gyro_x * TempyFollow;
						
							if ((!ABS(CV.Input_x)&& !ABS(CV.Input_y)) || (CV.OFFLINE_SET == 1) || (CV.Input_z == 0))
							{		
								vision_x = 0;
								vision_y = 0;
							}	

					}
					else if(PC.AimingState == 0 && SEDV_BIGER == 1)
					{
							//创新版本
							/*Yaw轴定点*/
							Yaw_AimimgRing.Pos_Calc(&Yaw_AimimgRing,
																								0,
																							CV.Input_x);
							Yaw_AimingSeconrdRing.Pos_Calc(&Yaw_AimingSeconrdRing,
																									Yaw_AimimgRing.PWM,
																											CV.ErrorC_x);
							
							/*Pitch轴定点*/
							Pitch_AimingRing.Pos_Calc(&Pitch_AimingRing,
																										0,
																								CV.Input_y);
							Pitch_AimingSeconrdRing.Pos_Calc(&Pitch_AimingSeconrdRing,
																									Pitch_AimingRing.PWM,
																											CV.ErrorC_y);
					
							vision_x = Yaw_AimingSeconrdRing.PWM + IMU_Cloud.data.gyro_z * Tempx;
							vision_y = Pitch_AimingSeconrdRing.PWM + IMU_Cloud.data.gyro_x * Tempy;
						
							if ((!ABS(CV.Output_x)&& !ABS(CV.Output_y)) || (CV.OFFLINE_SET == 1)|| (CV.Input_z == 0))
							{		
								vision_x = 0;
								vision_y = 0;
							}	
						
					}
					else
					{
							vision_x = 0;
							vision_y = 0;
					}
					
					//DEBUG
					if(SEV_Delta == 1)
					{
							
					}

        break;

						
		/**********************************遥控控制********************************/
        case RC_Controling_ON:
				
				
        Cloud_delta_Yaw = RCRocket.Right_x *2;
        Cloud_delta_Pitch = RCRocket.Right_y / 7;
				
				/*DEBUG 启动自瞄*/
				
				if(DR16.rc.ch5_wheel < 0)
				{
							//创新版本
							/*Yaw轴*/
							Yaw_AimingFollowRing.Pos_Calc(&Yaw_AimingFollowRing,
																								0,
																									CV.Input_x);
							Yaw_AimingFollowSeconrdRing.Pos_Calc(&Yaw_AimingFollowSeconrdRing,
																											Yaw_AimingFollowRing.PWM,
																													CV.ErrorC_x);
						
							/*Pitch轴*/
							Pitch_AimingFollowRing.Pos_Calc(&Pitch_AimingFollowRing,
																						CVOffset_y,
																								CV.Input_y);
							Pitch_AimingFollowSeconrdRing.Pos_Calc(&Pitch_AimingFollowSeconrdRing,
																									Pitch_AimingFollowRing.PWM,
																											CV.ErrorC_y);
						
							vision_x = Yaw_AimingFollowSeconrdRing.PWM + IMU_Cloud.data.gyro_z * TempxFollow;
							vision_y = Pitch_AimingFollowSeconrdRing.PWM + IMU_Cloud.data.gyro_x * TempyFollow;
						
							if ((!ABS(CV.Input_x)&& !ABS(CV.Input_y)) || (CV.OFFLINE_SET == 1) || (CV.Input_z == 0))
							{		
								vision_x = 0;
								vision_y = 0;
							}	
//							
				}
				else
				{
						vision_x = 0;
						vision_y = 0;
				}
				
				/*如果得到数据回到定点或者计算得出的数值为原点*/
//				if (!ABS(CV.Output_x)&& !ABS(CV.Output_y))
//					{		
//						vision_x = 0;
//						vision_y = 0;
//					}	
//				if(CV.OFFLINE_SET == 1)
//				{
//						vision_x = 0;
//						vision_y = 0;
//				}
				
//				if()
        break;
				
				
		/**********************************失能控制********************************/
        case None_Controling_ON:
				Cloud_delta_Yaw = 0;
				Cloud_delta_Pitch = 0;
				vision_x = 0;
				vision_y = 0;
        break;

        default:
				Cloud_delta_Yaw = 0;
				Cloud_delta_Pitch = 0;
        break;
    }

		if(PC.PCMode == PC_Sevrel)
		{
				Cloud_NormalProcess(Cloud_delta_Yaw,Cloud_delta_Pitch,switchmode);
		}
		else
		{
				Cloud_Process(Cloud_delta_Yaw,Cloud_delta_Pitch,switchmode);
		}

}


/**
  * @Data    2019-03-29 11:33
  * @brief   云台处理
  * @param   float Delta_YAW, float Detla_Pitch,uint8_t switchmode
  * @retval  void
  */
int Counter = 0;
float TempIMUYaw_Raw;
float TempPITCH_Raw;
float TempPushCal;
float Chassis_speed_offset,Cloud_Chassis_speed_offset;
float Exting_Count;
void Cloud_Process(float Delta_YAW, float Detla_Pitch,uint8_t switchmode)
{
	
		Cloud.Yaw_PF = Cloud.Yaw_Raw = RM6020s[0].totalAngle;
		
		/*掉线情况*/
		if(switchmode == None_Controling_ON || \
			 DR16.OFFLINE_SET ==1 || \
			 IMU_Cloud.OFFLINE_SET == 1 || \
			 Judgement_Check.OFFLINE_SET == 1)
				{
				Cloud.IMUYaw_PF = Cloud.IMUYaw_Raw = IMU_Cloud.totalYaw;
				Cloud.IMUPitch_PF = Cloud.IMUPitch_Raw = IMU.eular.roll;

				Cloud.Pitch_PF = Cloud.Pitch_Raw = RM6020s[1].totalAngle;
				Delta_YAW = Detla_Pitch = 0;
				RM6020s[0].outCurrent = 0;
				RM6020s[1].outCurrent = 0;
			
				Cloud_And_Emitter_CurrentSetting(0,0,RM2006s[0].outCurrent,0);
				return;
				}
				
				/*遥控器赋值转换*/	
				Cloud.IMUYaw_Raw += Delta_YAW/ 30.0f ;
				Cloud.Pitch_Raw -= Detla_Pitch;
				
				/*快速掉头*/
				if(PC.CtrlState == 1 && PC.TurnState == 1 && Exting_Count > 50)
				{
						Cloud.IMUYaw_Raw += 4095;
						Exting_Count = 0;
				}
				else
				{
						Exting_Count++;
				}
				
				
				
				
				switch(switchmode)
				{
		/**********************************电脑控制********************************/
						case PC_Controling_ON:
							switch(PC.PCMode)
							{
								case PC_CloudPlatfrom:

									if(Cloud.Pitch_Raw > Cloud_Pitch_Max)
									{
										Cloud.Pitch_Raw = Cloud_Pitch_Max;
									}
									if(Cloud.Pitch_Raw < Cloud_Pitch_Min)
									{
										Cloud.Pitch_Raw = Cloud_Pitch_Min;
									}
									
								break;
									
								case PC_NoneHead:
									/*由于是自旋所以不用YAW轴限幅*/
									if(Cloud.Pitch_Raw > Cloud_Pitch_Max)
										{
											Cloud.Pitch_Raw = Cloud_Pitch_Max;
										}
									if(Cloud.Pitch_Raw < Cloud_Pitch_Min)
										{
											Cloud.Pitch_Raw = Cloud_Pitch_Min;
										}
								break;
								
								case PC_Sevrel:
									/*换到另外一种云台计算模式*/
								break;
								
//								case PC_Swing:
//									break;
							}
						break;
							
							
		/**********************************遥控控制********************************/
						case RC_Controling_ON://限位可能要改,保留看看用不用360
									if(Cloud.Pitch_Raw > Cloud_Pitch_Max)
									{
										Cloud.Pitch_Raw = Cloud_Pitch_Max;
									}
									if(Cloud.Pitch_Raw < Cloud_Pitch_Min)
									{
										Cloud.Pitch_Raw = Cloud_Pitch_Min;
									}
									
						break;
									
									
		/**********************************失能控制********************************/
						case None_Controling_ON:
							
						break;

						default:
						break;
				}
				
				
				/*闭环抵消（云台陀螺仪）*/
				if(IMU_Chassis.OFFLINE_SET == 0)
				{
//						Cloud_Chassis_speed_offset = IMU_Chassis.data.gyro_z*16 / ABS(Yaw_InnerRing.Kp);
						Cloud_Chassis_speed_offset = IMU_Chassis.data.gyro_z*16 / ABS(Yaw_InnerRing.Kp);
				}
				else
				{
						Cloud_Chassis_speed_offset = 0;
				}
				
				/*滤波*/
				Filter_IIRLPF(&Cloud.IMUYaw_Raw,&Cloud.IMUYaw_PF,0.4);
				Filter_IIRLPF(&Cloud.Pitch_Raw,&Cloud.Pitch_PF,0.1);
				
				
				/*机械位置设置,如果打开了弹仓盖子就直接定在中点*/
//				if(SEV_Delta == 1)
//				{
//						M6623_setTargetAngle(1,Cloud_Pitch_Center);
//				}
//				else
//				{
						M6623_setTargetAngle(1,Cloud.Pitch_PF);
//				}
				/*判断是否处于自瞄模式或者神符模式，如果是的话就把当前的对应角度设置成为真是角度，方便自瞄*/
				if(DR16.rc.ch5_wheel < 0 || PC.AimingState == 1 || SEDV_BIGER == 1)
				{
						if(CV.Output_x)
						{
										if((Delta_YAW / 30.0f) != 0)
										{
												vision_x = 0;
										}
										else
										{
												Cloud.IMUYaw_Raw = IMU_Cloud.totalYaw;
												Cloud.IMUYaw_PF = IMU_Cloud.totalYaw;
										}

						}
						if(CV.Output_y)
						{
									if(Detla_Pitch != 0)
									{
											vision_y = 0;
									}
									else
									{
											Cloud.Pitch_Raw = RM6020s[1].totalAngle;
											RM6020s[1].targetAngle = RM6020s[1].totalAngle;
									}
						}
				}
				
				
				/*PID计算*/
				if(RM6020s[0].OFFLINE_SET == 0)
				{
						/*调试需要，如果要稳定的自瞄的话不能加陀螺仪闭环*/
						Yaw_OuterRing.Pos_Calc(&Yaw_OuterRing,Cloud.IMUYaw_PF,IMU_Cloud.totalYaw + vision_x);
						Yaw_OuterRing.PWM = (int)Yaw_OuterRing.PWM;
						Yaw_InnerRing.Pos_Calc(&Yaw_InnerRing,Yaw_OuterRing.PWM,\
						IMU_Cloud.data.gyro_z + Cloud_Chassis_speed_offset);
						RM6020s[0].UpdateFlag = 0;
				}
				
				if(RM6020s[1].OFFLINE_SET == 0)
				{
						/*调试需要*/
						Pitch_OuterRing.Pos_Calc(&Pitch_OuterRing,RM6020s[1].targetAngle,\
						RM6020s[1].totalAngle + vision_y);
						Pitch_InnerRing.Pos_Calc(&Pitch_InnerRing,Pitch_OuterRing.PWM,\
						RM6020s[1].realSpeed);
						RM6020s[1].UpdateFlag = 0;
				}
				
				/*曲线拟合*/
				/*扭腰曲线*/
				if(angle > 0)
				{
							Chassis_speed_offset = 1000.0f * (0.1115f*angle*angle - 0.8226f*angle + 1.3544f) - 1000;
				}
				else	
				{
							Chassis_speed_offset = 1000.0f * (0.1615f*angle*angle - 0.8226f*angle + 1.1544f) - 1000;
				}

				 
				/*扭腰模式抵消，PWM赋值*/
				if(SEDV_Swing == 1 || DR16.rc.s_right == 3)
				{
//						RM6020s[0].outCurrent = (int)(Yaw_InnerRing.PWM - IMU_Chassis.data.gyro_z*16 +Chassis_speed_offset);
						RM6020s[0].outCurrent = (int)(Yaw_InnerRing.PWM + Chassis_speed_offset);
				}
				else
				{
						RM6020s[0].outCurrent = (int)Yaw_InnerRing.PWM;
				}
			
				RM6020s[1].outCurrent = (int)Pitch_InnerRing.PWM;
				
			
		#ifndef CloudDebugMode
			Cloud_CurrentSettingOnlyYaw(RM6020s[0].outCurrent);
			Cloud_CurrentSettingOnlyPitchANDCarr(RM6020s[1].outCurrent,RM2006s[0].outCurrent);
		#endif
}

/**
  * @Data    2019-03-03 15:01
  * @brief   普通云台机械处理（IMU坏掉或者掉线的时候的紧急备用或者补给站模式）
  * @param   void
  * @retval  float
  */
void Cloud_NormalProcess(float Delta_YAW, float Detla_Pitch,uint8_t switchmode)
{
		/*保持云台IMU角度(不管你IMU是否掉线)*/
		/*IMU掉线的时候IMU的值会保持在最后的一个值，所以可能会出现飞车的情况*/
		if(IMU_Cloud.OFFLINE_SET == 0)
		{
				Cloud.IMUYaw_PF = Cloud.IMUYaw_Raw = IMU.totalYaw;
				Cloud.IMUPitch_PF = Cloud.IMUPitch_Raw = IMU.eular.roll;
		}
		
		if(DR16.OFFLINE_SET == 1 || \
			 switchmode == None_Controling_ON /*|| IMU.OFFLINE_SET == 1*/)
		{
				Delta_YAW = 0;
				Detla_Pitch = 0;

				Cloud.Yaw_PF = Cloud.Yaw_Raw = Cloud_Yaw_Center;
				Cloud.Pitch_PF = Cloud.Pitch_Raw = RM6020s[1].totalAngle;

				RM6020s[0].outCurrent = 1;
				RM6020s[1].outCurrent = 1;
				Cloud_And_Emitter_CurrentSetting(0,0,RM2006s[0].outCurrent,0);
				return;
		}
		
		
		Cloud.Pitch_Raw -= Detla_Pitch;
		if(Cloud.Pitch_Raw > Cloud_Pitch_Max)
		{
			Cloud.Pitch_Raw = Cloud_Pitch_Max;
		}
		if(Cloud.Pitch_Raw < Cloud_Pitch_Min) 
		{
			Cloud.Pitch_Raw = Cloud_Pitch_Min;
		}

		Filter_IIRLPF(&Cloud.Pitch_Raw,&Cloud.Pitch_PF,0.1);
		
		/*陀螺仪已经飞了的情况直接切换成为机械模式*/
		RM6020s[0].targetAngle = Cloud_Yaw_Center;
		
		M6623_setTargetAngle(0,Cloud.Yaw_PF);
		M6623_setTargetAngle(1,Cloud.Pitch_PF);
		
		/*陀螺仪掉线的异常状态*/	
				if(RM6020s[0].OFFLINE_SET == 0)
				{
						/**/
						Yaw_Ring_NIMU.Pos_Calc(&Yaw_Ring_NIMU,RM6020s[0].targetAngle,RM6020s[0].totalAngle);
						RM6020s[0].outCurrent = Yaw_Ring_NIMU.PWM;
						RM6020s[0].UpdateFlag = 0;
				}

				if(RM6020s[1].OFFLINE_SET == 0)
				{
						Pitch_Ring_NIMU.Pos_Calc(&Pitch_Ring_NIMU,RM6020s[1].targetAngle,\
						RM6020s[1].totalAngle);
						RM6020s[1].outCurrent = Pitch_Ring_NIMU.PWM;
						RM6020s[1].UpdateFlag = 0;
				}
				
				
			#ifndef CloudDebugMode
			Cloud_CurrentSettingOnlyYaw(RM6020s[0].outCurrent);
			Cloud_CurrentSettingOnlyPitchANDCarr(RM6020s[1].outCurrent,RM2006s[0].outCurrent);
			#endif
		
}


/**
  * @Data    2019-03-03 15:01
  * @brief   获取云台YAW轴和PITCH轴的旋转角度
  * @param   void
  * @retval  float
  */
float GetYAW_withCenter(void)
{
		return(RM6020s[0].totalAngle - Cloud_Yaw_Center) / 22.75f;
}

float GetYAW_withLeft(void)
{
		return(RM6020s[0].totalAngle - Cloud_Yaw_Min) / 22.75f;

}

float GetPitch_withCenter(void)
{
		return(RM6020s[1].totalAngle - Cloud_Pitch_Center);

}

float GetPitch_withDown(void)
{
		return(RM6020s[1].totalAngle - Cloud_Pitch_Min);

}


/**
  * @Data    2019-03-06 18:45
  * @brief   Pitch轴机械角度设定目标轴
  * @param   int Moto_Id,int32_t Target_Angle
  * @retval  void
  */
void M6623_setTargetAngle(int Moto_Id,int32_t Target_Angle)
{
  RM6020s[Moto_Id].targetAngle = Target_Angle;
		
}

/*-----------------------------------file of end------------------------------*/


