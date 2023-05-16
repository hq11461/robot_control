#ifndef _HONGWAI_H
#define _HONGWAI_H
#include "sys.h"
#include <stdio.h>
#include "stm32f4xx.h"
#include "motion.h"


#define searchR        GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)  
#define searchM        GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)  
#define searchL        GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15) 
#define searchB        GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)  

#define BLACK_AREA 1
#define WHITE_AREA 0

#define COMM_STOP  'I'//ֹͣ
#define COMM_UP    'A'//ǰ��
#define COMM_DOWN  'B'//����
#define COMM_LEFT  'C'//��ת
#define COMM_RIGHT 'D'//��ת

void hongwai_Init(void);
void search(Motion_Struct *motion_sign);



#endif
