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

#define COMM_STOP  'I'//停止
#define COMM_UP    'A'//前进
#define COMM_DOWN  'B'//后退
#define COMM_LEFT  'C'//左转
#define COMM_RIGHT 'D'//右转

void hongwai_Init(void);
void search(Motion_Struct *motion_sign);



#endif
