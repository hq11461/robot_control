#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm32f4xx.h"
#include "delay.h"

void Encoder_Init_TIM3(void);
void Encoder_Init_TIM5(void);
void encoder_Init(void);
int Read_Encoder(u8 TIMX);
int PID(float kp_variableA,float ki_variableA,int traget,int previous);

void tim2_Init(void);
void TIM3_IRQHandler(void);

#endif
