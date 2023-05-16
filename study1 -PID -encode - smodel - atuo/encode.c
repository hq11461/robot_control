/*
********************************************************************************************************
文件名：Encoder.c
功  能：配置编码器
备  注：
	硬件连接		STM32       
				     PA15 ------   B1A
						 PB3  ------   B1B
						 PB4  ------   B2A
						 PB5  ------   B2B
		
淘  宝：https://shop60670850.taobao.com
作  者：lilianhe
日  期: 2017-2-6
*********************************************************************************************************
*/

#include "encode.h"
#include "pid.h"
#include "ursat.h"
#include <stdio.h>
#include <stm32f4xx.h>
#include "motion.h"
#include "hongwai.h"
#include "motor.h"

extern PID_Struct pid_right;
extern PID_Struct pid_left;
extern PID_Struct pid_local;
extern PID_Struct pid_turn;
extern Motion_Struct motion_sign;

void encoder_Init(void)
	
{
    Encoder_Init_TIM5();
	Encoder_Init_TIM3();
}


//***************************定时器2初始化 ，使用编码器功能***************************//
//左电机编码器计数
//PB4----接 编码器A相 或者电机驱动的B1A标识
//PB5 ----接 编码器B相 或者电机驱动的B1B标识
void Encoder_Init_TIM3(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;   

	//GPIO功能时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);


	//配置IO口为复用功能-定时器通道
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;        //输入功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度100MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);


	//Timer configuration in Encoder mode 
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
	TIM_TimeBaseStructure.TIM_Period = 65535-1;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0x0;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

	

	//Reset counter 
	

    TIM_SetCounter(TIM3,30000);
	TIM_Cmd(TIM3, ENABLE);  
}
    
  
//***************************定时器5初始化 ，使用编码器功能***************************//
//右                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         电机编码器计数
//PH10----接 编码器A相 或者电机驱动的B2A标识
//PH11----接 编码器B相 或者电机驱动的B2B标识
void Encoder_Init_TIM5(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;   

	//GPIO功能时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);


	//配置IO口为复用功能-定时器通道
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;        //输入功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度100MHz
	GPIO_Init(GPIOH, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOH, GPIO_PinSource10, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOH, GPIO_PinSource11, GPIO_AF_TIM5);


	//Timer configuration in Encoder mode 
	TIM_DeInit(TIM5);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);

	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
	TIM_TimeBaseStructure.TIM_Period = 65535-1;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   
	
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	
	
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0x0;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
	TIM_ICInit(TIM5, &TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);

	

	//Reset counter 
	

    TIM_SetCounter(TIM5,30000);
	TIM_Cmd(TIM5, ENABLE);  
	
}


/**************************************************************************
函数功能：单位时间读取编码器计数
入口参数：定时器
返回  值：速度值
**************************************************************************/
int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
			case 5:  Encoder_TIM= TIM_GetCounter(TIM5);  TIM_SetCounter(TIM5,30000);break;
			case 2:  Encoder_TIM= TIM_GetCounter(TIM2);  TIM_SetCounter(TIM2,30000);break;
			case 3:  Encoder_TIM= TIM_GetCounter(TIM3); TIM_SetCounter(TIM3,30000);break;	
		 //case 4:  Encoder_TIM= (short)TIM4 -> CNT;  TIM4 -> CNT=30000;break;	
		
		 default:  Encoder_TIM=888;
	 }
		return Encoder_TIM;
}





void tim2_Init(void)
{
 TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
 NVIC_InitTypeDef  NVIC_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = 4999;
  TIM_TimeBaseStructure.TIM_Prescaler = 900-1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);  //手动清除中断标志位，避免刚初始化完就进入中断
	//3.使能中断
	
 

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //NVIC优先级分组
 /* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
   TIM_Cmd(TIM2, ENABLE);  
}
//uint16_t  Encoder_L=0,Encoder_R=0;     //速度值为每分钟的圈数
//extern PID_Struct pid_right, pid_left,pid_local, pid_turnright;
//float speed_L=0,speed_R=0;
//int para_L,para_R,para_local=0,PWM_L,PWM_R;
//int sign_turn = 0,turn=0;    //转向标志位
int op = 0;
void TIM2_IRQHandler(void)
{

	if(TIM_GetFlagStatus(TIM2, TIM_IT_Update) != RESET)   //时间到了
	{
		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);//清中断

		Motion_Select(&motion_sign) ;
		
//Run_motion();		
	}

}

