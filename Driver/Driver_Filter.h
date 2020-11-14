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
  |--FileName    : Driver_Filter.h                                                
  |--Version     : v1.0                                                            
  |--Author      : ���� & �                                                       
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

/*����ʽչ���˲��ṹ��*/
typedef struct 
{
    double Raw_Value;
    double Filter_Value;

    /*X�㼶����*/
    double X_Cushion[18];

    /*Y�㼶����*/
    double Y_Cushion[18];
}Filter_t;


extern Filter_t Filter_Follow;
extern Filter_t Filter_IMUYAW;
extern Filter_t Filter_PITCH;
extern Filter_t CV_XPos;
extern Filter_t CV_YPos;
	
/*����ʽ�˲�*/
double Polynomial_Filter(Filter_t *Filter);

/*���ݵ�ͨ�˲�ͨ��float*/
void Filter_IIRLPF(float *in, float *out, float LpfAttFactor);

#endif	// __DRIVER_FILTER_H
/*-----------------------------------file of end------------------------------*/


