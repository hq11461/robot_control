#include "encode.h"
#include "pid.h"
#include "ursat.h"
#include <stdio.h>
#include <stm32f4xx.h>
#include "motion.h"
#include "hongwai.h"
#include "motor.h"

Motion_Struct motion_sign;

void Motin_param_Init(void)
	
{
	motion_sign.firstenter = 1 ;   //��һ�ν���״̬��־λ
	motion_sign.gostraight = 1;
	motion_sign.turnright = 0;          //��ת��־λ
	motion_sign.turnleft = 0;     //��ת��־λ
	motion_sign.back = 0;     //���˱�־λ
	motion_sign.turnaround = 0;     //ҡͷ��־λ
	motion_sign.motion_running = 1;
	motion_sign.next_motionR = 0 ;
    motion_sign.next_motionL = 0 ;
	motion_sign.last_motion = 0 ;    //�����ת��һ��ת�����1����ת��2
	motion_sign.turnaround_elimination = 0;  //�ڶ��ν���ת���ж�ʱ������ǵ�һ�ν��յ�ǰ�ú����źž���1�����������ɨ�Եĸ���Ч��
}

void Motion_swith(Motion_Struct *motion_sign)                               //���´��˶���־λ�л��ɱ����˶���־λ
{
	
if(motion_sign->motion_running == 0)
{	
	if(motion_sign->last_motion  == 0 )
  {

	if(motion_sign->next_motionR < motion_sign->next_motionL)	
				{  
		Motion_mutual(1) ;
        motion_sign->last_motion = 1;
				}
        	
	else if (motion_sign->next_motionR > motion_sign->next_motionL)
				{
				Motion_mutual(3) ;	
				motion_sign->last_motion = 2 ;
				}
	else {
		  Motion_mutual(2);
		  printf("hongwaijudge_error");
		 }
	}else{
  
	if(motion_sign->last_motion%2 == 0)	
				{  
		Motion_mutual(1) ;   
					
				}
        	
	else if (motion_sign->last_motion%2 == 1)
				{
				Motion_mutual(3) ;	
	
				}
		
	else {
		  Motion_mutual(2);
		  printf("hongwaijudge_error");
		 }
  motion_sign->last_motion ++ ;
	 }         

	motion_sign->firstenter = 1;
//printf("motion_sign->last_motion = %d\r\n",motion_sign->last_motion);		
//	motion_sign->motion_running = 1;

}

}

void Motion_mutual(int motionselect)             //�˶���־λ���⺯��
{
	// printf("Motion_mutual = %d",motionselect);
if( motionselect == 1)
{
	motion_sign.gostraight = 0;          //ֱ�б�־λ
	motion_sign.turnright = 0;          //��ת��־λ
	motion_sign.turnleft = 1;     //��ת��־λ
	motion_sign.turnaround = 0;     //ҡͷ��־λ
}else if( motionselect == 3){
	motion_sign.gostraight = 0;          //ֱ�б�־λ
	motion_sign.turnright = 1;          //��ת��־λ
	motion_sign.turnleft = 0;     //��ת��־λ
	motion_sign.turnaround = 0;     //ҡͷ��־λ
}else if( motionselect == 2){
	motion_sign.gostraight = 1;          //ֱ�б�־λ
	motion_sign.turnright = 0;          //��ת��־λ
	motion_sign.turnleft = 0;     //��ת��־λ
	motion_sign.turnaround = 0;     //ҡͷ��־λ
}else if(motionselect == 5){
	motion_sign.gostraight = 0;          //ֱ�б�־λ
	motion_sign.turnright = 0;          //��ת��־λ
	motion_sign.turnleft = 0;     //��ת��־λ
	motion_sign.turnaround = 1;     //ҡͷ��־λ
}



}

int  Encoder_L=0,Encoder_R=0;     //�ٶ�ֵΪÿ���ӵ�Ȧ��
 extern PID_Struct pid_right;
 extern PID_Struct pid_left;
 extern PID_Struct pid_local;
 extern PID_Struct pid_turnright;
 extern PID_Struct pid_localright;
 extern PID_Struct pid_localleft;
float speed_L=0,speed_R=0,para_local=0;
int para_L,para_R,PWM_L,PWM_R;
int sign_turn = 0,turn=0;    //ת���־λ

void Turn_Judge(Motion_Struct *motion_sign)
{
			if(motion_sign->firstenter == 1)
						{
					motion_sign->motion_running = 1;
					//PID_param_init();
					motion_sign->firstenter=0;			
				
					TIM4->CCR2=0; 
					TIM4->CCR3=0; //����pwm	
						}
			
			
			
	search(motion_sign);		




			
			
  if((motion_sign->next_motionR - motion_sign->next_motionL)>5||(motion_sign->next_motionR - motion_sign->next_motionL)< -5||motion_sign->last_motion != 0 )
		 {
			
		motion_sign->motion_running = 0;
	//	Motion_swith(motion_sign);
		 }		
			
			
			

}

 int sumr = 1000;	
void Run_motion(void)
{
	
	
			if(motion_sign.firstenter == 1)
			{
			motion_sign.motion_running = 1;
			PID_param_init();
//				printf("///////////////");
			motion_sign.firstenter=0;
					
			}
			
				Encoder_R= Read_Encoder(5) - 30000;                   //��ȡ��������������仯��
				Encoder_L= Read_Encoder(3) - 30000;                   //��ȡ��������������仯��,��������Ϊ������� ���λ��180��
			
//				static int suml = 0;
				    
//				suml +=  Encoder_L;	
//	
//			printf(" sumr=%d\r\n", sumr)	;
//			printf(" suml=%d\r\n", suml)	;
	
			if(Encoder_R < 0)
			{
				Encoder_R = -Encoder_R;
			}
			if(Encoder_L < 0)
			{
				Encoder_L = -Encoder_L;
			}
	
	sumr = sumr+ Encoder_R - Encoder_L;    
			
			speed_R= Encoder_R*1200 /2496;                   //��ȡ��������������仯��
			speed_L= Encoder_L*1200 /2496;
		
		
			
						
						
			para_L=PID_Calc_Left(&pid_left,speed_L);	       //�����������õ�����ʽPID��������ֵ 
			para_R=PID_Calc_Right(&pid_right,speed_R);	       //�ҵ���������õ�����ʽPID��������ֵ 
			
#if (localpid_EN)			
			para_local= PID_Localsame(&pid_local,Encoder_R,Encoder_L);
#endif


			
//			if((para_L<-3)||(para_L>3))              //���� PID ��������������СʱƵ�����������𵴡�
//			{
			PWM_L = para_L+para_local;  
//			}   
//			if((para_R<-3)||(para_R>3))                     //���� PID ��������������СʱƵ�����������𵴡�
//			{
			PWM_R = para_R;  
				
		
  		    if(PWM_L>500)PWM_L=500;    //�޷� ��ֹ�ջٵ��
		    if(PWM_L<0)PWM_L=0;    //�޷� ��ֹ�ջٵ��
			if(PWM_R>500)PWM_R=500;    //�޷� ��ֹ�ջٵ��
			if(PWM_R<0)PWM_R=0;    //�޷� ��ֹ�ջٵ��
			
			PWM_L =  PWM_L;
			PWM_R =  PWM_R;
			
			
		TIM4->CCR3=PWM_R;  //����pwm
		  // TIM4->CCR1=200;  //����pwm
		TIM4->CCR2=PWM_L; //����pwm    
		   // TIM4->CCR2=200;
			
	
		 
}

void Turnleft_motion(PID_Struct *pid)
{ 

	       if(motion_sign.firstenter == 1)
			{
			motion_sign.motion_running = 1;
			PID_param_init();
			motion_sign.firstenter=0;	
			pid->Ki = 0;                                                 //	ȥ���ٶȻ�������
		
			}
	
			Encoder_L= Read_Encoder(3) - 30000;                   //��ȡ��������������仯��,��������Ϊ������� ���λ��180��
	
			if(Encoder_L < 0)
			{
				Encoder_L = -Encoder_L;
			}
	
			pid->target_val = PID_LocalTurn(&pid_localleft,Encoder_L) ;
	 
	        
	
			speed_L= Encoder_L*1200 /2496;
	
			PWM_L=PID_Calc_Left(pid,speed_L);	       //�����������õ�����ʽPID��������ֵ
	 
						
			if(PWM_L>400)PWM_L=400;    //�޷� ��ֹ�ջٵ��
			if(PWM_L<0)PWM_L=0;    //�޷� ��ֹ�ջٵ��
//			printf("PWM_L=%d",PWM_L)	;	
			TIM4->CCR2=PWM_L; 
//			TIM4->CCR2=150; 
//			TIM4->CCR1=0; //����pwm
//			
//printf("pid_localleft.err = %f\r\n",pid_localleft.err);				
         if(pid_localleft.err <= 0)
		 {
			
			Motion_mutual(2);
			motion_sign.firstenter = 1;
			motion_sign.turnaround_elimination = 0 ;
			
		
		 }

}
						
	

void Turnright_motion(PID_Struct *pid)
{ 

	       if(motion_sign.firstenter == 1)
			{
			motion_sign.motion_running = 1;
			PID_param_init();
			motion_sign.firstenter=0;	
			pid->Ki = 0;    				
			}
	
			Encoder_R= Read_Encoder(5) - 30000;                   //��ȡ��������������仯��,��������Ϊ������� ���λ��180��
	
			if(Encoder_R < 0)
			{
				Encoder_R = -Encoder_R;
			}
	
			pid->target_val = PID_LocalTurn(&pid_localright,Encoder_R) ;
			pid->Ki = 0 ;
	
			speed_R= Encoder_R*1200 /2496;
	
			PWM_R=PID_Calc_Left(pid,speed_R);	       //�����������õ�����ʽPID��������ֵ
	 
						
			if(PWM_R>400)PWM_R=400;    //�޷� ��ֹ�ջٵ��
			if(PWM_R<0)PWM_R=0;    //�޷� ��ֹ�ջٵ��
				
//			TIM4->CCR2=0; 
			TIM4->CCR3=PWM_R; //����pwm
//			printf("PWM_R=%d\r\n",PWM_R)	;
//			TIM4->CCR1=150; //����pwm
	//			printf("pid_localright.err = %f\r\n",pid_localright.err);
				
			if(pid_localright.err <= 0)
				{
			
				Motion_mutual(2);
				motion_sign.firstenter = 1;
				motion_sign.turnaround_elimination = 0 ;
			   
				}
						
}	

void Stoprotate_motion(PID_Struct *pidl,PID_Struct *pidr)
{ 

	       if(motion_sign.firstenter == 1)
			{
			motion_sign.motion_running = 1;
			PID_rotate_Init();
			motion_sign.firstenter=0;	
			pidl->Ki = 0; 
			pidr->Ki = 0;  
			}
	
			Encoder_R= Read_Encoder(5) - 30000;                   //��ȡ������
			Encoder_L= Read_Encoder(3) - 30000;     
			
			if(Encoder_R < 0)
			{
				Encoder_R = -Encoder_R;
			}
			if(Encoder_L < 0)
			{
				Encoder_L = -Encoder_L;
			}
	
			pidr->target_val = PID_LocalTurn(&pid_localright,Encoder_R) ;
			
			pidl->target_val = PID_LocalTurn(&pid_localleft,Encoder_L) ;
			
			
			speed_R= Encoder_R*1200 /2496;
			speed_L= Encoder_L*1200 /2496;
	
			PWM_R=PID_Calc_Left(pidr,speed_R);	       //�����������õ�����ʽPID��������ֵ
	        PWM_L=PID_Calc_Left(pidl,speed_L);	       //�����������õ�����ʽPID��������ֵ
						
			if(PWM_R>400)PWM_R=400;    //�޷� ��ֹ�ջٵ��
			if(PWM_R<0)PWM_R=0;    //�޷� ��ֹ�ջٵ��
			if(PWM_L>400)PWM_L=400;    //�޷� ��ֹ�ջٵ��
			if(PWM_L<0)PWM_L=0;    //�޷� ��ֹ�ջٵ��

			TIM4->CCR3=PWM_R; //����pwm
			TIM4->CCR2=PWM_L; 

			
			if(pid_localright.err <= 0)
				{
			
				Motion_mutual(2);
				motion_sign.firstenter = 1;
				motion_sign.turnaround_elimination = 0 ;
			   
				}
						
}


void Motion_Select(Motion_Struct *motion)
{
	int motion_station = 0;
 
		if(motion->gostraight  == 1)
		{
		motion_station  = Forward;
		}else if(motion->turnright  == 1){
		motion_station  = TurnLeft;
		}else if(motion->turnleft  == 1){
		motion_station  = TurnRight;	
		}else if(motion->back  == 1){
		motion_station  = Back;
		}else if(motion->turnaround  == 1){
		motion_station  = Rotate;
		}
//	 printf("motion_station = %d\r\n",motion_station);	
        switch(motion_station)
        {
            case  Forward:                //ǰ��
                Run_motion();
                break;
        
            case  TurnLeft :              //��ת
                Turnleft_motion(&pid_left);
                break;
			
            case  TurnRight:              //��ת
                Turnright_motion(&pid_right);
                break;
			
            case  Rotate:                 //ԭ�صȴ�
                Turn_Judge(&motion_sign);
                break;

        
              
        }
       
    

}

