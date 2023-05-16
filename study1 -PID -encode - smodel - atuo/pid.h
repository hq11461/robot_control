#ifndef __PID_H
#define __PID_H
#include "sys.h"
typedef struct
{
	float target_val;   //Ŀ��ֵ
	float err;          //ƫ��ֵ
	float err_last;     //��һ��ƫ��ֵ
	float Kp,Ki,Kd;     //���������֡�΢��ϵ��
	float integral;     //����ֵ
	float output_val;   //���ֵ
}PID_Struct;

 


#define  localpid_EN       0    //�Ƿ���λ�û����п���
#define  INTEGRAL_START_ERR  1000
#define  INTEGRAL_MAX_VAL    6000

void PID_param_init(void);
int PID_Localsame(PID_Struct *pid,int rightencode,int leftencode) ;

int PID_Calc_Left(PID_Struct *pid,float NextPoint);
int PID_Calc_Right(PID_Struct *pid,float NextPoint);
int PID_LocalTurn(PID_Struct *pid,int nowencode) ;
void PID_rotate_Init(void) ;

#endif

