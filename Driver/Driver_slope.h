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
  |--FileName    : Driver_slope.h                                                
  |--Version     : v1.0                                                            
  |--Author      : 口无 & 璨                                                       
  |--Date        : 2019-03-27               
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
#ifndef __DRIVER_SLOPE_H 
#define __DRIVER_SLOPE_H 

#include "stm32f4xx.h"

#define Slope_ATTime 500

typedef struct
{
    int32_t count;
    int32_t scale; 
    float   out;
} slope_t;

/*缓冲初始化设置*/
#define slope_default(Inoutcount,Inputscale,Inputout) \
{ \
   .count = Inoutcount, \
   .scale = Inputscale, \
   .out = Inputout, \
} \

extern slope_t WS_slope;
extern slope_t AD_slope;
extern slope_t QE_slope;
extern slope_t Friction_slope;
extern slope_t RCWS_slope;
extern slope_t RCAD_slope;
extern slope_t RCQE_slope;
/*斜坡函数重载入*/
void Slope_reloading(slope_t *slope, int32_t scale);

/*斜坡计算函数*/
float Slope_Calculation(slope_t *slope);


#endif	// __DRIVER_SLOPE_H
/*-----------------------------------file of end------------------------------*/


