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
  |--FileName    : Driver_slope.c                                              
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
#include "Driver_slope.h" 

/*б�»���*/
slope_t WS_slope = slope_default(0,0,0);
slope_t AD_slope = slope_default(0,0,0);
slope_t QE_slope = slope_default(0,0,0);
slope_t Friction_slope = slope_default(0,0,0);
slope_t RCWS_slope = slope_default(0,0,0);
slope_t RCAD_slope = slope_default(0,0,0);
slope_t RCQE_slope = slope_default(0,0,0);
/**
  * @Data    2019-03-27 11:49
  * @brief   б�º���������
  * @param   slope_t *slope, int32_t scale
  * @retval  void
  */
void Slope_reloading(slope_t *slope, int32_t scale)
{
    slope->count = 0;
    slope->scale = scale;
}

/**
  * @Data    2019-03-27 11:54
  * @brief   б�¼��㺯��
  * @param   slope_t *slope
  * @retval  void
  */
float Slope_Calculation(slope_t *slope)
{
    if (slope->scale <= 0)
	{
		return 0;
	}
    
  
    if (slope->count++ >= slope->scale)
	{
		slope->count = slope->scale;
	}
    
    slope->out = slope->count / ((float)slope->scale);
  
	return slope->out;
}
/*-----------------------------------file of end------------------------------*/


