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
  |--FileName    : Control_Shoot.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ���� & �                                                     
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
 
#include "Control_Shoot.h" 
#include "Task_Control.h"

#include "Switch.h"
#include "Control_PC.h"
#include "Driver_Judge.h"
#include "Driver_slope.h"
#include "Driver_PID.h"
#include "Driver_DR16.h"
#include "Driver_Analysis.h"
#include "Driver_Aiming.h"
#include "Driver_CurrentSetting.h"
#include "BSP_Init.h"


/*Ħ���ֺͲ������״̬�ṹ��*/

NewFriction_t FrictionNew;

/*�������PID��ʼ��*/
positionpid_t Shoot_OuterRing = Cartridge_OuterRing;
positionpid_t Shoot_InnerRing = Cartridge_InnerRing;

static int Couter = 0;
//static int SHOOTCounter;
/**
  * @Data    2019-04-01 15:29
  * @brief   ������ݸ�ֵ����
  * @param   uint8_t switchmode
  * @retval  void
  */
int ChangeSEVPoint = 0;
int SEV_Delta = 0;
int shot;
int NormalSpeedType,LowSpeedType;
int BIGState = 1;
int SpeedChangeTap = 0;
int INITState = 0;
void Shoot_Judgement(uint8_t switchmode)
{
	static int Shoot_InitPoint = 0;
	float SevorCheck;
		if(Shoot_InitPoint < 5)
		{
				/*Ħ���ֳ�������*/
				uint16_t ON_temp_s = 1000;
				Firction_SpeedSetting(ON_temp_s);
				Shoot_InitPoint++;
				FrictionNew.FrictionReady = 1;
		}
		
		/*�������Ƶ��������*/
    switch(switchmode)
    {
/***********************************���Կ���****************************************/
				case PC_Controling_ON:
					
					if(PC.LeftPressState == 1 || PC.LeftLongPressState == 1)
					{
							FrictionNew.shootFlag = 1;
					}
					else
					{
							FrictionNew.shootFlag = 0;
					}
					
					/*��������ٶ�Ϊ�˷�ֹ�������Ƽ�һ���Լ�������ٶ���Ϊ��һ����Ԥ��ֵ���ӵ�����*/
					FrictionNew.ShootSpeedMAX = 30 + ext_shoot_data.bullet_speed;
					
					/*������׼*/
					LASER_ON();
					
					static int ChangeSpeedPoint = 0;
					static int SpeedLastSave= 0;
					int SpeedChangTime = 0;
					static int INIT;
					
					
					/*�ٶȸ���*/
					/*ֻҪ�����ٶȣ��������ٶȲ�Ҫ*/
					if(PC.ChangeFrictionSpeedINIT == 1 && PC.CtrlState == 1)
					{
							INIT++;
					}
					if(PC.ChangeFrictionSpeedINIT == 1 && PC.CtrlState == 1 && INIT >= 100)
					{
							/*����*/
							if(FrictionNew.FrictionSpeed == frictionSpeedMin || FrictionNew.FrictionSpeed == 0)
							{
									FrictionNew.FrictionSpeed = FrictionHighSpeed;
									ChangeSpeedPoint = 0;
									PC.ChangeFrictionSpeedINIT = 0;
									INITState = 1;
							}
					}
					
					/*�ٶ��л���־λ*/
					if(PC.ShiftState == 1 && PC.ChangeFrictionSpeed == 1)
					{
							if(FrictionNew.FrictionSpeed == FrictionHighSpeed && ChangeSpeedPoint >= 10)
							{
									SpeedChangeTap = 1;
									ChangeSpeedPoint = 0;
									PC.ChangeFrictionSpeed = 0;
							}
							else if(FrictionNew.FrictionSpeed == FrictionLowSpeed && ChangeSpeedPoint >= 10)
							{
									SpeedChangeTap = 0;
									ChangeSpeedPoint = 0;
									PC.ChangeFrictionSpeed = 0;
							}
					}
					else
					{
							ChangeSpeedPoint++;
					}
					
					/*�ٶȻ����ı��־λ*/
					if(SpeedChangeTap == 1 && INITState == 1)
					{
							FrictionNew.FrictionSpeed -= 20;
							if(FrictionNew.FrictionSpeed < FrictionLowSpeed)
							{
									FrictionNew.FrictionSpeed = FrictionLowSpeed;
							}
					}
					else if(SpeedChangeTap == 0 && INITState == 1)
					{
							FrictionNew.FrictionSpeed += 20;
							if(FrictionNew.FrictionSpeed > FrictionHighSpeed)
							{
									FrictionNew.FrictionSpeed = FrictionHighSpeed;
							}
					}
					else
					{
							
					}

					
					/*Ħ����û�п��Ļ��Ͳ�������*/
					if(FrictionNew.FrictionSpeed <= 1000 )
					{
							LASER_OFF();
					}
					else
					{		
							/*�ٶȱ任�ˣ������������ʾ*/
							if(FrictionNew.FrictionSpeed != SpeedLastSave)
							{
									LASER_OFF();
									SpeedChangTime = 0;
							}
							
							/*���ݵ���*/
							SpeedChangTime++;
							
							if(SpeedChangTime > 20000000)
							{
									LASER_ON();
									if(SpeedChangTime > 40000000)
									{
											LASER_OFF();
											if(SpeedChangTime > 60000000)
											{
													LASER_ON();
											} 
									}
							}
					}
					
					/*�ٶȵ���*/
					SpeedLastSave = FrictionNew.FrictionSpeed;
					
					
					
					if(PC.Toggle_SEV == 1 && PC.CtrlState == 1)
					{
							if(SEV_Delta == 0 && ChangeSEVPoint >= 10)
							{
									SEV_Delta = 1;
								
									/*����ظ�*/
									LIDSwitch(1);
									ChangeSEVPoint = 0;
									PC.Toggle_SEV = 0;
							}
							if(SEV_Delta == 1 && ChangeSEVPoint >= 10)
							{
									SEV_Delta = 0;
								
									/*�������*/
									LIDSwitch(0);
									ChangeSEVPoint = 0;
									PC.Toggle_SEV = 0;
							}
					}
					
					
					
        break;

/***********************************ң�ؿ���****************************************/
        case RC_Controling_ON:
        switch(DR16.rc.s_right)
				{
						case Friction_All_OFF:
						//�Ƿ�������
						FrictionNew.shootFlag = 0;
						//�����Ƿ���
						LASER_OFF();
						//Ħ�����ٶ�
						FrictionNew.FrictionSpeed = 1000;
						LIDSwitch(1);
						break;
						
						
						case Friction_AND_Laser_ON:
						//�Ƿ�������
						FrictionNew.shootFlag = 0;
						//�����Ƿ���
						LASER_ON();
						//Ħ�����ٶ�
						FrictionNew.FrictionSpeed = 1280;
						LIDSwitch(0);
						break;
						
						
						case Cartridge_AND_Laser_ON:
						/*����ٶ�Ϊ1960*/
								FrictionNew.FrictionSpeed = 1280;
								FrictionNew.shootFlag = 1;
						LIDSwitch(1);
						LASER_ON();
						/*���Ƶ��*/
						FrictionNew.shootFreq = 100;
						FrictionNew.ShootSpeedMAX = 60;

						break;
						
						default:
						break;
				}
        break;

/***********************************����ʧ��****************************************/
        case None_Controling_ON:
				Shoot_Process(0,switchmode);
				FrictionNew.shootFlag = 0;
				FrictionNew.FrictionSpeed = 1000;
        break;

/***********************************Ĭ��****************************************/
        default:
				Shoot_Process(0,switchmode);
        break;
    }
		
		Shoot_Process(FrictionNew.FrictionSpeed,switchmode);
}



/**
  * @Data    2019-04-01 19:20
  * @brief   �������
  * @param   uint8_t switchmode
  * @retval  void
  */
static uint16_t freqCounter = 0;
uint16_t Heat_Record = 0;
static int ShootTick_5ms;

void Shoot_Process(uint16_t firctionSpeed,uint8_t switchmode)
{
		
		if( switchmode == None_Controling_ON)
		{
			RM2006s[0].turnCount = 0;
			RM2006s[0].targetAngle = RM2006s[0].totalAngle = RM2006s[0].realAngle;
		}
		
		/*Ħ�����ٶ�����*/
		Firction_SpeedSetting(firctionSpeed);

		/*��������*/
		if(Judgement_Check.OFFLINE_SET == 0)
		{
			/*��ȴƵ�ʽ��ͱ�֤���������ֱ��ͨ������ϵͳ������������*/
			//DEBUG
			FrictionNew.shootFreq = 10;
			
			/*��ǰ��������*/
			/*���㲽����ǰ�ȼ���Ӧ��ǹ������*/
			switch(ext_game_robot_state.robot_level)
			{
				case 1:
					FrictionNew.FrictionUpdata = 240;
					break;
				case 2:
					FrictionNew.FrictionUpdata = 360;
					break;
				case 3:
					FrictionNew.FrictionUpdata = 480;
					break;
				default:
					FrictionNew.FrictionUpdata = 240;
					break;
			}
			
			
			/*�Ƿ���ռ��ﱤ״̬*/
			if(ext_buff_musk.power_rune_buff  & (1 << 1))
			{
				 FrictionNew.BunkerFlag = 1;
			}
			else
			{
					FrictionNew.BunkerFlag = 0;
			}
			
			
			
			/*ͨ����������ʣ����Է���ķ���*/
			FrictionNew.AllowShootCount = \
			(FrictionNew.FrictionUpdata - ext_power_heat_data.shooter_heat0) \
			/ FrictionNew.ShootSpeedMAX;
			
//			SHOOTCOUNTER = FrictionNew.AllowShootCount;
			/*������εķ����ٶȲ�ͬ�Ļ������������ӵ���ȥ��*/
			if(ABS(ext_shoot_data.bullet_speed - FrictionNew.LastShootSpeed) > 0)
			{
					if(FrictionNew.shootFlag == 1 && FrictionNew.ShootOverFlag == 0)
					{
							FrictionNew.bulletcount++;
							FrictionNew.ShootOverFlag = 1;
					}
			}
			/*�ж��Ƿ���Է����ӵ�(ע�⣡���������Ƿ����󲦵�������£�����������)*/
			if(FrictionNew.AllowShootCount - FrictionNew.bulletcount > 1)
			{
				/*���ٱ�֤��ǰ�����������״̬�£����������ٴ���2��3������*/
				/*���������ĸ������ӳ�*/
				if(ext_power_heat_data.shooter_heat0 < FrictionNew.FrictionUpdata - 45)
				{
  				FrictionNew.HeatShootFlag = 1;
					/*���浱ǰ���������*/
					Heat_Record = ext_power_heat_data.shooter_heat0;
				}
			}
			else
			{
					FrictionNew.HeatShootFlag = 0;
					ShootTick_5ms++;
  					if(ShootTick_5ms > 20)
						{
								if(ABS(ext_power_heat_data.shooter_heat0 - Heat_Record) > 0)
								{
										FrictionNew.bulletcount = 0;
								}
								ShootTick_5ms = 0;
						}
			}
		}
		else
		{
				/*����ģʽ����ң�������ߣ�ֱ����ң������ֵ����ȴֵ*/
		}
		
		/*�����ȴ*/
		if(freqCounter++ > FrictionNew.shootFreq)
		{
				FrictionNew.shootReady = 1;
				freqCounter = 0;
		}
		
		/*shootFlagΪ�ⲿ�����ı�־λ��shootReadyΪ��̷���ʱ����ȴ*/
		/*loadFinishΪ�ִβ������ݽ����Ƿ���ɣ�HeatShootFlagΪ����������ƿ���*/
		if(FrictionNew.shootFlag == 1 && FrictionNew.shootReady == 1 && \
			FrictionNew.loadFinish == 1)
		{
				if(FrictionNew.HeatShootFlag == 1 || Judgement_Check.OFFLINE_SET == 1)
				{
						/*Ŀ��ֵ�ı�*/
						if(SEDV_BIGER == 0)
						{
								RM2006s[0].targetAngle += Fire_Round;
							  BulletNumberOutput++;
								freqCounter = 0;
						
								/*�ж�Ϊ�Ѿ������ȥ��*/
								FrictionNew.ShootOverFlag = 0;
						
								/*������ȴ*/
								FrictionNew.shootReady = 0;
								FrictionNew.shootFlag = 0;
								BIGState = 0;
						}
						else if(SEDV_BIGER == 1 && CV.RealFrontSet == 1)
						{
								if((BIGState)% 4 == 0)
								{
										/*����������������*/
										BIGState++;
										RM2006s[0].targetAngle += Fire_Round;
										BulletNumberOutput+=1;
										
										freqCounter = 0;
										/*�ж�Ϊ�Ѿ������ȥ��*/
										FrictionNew.ShootOverFlag = 0;
								
										/*������ȴ*/
										FrictionNew.shootReady = 0;
										FrictionNew.shootFlag = 0;
								}
								else
								{
										BIGState++;
										freqCounter = 0;
						
										/*�ж�Ϊ�Ѿ������ȥ��*/
										FrictionNew.ShootOverFlag = 0;
								
										/*������ȴ*/
										FrictionNew.shootReady = 0;
										FrictionNew.shootFlag = 0;
								}
						}
						
				}
		}
		
		/*PID����Ϳ����ж�*/
		if(RM2006s[0].OFFLINE_SET == 0)
		{
				/*״̬��־λֹͣ*/
				/*˳�򿨵�*/
				static uint8_t Shoot_blocking = 0;
				/*���򿨵�*/
				static uint16_t Shoot_Seconrd_blocking = 0;
				
				static int blockCounter = 0;
				FrictionNew.loadFinish = 0;
				
				Shoot_OuterRing.Pos_Calc(&Shoot_OuterRing,RM2006s[0].targetAngle,RM2006s[0].totalAngle);
				Shoot_InnerRing.Pos_Calc(&Shoot_InnerRing,Shoot_OuterRing.PWM,RM2006s[0].realSpeed);
				RM2006s[0].outCurrent = Shoot_InnerRing.PWM;
				
				
				if(ABS(RM2006s[0].outCurrent) > 3000 && ABS(RM2006s[0].realSpeed) < 50 && \
					blockCounter++ > 20)
				{
						/*����ѭ��*/
						if(Shoot_blocking %2 == 0)
						{
							  /*״̬����*/
								Shoot_blocking++;
								
								/*�ı�״ֵ̬*/
								RM2006s[0].targetAngle -= Fire_Round*2;
								Shoot_Seconrd_blocking++;
						}
						
						/*����Ѿ���ס ��ת*/
						if(Shoot_blocking %2 == 1)
						{
								if(ABS(RM2006s[0].outCurrent) > 3000 && ABS(RM2006s[0].realSpeed) < 50 && \
								Shoot_Seconrd_blocking++ > 20)
								{
										/*״̬����*/
										Shoot_blocking++;
										
										/*�ı�״ֵ̬*/
										RM2006s[0].targetAngle += Fire_Round*2;
										blockCounter = 0;
										Shoot_Seconrd_blocking = 0;
								}
						}
				}
				
				if(ABS(Shoot_OuterRing.error) < 8000)
				{
						FrictionNew.loadFinish = 1;
						Shoot_blocking = 0;
						blockCounter = 0;
				}
				
				if(ABS(RM2006s[0].turnCount) > 100)
				{	
						RM2006s[0].targetAngle -= (8192*RM2006s[0].turnCount);
						RM2006s[0].turnCount = 0;
				}
			
		}
		
		FrictionNew.LastShootSpeed = ext_shoot_data.bullet_speed;
		
		#ifndef ShootDebugMode
		Cloud_CurrentSettingOnlyPitchANDCarr(RM6020s[1].outCurrent,RM2006s[0].outCurrent);
		#endif
}


/**
	* @Data    2019-04-02 17:13
	* @brief   ����Ħ�����ٶ�
	* @param   uint16_t speed
	* @retval  void
	*/
void Firction_SpeedSetting(uint16_t speed)
{
		if(speed > frictionSpeedMax)
    {
        speed = frictionSpeedMax;
    }
    if(speed < frictionSpeedMin)
    {
        speed = frictionSpeedMin;
    }

    TIM_SetComparex[0](TIM5, speed);
    TIM_SetComparex[1](TIM5, speed);
}






/*-----------------------------------file of end------------------------------*/


