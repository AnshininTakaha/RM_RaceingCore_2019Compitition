/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无 & 璨，                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Driver_Filter.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无 & 璨                                                       
  |--Date        : 2019-03-25               
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
#ifndef __DRIVER_FILTER_H 
#define __DRIVER_FILTER_H 

#include "stm32f4xx.h"

/*多项式展开滤波结构体*/
typedef struct 
{
    double Raw_Value;
    double Filter_Value;

    /*X层级缓冲*/
    double X_Cushion[18];

    /*Y层级缓冲*/
    double Y_Cushion[18];
}Filter_t;


extern Filter_t Filter_Follow;
extern Filter_t Filter_IMUYAW;
extern Filter_t Filter_PITCH;
extern Filter_t CV_XPos;
extern Filter_t CV_YPos;
	
/*多项式滤波*/
double Polynomial_Filter(Filter_t *Filter);

/*数据低通滤波通道float*/
void Filter_IIRLPF(float *in, float *out, float LpfAttFactor);

#endif	// __DRIVER_FILTER_H
/*-----------------------------------file of end------------------------------*/


