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
  |--FileName    : BSP_MATH.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无 & 璨                                                     
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
  * @brief   限幅
  * @param   float *KI_OUT, 对应值
  *          float MAXER    限幅值
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


