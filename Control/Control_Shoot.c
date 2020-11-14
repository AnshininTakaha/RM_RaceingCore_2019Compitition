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
  |--FileName    : Control_Shoot.c                                              
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


/*摩擦轮和拨弹电机状态结构体*/

NewFriction_t FrictionNew;

/*拨弹电机PID初始化*/
positionpid_t Shoot_OuterRing = Cartridge_OuterRing;
positionpid_t Shoot_InnerRing = Cartridge_InnerRing;

static int Couter = 0;
//static int SHOOTCounter;
/**
  * @Data    2019-04-01 15:29
  * @brief   射击数据赋值处理
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
				/*摩擦轮初次启动*/
				uint16_t ON_temp_s = 1000;
				Firction_SpeedSetting(ON_temp_s);
				Shoot_InitPoint++;
				FrictionNew.FrictionReady = 1;
		}
		
		/*规则限制的最大热量*/
    switch(switchmode)
    {
/***********************************电脑控制****************************************/
				case PC_Controling_ON:
					
					if(PC.LeftPressState == 1 || PC.LeftLongPressState == 1)
					{
							FrictionNew.shootFlag = 1;
					}
					else
					{
							FrictionNew.shootFlag = 0;
					}
					
					/*限制最大速度为了防止超出限制加一个自己射击的速度作为下一发的预测值叠加到上面*/
					FrictionNew.ShootSpeedMAX = 30 + ext_shoot_data.bullet_speed;
					
					/*激光瞄准*/
					LASER_ON();
					
					static int ChangeSpeedPoint = 0;
					static int SpeedLastSave= 0;
					int SpeedChangTime = 0;
					static int INIT;
					
					
					/*速度更换*/
					/*只要两个速度，其他的速度不要*/
					if(PC.ChangeFrictionSpeedINIT == 1 && PC.CtrlState == 1)
					{
							INIT++;
					}
					if(PC.ChangeFrictionSpeedINIT == 1 && PC.CtrlState == 1 && INIT >= 100)
					{
							/*启动*/
							if(FrictionNew.FrictionSpeed == frictionSpeedMin || FrictionNew.FrictionSpeed == 0)
							{
									FrictionNew.FrictionSpeed = FrictionHighSpeed;
									ChangeSpeedPoint = 0;
									PC.ChangeFrictionSpeedINIT = 0;
									INITState = 1;
							}
					}
					
					/*速度切换标志位*/
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
					
					/*速度缓慢改变标志位*/
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

					
					/*摩擦轮没有开的话就不开激光*/
					if(FrictionNew.FrictionSpeed <= 1000 )
					{
							LASER_OFF();
					}
					else
					{		
							/*速度变换了，给予操作手提示*/
							if(FrictionNew.FrictionSpeed != SpeedLastSave)
							{
									LASER_OFF();
									SpeedChangTime = 0;
							}
							
							/*数据叠加*/
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
					
					/*速度迭代*/
					SpeedLastSave = FrictionNew.FrictionSpeed;
					
					
					
					if(PC.Toggle_SEV == 1 && PC.CtrlState == 1)
					{
							if(SEV_Delta == 0 && ChangeSEVPoint >= 10)
							{
									SEV_Delta = 1;
								
									/*舵机关盖*/
									LIDSwitch(1);
									ChangeSEVPoint = 0;
									PC.Toggle_SEV = 0;
							}
							if(SEV_Delta == 1 && ChangeSEVPoint >= 10)
							{
									SEV_Delta = 0;
								
									/*舵机开盖*/
									LIDSwitch(0);
									ChangeSEVPoint = 0;
									PC.Toggle_SEV = 0;
							}
					}
					
					
					
        break;

/***********************************遥控控制****************************************/
        case RC_Controling_ON:
        switch(DR16.rc.s_right)
				{
						case Friction_All_OFF:
						//是否可以射击
						FrictionNew.shootFlag = 0;
						//激光是否开启
						LASER_OFF();
						//摩擦轮速度
						FrictionNew.FrictionSpeed = 1000;
						LIDSwitch(1);
						break;
						
						
						case Friction_AND_Laser_ON:
						//是否可以射击
						FrictionNew.shootFlag = 0;
						//激光是否开启
						LASER_ON();
						//摩擦轮速度
						FrictionNew.FrictionSpeed = 1280;
						LIDSwitch(0);
						break;
						
						
						case Cartridge_AND_Laser_ON:
						/*最大速度为1960*/
								FrictionNew.FrictionSpeed = 1280;
								FrictionNew.shootFlag = 1;
						LIDSwitch(1);
						LASER_ON();
						/*射击频率*/
						FrictionNew.shootFreq = 100;
						FrictionNew.ShootSpeedMAX = 60;

						break;
						
						default:
						break;
				}
        break;

/***********************************控制失能****************************************/
        case None_Controling_ON:
				Shoot_Process(0,switchmode);
				FrictionNew.shootFlag = 0;
				FrictionNew.FrictionSpeed = 1000;
        break;

/***********************************默认****************************************/
        default:
				Shoot_Process(0,switchmode);
        break;
    }
		
		Shoot_Process(FrictionNew.FrictionSpeed,switchmode);
}



/**
  * @Data    2019-04-01 19:20
  * @brief   射击处理
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
		
		/*摩擦轮速度限制*/
		Firction_SpeedSetting(firctionSpeed);

		/*热量计算*/
		if(Judgement_Check.OFFLINE_SET == 0)
		{
			/*冷却频率降低保证射击正常，直接通过裁判系统的限制来计算*/
			//DEBUG
			FrictionNew.shootFreq = 10;
			
			/*当前热量计算*/
			/*计算步兵当前等级对应的枪口热量*/
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
			
			
			/*是否处于占领碉堡状态*/
			if(ext_buff_musk.power_rune_buff  & (1 << 1))
			{
				 FrictionNew.BunkerFlag = 1;
			}
			else
			{
					FrictionNew.BunkerFlag = 0;
			}
			
			
			
			/*通过热量计算剩余可以发射的发数*/
			FrictionNew.AllowShootCount = \
			(FrictionNew.FrictionUpdata - ext_power_heat_data.shooter_heat0) \
			/ FrictionNew.ShootSpeedMAX;
			
//			SHOOTCOUNTER = FrictionNew.AllowShootCount;
			/*如果两次的发射速度不同的话就算作发射子弹出去了*/
			if(ABS(ext_shoot_data.bullet_speed - FrictionNew.LastShootSpeed) > 0)
			{
					if(FrictionNew.shootFlag == 1 && FrictionNew.ShootOverFlag == 0)
					{
							FrictionNew.bulletcount++;
							FrictionNew.ShootOverFlag = 1;
					}
			}
			/*判断是否可以发射子弹(注意！！！无论是否请求拨弹都会更新！！！！！！)*/
			if(FrictionNew.AllowShootCount - FrictionNew.bulletcount > 1)
			{
				/*至少保证当前热量（会更新状态下）的热量至少大于2到3个弹丸*/
				/*由于热量的更新有延迟*/
				if(ext_power_heat_data.shooter_heat0 < FrictionNew.FrictionUpdata - 45)
				{
  				FrictionNew.HeatShootFlag = 1;
					/*储存当前的射击热量*/
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
				/*调试模式或者遥控器掉线，直接用遥控器赋值的冷却值*/
		}
		
		/*射击冷却*/
		if(freqCounter++ > FrictionNew.shootFreq)
		{
				FrictionNew.shootReady = 1;
				freqCounter = 0;
		}
		
		/*shootFlag为外部触发的标志位，shootReady为最短发射时间冷却*/
		/*loadFinish为分次拨盘数据解析是否完成，HeatShootFlag为射击热量限制开关*/
		if(FrictionNew.shootFlag == 1 && FrictionNew.shootReady == 1 && \
			FrictionNew.loadFinish == 1)
		{
				if(FrictionNew.HeatShootFlag == 1 || Judgement_Check.OFFLINE_SET == 1)
				{
						/*目标值改变*/
						if(SEDV_BIGER == 0)
						{
								RM2006s[0].targetAngle += Fire_Round;
							  BulletNumberOutput++;
								freqCounter = 0;
						
								/*判断为已经射击出去了*/
								FrictionNew.ShootOverFlag = 0;
						
								/*重新冷却*/
								FrictionNew.shootReady = 0;
								FrictionNew.shootFlag = 0;
								BIGState = 0;
						}
						else if(SEDV_BIGER == 1 && CV.RealFrontSet == 1)
						{
								if((BIGState)% 4 == 0)
								{
										/*大神符计数射击开关*/
										BIGState++;
										RM2006s[0].targetAngle += Fire_Round;
										BulletNumberOutput+=1;
										
										freqCounter = 0;
										/*判断为已经射击出去了*/
										FrictionNew.ShootOverFlag = 0;
								
										/*重新冷却*/
										FrictionNew.shootReady = 0;
										FrictionNew.shootFlag = 0;
								}
								else
								{
										BIGState++;
										freqCounter = 0;
						
										/*判断为已经射击出去了*/
										FrictionNew.ShootOverFlag = 0;
								
										/*重新冷却*/
										FrictionNew.shootReady = 0;
										FrictionNew.shootFlag = 0;
								}
						}
						
				}
		}
		
		/*PID计算和卡弹判断*/
		if(RM2006s[0].OFFLINE_SET == 0)
		{
				/*状态标志位停止*/
				/*顺向卡弹*/
				static uint8_t Shoot_blocking = 0;
				/*逆向卡弹*/
				static uint16_t Shoot_Seconrd_blocking = 0;
				
				static int blockCounter = 0;
				FrictionNew.loadFinish = 0;
				
				Shoot_OuterRing.Pos_Calc(&Shoot_OuterRing,RM2006s[0].targetAngle,RM2006s[0].totalAngle);
				Shoot_InnerRing.Pos_Calc(&Shoot_InnerRing,Shoot_OuterRing.PWM,RM2006s[0].realSpeed);
				RM2006s[0].outCurrent = Shoot_InnerRing.PWM;
				
				
				if(ABS(RM2006s[0].outCurrent) > 3000 && ABS(RM2006s[0].realSpeed) < 50 && \
					blockCounter++ > 20)
				{
						/*卡弹循环*/
						if(Shoot_blocking %2 == 0)
						{
							  /*状态叠加*/
								Shoot_blocking++;
								
								/*改变状态值*/
								RM2006s[0].targetAngle -= Fire_Round*2;
								Shoot_Seconrd_blocking++;
						}
						
						/*如果已经卡住 回转*/
						if(Shoot_blocking %2 == 1)
						{
								if(ABS(RM2006s[0].outCurrent) > 3000 && ABS(RM2006s[0].realSpeed) < 50 && \
								Shoot_Seconrd_blocking++ > 20)
								{
										/*状态叠加*/
										Shoot_blocking++;
										
										/*改变状态值*/
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
	* @brief   设置摩擦轮速度
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


