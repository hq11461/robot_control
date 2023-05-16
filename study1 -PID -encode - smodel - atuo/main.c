#include <stdio.h>
#include <stm32f4xx.h>
#include "delay.h"
#include "ursat.h"
#include "hc05.h"
#include "oled.h"
#include "bmp.h"    //储存图片点阵头文件
#include "mpu9250.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "myiic.h"
#include "motor.h"
#include "hongwai.h"
#include "encode.h"
#include "ANO.h"
#include "pid.h"
#include "motion.h"

//int PID(float kp,float ki,float kd,s16 traget,s16 previous)
//{
//	u16 pwm_val1;
//	s16 e;
//	static s16 E;
//	static int e_pre;

//	e=traget-previous;
//	E=E+e;
//	if(E>100)E=250;
//	if(E<-100)E=-250;
//	pwm_val1=kp*(e)+ki*(E+e)+kd*(e-e_pre);
//	if(pwm_val1>100)pwm_val1=100;
//	if(pwm_val1<20)pwm_val1=20;
//	e_pre=e;
//	return pwm_val1;
//}


  uint16_t d,model;
  int flag=0;
void USART2_IRQHandler(void)//蓝牙中断 
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
		
		d=USART_ReceiveData(USART2);//		d等于蓝牙接收值
        flag=1;
				if(d==1)          //如果d=1为蓝牙控制模式，d=3为自动循迹模式
					model=1;
				if(d==3)
					model=0;
		
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
	}

int main(void)
{

    
//    MPU9250_Init();
//    mpu_dmp_init();
	urast1_init(115200);              //初始化USART

	

	//OLED_Init();			//初始化OLED  
	//OLED_Clear(); 
	TIM_Config();
    urast2_init(9600);
    ble_config_set();  	//蓝牙AT指令初始化函数
	hongwai_Init();
	 encoder_Init();
    //showyaw();
	PID_param_init();
	Motin_param_Init();
	tim2_Init();
extern PID_Struct pid_right,pid_left,pid_localleft,pid_localright;
extern uint16_t Encoder_L,Encoder_R,PWM_L,PWM_R,i;     //速度值为每秒钟的圈数
extern float speed_L,speed_R,num;
extern int  para_L,para_R,sumr;
uint8_t a,b,c,d,e,f;
extern Motion_Struct motion_sign;


while(1)
{
//	int i;
//GPIO_ResetBits( GPIOB,  GPIO_Pin_6); 
//GPIO_ResetBits( GPIOB,  GPIO_Pin_9);   
//	TIM4->CCR3 = 200;
//	TIM4->CCR2 = 200;
////	a=(int)Encoder_L;
//////	
////	b=Read_Encoder(5);
////	
	delay_ms(100);
//	
//GPIO_SetBits( GPIOB,  GPIO_Pin_6); 
//GPIO_SetBits( GPIOB,  GPIO_Pin_9);   	
	
	e=(int)speed_L;
	f=(int)speed_R;
	c=pid_localleft.err;
	d=(int)pid_localright.err;
 Test_Send_User(PWM_L,PWM_R,e,f,sumr,pid_right.integral,pid_left.err,pid_left.integral,Encoder_L,Encoder_R);
	search(&motion_sign);
	Motion_swith(&motion_sign);
//	printf("motion_signR = %d,motion_signR = %d,go = %d,L = %d, r=%d,PWM_L = %u,PWM_R = %u\r\n",motion_sign.next_motionR,motion_sign.next_motionL,motion_sign.gostraight,motion_sign.turnleft,motion_sign.turnright,PWM_L,PWM_R);
 }

  }

