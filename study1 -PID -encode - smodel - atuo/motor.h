#ifndef __MOTOR_H
#define __MOTOR_H



#define LEFT_MOTOR_GO_SET        GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define LEFT_MOTOR_GO_RESET      GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define RIGHT_MOTOR_GO_SET       GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define RIGHT_MOTOR_GO_RESET     GPIO_ResetBits(GPIOB,GPIO_Pin_8)


void TIM_Config(void);
void SetMotorSpeed(unsigned char ucChannel,signed char cSpeed);

void run(signed char speed,int time);       //前进函数
void brake(int time);               //刹车函数
void Left(signed char speed,int time);      //左转函数
void Spin_Left(signed char speed,int time); //左旋转函数
void Right(signed char speed,int time);     //右转函数
void Spin_Right(signed char speed,int time);//右旋转函数
void back(signed char speed,int time);      //后退函数

#endif

