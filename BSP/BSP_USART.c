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
  |--FileName    : BSP_USART.c                                              
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
#include "BSP_USART.h" 

#pragma import(__use_no_semihosting)    

/* =========================== supportfunctions of begin =========================== */
/*标准库需要的支持函数 */
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;  

/*定义_sys_exit()以避免使用半主机模式*/
void _sys_exit(int x) 
{ 
	x = x; 
} 

/*定义重定义接受函数对应串口*/
static USART_TypeDef* Using_USART = USART2;

/*重定义发送函数*/
int fputc(int ch, FILE *f)
{
    USART_SendData(Using_USART, (uint8_t) ch);
    while (USART_GetFlagStatus(Using_USART, USART_FLAG_TXE) == RESET);
    return (ch);
}

/*重新定义接受串口*/
int fgetc(FILE* f)
{
    while (USART_GetFlagStatus(Using_USART, USART_FLAG_RXNE) == RESET);
    return (int)USART_ReceiveData(Using_USART);
}


/* =========================== supportfunctions of end =========================== */

/* =========================== AbilityFunctions of begin =========================== */
/*发送一个字符*/
void USART_SendByte(USART_TypeDef*USARTx,uint8_t ch)
{
	USART_SendData(USARTx,ch);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TXE)==RESET);
}

/*发送一串字符串*/
void USART_SendString(USART_TypeDef*USARTx,char*str)
{
	unsigned int k=0;
	do{
		USART_SendByte(USARTx,*(str+k));
	    k++;	
	}while(*(str+k)!= '\0');
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET)
	{
	}
}
/* =========================== AbilityFunctions of end =========================== */

/**
  * @Data    2019-03-22 21:48
  * @brief   USART1快速初始化（DR16）
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART1_QuickInit(uint32_t USART_BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
	
    RCC_AHB1PeriphClockCmd(USART1_TX_GPIO_CLK,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    /* 配置Tx引脚  */
    GPIO_InitStructure.GPIO_Pin = USART1_TX_Pin;
    GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);

    /* 配置Rx引脚 */
    GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;
    GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);

    /* 连接 PXx 到 USARTx_Tx，其实就是IO口复用*/
    GPIO_PinAFConfig(USART1_TX_GPIO_PORT, USART1_TX_PINSOURCE, GPIO_AF_USART1);

    /*  连接 PXx 到 USARTx_Rx，其实就是IO口复用*/
    GPIO_PinAFConfig(USART1_RX_GPIO_PORT, USART1_RX_PINSOURCE, GPIO_AF_USART1);

    /* 配置串USART 模式 */
    USART_InitStructure.USART_BaudRate = USART_BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);

    /* 串口中断优先级配置 */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

    /* 使能串口空闲中断 */
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);

    /* 使能串口 */
    USART_Cmd(USART1, ENABLE);
}

/**
  * @Data    2019-03-22 21:53
  * @brief   USART1_DMA初始化（DR16）
  * @param   uint32_t USART1_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize)
{
    DMA_InitTypeDef DMA_InitStructure;

    /*开启DMA2时钟*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    DMA_DeInit(USART1_RX_DMA_STREAM);

    /* 确保DMA数据流复位完成 */
    while(DMA_GetCmdStatus(USART1_RX_DMA_STREAM) != DISABLE)
    {
        /*如果没有复位完成会无限的卡着while这里*/
    }

    DMA_InitStructure.DMA_Channel = USART1_RX_DMA_CHANNEL;
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_RX_ADDR;//(uint32_t)(&USART1->DR)	//串口1数据寄存器地址

    /*USART1_DMABuff_addr ->参数*/
    DMA_InitStructure.DMA_Memory0BaseAddr = USART1_DMABuff_addr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;

    /*传输大小DMA_BufferSize=SENDBUFF_SIZE*/
    DMA_InitStructure.DMA_BufferSize = buffsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;

    /*禁用FIFO*/
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;

    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

    /*配置DMA2的数据流*/
    DMA_Init(USART1_RX_DMA_STREAM, &DMA_InitStructure);

    /*使能DMA*/
    DMA_Cmd(USART1_RX_DMA_STREAM, ENABLE);

    /* 等待DMA数据流有效*/
    while(DMA_GetCmdStatus(USART1_RX_DMA_STREAM) != ENABLE)
    {
    }

    /*使能DMA接收请求*/
    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
}

/**
  * @Data    2019-03-23 10:21
  * @brief   USART2快速初始化（辅助视觉瞄准）
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART2_QuickInit(uint32_t USART_BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(USART2_TX_GPIO_CLK | USART2_RX_GPIO_CLK,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    /* 配置Tx引脚  */
    GPIO_InitStructure.GPIO_Pin = USART2_TX_Pin;  
    GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);

    /* 配置Rx引脚 */
    GPIO_InitStructure.GPIO_Pin = USART2_RX_Pin;
    GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);
    
    /* 连接 PXx 到 USARTx_Tx*/
    GPIO_PinAFConfig(USART2_TX_GPIO_PORT, USART2_TX_PINSOURCE, GPIO_AF_USART2);

    /*  连接 PXx 到 USARTx_Rx*/
    GPIO_PinAFConfig(USART2_RX_GPIO_PORT, USART2_RX_PINSOURCE, GPIO_AF_USART2);

    /*配置USART模式*/
    USART_InitStructure.USART_BaudRate = USART_BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure); 
	
	  /* 串口中断优先级配置 */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	  
    USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
    USART_Cmd(USART2, ENABLE);
}

/**
  * @Data    2019-03-23 10:28
  * @brief   USART2_DMA初始化（视觉自瞄）
  * @param   uint32_t USART2_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize)
{
    DMA_InitTypeDef DMA_InitStructure;


    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
    DMA_DeInit(USART2_RX_DMA_STREAM);

    /* 确保DMA数据流复位完成 */
    while(DMA_GetCmdStatus(USART2_RX_DMA_STREAM) != DISABLE)
    {
    }

    DMA_InitStructure.DMA_Channel = USART2_RX_DMA_CHANNEL;  
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART2_RX_ADDR;	 
    DMA_InitStructure.DMA_Memory0BaseAddr = USART2_DMABuff_addr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
    DMA_InitStructure.DMA_BufferSize = buffsize;    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;		
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    	   
    DMA_Init(USART2_RX_DMA_STREAM, &DMA_InitStructure);
      
    /*使能DMA*/
    DMA_Cmd(USART2_RX_DMA_STREAM, ENABLE);
    
    /* 等待DMA数据流有效*/
    while(DMA_GetCmdStatus(USART2_RX_DMA_STREAM) != ENABLE)
    {
    }
    
    //使能DMA接收  
    USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); 
}

/**
  * @Data    2019-03-23 10:31
  * @brief   USART3快速初始化（裁判系统）
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART3_QuickInit(uint32_t USART_BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(USART3_TX_GPIO_CLK | USART3_RX_GPIO_CLK,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    
    GPIO_InitStructure.GPIO_Pin = USART3_TX_Pin;  
    GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USART3_RX_Pin;
    GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStructure);
    

    GPIO_PinAFConfig(USART3_TX_GPIO_PORT, USART3_TX_PINSOURCE, GPIO_AF_USART3);
    GPIO_PinAFConfig(USART3_RX_GPIO_PORT, USART3_RX_PINSOURCE, GPIO_AF_USART3);
    
    USART_InitStructure.USART_BaudRate = USART_BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure); 


    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//空闲中断
    USART_Cmd(USART3, ENABLE);
}

/**
  * @Data    2019-03-23 10:32
  * @brief   USART3_DMA（裁判系统）
  * @param   uint32_t USART1_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART3_RXDMA_Config(uint32_t USART3_DMABuff_addr, uint32_t buffsize)
{
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
      
    DMA_DeInit(USART3_RX_DMA_STREAM);

    while(DMA_GetCmdStatus(USART3_RX_DMA_STREAM) != DISABLE)
    {
    }

    DMA_InitStructure.DMA_Channel = USART3_RX_DMA_CHANNEL;
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART3_RX_ADDR;
    DMA_InitStructure.DMA_Memory0BaseAddr = USART3_DMABuff_addr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = buffsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(USART3_RX_DMA_STREAM, &DMA_InitStructure);

    DMA_Cmd(USART3_RX_DMA_STREAM, ENABLE);
  
    while(DMA_GetCmdStatus(USART3_RX_DMA_STREAM) != ENABLE)
    {
    }
    
    USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);

}


/**
  * @Data    2019-03-23 10:43
  * @brief   USART6初始化（陀螺仪）
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART6_QuickInit(uint32_t USART_BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(USART6_TX_GPIO_CLK | USART6_RX_GPIO_CLK,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin = USART6_TX_Pin;  
    GPIO_Init(USART6_TX_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USART6_RX_Pin;
    GPIO_Init(USART6_RX_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_PinAFConfig(USART6_TX_GPIO_PORT, USART6_TX_PINSOURCE, GPIO_AF_USART6);
    GPIO_PinAFConfig(USART6_RX_GPIO_PORT, USART6_RX_PINSOURCE, GPIO_AF_USART6);

    USART_InitStructure.USART_BaudRate = USART_BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART6, &USART_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART6, USART_IT_IDLE, ENABLE);//空闲中断
    
    USART_Cmd(USART6, ENABLE);
}

/**
  * @Data    2019-03-23 11:03
  * @brief   USART6_DMA初始化（陀螺仪）
  * @param   uint32_t USART6_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART6_RXDMA_Config(uint32_t USART6_DMABuff_addr, uint32_t buffsize)
{
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
    DMA_DeInit(USART6_RX_DMA_STREAM);

    /* 确保DMA数据流复位完成 */
    while(DMA_GetCmdStatus(USART6_RX_DMA_STREAM) != DISABLE)
    {
    }

    DMA_InitStructure.DMA_Channel = USART6_RX_DMA_CHANNEL;  
    DMA_InitStructure.DMA_PeripheralBaseAddr = USART6_RX_ADDR;	 
    DMA_InitStructure.DMA_Memory0BaseAddr = USART6_DMABuff_addr;	
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
    DMA_InitStructure.DMA_BufferSize = buffsize;	    
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
		   
    DMA_Init(USART6_RX_DMA_STREAM, &DMA_InitStructure);
      

    DMA_Cmd(USART6_RX_DMA_STREAM, ENABLE);
    

    while(DMA_GetCmdStatus(USART6_RX_DMA_STREAM) != ENABLE)
    {
    }
    
    USART_DMACmd(USART6,USART_DMAReq_Rx,ENABLE);
}


/**
  * @Data    2019-03-23 11:03
  * @brief   USART7初始化（晓生自瞄备选）
  * @param   uint32_t USART6_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART7_QuickInit(uint32_t USART_BaudRate)
{
		//GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE); //使能GPIOD时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7,ENABLE);//使能USART2时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_UART7); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_UART7); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_7; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOE,&GPIO_InitStructure); //初始化PA9，PA10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = USART_BaudRate;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(UART7, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(UART7, ENABLE);  //使能串口2 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	
	USART_ITConfig(UART7, USART_IT_IDLE, ENABLE);//空闲中断
	//USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=5;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
}


/**
  * @Data    2019-03-23 11:03
  * @brief   USART7_DMA初始化（陀螺仪）
  * @param   uint32_t USART6_DMABuff_addr, uint32_t buffsize
  * @retval  void
  */
void USART7_RXDMA_Config(uint32_t USART7_DMABuff_addr, uint32_t buffsize)
{
	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//开启DMA1时钟
	  
	DMA_DeInit(DMA1_Stream3);// 复位初始化DMA数据流 

	while(DMA_GetCmdStatus(DMA1_Stream3) != DISABLE);//确保DMA数据流复位完成
	
	DMA_InitStructure.DMA_Channel = DMA_Channel_5; //usart6 rx对应dma1，通道5，数据流1 	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART7->DR);	//设置DMA源：串口数据寄存器地址 	
	DMA_InitStructure.DMA_Memory0BaseAddr = USART7_DMABuff_addr;//存地址(要传输的变量的指针)
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//方向：从外设到内存		
	DMA_InitStructure.DMA_BufferSize = buffsize;	//传输大小DMA_BufferSize=SENDBUFF_SIZE		
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址不增    	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//内存地址自增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//外设数据单位		
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//内存数据单位 8bit	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA模式：不断循环
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//优先级：中	     
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//禁用FIFO       
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//存储器突发传输 16 个节拍   	
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //外设突发传输 1 个节拍 
	DMA_Init(DMA1_Stream3, &DMA_InitStructure);//配置DMA2的数据流		 
	  
	DMA_Cmd(DMA1_Stream3, ENABLE);//使能DMA
  
	while(DMA_GetCmdStatus(DMA1_Stream3) != ENABLE);// 等待DMA数据流有效
  
	USART_DMACmd(UART7,USART_DMAReq_Rx,ENABLE); 	//使能DMA接收
}



/**
  * @Data    2019-03-23 10:43
  * @brief   USART8初始化（陀螺仪）
  * @param   uint32_t USART_BaudRate
  * @retval  void
  */
void USART8_QuickInit(uint32_t USART_BaudRate)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(USART8_TX_GPIO_CLK | USART8_RX_GPIO_CLK,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE);
  
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

    GPIO_InitStructure.GPIO_Pin = USART8_TX_Pin;  
    GPIO_Init(USART8_TX_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = USART8_RX_Pin;
    GPIO_Init(USART8_RX_GPIO_PORT, &GPIO_InitStructure);
    
    GPIO_PinAFConfig(USART8_TX_GPIO_PORT, USART8_TX_PINSOURCE, GPIO_AF_UART8);
    GPIO_PinAFConfig(USART8_RX_GPIO_PORT, USART8_RX_PINSOURCE, GPIO_AF_UART8);

    USART_InitStructure.USART_BaudRate = USART_BaudRate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(UART8, &USART_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = UART8_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(UART8, USART_IT_IDLE, ENABLE);//空闲中断
    
    USART_Cmd(UART8, ENABLE);
}


void USART8_RXDMA_Config(uint32_t USART8_DMABuff_addr, uint32_t buffsize)
{
		DMA_InitTypeDef DMA_InitStructure;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
		DMA_DeInit(DMA1_Stream6);
		while(DMA_GetCmdStatus(DMA1_Stream6) != DISABLE)
		{
		}
		DMA_InitStructure.DMA_Channel = DMA_Channel_5; //usart6 rx对应dma1，通道5，数据流1 	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&UART8->DR);	//设置DMA源：串口数据寄存器地址 	
	DMA_InitStructure.DMA_Memory0BaseAddr = USART8_DMABuff_addr;//存地址(要传输的变量的指针)
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//方向：从外设到内存		
	DMA_InitStructure.DMA_BufferSize = buffsize;	//传输大小DMA_BufferSize=SENDBUFF_SIZE		
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址不增    	
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//内存地址自增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//外设数据单位		
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//内存数据单位 8bit	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA模式：不断循环
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//优先级：中	     
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//禁用FIFO       
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//存储器突发传输 16 个节拍   	
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //外设突发传输 1 个节拍 
	DMA_Init(DMA1_Stream6, &DMA_InitStructure);//配置DMA2的数据流

	DMA_Cmd(DMA1_Stream6, ENABLE);//使能DMA
  
	while(DMA_GetCmdStatus(DMA1_Stream6) != ENABLE)
	{
			
	}
  
	USART_DMACmd(UART8,USART_DMAReq_Rx,ENABLE); 	//使能DMA接收  		
}
/**
	* @Data    2019-03-15 16:54
	* @brief   ANO发送专用接收器
	* @param   USART_TypeDef* USARTx,char ch
	* @retval  void
	*/
void ANO_SendChar(USART_TypeDef* USARTx,char ch)
{
	USART_SendData(USARTx, (uint8_t) ch);
	while (USART_GetFlagStatus(Using_USART, USART_FLAG_TXE) == RESET);	  
}

void USART_sendChar(USART_TypeDef* USARTx,char ch)
{
	USART_SendData(USARTx, (uint8_t) ch);
	while (USART_GetFlagStatus(Using_USART, USART_FLAG_TXE) == RESET);	  
}

void USART3_sendChar(USART_TypeDef* USARTx,char ch)
{
	USART_SendData(USARTx, (uint8_t) ch);
	while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	  
}

void USART_ALLFSendChar(USART_TypeDef* USARTx,char*str)
{
	unsigned int k=0;
	do{
		USART_SendByte(USARTx,*(str+k));
	    k++;	
	}while(*(str+k)!= '\0');
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET)
	{
	}
}

/*-----------------------------------file of end------------------------------*/


