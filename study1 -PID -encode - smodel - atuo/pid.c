#include "pid.h"
#include <stdio.h>
#include <stm32f4xx.h>



//1.增量式pid
//定义PID相关宏
// 这三个参数设定对电机运行影响非常大
/*************************************/

 PID_Struct pid_right;
 PID_Struct pid_left;
 PID_Struct pid_local;
// PID_Struct pid_turnright;
 PID_Struct pid_localright;
 PID_Struct pid_localleft;
 
 void PID_rotate_Init(void)   //结构体记录值清零
 {
	pid_right.target_val = 120;
	pid_right.err = 0.0;
	pid_right.err_last = 0.0;
	pid_right.Kp = 13.6;
	pid_right.Ki = 2.25;
	pid_right.Kd = 0.065;
	pid_right.integral=0.0;

	/* 速度相关初始化参数 */
				
	pid_left.output_val=0.0;
	pid_left.err=0.0;
	pid_left.err_last=0.0;
	pid_left.integral=0.0;
	pid_left.target_val = 120;
	pid_left.Kp = 18.0;
	pid_left.Ki = 0.6;
	pid_left.Kd = 0.2;
	
	
	
	pid_localright.err = 1 * 2496;     //转向单轮所需圈数
	pid_localright.Kp = 8.5;
	pid_localright.Ki = 0;
	pid_localright.Kd = 0;
	
	pid_localleft.err = 1 * 2496;     //转向单轮所需圈数
	pid_localleft.Kp = 10;
	pid_localleft.Ki = 0;
	pid_localleft.Kd = 0;
 
 }
 
void PID_param_init(void)
{
	/* 位置相关初始化参数 */
				
	pid_right.target_val = 120;
	pid_right.err = 0.0;
	pid_right.err_last = 0.0;
	pid_right.Kp = 13.6;
	pid_right.Ki = 2.25;
	pid_right.Kd = 0.065;
	pid_right.integral=0.0;

	/* 速度相关初始化参数 */
				
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
	
	pid_localright.err = 1.69 * 2496;     //转向单轮所需圈数
	pid_localright.Kp = 8.5;
	pid_localright.Ki = 0;
	pid_localright.Kd = 0;
	
	pid_localleft.err = 1.69 * 2496;     //转向单轮所需圈数
	pid_localleft.Kp = 10;
	pid_localleft.Ki = 0;
	pid_localleft.Kd = 0;
	
}


/********************位置式PID控制设计************************************/
//NextPoint当前输出值
//SetPoint设定值


//转向后退定位位置环PID
int PID_LocalTurn(PID_Struct *pid,int nowencode) 
{
                             
int Outpid;                                        //当前误差
//static int sum = 0;	

//     sum +=  nowencode;                       
	 pid->err = pid->err - nowencode;                                //误差计算
//printf("==pid_localright.err = %f\r\n",pid_localright.err);	
//printf("==pid_localleft.err = %f\r\n",pid_localleft.err);		
//	printf("pid->err=%f\r\n",pid->err)	;
//	printf(" nowencode=%d\r\n", nowencode)	;
//    printf(" sum=%d\r\n", sum)	;
	//积分分离，防止积分累计过大影响系统响应
	
	
	Outpid = pid->Kp * pid->err +
	                  pid->Ki * pid->integral +
	                  pid->Kd *(pid->err - pid->err_last);

	/*误差传递*/
	pid->err_last = pid->err;
	
	if(Outpid>pid_right.target_val)        //位置环输出限幅，为了不高于速度环限速
	{
	Outpid = pid_right.target_val;
	}
	
  return(Outpid);  


}

//直行位置环PID
int PID_Localsame(PID_Struct *pid,int aimencode,int nowencode) 
{
                             

	int Outpid;                                        //当前误差
	

	
	//一阶低通滤波

                             
	 pid->err = aimencode - nowencode;                                //增量计算
	
	
 
	
	
	
	Outpid = pid->Kp * pid->err +
	                  pid->Ki * pid->integral +
	                  pid->Kd *(pid->err - pid->err_last);

	/*误差传递*/
	pid->err_last = pid->err;
  return(Outpid);  


}

//左轮PID
int PID_Calc_Right(PID_Struct *pid,float NextPoint) 
{
	
	int Outpid;                                        //当前误差
	
   pid->err = pid->target_val - NextPoint; 
	
	//一阶低通滤波
   if(pid->err_last!=0)
   {
	   pid->err= 0.8f*pid->err + 0.2f*pid->err_last;
   }
	   
	//积分分离，防止积分累计过大影响系统响应
//	if(pid->err > INTEGRAL_START_ERR && pid->err < INTEGRAL_START_ERR)
//	{
//		pid->integral += pid->err;  
//        /*积分范围限定，防止积分饱和*/
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
   
	/*误差传递*/
	pid->err_last = pid->err;
  return(Outpid);  
}

 float num = 0;
//右轮PID
int PID_Calc_Left(PID_Struct *pid,float NextPoint) 
{                      
	
	int Outpid;                                        //当前误差
	
   pid->err = pid->target_val - NextPoint;                                //增量计算
	
	//一阶低通滤波
   if(pid->err_last!=0)
   {
	   pid->err= 0.8f*pid->err + 0.2f*pid->err_last;
   }
	   
	//积分分离，防止积分累计过大影响系统响应
//	if(pid->err > INTEGRAL_START_ERR && pid->err < INTEGRAL_START_ERR)
//	{
//		pid->integral += pid->err;  
//        /*积分范围限定，防止积分饱和*/
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

	/*误差传递*/
	pid->err_last = pid->err;
  return(Outpid);  
	
}

