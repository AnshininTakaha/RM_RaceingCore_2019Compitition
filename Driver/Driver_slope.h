/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,���� & 貣�                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Driver_slope.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ���� & �                                                       
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

/*�����ʼ������*/
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
/*б�º���������*/
void Slope_reloading(slope_t *slope, int32_t scale);

/*б�¼��㺯��*/
float Slope_Calculation(slope_t *slope);


#endif	// __DRIVER_SLOPE_H
/*-----------------------------------file of end------------------------------*/


