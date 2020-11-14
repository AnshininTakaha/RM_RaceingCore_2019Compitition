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
  |--FileName    : Control_PC.c                                              
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
#include "Control_PC.h"
#include "Control_Shoot.h"
#include "Driver_slope.h"
#include "Driver_Judge.h"

#include "Switch.h"
 
/*������Կ��ƴ���ṹ��*/
PC_t PC;
/*��λȷ��*/
/*������Ƽ�λ*/
/*WASD�������*/
/*QE��������*/
/*Shift+�����λ����*/
/*Ctrl+�����λ����(�л��ɴ�װ�׵���׼ģʽ)*/
/*R��*/
/*Ctrl + F:�л���Ϊ��еģʽ��IMU���ߣ�*/
/*G:�����ģʽ*/
/*Z:*/
/*X:*/
/*Ctrl + C:�л���Ϊ��̨����ģʽ*/
/*Ctrl + V:�л���Ϊ����ģʽ*/
/*B:����ģʽ */
/*�����*/
/*�Ҽ�������*/ 
 /**
  * @Data    2019-03-07 21:10
  * @brief   ���Կ��Ƴ�ʼ��
  * @param   void
  * @retval  void
  */
void PC_Init(void)
{
  /*��ʼ��Ĭ��Ϊ��̨����ģʽ*/
  PC.PCMode = PC_CloudPlatfrom;
  PC.InitState = 1;
}

/**
  * @Data    2019-03-16 10:43
  * @brief   PC�����ܴ���
  * @param   void
  * @retval  void
  */
void PCControl_Process(void)
{
  /*�����λ�ж�*/
  SpeicalKey_Process();
//  Modechange_Judgement();
  Derection_Process(&PCRocket);
}

/**
  * @Data    2019-03-10 19:44
  * @brief   ���⹦�ܼ�λ�ж�
  * @param   void
  * @retval  void
  */

/*�����������־λ*/
float SEDV_BIGER = 0;
/*������л�������־λ*/
uint32_t BIGChangePoint = 0;
	
/*��תģʽ������־λ*/
float SEDV_NoneHeadMode = 0;
/*��ͷģʽ�л�������־λ*/
uint32_t NoneHeadPoint= 0;

/*Ť��ģʽ������־λ*/
float SEDV_Swing = 0;
/*Ť��ģʽ�л�������־λ*/
float Swing_StateCounter = 0;

/*�л���Сװ�ױ�־λ*/
float SECV_BIGModule = 0;
/*�л���Сװ�׼�����־λ*/
float BIGModule_Counter = 0;


void SpeicalKey_Process(void)
{
  /*��¼���ⰴ���ı�־��ֻҪ���¾ͻ��ж�Ӧ�ı�־*/
	/*******************����Shift******************/
	/*����Shift:����*/
  if(GetKeyMouseAction(KEYBOARD_PRESSED_SHIFT,PRESS))
  {
			PC.ShiftState = 1;
  }
  else
  {
			PC.ShiftState = 0;
  }

	
  /*******************����Ctrl******************/
	/*����Ctrl:����*/
  if(GetKeyMouseAction(KEYBOARD_PRESSED_CTRL,PRESS))
  {
			PC.CtrlState = 1;
  }
  else
  {
			PC.CtrlState = 0;
  }
	

	/*******************����G******************/

	/*���G���л���Ϊ��תģʽ*/
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
	
	/*�жϵ�ǰ״̬��־λ*/
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

	/*******************����V******************/
	/*���SHIFT+V�������*/
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

	
	
	/*******************����R******************/
	/*���Ctrl+R����������*/
	/*���R��������̨׷��ģʽ*/
	if(GetKeyMouseAction(KEYBOARD_PRESSED_R,PRESS))
	{
			PC.Toggle_SEV = 1;
			if(PC.CtrlState == 0)
			{
					PC.PCMode = PC_CloudPlatfrom;
					/*���Ť��ģʽ*/
					SEDV_Swing = 0;
					/*�����תģʽ*/
					SEDV_NoneHeadMode = 0;
					/*��ϴ����ģʽ*/
					SEDV_BIGER = 0;
					/*��ϴ�װ��ģʽ*/
					SECV_BIGModule = 0;
			}
	}
	else
	{
			PC.Toggle_SEV = 0;
			ChangeSEVPoint++;
	}
	
	/*******************����X******************/
	/*����Ctrl+X:��ʼ��Ħ����*/
	if(GetKeyMouseAction(KEYBOARD_PRESSED_X,PRESS))
	{
			PC.ChangeFrictionSpeedINIT = 1;
	}
	else
	{
			PC.ChangeFrictionSpeedINIT = 0;
	}
	
	/*******************����C******************/
	/*���Shift+C���л���Сװ�װ���*/
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

	
	
	/*******************����Q******************/
	/*���Ctrl+Q:180��ͷ*/
	if(GetKeyMouseAction(KEYBOARD_PRESSED_Q,PRESS))
	{
			PC.TurnState = 1;
	}
	else
	{
			PC.TurnState = 0;
	}
	
	/*******************����F******************/
	/*���F������Ť��*/
	if(GetKeyMouseAction(KEYBOARD_PRESSED_F,PRESS))
	{
			PC.SwingState = 1;
			PC.PCMode = PC_CloudPlatfrom;
			/*�������*/
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
	
	/*******************����Z******************/
	/*���Shitt+Z��Ħ���ָı��ٶ�*/
	if(GetKeyMouseAction(KEYBOARD_PRESSED_Z,PRESS))
	{
			PC.ChangeFrictionSpeed = 1;
	}
	else
	{
			PC.ChangeFrictionSpeed = 0;
	}
	
	/*******************����B******************/
	/*����B�������Զ�����ģʽ*/
//	if(GetKeyMouseAction(KEYBOARD_PRESSED_B,PRESS))
//	{
//			
//	}
//	else
//	{
//			
//	}
	
	/*����������*/
	if(GetKeyMouseAction(MOUSE_PRESS_L,PRESS))
  {
			PC.LeftPressState = 1; 
	}
	else
	{
			PC.LeftPressState = 0;
	}
	/*����������*/
	if(GetKeyMouseAction(MOUSE_PRESS_L,LONG_PRESS) /*&& GetKeyMouseAction(MOUSE_PRESS_L,PRESS)*/)
	{
			PC.LeftLongPressState = 1;
	}
	else
	{
			PC.LeftLongPressState = 0;
	}
	
	
	/*��������Ҽ�*/
	if(GetKeyMouseAction(MOUSE_PRESS_R,PRESS))
	{
			PC.RightPressState = 1;
			/*��������*/
			PC.AimingState = 1;
			/*��ϴ����*/
			SEDV_BIGER = 0;
	}
	else
	{
			PC.RightPressState = 0;
			PC.AimingState = 0;
	}
	/*��������Ҽ�*/
	if(GetKeyMouseAction(MOUSE_PRESS_R,LONG_PRESS) /*&& GetKeyMouseAction(MOUSE_PRESS_R,PRESS)*/)
	{
			PC.RightLongPressState = 1;
	}
	else
	{
			PC.RightLongPressState = 0;
	}

	
	
	
	
	/*��Ϣ�����ж�*/
	/*�Ƿ����˴����*/
	/*0��ɫ��2��ɫ,1Ϊ����������ʶ��*/
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
	
	/*�����װ��*/
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
	
	/*����Сװ��*/
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
  * @brief   ģʽ�ı��ж�
  * @param   void
  * @retval  void
  */
//void Modechange_Judgement(void)
//{
//  if(PC.CtrlState == 1)
//  {
//    /*ʶ����ϼ�*/
//		if(PC_CloudPlatfromChange)/*Ctrl + B*/
//		{
//			PC.PCMode = PC_NoneHead;
//		}
//		
//		/*��̨׷��ģʽ*/
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
  * @brief   ������ٶ��жϴ���
  * @param   RCRocket_t *rocket
  * @retval  void
  */
void Derection_Process(PCRocket_t *rocket)
{
  float SpeedNow = 0;
  float Q_SpeedNow = 0,E_SpeedNow = 0;

	/*ע�ⳬ�������⣬������һ�����������ƣ��Լ��ж�˳������*/
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
	
  
  /*��ֱ������(����������Ϊx)*/
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
    /*���㴦��*/
    rocket->PC_x = 0;
    /*б�����³�ʼ��*/
    Slope_reloading(&WS_slope,Slope_ATTime/10);
  }


  /*��������(����������Ϊy)*/
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
    /*���㴦��*/
    rocket->PC_y = 0;
    /*б�����³�ʼ��*/
    Slope_reloading(&AD_slope,Slope_ATTime/10);
  }
  
  /*�ԽǷ����ж�*/
  if(GetKeyMouseAction(KEYBOARD_PRESSED_Q,PRESS))
  {
    Q_SpeedNow = -SpeedNow;
  }
  else if(GetKeyMouseAction(KEYBOARD_PRESSED_E,PRESS))
  {
    E_SpeedNow = SpeedNow;
  }

  /*����QE��ť���ٶ�*/
  rocket->PC_degrees = Q_SpeedNow + E_SpeedNow;
  
}


 /*-----------------------------------file of end------------------------------*/