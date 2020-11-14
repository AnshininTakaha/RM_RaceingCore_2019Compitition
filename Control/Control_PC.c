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
  |--FileName    : Control_PC.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无 & 璨                                                     
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
#include "Control_PC.h"
#include "Control_Shoot.h"
#include "Driver_slope.h"
#include "Driver_Judge.h"

#include "Switch.h"
 
/*定义电脑控制储存结构体*/
PC_t PC;
/*键位确定*/
/*方向控制键位*/
/*WASD方向控制*/
/*QE自旋控制*/
/*Shift+方向键位加速*/
/*Ctrl+方向键位减速(切换成大装甲的瞄准模式)*/
/*R：*/
/*Ctrl + F:切换成为机械模式（IMU掉线）*/
/*G:大神符模式*/
/*Z:*/
/*X:*/
/*Ctrl + C:切换成为云台跟随模式*/
/*Ctrl + V:切换成为自旋模式*/
/*B:自旋模式 */
/*左键：*/
/*右键：自瞄*/ 
 /**
  * @Data    2019-03-07 21:10
  * @brief   电脑控制初始化
  * @param   void
  * @retval  void
  */
void PC_Init(void)
{
  /*初始化默认为云台跟随模式*/
  PC.PCMode = PC_CloudPlatfrom;
  PC.InitState = 1;
}

/**
  * @Data    2019-03-16 10:43
  * @brief   PC控制总处理
  * @param   void
  * @retval  void
  */
void PCControl_Process(void)
{
  /*特殊键位判定*/
  SpeicalKey_Process();
//  Modechange_Judgement();
  Derection_Process(&PCRocket);
}

/**
  * @Data    2019-03-10 19:44
  * @brief   特殊功能键位判定
  * @param   void
  * @retval  void
  */

/*大神符启动标志位*/
float SEDV_BIGER = 0;
/*大神符切换计数标志位*/
uint32_t BIGChangePoint = 0;
	
/*自转模式启动标志位*/
float SEDV_NoneHeadMode = 0;
/*无头模式切换计数标志位*/
uint32_t NoneHeadPoint= 0;

/*扭腰模式启动标志位*/
float SEDV_Swing = 0;
/*扭腰模式切换计数标志位*/
float Swing_StateCounter = 0;

/*切换大小装甲标志位*/
float SECV_BIGModule = 0;
/*切换大小装甲计数标志位*/
float BIGModule_Counter = 0;


void SpeicalKey_Process(void)
{
  /*记录特殊按键的标志，只要按下就会有对应的标志*/
	/*******************按下Shift******************/
	/*按下Shift:加速*/
  if(GetKeyMouseAction(KEYBOARD_PRESSED_SHIFT,PRESS))
  {
			PC.ShiftState = 1;
  }
  else
  {
			PC.ShiftState = 0;
  }

	
  /*******************按下Ctrl******************/
	/*按下Ctrl:减速*/
  if(GetKeyMouseAction(KEYBOARD_PRESSED_CTRL,PRESS))
  {
			PC.CtrlState = 1;
  }
  else
  {
			PC.CtrlState = 0;
  }
	

	/*******************按下G******************/

	/*点击G：切换成为自转模式*/
	if(GetKeyMouseAction(KEYBOARD_PRESSED_G,PRESS))
	{
			PC.NoneHeadState = 1;
			SEDV_Swing = 0;
	}
	else
	{
			NoneHeadPoint++;
			PC.NoneHeadState = 0;
	}
	
	/*判断当前状态标志位*/
	if(SEDV_NoneHeadMode == 0 && NoneHeadPoint >= 5 && PC.NoneHeadState == 1)
	{
			PC.PCMode = PC_NoneHead;
			SEDV_NoneHeadMode = 1;
			NoneHeadPoint = 0;
	}
	else if(SEDV_NoneHeadMode == 1 && NoneHeadPoint >= 5 && PC.NoneHeadState == 1)
	{
			PC.PCMode = PC_CloudPlatfrom;
			SEDV_NoneHeadMode = 0;
			NoneHeadPoint = 0;
			SEDV_Swing = 0;
	}

	/*******************按下V******************/
	/*点击SHIFT+V：大神符*/
	if(GetKeyMouseAction(KEYBOARD_PRESSED_V,PRESS))
	{
			PC.DamnBigState = 1;
	}
	else
	{
			BIGChangePoint++;
			PC.DamnBigState = 0;
	}
	
	if(PC.DamnBigState == 1 && PC.ShiftState == 1)
	{
			if(BIGChangePoint >=5 && SEDV_BIGER == 0)
			{
					SEDV_BIGER = 1;
					BIGChangePoint = 0;
					PC.BIGState = 0;
			}
			else if(BIGChangePoint >= 5 && SEDV_BIGER == 1)
			{
					SEDV_BIGER = 0;
					BIGChangePoint = 0;
					PC.BIGState = 0;
			}
	}
//	else
//	{
//			BIGChangePoint++;
//	}

	
	
	/*******************按下R******************/
	/*点击Ctrl+R：开启弹仓*/
	/*点击R：开启云台追随模式*/
	if(GetKeyMouseAction(KEYBOARD_PRESSED_R,PRESS))
	{
			PC.Toggle_SEV = 1;
			if(PC.CtrlState == 0)
			{
					PC.PCMode = PC_CloudPlatfrom;
					/*打断扭腰模式*/
					SEDV_Swing = 0;
					/*打断自转模式*/
					SEDV_NoneHeadMode = 0;
					/*打断大神符模式*/
					SEDV_BIGER = 0;
					/*打断大装甲模式*/
					SECV_BIGModule = 0;
			}
	}
	else
	{
			PC.Toggle_SEV = 0;
			ChangeSEVPoint++;
	}
	
	/*******************按下X******************/
	/*长按Ctrl+X:初始化摩擦轮*/
	if(GetKeyMouseAction(KEYBOARD_PRESSED_X,PRESS))
	{
			PC.ChangeFrictionSpeedINIT = 1;
	}
	else
	{
			PC.ChangeFrictionSpeedINIT = 0;
	}
	
	/*******************按下C******************/
	/*点击Shift+C：切换大小装甲版面*/
	if(GetKeyMouseAction(KEYBOARD_PRESSED_C,PRESS))
	{
			PC.BIGMODULEState = 1;
	}
	else
	{
			BIGModule_Counter++;
			PC.BIGMODULEState = 0;
	}
	
	if(PC.ShiftState == 1 && PC.BIGMODULEState ==1 && BIGModule_Counter >= 5)
	{
			if(SECV_BIGModule == 1)
			{
					SECV_BIGModule = 0;
					BIGModule_Counter = 0;
			}
			else if(SECV_BIGModule == 0)
			{
					SECV_BIGModule = 1;
					BIGModule_Counter = 0;
			}
	}

	
	
	/*******************按下Q******************/
	/*点击Ctrl+Q:180掉头*/
	if(GetKeyMouseAction(KEYBOARD_PRESSED_Q,PRESS))
	{
			PC.TurnState = 1;
	}
	else
	{
			PC.TurnState = 0;
	}
	
	/*******************按下F******************/
	/*点击F：按下扭腰*/
	if(GetKeyMouseAction(KEYBOARD_PRESSED_F,PRESS))
	{
			PC.SwingState = 1;
			PC.PCMode = PC_CloudPlatfrom;
			/*打断自旋*/
			SEDV_NoneHeadMode = 0;
			
	}
	else
	{
			Swing_StateCounter++;
			PC.SwingState = 0;
	}
	if(Swing_StateCounter >= 5 && PC.SwingState == 1)
	{
			if(SEDV_Swing == 1)
			{
					SEDV_Swing = 0;
					PC.SwingState = 0;
					Swing_StateCounter = 0;
			}
			else if(SEDV_Swing == 0)
			{
					SEDV_Swing = 1;
					PC.SwingState = 0;
					Swing_StateCounter = 0;
			}
	}
	
	/*******************按下Z******************/
	/*点击Shitt+Z，摩擦轮改变速度*/
	if(GetKeyMouseAction(KEYBOARD_PRESSED_Z,PRESS))
	{
			PC.ChangeFrictionSpeed = 1;
	}
	else
	{
			PC.ChangeFrictionSpeed = 0;
	}
	
	/*******************按下B******************/
	/*按下B：启动自动跟随模式*/
//	if(GetKeyMouseAction(KEYBOARD_PRESSED_B,PRESS))
//	{
//			
//	}
//	else
//	{
//			
//	}
	
	/*按下鼠标左键*/
	if(GetKeyMouseAction(MOUSE_PRESS_L,PRESS))
  {
			PC.LeftPressState = 1; 
	}
	else
	{
			PC.LeftPressState = 0;
	}
	/*长按鼠标左键*/
	if(GetKeyMouseAction(MOUSE_PRESS_L,LONG_PRESS) /*&& GetKeyMouseAction(MOUSE_PRESS_L,PRESS)*/)
	{
			PC.LeftLongPressState = 1;
	}
	else
	{
			PC.LeftLongPressState = 0;
	}
	
	
	/*按下鼠标右键*/
	if(GetKeyMouseAction(MOUSE_PRESS_R,PRESS))
	{
			PC.RightPressState = 1;
			/*启动自瞄*/
			PC.AimingState = 1;
			/*打断大神符*/
			SEDV_BIGER = 0;
	}
	else
	{
			PC.RightPressState = 0;
			PC.AimingState = 0;
	}
	/*长按鼠标右键*/
	if(GetKeyMouseAction(MOUSE_PRESS_R,LONG_PRESS) /*&& GetKeyMouseAction(MOUSE_PRESS_R,PRESS)*/)
	{
			PC.RightLongPressState = 1;
	}
	else
	{
			PC.RightLongPressState = 0;
	}

	
	
	
	
	/*信息发送判定*/
	/*是否开启了大神符*/
	/*0红色，2蓝色,1为红蓝都可以识别*/
	if(SEDV_BIGER == 1)
	{
			if(ext_game_robot_state.robot_id > 7)
			{
					USART_ALLFSendChar(USART6,"S212E");
			}
			else
			{
					USART_ALLFSendChar(USART6,"S210E");
			}
			
	}
	
	/*自瞄大装甲*/
	if(SECV_BIGModule == 1 && SEDV_BIGER == 0)
	{
			if(ext_game_robot_state.robot_id > 7)
			{
				
					USART_ALLFSendChar(USART6,"S120E");
			}
			else
			{
					USART_ALLFSendChar(USART6,"S122E");
			}
	}
	
	/*自瞄小装甲*/
	if(SECV_BIGModule == 0 && SEDV_BIGER == 0)
	{
			if(ext_game_robot_state.robot_id > 7)
			{
					USART_ALLFSendChar(USART6,"S110E");
			}
			else
			{
					USART_ALLFSendChar(USART6,"S112E");
			}
	}
	
}

/**
  * @Data    2019-03-10 20:35
  * @brief   模式改变判定
  * @param   void
  * @retval  void
  */
//void Modechange_Judgement(void)
//{
//  if(PC.CtrlState == 1)
//  {
//    /*识别组合键*/
//		if(PC_CloudPlatfromChange)/*Ctrl + B*/
//		{
//			PC.PCMode = PC_NoneHead;
//		}
//		
//		/*云台追踪模式*/
//		if(PC_NoneHeadChange)/*Ctrl + V*/
//		{
////			PC.PCMode =  PC_NoneHead;
//			PC.PCMode =  PC_CloudPlatfrom;
//		}
//		
//		if(PC_SwingChange)/*Ctrl + C*/
//		{
//				PC.PCMode =  PC_Swing;
//		}
//		
//		if(PC_SevrelChange)/*Ctl + F*/
//		{
//			PC.PCMode = PC_Sevrel;
//		}
//		
//		
//  }
//}

/**
  * @Data    2019-03-10 21:00
  * @brief   方向和速度判断处理
  * @param   RCRocket_t *rocket
  * @retval  void
  */
void Derection_Process(PCRocket_t *rocket)
{
  float SpeedNow = 0;
  float Q_SpeedNow = 0,E_SpeedNow = 0;

	/*注意超功率问题，这里多加一个开关来限制，以及判断顺序问题*/
  if(PC.ShiftState == 1 && ChassPowerStatus <= OverPower_Many)
  {
    SpeedNow = Speed_Fast;
  }
  else if(PC.CtrlState == 1)
  {
    SpeedNow = Speed_Low;
  }
	//DEBUG
//	else if(SEV_Delta == 1)
//	{
//			SpeedNow = Speed_Packages;
//	}
	else if(PC.CtrlState == 0 && PC.ShiftState == 0)
  {
    SpeedNow = Speed_Normal;
  }
	
  
  /*竖直方向处理(建立坐标轴为x)*/
  if(GetKeyMouseAction(KEYBOARD_PRESSED_W,PRESS))
  {
    rocket->PC_x = SpeedNow * Slope_Calculation(&WS_slope);
  }
  else if(GetKeyMouseAction(KEYBOARD_PRESSED_S,PRESS))
  {
    rocket->PC_x = -SpeedNow * Slope_Calculation(&WS_slope);
  }
  else
  {
    /*归零处理*/
    rocket->PC_x = 0;
    /*斜坡重新初始化*/
    Slope_reloading(&WS_slope,Slope_ATTime/10);
  }


  /*横向方向处理(建立坐标轴为y)*/
  if(GetKeyMouseAction(KEYBOARD_PRESSED_A,PRESS))
  {
    rocket->PC_y = SpeedNow * Slope_Calculation(&AD_slope);
  }
  else if(GetKeyMouseAction(KEYBOARD_PRESSED_D,PRESS))
  {
    rocket->PC_y = -SpeedNow * Slope_Calculation(&AD_slope);
  }
  else
  {
    /*归零处理*/
    rocket->PC_y = 0;
    /*斜坡重新初始化*/
    Slope_reloading(&AD_slope,Slope_ATTime/10);
  }
  
  /*对角方向判断*/
  if(GetKeyMouseAction(KEYBOARD_PRESSED_Q,PRESS))
  {
    Q_SpeedNow = -SpeedNow;
  }
  else if(GetKeyMouseAction(KEYBOARD_PRESSED_E,PRESS))
  {
    E_SpeedNow = SpeedNow;
  }

  /*整合QE按钮的速度*/
  rocket->PC_degrees = Q_SpeedNow + E_SpeedNow;
  
}


 /*-----------------------------------file of end------------------------------*/