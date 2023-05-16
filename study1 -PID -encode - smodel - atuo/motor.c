#include <stdio.h>
#include "stm32f4xx.h"
#include "delay.h"
#include "hc05.h"
#include "Math.h"
#include "motor.h"

static TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
static TIM_OCInitTypeDef  TIM_OCInitStructure;


void TIM_Config(void)
{
   GPIO_InitTypeDef GPIO_InitStructure;
 
  /* TIM3 clock enable */
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  /* GPIOC clock enable */
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
   
	

 /* Configure PG6 and PG8 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_9;//�������תPB6\PB7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
 
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_7 ;//pwm�ö˿�PB6\PB7
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
   GPIO_Init(GPIOB, &GPIO_InitStructure); 

   /* Connect TIM3 pins to AF2 */  
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_TIM4); 
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = 1000-1;//pwmƵ��1000hz
  TIM_TimeBaseStructure.TIM_Prescaler = 900-1;//Ƶ��100000hz
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //cntС��ccrΪ��Ч״̬
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0 ;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//��Ч״̬Ϊ�ߵ�ƽ
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);
  
  TIM_Cmd(TIM4, ENABLE);

TIM4->CCR3=0;
TIM4->CCR2=0;

GPIO_ResetBits( GPIOB,  GPIO_Pin_6); 
GPIO_ResetBits( GPIOB,  GPIO_Pin_9);   
 }

 void SetMotorSpeed(unsigned char ucChannel,signed char cSpeed)
{
//		static short sMotorSpeed = 0;
		short sPWM;
//	  float fDir = 1;
	
		if (cSpeed>=100) cSpeed = 100;
	  if (cSpeed<=-100) cSpeed = -100;
	
   	sPWM = fabs(cSpeed);
	switch(ucChannel)
	{
		case 0://���� PB6 8
		 TIM_SetCompare1(TIM4,sPWM);
			if (cSpeed>0) 
				RIGHT_MOTOR_GO_RESET;
			else if(cSpeed<0) 
				RIGHT_MOTOR_GO_SET;		
			break;
		case 1://���� PB7 9
		  TIM_SetCompare2(TIM4,sPWM);
			if (cSpeed>0) 
				LEFT_MOTOR_GO_SET;
			else if (cSpeed<0)
				LEFT_MOTOR_GO_RESET;
			break;			
	}
}

//----------------------------------�˶�����--------------------------------
void run(signed char speed,int time)  //ǰ������
{
		  signed char f_speed = -speed;
			SetMotorSpeed(1,f_speed);//����  //Ϊ����
			SetMotorSpeed(0,speed);//����   //Ϊ����
			delay_ms(time);                 //ʱ��Ϊ����
}



void brake(int time) //ɲ������
{
	  SetMotorSpeed(1,0);//����   //Ϊ0
	  SetMotorSpeed(0,0);//����   //Ϊ0
	  RIGHT_MOTOR_GO_RESET;
	  LEFT_MOTOR_GO_RESET;
		delay_ms(time);             //ʱ��Ϊ����  
}

void Right(signed char speed,int time) //��ת����
{
	  SetMotorSpeed(1,0);//����     //���ֲ���
	  SetMotorSpeed(0,speed);        //����Ϊ��
		delay_ms(time);                 //ʱ��Ϊ����  

}
void Spin_Left(signed char speed,int time) //����ת����
{
	  signed char u_speed = 100 - speed; 
 	  SetMotorSpeed(1,speed);//����     //����Ϊ��
	  SetMotorSpeed(0,u_speed);            //����Ϊ��
		delay_ms(time);                    //ʱ��Ϊ����  

}
void Left(signed char speed,int time)  //��ת����
{
	  signed char f_speed = - speed;
	  SetMotorSpeed(1,f_speed);//����     //����Ϊ��
	  SetMotorSpeed(0,0);                 //����Ϊ0
		delay_ms(time);                   //ʱ��Ϊ����  

}
void Spin_Right(signed char speed,int time) //����ת����
{
	  signed char u_speed = 100 - speed;
	  signed char f_speed = - speed;
	  SetMotorSpeed(1,-u_speed);//����     //����Ϊ��
	  SetMotorSpeed(0,f_speed);            //����Ϊ��
		delay_ms(time);                    //ʱ��Ϊ����  

}
void back(signed char speed,int time) //���˺���
{
	  signed char u_speed = 100- speed;
	  signed char f_speed = - u_speed;
	  SetMotorSpeed(1,u_speed);//����   //Ϊ����
	  SetMotorSpeed(0,f_speed);//���� //Ϊ����
		delay_ms(time);                 //ʱ��Ϊ����  

}











