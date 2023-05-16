#ifndef __PID_H
#define __PID_H
#include "sys.h"
typedef struct
{
	float target_val;   //目标值
	float err;          //偏差值
	float err_last;     //上一个偏差值
	float Kp,Ki,Kd;     //比例、积分、微分系数
	float integral;     //积分值
	float output_val;   //输出值
}PID_Struct;

 


#define  localpid_EN       0    //是否开启位置环并行控制
#define  INTEGRAL_START_ERR  1000
#define  INTEGRAL_MAX_VAL    6000

void PID_param_init(void);
int PID_Localsame(PID_Struct *pid,int rightencode,int leftencode) ;

int PID_Calc_Left(PID_Struct *pid,float NextPoint);
int PID_Calc_Right(PID_Struct *pid,float NextPoint);
int PID_LocalTurn(PID_Struct *pid,int nowencode) ;
void PID_rotate_Init(void) ;

#endif

