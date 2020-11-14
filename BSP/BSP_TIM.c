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
  |--FileName    : BSP_TIM.c                                              
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
#include "BSP_TIM.h" 
 
TIM_SetComparex_f *const TIM_SetComparex[4] =
{
    TIM_SetCompare1,
    TIM_SetCompare2,
    TIM_SetCompare3,
    TIM_SetCompare4
};

/**
  * @Data    2019-03-22 21:08
  * @brief   TIM通用快速初始化
  * @param   void
  * @retval  void
  */
void TIM_PWM_Init(u16 prescaler, u16 period, u16 Pulse)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
		TIM_OCInitTypeDef  TIM_OCInitStructure;	
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource0, GPIO_AF_TIM5);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource1, GPIO_AF_TIM5);
	
		/*舵机*/
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource2, GPIO_AF_TIM5);

		TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
		TIM_TimeBaseStructure.TIM_Period = period;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		
		TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
		
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
		TIM_OCInitStructure.TIM_Pulse = Pulse;
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
		
		/*设置互补输出PWM极性，初始电平为高(不用也要配置，否则输出可能出错)*/
		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
		/*设置互补输出空闲时输出电平(不用也要配置，否则输出可能出错)*/
		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

		/*双通道输出初始化*/
		TIM_OC1Init(TIM5, &TIM_OCInitStructure);
		TIM_OC2Init(TIM5, &TIM_OCInitStructure);
		TIM_OC3Init(TIM5, &TIM_OCInitStructure);

		/*使能定时器*/
		TIM_Cmd(TIM5, ENABLE);

}


/**
  * @Data    2019-03-22 21:08
  * @brief   舵机TIM初始化
  * @param   void
  * @retval  void
  */
void TIM1_PWM_Init(u16 prescaler, u16 period, u16 Pulse)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	/* 配置时基结构体 */
	TIM_OCInitTypeDef  TIM_OCInitStructure;	/*配置输出比较结构体*/
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//使能定时器时钟
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8, GPIO_AF_TIM1);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9, GPIO_AF_TIM1);

	//配置定时器时钟分频
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	//配置自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Period = period;
	//配置死区时间与采样滤波分频，不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//配置计数模式，向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	//配置输出模式，PWM1模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	//使能输出
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//不使能互补输出
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	//设置初始占空比
	TIM_OCInitStructure.TIM_Pulse = Pulse;
	//设置PWM极性，初始电平为高
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//设置空闲时输出电平
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	
	//设置互补输出PWM极性，初始电平为高(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	//设置互补输出空闲时输出电平(不用也要配置，否则输出可能出错)
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

	//初始化为对应通道的输出，通道1
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	//初始化为对应通道的输出，通道1
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);

	//使能定时器
	TIM_Cmd(TIM1, ENABLE);

	/* 高级定时器需要使能PWM输出 */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}


/**
	* @brief  弹舱盖子开关设置
  * @param	0 关 1 开
  * @retval None
  */
void LIDSwitch(uint8_t mode)
{
	if (mode == 0)//关
	{
		TIM_SetCompare1(TIM1,500);
		TIM_SetCompare3(TIM5,500);
		
	}
	else
	{
		TIM_SetCompare1(TIM1,2500);
		TIM_SetCompare3(TIM5,1900);
	}
}
//void TIM_PWM_Init(uint16_t prescaler, uint16_t period, uint16_t Pulse)
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
//		TIM_OCInitTypeDef  TIM_OCInitStructure;	
//		
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
//		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
//		
//		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;    
//		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; 
//		
//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//		GPIO_Init(GPIOA, &GPIO_InitStructure);
//		GPIO_PinAFConfig(GPIOA,GPIO_PinSource8, GPIO_AF_TIM1);

//		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//		GPIO_Init(GPIOA, &GPIO_InitStructure);
//		GPIO_PinAFConfig(GPIOA,GPIO_PinSource9, GPIO_AF_TIM1);


//		TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
//		TIM_TimeBaseStructure.TIM_Period = period;
//		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//		
//		TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
//		

//		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//		TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
//		TIM_OCInitStructure.TIM_Pulse = Pulse;
//		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//		TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
//		
//		/*设置互补输出PWM极性，初始电平为高(不用也要配置，否则输出可能出错)*/
//		TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
//		/*设置互补输出空闲时输出电平(不用也要配置，否则输出可能出错)*/
//		TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

//			/*双通道输出初始化*/
//		TIM_OC1Init(TIM1, &TIM_OCInitStructure);
//		TIM_OC2Init(TIM1, &TIM_OCInitStructure);

//		/*使能定时器*/
//		TIM_Cmd(TIM1, ENABLE);
//		/* 高级定时器需要使能PWM输出 */
//		TIM_CtrlPWMOutputs(TIM1, ENABLE);
//}



/*-----------------------------------file of end------------------------------*/


