/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无 & 璨,                          |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : BSP_LED.c                                              
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
#include "BSP_LED.h" 

/**
  * @Data    2019-03-22 19:59
  * @brief   LED初始化
  * @param   void
  * @retval  void
  */
	
	
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOB \
    | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
    
    #ifdef RMOfficialBoardA
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | \
    GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;  
    GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化

    GPIO_SetBits(GPIOF,GPIO_Pin_14);
		GPIO_SetBits(GPIOE,GPIO_Pin_11);

		GPIO_SetBits(GPIOG,GPIO_Pin_1);
		GPIO_SetBits(GPIOG,GPIO_Pin_2);
		GPIO_SetBits(GPIOG,GPIO_Pin_3);
		GPIO_SetBits(GPIOG,GPIO_Pin_4);
		GPIO_SetBits(GPIOG,GPIO_Pin_5);
		GPIO_SetBits(GPIOG,GPIO_Pin_6);
		GPIO_SetBits(GPIOG,GPIO_Pin_7);
		GPIO_SetBits(GPIOG,GPIO_Pin_8);
    #endif

    #ifdef WildWolfOfficialBoard_F
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_Init(GPIOE, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_Init(GPIOE, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
		GPIO_Init(GPIOE, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_Init(GPIOE, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
		GPIO_Init(GPIOE, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
		GPIO_Init(GPIOE, &GPIO_InitStructure);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
		GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_SetBits(GPIOB,GPIO_Pin_4);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);

		GPIO_SetBits(GPIOE,GPIO_Pin_9);
		GPIO_SetBits(GPIOE,GPIO_Pin_10);
		GPIO_SetBits(GPIOE,GPIO_Pin_11);
		GPIO_SetBits(GPIOE,GPIO_Pin_12);
		GPIO_SetBits(GPIOE,GPIO_Pin_13);
		GPIO_SetBits(GPIOE,GPIO_Pin_14);
		GPIO_SetBits(GPIOE,GPIO_Pin_15);
		
		#endif
}

/*-----------------------------------file of end------------------------------*/
