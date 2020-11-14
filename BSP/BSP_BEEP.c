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
  |--FileName    : BSP_BEEP.c                                              
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
#include "BSP_BEEP.h" 

/**
  * @Data    2019-03-22 22:08
  * @brief   ��������ʼ��
  * @param   uint32_t psc, uint32_t arr
  * @retval  void
  */
void BEEP_Init(uint32_t psc, uint32_t arr)
{
    GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����

    #ifdef RMOfficialBoardA
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  	//TIM12ʱ��ʹ��    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTFʱ��	
		
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12); //GPIOF9����Ϊ��ʱ��12
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;           //GPIOF14	
		GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��PB14
    #endif
	
		#ifdef WildWolfOfficialBoard_F
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  	//TIM12ʱ��ʹ��    
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTFʱ��	
		
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12); //GPIOF9����Ϊ��ʱ��12
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;           //GPIOF14	
		GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��PB14
		#endif

    TIM_TimeBaseStructure.TIM_Prescaler=psc;  
		TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
		TIM_TimeBaseStructure.TIM_Period=arr;
		TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
		
		TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
		TIM_OC1Init(TIM12, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM12,ENABLE);
    TIM_Cmd(TIM12, ENABLE);
    TIM12->CCR1 = 0;
}


/**
  * @Data    2019-03-23 15:14
  * @brief   ��������TIM12��Ӧ��ֵ�����Ʒ�������
  * @param   uint16_t value
  * @retval  void
  */
void SetBeepValue(uint16_t value)
{
    TIM12->CCR1 = value;
}

/**
  * @Data    2019-03-23 15:15
  * @brief   ���÷������ź�
  * @param   uint8_t mode
  * @retval  void
  */
void SetBeepSignal(uint8_t mode)
{
    if (mode == 1)
    {
      SetBeepValue(500);
			vTaskDelay(100);
			SetBeepValue(100);
			vTaskDelay(100);
			SetBeepValue(0);
			
    }
    else if (mode == 2)
    {
      SetBeepValue(0);
    }
    else
    {}
}
/*-----------------------------------file of end------------------------------*/


