#include "pid.h"
#include <stdio.h>
#include <stm32f4xx.h>



//1.����ʽpid
//����PID��غ�
// �����������趨�Ե������Ӱ��ǳ���
/*************************************/

 PID_Struct pid_right;
 PID_Struct pid_left;
 PID_Struct pid_local;
// PID_Struct pid_turnright;
 PID_Struct pid_localright;
 PID_Struct pid_localleft;
 
 void PID_rotate_Init(void)   //�ṹ���¼ֵ����
 {
	pid_right.target_val = 120;
	pid_right.err = 0.0;
	pid_right.err_last = 0.0;
	pid_right.Kp = 13.6;
	pid_right.Ki = 2.25;
	pid_right.Kd = 0.065;
	pid_right.integral=0.0;

	/* �ٶ���س�ʼ������ */
				
	pid_left.output_val=0.0;
	pid_left.err=0.0;
	pid_left.err_last=0.0;
	pid_left.integral=0.0;
	pid_left.target_val = 120;
	pid_left.Kp = 18.0;
	pid_left.Ki = 0.6;
	pid_left.Kd = 0.2;
	
	
	
	pid_localright.err = 1 * 2496;     //ת��������Ȧ��
	pid_localright.Kp = 8.5;
	pid_localright.Ki = 0;
	pid_localright.Kd = 0;
	
	pid_localleft.err = 1 * 2496;     //ת��������Ȧ��
	pid_localleft.Kp = 10;
	pid_localleft.Ki = 0;
	pid_localleft.Kd = 0;
 
 }
 
void PID_param_init(void)
{
	/* λ����س�ʼ������ */
				
	pid_right.target_val = 120;
	pid_right.err = 0.0;
	pid_right.err_last = 0.0;
	pid_right.Kp = 13.6;
	pid_right.Ki = 2.25;
	pid_right.Kd = 0.065;
	pid_right.integral=0.0;

	/* �ٶ���س�ʼ������ */
				
	pid_left.output_val=0.0;
	pid_left.err=0.0;
	pid_left.err_last=0.0;
	pid_left.integral=0.0;
	pid_left.target_val = 120;
	pid_left.Kp = 13.6;
	pid_left.Ki = 2.25;
	pid_left.Kd = 0.065;
	
	pid_local.Kp = 9.5;
	pid_local.Ki = 0.5;
	pid_local.Kd = 0;
	
	pid_localright.err = 1.69 * 2496;     //ת��������Ȧ��
	pid_localright.Kp = 8.5;
	pid_localright.Ki = 0;
	pid_localright.Kd = 0;
	
	pid_localleft.err = 1.69 * 2496;     //ת��������Ȧ��
	pid_localleft.Kp = 10;
	pid_localleft.Ki = 0;
	pid_localleft.Kd = 0;
	
}


/********************λ��ʽPID�������************************************/
//NextPoint��ǰ���ֵ
//SetPoint�趨ֵ


//ת����˶�λλ�û�PID
int PID_LocalTurn(PID_Struct *pid,int nowencode) 
{
                             
int Outpid;                                        //��ǰ���
//static int sum = 0;	

//     sum +=  nowencode;                       
	 pid->err = pid->err - nowencode;                                //������
//printf("==pid_localright.err = %f\r\n",pid_localright.err);	
//printf("==pid_localleft.err = %f\r\n",pid_localleft.err);		
//	printf("pid->err=%f\r\n",pid->err)	;
//	printf(" nowencode=%d\r\n", nowencode)	;
//    printf(" sum=%d\r\n", sum)	;
	//���ַ��룬��ֹ�����ۼƹ���Ӱ��ϵͳ��Ӧ
	
	
	Outpid = pid->Kp * pid->err +
	                  pid->Ki * pid->integral +
	                  pid->Kd *(pid->err - pid->err_last);

	/*����*/
	pid->err_last = pid->err;
	
	if(Outpid>pid_right.target_val)        //λ�û�����޷���Ϊ�˲������ٶȻ�����
	{
	Outpid = pid_right.target_val;
	}
	
  return(Outpid);  


}

//ֱ��λ�û�PID
int PID_Localsame(PID_Struct *pid,int aimencode,int nowencode) 
{
                             

	int Outpid;                                        //��ǰ���
	

	
	//һ�׵�ͨ�˲�

                             
	 pid->err = aimencode - nowencode;                                //��������
	
	
 
	
	
	
	Outpid = pid->Kp * pid->err +
	                  pid->Ki * pid->integral +
	                  pid->Kd *(pid->err - pid->err_last);

	/*����*/
	pid->err_last = pid->err;
  return(Outpid);  


}

//����PID
int PID_Calc_Right(PID_Struct *pid,float NextPoint) 
{
	
	int Outpid;                                        //��ǰ���
	
   pid->err = pid->target_val - NextPoint; 
	
	//һ�׵�ͨ�˲�
   if(pid->err_last!=0)
   {
	   pid->err= 0.8f*pid->err + 0.2f*pid->err_last;
   }
	   
	//���ַ��룬��ֹ�����ۼƹ���Ӱ��ϵͳ��Ӧ
//	if(pid->err > INTEGRAL_START_ERR && pid->err < INTEGRAL_START_ERR)
//	{
//		pid->integral += pid->err;  
//        /*���ַ�Χ�޶�����ֹ���ֱ���*/
//		if(pid->integral > INTEGRAL_MAX_VAL)
//		{
//			pid->integral = INTEGRAL_MAX_VAL;
//		}
//		else if(pid->integral < -INTEGRAL_MAX_VAL)
//		{
//			pid->integral = -INTEGRAL_MAX_VAL;
//		}
//	}	
 //  printf("===pid->Rerr=== = %f\r\n",pid->err);
    pid->integral += pid->err;  
	
	Outpid = pid->Kp * pid->err +
	                  pid->Ki * pid->integral +
	                  pid->Kd *(pid->err - pid->err_last);
   
	/*����*/
	pid->err_last = pid->err;
  return(Outpid);  
}

 float num = 0;
//����PID
int PID_Calc_Left(PID_Struct *pid,float NextPoint) 
{                      
	
	int Outpid;                                        //��ǰ���
	
   pid->err = pid->target_val - NextPoint;                                //��������
	
	//һ�׵�ͨ�˲�
   if(pid->err_last!=0)
   {
	   pid->err= 0.8f*pid->err + 0.2f*pid->err_last;
   }
	   
	//���ַ��룬��ֹ�����ۼƹ���Ӱ��ϵͳ��Ӧ
//	if(pid->err > INTEGRAL_START_ERR && pid->err < INTEGRAL_START_ERR)
//	{
//		pid->integral += pid->err;  
//        /*���ַ�Χ�޶�����ֹ���ֱ���*/
//		if(pid->integral > INTEGRAL_MAX_VAL)
//		{
//			pid->integral = INTEGRAL_MAX_VAL;
//		}
//		else if(pid->integral < -INTEGRAL_MAX_VAL)
//		{
//			pid->integral = -INTEGRAL_MAX_VAL;
//		}
//	}

//	printf("===pid->Lerr=== = %f\r\n",pid->err);	   
    pid->integral += pid->err;  
	num +=	pid->err;
	Outpid = pid->Kp * pid->err +
	                  pid->Ki * pid->integral +
	                  pid->Kd *(pid->err - pid->err_last);

	/*����*/
	pid->err_last = pid->err;
  return(Outpid);  
	
}

