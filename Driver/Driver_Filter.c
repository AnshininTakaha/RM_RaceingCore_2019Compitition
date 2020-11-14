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
  |--FileName    : Driver_Filter.c                                              
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
#include "Driver_Filter.h" 


Filter_t Filter_Follow;
Filter_t Filter_IMUYAW;
Filter_t Filter_PITCH;
Filter_t CV_XPos;
Filter_t CV_YPos;

double HighBuffer[18] = {
    0.0001539807224874,	-0.001633551718237,  0.008285871521075,  -0.02655137141783,
    0.05976268341326, 	-0.09892004512411,   0.1209510267949,  	 -0.1024952672175,
    0.04044670396161,  	0.04044670396161,  	 -0.1024952672175,   0.1209510267949,
    -0.09892004512411,  0.05976268341326, 	 -0.02655137141783,  0.008285871521075,
    -0.001633551718237,	0.0001539807224874
  };

double LowBuffer[18] = {
                 1,   -12.83384996104,    77.93650732675,   -297.3335694968,
    797.9129616887,   -1597.972651706,    2472.494945198,   -3018.357074163,
    2942.681165509,   -2303.842335957,    1448.206814835,   -726.6729407251,
    287.4544421962,   -87.75235536838,    19.96212762001,      -3.188300212,
    0.3191936459711,  -0.01508036852769 
};

/**
  * @Data    2019-03-28 11:05
  * @brief   多项式滤波
  * @param   Filter_t *Filter
  * @retval  double
  */
double Polynomial_Filter(Filter_t *Filter)
{
    int temp;
    for(temp = 17; temp > 0; temp--)
    {
        /*时不变系统递归*/
        Filter->Y_Cushion[temp] = Filter->Y_Cushion[temp - 1];
        Filter->X_Cushion[temp] = Filter->X_Cushion[temp - 1];
    }

    Filter->X_Cushion[0] = Filter->Raw_Value;
    Filter->Y_Cushion[0] = HighBuffer[0] * Filter->X_Cushion[0];

    for(temp = 1; temp < 18; temp++)
    {
        /*根据后面的变化值决定最后的输出值*/
        Filter->Y_Cushion[0] =  Filter->Y_Cushion[0] + HighBuffer[temp] * Filter->X_Cushion[temp]- LowBuffer[temp] * Filter->Y_Cushion[temp];
    }

    /*输出值*/
    Filter->Filter_Value = Filter->Y_Cushion[0];
    return Filter->Filter_Value;

}

/**
  * @Data    2019-02-28 19:35
  * @brief   数据滤波通道
  * @param   float *in,float *out,float LpfAttFactor
  * @retval  void
  */
void Filter_IIRLPF(float *in, float *out, float LpfAttFactor)
{
    *out = *out + LpfAttFactor*(*in - *out);
}



/*-----------------------------------file of end------------------------------*/


