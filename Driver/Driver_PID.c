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
  |--FileName    : Driver_PID.c                                              
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
#include "Driver_PID.h"


#include "BSP_Init.h"

/**
  * @Data    2019-02-19 15:46
  * @brief   增量式PID计算
  * @param   incrementalpid_t *pid,   增量式PID结构体
  *          float target,            对应的增量式PID目标值
  *          float measured           对应的增量式PID测量值
  * @retval  int
  */
void IncrementalPID_Calculation(incrementalpid_t *pid, float target, float measured)
{
    pid->Target_speed = target;
    pid->Measured_speed = measured;

    pid->error = pid->Target_speed - pid->Measured_speed;

    /*消除抖动*/
     if(ABS(pid->error) < 0.2f )
     {
         pid->error = 0.0f;
     }

    /*PID公式*/
    pid->Kp_Output = pid->Kp * (pid->error - pid->last_error);
    pid->Ki_Output = pid->Ki * (pid->error);
    pid->Kd_Output = pid->Kd * (pid->error - 2*pid->last_error + pid->beforelast_error);


    /*Ki限幅*/
    Limiting(&pid->Ki_Output,pid->IntegralLimit);

    pid->PWM += (pid->Kp_Output + pid->Ki_Output + pid->Kd_Output);

    /*输出限幅*/
    Limiting(&pid->PWM,pid->MaxOutput);

    /*递进*/
    pid->beforelast_error = pid->last_error;
    pid->last_error = pid->error;

}

/**
  * @Data    2019-02-19 16:01
  * @brief   位置式PID计算
  * @param   positionpid_t *pid, 位置式PID计算
  *          float target,       位置式PID目标值
  *          float measured      位置式PID测量值
  * @retval  int
  */
void PositionPID_Calculation(positionpid_t *pid, float target, float measured)
{
    float kp_output,ki_output,kd_output;

	
		
    pid->Target = (float)target;
    pid->Measured = (float)measured;
    pid->error = pid->Target - pid->Measured;
//		pid->error = (int)pid->error;

//		if(ABS(pid->error) <0.5)
//		{
//				pid->error = 0;
//		}
		
    /*积分分离*/
		if(ABS(pid->error) < 20)
		{
			pid->Add_error += pid->error;
		}
		
		
		

    /*位置式PID计算公式*/
    pid->Kp_Output = pid->Kp * pid->error;
    pid->Ki_Output = pid->Ki * pid->Add_error;
    pid->Kd_Output = pid->Kd * (pid->error - pid->last_error);
		
//		if(ABS(pid->error) < 0.5)
//		{
//				pid->Kd_Output = 0;
//		}

    /*Ki限幅*/
    Limiting(&pid->Ki_Output,pid->IntegralLimit);

    pid->PWM = (pid->Kp_Output + pid->Ki_Output + pid->Kd_Output);

    /*输出限幅*/
    Limiting(&pid->PWM,pid->MaxOutput);

    pid->last_error = pid ->error;
		
			
//    return pid->PWM;
}


/**
  * @Data    2019-03-07 17:07
  * @brief   测试的位置模糊PID计算
  * @param   positionpid_t *pid,float target, float measured
  * @retval  void
  */
void FuzzyPID_PosCalculation(positionpid_t *pid,float target, float measured)
{
    float kp_output,ki_output,kd_output;

    pid->Target = (float)target;
    pid->Measured = (float)measured;
    pid->error = pid->Target - pid->Measured;
    pid->ec_error = pid->error - pid->last_error;
    /*模糊推导*/
    pid->Kp = fuzzy_kp(pid->error,pid->ec_error,pid->KpRule);
    pid->Ki = fuzzy_ki(pid->error,pid->ec_error,pid->KiRule);
    pid->Kd = fuzzy_kd(pid->error,pid->ec_error,pid->KdRule);

    if(ABS(pid->error) < 20)
		{
			pid->Add_error += pid->error;
		}
    
    /*消除抖动*/
    if(ABS(pid->error) < 0.5f )
    {
        pid->error = 0.0f;
    }
		
		
		

    kp_output = pid->Kp * pid->error;
    ki_output = pid->Ki * pid->Add_error;
    kd_output = pid->Kd * pid->ec_error;
    
    Limiting(&ki_output,pid->IntegralLimit);

    pid->PWM = (kp_output + ki_output + kd_output);

    /*输出限幅*/
    Limiting(&pid->PWM,pid->MaxOutput);

    pid->last_error = pid ->error;

//    return pid->PWM;
}




/* =========================== FUZZYCAL of begin =========================== */
/**
  * @Data    2019-02-19 16:31
  * @brief   模糊KP推导
  * @param   float e, float ec
  * @retval  float
  */
float fuzzy_kp(float e, float ec, float InputKpRule[4])
{ 
    /*定义Kp的计算值*/
    float Kp_calcu;

    /*定义一个提取模糊规则表的数字储存num，e的隶属程度，ec的隶属程度*/
    unsigned char  num,pe,pec; 

    /*e误差的模糊论域，可通过真实的误差来进行调整（根据电机的实际误差）*/
    float eRule[7]={-80.0,-50.0,-20.0,0.0,20.0,50.0,80.0};

    /*ec误差变化率的模糊论域，可以通过真实的误差变化率来进行调整（根据电机的实际误差）*/
    float ecRule[7]={-7.0,-5.0,-3.0,0.0,3.0,5.0,7.0};

    /*Kp 的模糊子集*/
    float kpRule[4]={InputKpRule[0],InputKpRule[1],InputKpRule[2],InputKpRule[3]}; 

    float eFuzzy[2]={0.0,0.0};//隶属于误差 E 的隶属程度
    float ecFuzzy[2]={0.0,0.0}; //隶属于误差变化率 EC 的隶属程度
    float KpFuzzy[4]={0.0,0.0,0.0,0.0}; //隶属于 Kp 的隶属程度

    /*Kp的模糊规则表*/
    int KpRule[7][7]= 
    {
        3,3,3,3,3,3,3, 
        2,2,2,2,1,2,2, 
        1,1,1,1,1,1,1, 
        1,1,0,1,0,1,1, 
        0,0,1,0,0,1,0, 
        0,1,0,1,0,0,2, 
        3,3,3,3,3,3,3 
    };

    /***** 误差 E 隶属函数描述 *****/ 
    /*计算其中一边的隶属程度的模糊值，并确定数值对应的区域*/
    if(e<eRule[0]) 
    { 
        eFuzzy[0] =1.0; pe = 0; 
    } 
    else if(eRule[0]<=e && e<eRule[1]) 
    { 
        eFuzzy[0] = (eRule[1]-e)/(eRule[1]-eRule[0]); pe = 0; 
    } 
    else if(eRule[1]<=e && e<eRule[2]) 
    { 
        eFuzzy[0] = (eRule[2] -e)/(eRule[2]-eRule[1]); pe = 1; 
    } 
    else if(eRule[2]<=e && e<eRule[3]) 
    {   
        eFuzzy[0] = (eRule[3] -e)/(eRule[3]-eRule[2]); pe = 2;
    } 
    else if(eRule[3]<=e && e<eRule[4]) 
    { 
        eFuzzy[0] = (eRule[4]-e)/(eRule[4]-eRule[3]); pe = 3; 
    } 
    else if(eRule[4]<=e && e<eRule[5]) 
    { 
        eFuzzy[0] = (eRule[5]-e)/(eRule[5]-eRule[4]); pe = 4; 
    } 
    else if(eRule[5]<=e && e<eRule[6]) 
    { 
        eFuzzy[0] = (eRule[6]-e)/(eRule[6]-eRule[5]); pe = 5; 
    } 
    else 
    { 
        eFuzzy[0] =0.0; pe =5; 
    } 

    /*算出其中一边的隶属程度后可以通过对应关系算出另外一边的隶属程度*/
    eFuzzy[1] =1.0 - eFuzzy[0]; 

    /*同理，算出ec的隶属程度，并确定数值对应的区域*/
    if(ec<ecRule[0])  
    { 
        ecFuzzy[0] =1.0; pec = 0; 
    } 
    else if(ecRule[0]<=ec && ec<ecRule[1]) 
    { 
        ecFuzzy[0] = (ecRule[1] - ec)/(ecRule[1]-ecRule[0]); pec = 0 ; 
    } 
    else if(ecRule[1]<=ec && ec<ecRule[2]) 
    { 
        ecFuzzy[0] = (ecRule[2] - ec)/(ecRule[2]-ecRule[1]); pec = 1; 
    } 
    else if(ecRule[2]<=ec && ec<ecRule[3]) 
    { 
        ecFuzzy[0] = (ecRule[3] - ec)/(ecRule[3]-ecRule[2]); pec = 2 ; 
    } 
    else if(ecRule[3]<=ec && ec<ecRule[4]) 
    { 
        ecFuzzy[0] = (ecRule[4]-ec)/(ecRule[4]-ecRule[3]); pec=3; 
    } 
    else if(ecRule[4]<=ec && ec<ecRule[5]) 
    { 
        ecFuzzy[0] = (ecRule[5]-ec)/(ecRule[5]-ecRule[4]); pec=4; 
    } 
    else if(ecRule[5]<=ec && ec<ecRule[6]) 
    { 
        ecFuzzy[0] = (ecRule[6]-ec)/(ecRule[6]-ecRule[5]); pec=5; 
    } 
    else 
    { 
        ecFuzzy[0] =0.0; pec = 5; 
    } 
    
    /*算出其中一边的隶属程度后可以通过对应关系算出另外一边的隶属程度*/
    ecFuzzy[1] = 1.0 - ecFuzzy[0];

    /********* 查询模糊规则表 *********/ 
    /*根据定义的规则表算出四个值*/
    num =KpRule[pe][pec]; 
    KpFuzzy[num] += eFuzzy[0]*ecFuzzy[0]; 
    num =KpRule[pe][pec+1]; 
    KpFuzzy[num] += eFuzzy[0]*ecFuzzy[1]; 
    num =KpRule[pe+1][pec]; 
    KpFuzzy[num] += eFuzzy[1]*ecFuzzy[0]; 
    num =KpRule[pe+1][pec+1]; 
    KpFuzzy[num] += eFuzzy[1]*ecFuzzy[1]; 

    /*加权平均法计算模糊PID*/
    Kp_calcu=KpFuzzy[0]*kpRule[0]+KpFuzzy[1]*kpRule[1]+KpFuzzy[2]*kpRule[2] +KpFuzzy[3]*kpRule[3]; 

    return(Kp_calcu);
}


/**
  * @Data    2019-02-19 16:32
  * @brief   ki模糊值推导
  * @param   float e, float ec
  * @retval  float
  */
float fuzzy_ki(float e, float ec, float InputKiRule[4]) 
{ 
    float Ki_calcu; 
    unsigned char num,pe,pec; 

    float eRule[7]={-120.0,-80.0,-40.0,0.0,40.0,80.0,120.0};

    float ecRule[7]={-7.0,-5.0,-3.0,0.0,3.0,5.0,7.0};

    float kiRule[4]={InputKiRule[0],InputKiRule[1],InputKiRule[2],InputKiRule[3]}; 

    float eFuzzy[2]={0.0,0.0}; 
    float ecFuzzy[2]={0.0,0.0}; 
    
    float KiFuzzy[4]={0.0,0.0,0.0,0.0}; 
    int KiRule[7][7]= 
    { 
        0,0,0,0,0,0,0, 
        0,0,0,0,0,0,0, 
        0,0,0,0,0,0,0, 
        0,0,0,0,0,0,0, 
        0,0,0,0,0,0,0, 
        2,0,0,0,0,0,1, 
        3,3,3,3,3,3,3 
    }; 
        /***** 误差隶属函数描述 *****/ 
        if(e<eRule[0]) 
        { 
            eFuzzy[0] =1.0; pe = 0; 
        } 
        else if(eRule[0]<=e && e<eRule[1]) 
        { 
            eFuzzy[0] = (eRule[1]-e)/(eRule[1]-eRule[0]); pe = 0; 
        } 
        else if(eRule[1]<=e && e<eRule[2]) 
        { 
            eFuzzy[0] = (eRule[2] -e)/(eRule[2]-eRule[1]); pe = 1; 
        } 
        else if(eRule[2]<=e && e<eRule[3]) 
        { 
            eFuzzy[0] = (eRule[3] -e)/(eRule[3]-eRule[2]); pe = 2; 
        } 
        else if(eRule[3]<=e && e<eRule[4]) 
        { 
            eFuzzy[0] = (eRule[4]-e)/(eRule[4]-eRule[3]); pe = 3; 
        } 
        else if(eRule[4]<=e && e<eRule[5]) 
        { 
            eFuzzy[0] = (eRule[5]-e)/(eRule[5]-eRule[4]); pe = 4; 
        } 
        else if(eRule[5]<=e && e<eRule[6]) 
        { 
            eFuzzy[0] = (eRule[6]-e)/(eRule[6]-eRule[5]); pe = 5; 
        } 
        else 
        { 
            eFuzzy[0] =0.0; pe =5; 
        } 
        eFuzzy[1] =1.0 - eFuzzy[0]; 
        
        /***** 误差变化隶属函数描述 *****/  
        if(ec<ecRule[0])  
        { 
            ecFuzzy[0] =1.0; pec = 0; 
        } 
        else if(ecRule[0]<=ec && ec<ecRule[1])
        { 
            ecFuzzy[0] = (ecRule[1] - ec)/(ecRule[1]-ecRule[0]); pec = 0 ; 
        } 
        else if(ecRule[1]<=ec && ec<ecRule[2]) 
        { 
            ecFuzzy[0] = (ecRule[2] - ec)/(ecRule[2]-ecRule[1]); pec = 1; 
        } 
        else if(ecRule[2]<=ec && ec<ecRule[3]) 
        { 
            ecFuzzy[0] = (ecRule[3] - ec)/(ecRule[3]-ecRule[2]); pec = 2 ; 
        } 
        else if(ecRule[3]<=ec && ec<ecRule[4]) 
        { 
            ecFuzzy[0] = (ecRule[4]-ec)/(ecRule[4]-ecRule[3]); pec=3; 
        } 
        else if(ecRule[4]<=ec && ec<ecRule[5]) 
        { 
            ecFuzzy[0] = (ecRule[5]-ec)/(ecRule[5]-ecRule[4]); pec=4; 
        } 
        else if(ecRule[5]<=ec && ec<ecRule[6]) 
        { 
            ecFuzzy[0] = (ecRule[6]-ec)/(ecRule[6]-ecRule[5]); pec=5; 
        } 
        else 
        { 
            ecFuzzy[0] =0.0; pec = 5; 
        } 
        ecFuzzy[1] = 1.0 - ecFuzzy[0]; 
        /*********** 查询模糊规则表 ***************/ 
        num =KiRule[pe][pec]; 
        KiFuzzy[num] += eFuzzy[0]*ecFuzzy[0]; 
        num =KiRule[pe][pec+1]; 
        KiFuzzy[num] += eFuzzy[0]*ecFuzzy[1]; 
        num =KiRule[pe+1][pec]; 
        KiFuzzy[num] += eFuzzy[1]*ecFuzzy[0]; 
        num =KiRule[pe+1][pec+1]; 
        KiFuzzy[num] += eFuzzy[1]*ecFuzzy[1]; 
        /******** 加 权 平 均 法 解 模 糊 ********/ 
        Ki_calcu=KiFuzzy[0]*kiRule[0]+KiFuzzy[1]*kiRule[1]+KiFuzzy[2]*kiRule[2] +KiFuzzy[3]*kiRule[3]; 
        return(Ki_calcu); 
} 


/**
  * @Data    2019-02-19 16:33
  * @brief   kd模糊值推导
  * @param   float e, float ec
  * @retval  float
  */
float fuzzy_kd(float e, float ec, float InputKdRule[4]) 
{ 
    float Kd_calcu; 
    unsigned char num,pe,pec; 
    float eRule[7]={-80.0,-40.0,-20.0,0.0,20.0,40.0,80.0};

    float ecRule[7]={-7.0,-5.0,-3.0,0.0,3.0,5.0,7.0};

    float kdRule[4]={InputKdRule[0],InputKdRule[1],InputKdRule[2],InputKdRule[3]}; 
    
    float eFuzzy[2]={0.0,0.0}; 
    float ecFuzzy[2]={0.0,0.0}; 

    
    float KdFuzzy[4]={0.0,0.0,0.0,0.0}; 
    int KdRule[7][7]= 
    { 
        3,3,3,2,2,2,2, 
        2,2,2,1,1,1,1, 
        1,1,2,1,1,2,1, 
        1,1,0,1,0,1,1, 
        1,1,0,0,0,1,1, 
        2,2,1,0,1,1,1, 
        3,3,3,3,2,3,2  
    }; 
            /***** 误差隶属函数描述 *****/ 
    if(e<eRule[0]) 
    { 
        eFuzzy[0] =1.0; pe = 0; 
    } 
    else if(eRule[0]<=e && e<eRule[1]) 
    { 
        eFuzzy[0] = (eRule[1]-e)/(eRule[1]-eRule[0]); pe = 0; 
    } 
    else if(eRule[1]<=e && e<eRule[2]) 
    { 
        eFuzzy[0] = (eRule[2] -e)/(eRule[2]-eRule[1]); pe = 1; 
    } 
    else if(eRule[2]<=e && e<eRule[3]) 
    { 
        eFuzzy[0] = (eRule[3] -e)/(eRule[3]-eRule[2]); pe = 2; 
    } 
    else if(eRule[3]<=e && e<eRule[4]) 
    { 
        eFuzzy[0] = (eRule[4]-e)/(eRule[4]-eRule[3]); pe = 3; 
    } 
    else if(eRule[4]<=e && e<eRule[5]) 
    { 
        eFuzzy[0] = (eRule[5]-e)/(eRule[5]-eRule[4]); pe = 4; 
    } 
    else if(eRule[5]<=e && e<eRule[6]) 
    { 
        eFuzzy[0] = (eRule[6]-e)/(eRule[6]-eRule[5]); pe = 5; 
    } 
    else 
    { 
         eFuzzy[0] =0.0; pe =5; 
    } 
    eFuzzy[1] =1.0 - eFuzzy[0]; 
    /***** 误差变化隶属函数描述 *****/  
    if(ec<ecRule[0])  
    { 
        ecFuzzy[0] =1.0; pec = 0; 
    } 
    else if(ecRule[0]<=ec && ec<ecRule[1]) 
    { 
        ecFuzzy[0] = (ecRule[1] - ec)/(ecRule[1]-ecRule[0]); pec = 0 ; 
    } 
    else if(ecRule[1]<=ec && ec<ecRule[2]) 
    { 
        ecFuzzy[0] = (ecRule[2] - ec)/(ecRule[2]-ecRule[1]); pec = 1; 
    } 
    else if(ecRule[2]<=ec && ec<ecRule[3]) 
    { 
        ecFuzzy[0] = (ecRule[3] - ec)/(ecRule[3]-ecRule[2]); pec = 2 ; 
    } 
    else if(ecRule[3]<=ec && ec<ecRule[4]) 
    { 
        ecFuzzy[0] = (ecRule[4]-ec)/(ecRule[4]-ecRule[3]); pec=3; 
    } 
    else if(ecRule[4]<=ec && ec<ecRule[5]) 
    { 
        ecFuzzy[0] = (ecRule[5]-ec)/(ecRule[5]-ecRule[4]); pec=4; 
    } 
    else if(ecRule[5]<=ec && ec<ecRule[6]) 
    { 
        ecFuzzy[0] = (ecRule[6]-ec)/(ecRule[6]-ecRule[5]); pec=5; 
    } 
    else 
    { 
        ecFuzzy[0] =0.0; pec = 5; 
    } 
    ecFuzzy[1] = 1.0 - ecFuzzy[0];
     /*********** 查询模糊规则表 *************/ 
    num =KdRule[pe][pec]; 
    KdFuzzy[num] += eFuzzy[0]*ecFuzzy[0]; 
    num =KdRule[pe][pec+1]; 
    KdFuzzy[num] += eFuzzy[0]*ecFuzzy[1]; 
    num =KdRule[pe+1][pec]; 
    KdFuzzy[num] += eFuzzy[1]*ecFuzzy[0]; 
    num =KdRule[pe+1][pec+1]; 
    KdFuzzy[num] += eFuzzy[1]*ecFuzzy[1]; 
    /******** 加权平均法解模糊 ********/ 
    Kd_calcu=KdFuzzy[0]*kdRule[0]+KdFuzzy[1]*kdRule[1]+KdFuzzy[2]*kdRule[2] +KdFuzzy[3]*kdRule[3]; 
    return(Kd_calcu); 
} 
/* =========================== FUZZYCAL of end =========================== */
/*-----------------------------------file of end------------------------------*/


