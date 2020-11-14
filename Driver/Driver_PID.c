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
  |--FileName    : Driver_PID.c                                              
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
#include "Driver_PID.h"


#include "BSP_Init.h"

/**
  * @Data    2019-02-19 15:46
  * @brief   ����ʽPID����
  * @param   incrementalpid_t *pid,   ����ʽPID�ṹ��
  *          float target,            ��Ӧ������ʽPIDĿ��ֵ
  *          float measured           ��Ӧ������ʽPID����ֵ
  * @retval  int
  */
void IncrementalPID_Calculation(incrementalpid_t *pid, float target, float measured)
{
    pid->Target_speed = target;
    pid->Measured_speed = measured;

    pid->error = pid->Target_speed - pid->Measured_speed;

    /*��������*/
     if(ABS(pid->error) < 0.2f )
     {
         pid->error = 0.0f;
     }

    /*PID��ʽ*/
    pid->Kp_Output = pid->Kp * (pid->error - pid->last_error);
    pid->Ki_Output = pid->Ki * (pid->error);
    pid->Kd_Output = pid->Kd * (pid->error - 2*pid->last_error + pid->beforelast_error);


    /*Ki�޷�*/
    Limiting(&pid->Ki_Output,pid->IntegralLimit);

    pid->PWM += (pid->Kp_Output + pid->Ki_Output + pid->Kd_Output);

    /*����޷�*/
    Limiting(&pid->PWM,pid->MaxOutput);

    /*�ݽ�*/
    pid->beforelast_error = pid->last_error;
    pid->last_error = pid->error;

}

/**
  * @Data    2019-02-19 16:01
  * @brief   λ��ʽPID����
  * @param   positionpid_t *pid, λ��ʽPID����
  *          float target,       λ��ʽPIDĿ��ֵ
  *          float measured      λ��ʽPID����ֵ
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
		
    /*���ַ���*/
		if(ABS(pid->error) < 20)
		{
			pid->Add_error += pid->error;
		}
		
		
		

    /*λ��ʽPID���㹫ʽ*/
    pid->Kp_Output = pid->Kp * pid->error;
    pid->Ki_Output = pid->Ki * pid->Add_error;
    pid->Kd_Output = pid->Kd * (pid->error - pid->last_error);
		
//		if(ABS(pid->error) < 0.5)
//		{
//				pid->Kd_Output = 0;
//		}

    /*Ki�޷�*/
    Limiting(&pid->Ki_Output,pid->IntegralLimit);

    pid->PWM = (pid->Kp_Output + pid->Ki_Output + pid->Kd_Output);

    /*����޷�*/
    Limiting(&pid->PWM,pid->MaxOutput);

    pid->last_error = pid ->error;
		
			
//    return pid->PWM;
}


/**
  * @Data    2019-03-07 17:07
  * @brief   ���Ե�λ��ģ��PID����
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
    /*ģ���Ƶ�*/
    pid->Kp = fuzzy_kp(pid->error,pid->ec_error,pid->KpRule);
    pid->Ki = fuzzy_ki(pid->error,pid->ec_error,pid->KiRule);
    pid->Kd = fuzzy_kd(pid->error,pid->ec_error,pid->KdRule);

    if(ABS(pid->error) < 20)
		{
			pid->Add_error += pid->error;
		}
    
    /*��������*/
    if(ABS(pid->error) < 0.5f )
    {
        pid->error = 0.0f;
    }
		
		
		

    kp_output = pid->Kp * pid->error;
    ki_output = pid->Ki * pid->Add_error;
    kd_output = pid->Kd * pid->ec_error;
    
    Limiting(&ki_output,pid->IntegralLimit);

    pid->PWM = (kp_output + ki_output + kd_output);

    /*����޷�*/
    Limiting(&pid->PWM,pid->MaxOutput);

    pid->last_error = pid ->error;

//    return pid->PWM;
}




/* =========================== FUZZYCAL of begin =========================== */
/**
  * @Data    2019-02-19 16:31
  * @brief   ģ��KP�Ƶ�
  * @param   float e, float ec
  * @retval  float
  */
float fuzzy_kp(float e, float ec, float InputKpRule[4])
{ 
    /*����Kp�ļ���ֵ*/
    float Kp_calcu;

    /*����һ����ȡģ�����������ִ���num��e�������̶ȣ�ec�������̶�*/
    unsigned char  num,pe,pec; 

    /*e����ģ�����򣬿�ͨ����ʵ����������е��������ݵ����ʵ����*/
    float eRule[7]={-80.0,-50.0,-20.0,0.0,20.0,50.0,80.0};

    /*ec���仯�ʵ�ģ�����򣬿���ͨ����ʵ�����仯�������е��������ݵ����ʵ����*/
    float ecRule[7]={-7.0,-5.0,-3.0,0.0,3.0,5.0,7.0};

    /*Kp ��ģ���Ӽ�*/
    float kpRule[4]={InputKpRule[0],InputKpRule[1],InputKpRule[2],InputKpRule[3]}; 

    float eFuzzy[2]={0.0,0.0};//��������� E �������̶�
    float ecFuzzy[2]={0.0,0.0}; //���������仯�� EC �������̶�
    float KpFuzzy[4]={0.0,0.0,0.0,0.0}; //������ Kp �������̶�

    /*Kp��ģ�������*/
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

    /***** ��� E ������������ *****/ 
    /*��������һ�ߵ������̶ȵ�ģ��ֵ����ȷ����ֵ��Ӧ������*/
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

    /*�������һ�ߵ������̶Ⱥ����ͨ����Ӧ��ϵ�������һ�ߵ������̶�*/
    eFuzzy[1] =1.0 - eFuzzy[0]; 

    /*ͬ�����ec�������̶ȣ���ȷ����ֵ��Ӧ������*/
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
    
    /*�������һ�ߵ������̶Ⱥ����ͨ����Ӧ��ϵ�������һ�ߵ������̶�*/
    ecFuzzy[1] = 1.0 - ecFuzzy[0];

    /********* ��ѯģ������� *********/ 
    /*���ݶ���Ĺ��������ĸ�ֵ*/
    num =KpRule[pe][pec]; 
    KpFuzzy[num] += eFuzzy[0]*ecFuzzy[0]; 
    num =KpRule[pe][pec+1]; 
    KpFuzzy[num] += eFuzzy[0]*ecFuzzy[1]; 
    num =KpRule[pe+1][pec]; 
    KpFuzzy[num] += eFuzzy[1]*ecFuzzy[0]; 
    num =KpRule[pe+1][pec+1]; 
    KpFuzzy[num] += eFuzzy[1]*ecFuzzy[1]; 

    /*��Ȩƽ��������ģ��PID*/
    Kp_calcu=KpFuzzy[0]*kpRule[0]+KpFuzzy[1]*kpRule[1]+KpFuzzy[2]*kpRule[2] +KpFuzzy[3]*kpRule[3]; 

    return(Kp_calcu);
}


/**
  * @Data    2019-02-19 16:32
  * @brief   kiģ��ֵ�Ƶ�
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
        /***** ��������������� *****/ 
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
        
        /***** ���仯������������ *****/  
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
        /*********** ��ѯģ������� ***************/ 
        num =KiRule[pe][pec]; 
        KiFuzzy[num] += eFuzzy[0]*ecFuzzy[0]; 
        num =KiRule[pe][pec+1]; 
        KiFuzzy[num] += eFuzzy[0]*ecFuzzy[1]; 
        num =KiRule[pe+1][pec]; 
        KiFuzzy[num] += eFuzzy[1]*ecFuzzy[0]; 
        num =KiRule[pe+1][pec+1]; 
        KiFuzzy[num] += eFuzzy[1]*ecFuzzy[1]; 
        /******** �� Ȩ ƽ �� �� �� ģ �� ********/ 
        Ki_calcu=KiFuzzy[0]*kiRule[0]+KiFuzzy[1]*kiRule[1]+KiFuzzy[2]*kiRule[2] +KiFuzzy[3]*kiRule[3]; 
        return(Ki_calcu); 
} 


/**
  * @Data    2019-02-19 16:33
  * @brief   kdģ��ֵ�Ƶ�
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
            /***** ��������������� *****/ 
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
    /***** ���仯������������ *****/  
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
     /*********** ��ѯģ������� *************/ 
    num =KdRule[pe][pec]; 
    KdFuzzy[num] += eFuzzy[0]*ecFuzzy[0]; 
    num =KdRule[pe][pec+1]; 
    KdFuzzy[num] += eFuzzy[0]*ecFuzzy[1]; 
    num =KdRule[pe+1][pec]; 
    KdFuzzy[num] += eFuzzy[1]*ecFuzzy[0]; 
    num =KdRule[pe+1][pec+1]; 
    KdFuzzy[num] += eFuzzy[1]*ecFuzzy[1]; 
    /******** ��Ȩƽ������ģ�� ********/ 
    Kd_calcu=KdFuzzy[0]*kdRule[0]+KdFuzzy[1]*kdRule[1]+KdFuzzy[2]*kdRule[2] +KdFuzzy[3]*kdRule[3]; 
    return(Kd_calcu); 
} 
/* =========================== FUZZYCAL of end =========================== */
/*-----------------------------------file of end------------------------------*/


