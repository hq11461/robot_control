#ifndef __MOTOR_H
#define __MOTOR_H



#define LEFT_MOTOR_GO_SET        GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define LEFT_MOTOR_GO_RESET      GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define RIGHT_MOTOR_GO_SET       GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define RIGHT_MOTOR_GO_RESET     GPIO_ResetBits(GPIOB,GPIO_Pin_8)


void TIM_Config(void);
void SetMotorSpeed(unsigned char ucChannel,signed char cSpeed);

void run(signed char speed,int time);       //ǰ������
void brake(int time);               //ɲ������
void Left(signed char speed,int time);      //��ת����
void Spin_Left(signed char speed,int time); //����ת����
void Right(signed char speed,int time);     //��ת����
void Spin_Right(signed char speed,int time);//����ת����
void back(signed char speed,int time);      //���˺���

#endif

