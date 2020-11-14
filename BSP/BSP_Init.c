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
  |--FileName    : BSP_Init.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ���� & �                                                     
  |--Date        : 2019-03-22             
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
#include "BSP_Init.h" 

uint8_t DBUS_DataBuff[RC_BUFFSIZE];
uint8_t GYIMU_RXBuff[GYIMU_BUFFSIZE];
uint8_t Judge_DataBuff[Judge_BuffSIZE];
uint8_t Vision_DataBuff[VISION_BUFFSIZE];
uint8_t Vision_DataBufferNew[VISION_NEW_BUFFERSIZE];
/**
  * @Data    2019-03-23 11:33
  * @brief   BSP�ײ���ȫ��ʼ��
  * @param   void
  * @retval  void
  */
void Devices_Init(void)
{
    /*����ϵͳ�ж����ȼ�����Ϊ4*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    /* =========================== BSP_Part of begin =========================== */
    /*CAN1��ʼ��*/
		CAN1_QuickInit();
	
		/*CAN2��ʼ��*/
		CAN2_QuickInit();
	
		/*��������ʼ��*/
		BEEP_Init(89, 2000);
	
		/*LED��ʼ��*/
		LED_Init();
	
		/*�����ʼ��*/
		Laser_Init();
    /* =========================== BSP_Part of end =========================== */
    
    /* =========================== Modular_Part of begin =========================== */
		/*�����ʼ��*/
		ServoBSP_Init();
		
    /*Ħ���ֳ�ʼ��*/
		FrictionBSP_Init();

    /*�����ǳ�ʼ��*/
		

    /*DR16ң������ʼ��*/
    DR16BSP_Init();

    /*����ϵͳ��ʼ��*/
    JudgeBSP_Init();

    /*�Ӿ���ʼ��*/
    VisionBSP_Init();

     
    /* =========================== Modular_Part of end =========================== */
}

/**
  * @Data    2019-03-23 11:59
  * @brief   Ħ���ֳ�ʼ��
  * @param   void
  * @retval  void
  */
void FrictionBSP_Init(void)
{
    #ifdef RMOfficialBoardA
		TIM_PWM_Init(179, 19999,1000);//TIM1
		#endif
		#ifdef WildWolfOfficialBoard_F
		TIM_PWM_Init(89, 19999,1000);//TIM5
		#endif
}

/**
  * @Data    2019-03-23 12:01
  * @brief   �����ǳ�ʼ��
  * @param   void
  * @retval  void
  */
void IMUBSP_Init(void)
{
		/*������Ϊ����������*/
		#ifdef RMOfficialBoardA
		USART6_QuickInit(115200);
		USART6_RXDMA_Config((uint32_t)GYIMU_RXBuff,GYIMU_BUFFSIZE);
		#endif
		#ifdef WildWolfOfficialBoard_F
		USART6_QuickInit(115200);
		USART6_RXDMA_Config((uint32_t)GYIMU_RXBuff,GYIMU_BUFFSIZE);
		#endif
}

/**
  * @Data    2019-03-23 12:05
  * @brief   DR16ң������ʼ��
  * @param   void
  * @retval  void
  */
void DR16BSP_Init(void)
{
    #ifdef RMOfficialBoardA
		USART1_QuickInit(100000);
		USART1_RXDMA_Config((uint32_t)DBUS_DataBuff, RC_BUFFSIZE);	
		#endif
		#ifdef WildWolfOfficialBoard_F
		USART1_QuickInit(100000);
		USART1_RXDMA_Config((uint32_t)DBUS_DataBuff, RC_BUFFSIZE);	
		#endif
}

/**
  * @Data    2019-03-23 12:08
  * @brief   ����ϵͳ��ʼ��
  * @param   void
  * @retval  void
  */
void JudgeBSP_Init(void)
{
    USART3_QuickInit(115200);
    USART3_RXDMA_Config((uint32_t)Judge_DataBuff, Judge_BuffSIZE);
}

/**
  * @Data    2019-03-23 12:10
  * @brief   �Ӿ���ʼ��
  * @param   void
  * @retval  void
  */
void VisionBSP_Init(void)
{
    #ifdef RMOfficialBoardA
    USART2_QuickInit(115200);	
	  USART2_RXDMA_Config((uint32_t)Vision_DataBuff, VISION_BUFFSIZE);
    #endif
    #ifdef WildWolfOfficialBoard_F
		#if ANOUse
//		USART2_QuickInit(115200);
		/*�����������Ӿ�*/
		USART6_QuickInit(115200);
//		USART8_QuickInit(115200);
		#else
		USART2_QuickInit(1500000);
		#endif
//	  USART2_RXDMA_Config((uint32_t)Vision_DataBuff, VISION_BUFFSIZE);
		/*�����������Ӿ�*/
		USART6_RXDMA_Config((uint32_t)Vision_DataBuff,VISION_BUFFSIZE);
//		USART6_RXDMA_Config((uint32_t)Vision_DataBufferNew,VISION_NEW_BUFFERSIZE);
//		USART8_RXDMA_Config((uint32_t)Vision_DataBufferNew,VISION_NEW_BUFFERSIZE);
    #endif
}

/**
  * @Data    2019-03-23 12:10
  * @brief   �����ʼ��
  * @param   void
  * @retval  void
  */
void ServoBSP_Init(void)
{
		
		/*DMA�Ǳ��õ�*/
		TIM1_PWM_Init(179,19999,1000); 
}

/*-----------------------------------file of end------------------------------*/


