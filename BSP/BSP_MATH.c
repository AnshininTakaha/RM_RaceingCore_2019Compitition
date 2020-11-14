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
  |--FileName    : BSP_MATH.c                                              
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
#include "BSP_MATH.h" 

#include "math.h"
/**
  * @Data    2019-02-19 15:17
  * @brief   �޷�
  * @param   float *KI_OUT, ��Ӧֵ
  *          float MAXER    �޷�ֵ
  * @retval  void
  */
void Limiting(float *KI_OUT,float MAXER)
{
		if(*KI_OUT > MAXER)
    {
        *KI_OUT = MAXER;
    }
    if(*KI_OUT < -MAXER)
    {
        *KI_OUT = -MAXER;
    }
}

void LimitingInt(int *KI_OUT,int MAXER)
{
		if(*KI_OUT > MAXER)
    {
        *KI_OUT = MAXER;
    }
    if(*KI_OUT < -MAXER)
    {
        *KI_OUT = -MAXER;
    }
}

void LimitingU32(int32_t *KI_OUT,int32_t MAXER)
{
		if(*KI_OUT > MAXER)
    {
        *KI_OUT = MAXER;
    }
    if(*KI_OUT < -MAXER)
    {
        *KI_OUT = -MAXER;
    }
}

int16_t ABSing (int16_t Input)
{
		if(Input >= 0)
		{
				Input = Input;
		}
		if(Input < 0)
		{
				Input = -Input;
		}
		return Input;
}
/*-----------------------------------file of end------------------------------*/


