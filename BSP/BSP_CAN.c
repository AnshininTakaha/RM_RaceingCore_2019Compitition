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
  |--FileName    : BSP_CAN.c                                              
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
#include "BSP_CAN.h" 


/**
  * @Data    2019-03-22 20:30
  * @brief   CAN1初始化
  * @param   void
  * @retval  void
  */
void CAN1_QuickInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_AHB1PeriphClockCmd(CAN1_RX_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    /*配置CAN1的TX引脚*/
    GPIO_InitStructure.GPIO_Pin = CAN1_TX_Pin;
    GPIO_Init(CAN1_TX_GPIO_PORT, &GPIO_InitStructure);
    /* 连接 IO 到 CAN1_Tx*/
    GPIO_PinAFConfig(CAN1_TX_GPIO_PORT, CAN1_TX_PINSOURCE, GPIO_AF_CAN1);


    /*配置CAN1的RX引脚*/
    GPIO_InitStructure.GPIO_Pin = CAN1_RX_Pin;
    GPIO_Init(CAN1_RX_GPIO_PORT, &GPIO_InitStructure);
    /*连接到CAN1_Rx*/
    GPIO_PinAFConfig(CAN1_RX_GPIO_PORT, CAN1_RX_PINSOURCE, GPIO_AF_CAN1);

    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = ENABLE;
    CAN_InitStructure.CAN_AWUM = ENABLE;		   
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  	  

    /*单元时间长度=45/(1+3+5)/5=1 Mbps*/
    CAN_InitStructure.CAN_SJW = CAN1_SJW;
    CAN_InitStructure.CAN_BS1 = CAN1_BS1;
    CAN_InitStructure.CAN_BS2 = CAN1_BS2;
    CAN_InitStructure.CAN_Prescaler = CAN1_Prescaler;
    CAN_Init(CAN1, &CAN_InitStructure);

    /*分频器设置*/
    CAN_FilterInitStructure.CAN_FilterNumber = 0;									
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;					
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;				
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0 ;			
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;			

    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;				
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000; 				
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;			
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;			

    CAN_FilterInit(&CAN_FilterInitStructure);

    /*中断配置*/
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_Init(&NVIC_InitStructure);

    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
		
}


/**
  * @Data    2019-03-22 20:30
  * @brief   CAN2初始化
  * @param   void
  * @retval  void
  */
void CAN2_QuickInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* 使能 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	//使能CAN2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
	
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* 连接 IO 到 CAN2_Tx*/
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2);

	/*  连接 IO 到 CAN2_Rx*/
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
	
	/************************CAN 模式配置*********************************************/
	CAN_InitStructure.CAN_TTCM = DISABLE;			   //MCR-TTCM  时间触发通信模式
	CAN_InitStructure.CAN_ABOM = ENABLE;			   //MCR-ABOM  自动离线管理 
	CAN_InitStructure.CAN_AWUM = ENABLE;			   //MCR-AWUM  使用自动唤醒模式
	CAN_InitStructure.CAN_NART = DISABLE;			   //MCR-NART  禁止报文自动重传	  DISABLE-自动重传
	CAN_InitStructure.CAN_RFLM = DISABLE;			   //MCR-RFLM  接收FIFO 锁定模式  DISABLE-溢出时新报文会覆盖原有报文  
	CAN_InitStructure.CAN_TXFP = DISABLE;			   //MCR-TXFP  发送FIFO优先级 DISABLE-优先级取决于报文标示符
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  	   //Mode  工作模式
	
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;		   	   //BTR-SJW 重新同步跳跃宽度 2个时间单元
	
	/* ss=1 bs1=5 bs2=3 位时间宽度为(1+9+4) 波特率即为时钟周期tq*(1+9+4)  */
	CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;		   //BTR-TS1 时间段1 占用了6个时间单元
	CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;		   //BTR-TS1 时间段2 占用了3个时间单元	
	
	/* CAN Baudrate = 1 MBps (1MBps已为stm32的CAN最高速率) (CAN 时钟频率为 APB 1 = 42 MHz) */
	CAN_InitStructure.CAN_Prescaler = 5;		   ////BTR-BRP 波特率分频器  定义了时间单元的时间长度 42/(1+9+4)/3=1 Mbps
	CAN_Init(CAN2, &CAN_InitStructure);
	
	/*********************CAN筛选器初始化***********************************************/
	CAN_FilterInitStructure.CAN_FilterNumber = 14;									//筛选器组0
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;					//工作在ID掩码模式
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;				//筛选器位宽为单个32位。
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;			//筛选器被关联到FIFO0
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;			//使能筛选器
	/* 使能筛选器，按照标志的内容进行比对筛选，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */
	
	//不进行过滤
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;				//要筛选的ID高位 
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000; 				//要筛选的ID低位 
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;			//筛选器高16位每位不须匹配
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;			//筛选器低16位每位不须匹配
	
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	/* FIFO0 message pending interrupt */
	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);
}


/**
  * @brief  CAN2快速初始化
  * @param  None
  * @retval None
  */
//void CAN2_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	CAN_InitTypeDef CAN_InitStructure;
//	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	/* 使能 GPIO 时钟 */
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
//	//使能CAN2时钟
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
//	
//	/* GPIO初始化 */
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;  
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	
//	/* 配置Tx引脚  */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  
//	GPIO_Init(GPIOB, &GPIO_InitStructure);

//	/* 配置Rx引脚 */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
//	/* 连接 IO 到 CAN2_Tx*/
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_CAN2);

//	/*  连接 IO 到 CAN2_Rx*/
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_CAN2);
//	
//	/************************CAN 模式配置*********************************************/
//	CAN_InitStructure.CAN_TTCM = DISABLE;			   //MCR-TTCM  时间触发通信模式
//	CAN_InitStructure.CAN_ABOM = ENABLE;			   //MCR-ABOM  自动离线管理 
//	CAN_InitStructure.CAN_AWUM = ENABLE;			   //MCR-AWUM  使用自动唤醒模式
//	CAN_InitStructure.CAN_NART = DISABLE;			   //MCR-NART  禁止报文自动重传	  DISABLE-自动重传
//	CAN_InitStructure.CAN_RFLM = DISABLE;			   //MCR-RFLM  接收FIFO 锁定模式  DISABLE-溢出时新报文会覆盖原有报文  
//	CAN_InitStructure.CAN_TXFP = DISABLE;			   //MCR-TXFP  发送FIFO优先级 DISABLE-优先级取决于报文标示符
//	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  	   //Mode  工作模式
//	
//	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;		   	   //BTR-SJW 重新同步跳跃宽度 2个时间单元
//	
//	/* ss=1 bs1=5 bs2=3 位时间宽度为(1+9+4) 波特率即为时钟周期tq*(1+9+4)  */
//	CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;		   //BTR-TS1 时间段1 占用了6个时间单元
//	CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;		   //BTR-TS1 时间段2 占用了3个时间单元	
//	
//	/* CAN Baudrate = 1 MBps (1MBps已为stm32的CAN最高速率) (CAN 时钟频率为 APB 1 = 42 MHz) */
//	CAN_InitStructure.CAN_Prescaler = 5;		   ////BTR-BRP 波特率分频器  定义了时间单元的时间长度 42/(1+9+4)/3=1 Mbps
//	CAN_Init(CAN2, &CAN_InitStructure);
//	
//	/*********************CAN筛选器初始化***********************************************/
//	CAN_FilterInitStructure.CAN_FilterNumber = 14;									//筛选器组0
//	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;					//工作在ID掩码模式
//	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;				//筛选器位宽为单个32位。
//	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;			//筛选器被关联到FIFO0
//	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;			//使能筛选器
//	/* 使能筛选器，按照标志的内容进行比对筛选，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */
//	
//	//不进行过滤
//	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;				//要筛选的ID高位 
//	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000; 				//要筛选的ID低位 
//	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;			//筛选器高16位每位不须匹配
//	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;			//筛选器低16位每位不须匹配
//	
//	CAN_FilterInit(&CAN_FilterInitStructure);
//	
//	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_Init(&NVIC_InitStructure);
//	
//	/* FIFO0 message pending interrupt */
//	CAN_ITConfig(CAN2, CAN_IT_FMP0, ENABLE);

//}
/**
  * @Data    2019-02-19 11:42
  * @brief   通过CAN发送指令到对应的ID上
  * @param   CAN_TypeDef* CANx,   对应的CAN
  *          uint8_t id_type,     对应的ID模式
  *          uint32_t id,         对应的ID
  *          uint8_t data[8]      储存的数据
  * @retval  void
  */
void CAN_sendData(CAN_TypeDef* CANx, uint8_t id_type, uint32_t id, \
uint8_t data[8])
{ 
    CanTxMsg TxMessage;

    /*ID号*/
    if(id_type == CAN_Id_Standard) 
		{
        TxMessage.StdId = id;
    }
    else 
		{
        TxMessage.ExtId = id;					 
    }

    /*ID类型*/
    TxMessage.IDE = id_type;

    /*发送的数据*/					 
    TxMessage.RTR = CAN_RTR_DATA;	

    /*数据长度字节为8*/
    TxMessage.DLC = 0x08;						 

    /*设置要发送的数据，储存进结构体中*/
    for (uint8_t i = 0; i < 8; i++)
    {
        TxMessage.Data[i] = data[i];
    }

    /*发送数据*/
    CAN_Transmit(CANx, &TxMessage);
}
/*-----------------------------------file of end------------------------------*/
