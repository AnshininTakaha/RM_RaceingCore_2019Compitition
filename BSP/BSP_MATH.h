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
  |--FileName    : BSP_MATH.h                                                
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
#ifndef __BSP_MATH_H 
#define __BSP_MATH_H 

#include "stm32f4xx.h"

#define PI 3.1415926f
#define M_PI 3.1415926535897932384626433832795f
#define HALF_PI 1.5707963267948966192313216916398f
#define TWO_PI 6.283185307179586476925286766559f
#define DEG_TO_RAD 0.017453292519943295769236907684886f
#define RAD_TO_DEG 57.295779513082320876798154814105f
#define EULER 2.718281828459045235360287471352f
#define ABS(x)   (((x)>0)?(x):-(x))

#define MIN(a,b) ((a<b)?a:b)

#define MAX(a,b)	((a<b)?b:a)

#define DEG_TO_RAD 0.017453292519943295769236907684886f

#define VAL_LIMIT(val,min,max) \
if (val<=min)\
{\
	val = min;\
}\
else if (val>=max)\
{\
	val = max;\
}\

#define LIMIT(TargetValue, LimitValue) \
if (TargetValue > LimitValue)\
{\
	TargetValue = LimitValue;\
}\
else if (TargetValue < -LimitValue)\
{\
	TargetValue = -LimitValue;\
}\

/*限幅*/
void Limiting(float *KI_OUT,float MAXER);
void LimitingInt(int *KI_OUT,int MAXER);
void LimitingU32(int32_t *KI_OUT,int32_t MAXER);
int16_t ABSing (int16_t Input);
#endif	// __BSP_MATH_H
/*-----------------------------------file of end------------------------------*/


