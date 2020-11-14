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
  |--FileName    : BSP_Init.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无 & 璨                                                     
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
  * @brief   BSP底层完全初始化
  * @param   void
  * @retval  void
  */
void Devices_Init(void)
{
    /*设置系统中断优先级分组为4*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    /* =========================== BSP_Part of begin =========================== */
    /*CAN1初始化*/
		CAN1_QuickInit();
	
		/*CAN2初始化*/
		CAN2_QuickInit();
	
		/*蜂鸣器初始化*/
		BEEP_Init(89, 2000);
	
		/*LED初始化*/
		LED_Init();
	
		/*激光初始化*/
		Laser_Init();
    /* =========================== BSP_Part of end =========================== */
    
    /* =========================== Modular_Part of begin =========================== */
		/*舵机初始化*/
		ServoBSP_Init();
		
    /*摩擦轮初始化*/
		FrictionBSP_Init();

    /*陀螺仪初始化*/
		

    /*DR16遥控器初始化*/
    DR16BSP_Init();

    /*裁判系统初始化*/
    JudgeBSP_Init();

    /*视觉初始化*/
    VisionBSP_Init();

     
    /* =========================== Modular_Part of end =========================== */
}

/**
  * @Data    2019-03-23 11:59
  * @brief   摩擦轮初始化
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
  * @brief   陀螺仪初始化
  * @param   void
  * @retval  void
  */
void IMUBSP_Init(void)
{
		/*更换成为陀螺仪启动*/
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
  * @brief   DR16遥控器初始化
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
  * @brief   裁判系统初始化
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
  * @brief   视觉初始化
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
		/*自瞄和神符的视觉*/
		USART6_QuickInit(115200);
//		USART8_QuickInit(115200);
		#else
		USART2_QuickInit(1500000);
		#endif
//	  USART2_RXDMA_Config((uint32_t)Vision_DataBuff, VISION_BUFFSIZE);
		/*自瞄和神符的视觉*/
		USART6_RXDMA_Config((uint32_t)Vision_DataBuff,VISION_BUFFSIZE);
//		USART6_RXDMA_Config((uint32_t)Vision_DataBufferNew,VISION_NEW_BUFFERSIZE);
//		USART8_RXDMA_Config((uint32_t)Vision_DataBufferNew,VISION_NEW_BUFFERSIZE);
    #endif
}

/**
  * @Data    2019-03-23 12:10
  * @brief   舵机初始化
  * @param   void
  * @retval  void
  */
void ServoBSP_Init(void)
{
		
		/*DMA是备用的*/
		TIM1_PWM_Init(179,19999,1000); 
}

/*-----------------------------------file of end------------------------------*/


