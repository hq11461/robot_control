#ifndef __MOTION_H
#define __MOTION_H

#include "pid.h"


typedef struct
{
	int firstenter;   //��һ�ν���״̬��־λ
	int gostraight;
	int turnright;          //��ת��־λ
	int turnleft;     //��ת��־λ
	int back;     //���˱�־λ
	int turnaround;     //ҡͷ��־λ
	int motion_running;     //�˶����б�־λ
	int next_motionL;      //�������ж��´��˶�ģʽ�ݴ�λ
	int next_motionR;
	int last_motion ;       //�ϴ�ת���˶��洢��־λ
	int turnaround_elimination;   //������ת��ʶ��������־λ
}Motion_Struct;


#define    Stop        0          //ֹͣ
#define    Forward     2           //ǰ��    
#define    TurnLeft    1          //��ת
#define    TurnRight   3           //��ת
#define    Rotate      4           //ԭ����ת   
#define    Back        5          //����

void Motin_param_Init(void);
void Run_motion(void);
void Turnleft_motion(PID_Struct *pid);
void Turnright_motion(PID_Struct *pid);
void Motion_Select(Motion_Struct *motion);
void Motion_mutual(int motionselect) ; 
void Motion_swith(Motion_Struct *motion_sign)  ;

#endif
