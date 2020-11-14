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
  |--FileName    : Driver_ANO.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无 & 璨                                                     
  |--Date        : 2019-03-26             
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
#include "Driver_ANO.h" 

/*ANO上位机发送储存数据*/
int8_t send_buf[15]= {0};

/**
  * @Data    2019-03-26 17:39
  * @brief   ANO上位机传输数据
  * @param   int16_t Temp_Target1,int16_t Temp_Now1,\
	         int16_t Temp_Target2,int16_t Temp_Now2
  * @retval  void
  */
void ANO_Send_Data_V1(int16_t Temp_Target1,int16_t Temp_Now1,int16_t Temp_Target2,\
int16_t Temp_Now2)
{
    int8_t data_sum=0;
	int i=0;
	send_buf[0]=0xAA;
	send_buf[1]=0x01;
	send_buf[2]=0xAF;
	send_buf[3]=0x02;
	send_buf[4]=0x08;
	send_buf[5]=Temp_Target1>>8;
	send_buf[6]=Temp_Target1;
	send_buf[7]=Temp_Now1>>8;
	send_buf[8]=Temp_Now1;
	send_buf[9]=Temp_Target2>>8;
	send_buf[10]=Temp_Target2;
	send_buf[11]=Temp_Now2>>8;
	send_buf[12]=Temp_Now2;
	for(i=0;i<13;i++)
	{
	    data_sum+=send_buf[i];
	}
	send_buf[13]=data_sum;
	for(i=0;i<14;i++)
	{
		ANO_SendChar(USART2,send_buf[i]);
	}
}


/*-----------------------------------file of end------------------------------*/


