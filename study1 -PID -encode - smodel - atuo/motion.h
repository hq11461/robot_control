#ifndef __MOTION_H
#define __MOTION_H

#include "pid.h"


typedef struct
{
	int firstenter;   //第一次进入状态标志位
	int gostraight;
	int turnright;          //右转标志位
	int turnleft;     //左转标志位
	int back;     //后退标志位
	int turnaround;     //摇头标志位
	int motion_running;     //运动进行标志位
	int next_motionL;      //红外检测判断下次运动模式暂存位
	int next_motionR;
	int last_motion ;       //上次转向运动存储标志位
	int turnaround_elimination;   //红外检测转向识别消抖标志位
}Motion_Struct;


#define    Stop        0          //停止
#define    Forward     2           //前进    
#define    TurnLeft    1          //左转
#define    TurnRight   3           //右转
#define    Rotate      4           //原地旋转   
#define    Back        5          //后退

void Motin_param_Init(void);
void Run_motion(void);
void Turnleft_motion(PID_Struct *pid);
void Turnright_motion(PID_Struct *pid);
void Motion_Select(Motion_Struct *motion);
void Motion_mutual(int motionselect) ; 
void Motion_swith(Motion_Struct *motion_sign)  ;

#endif
