#include <stdio.h>
#include "stm32f4xx.h"
#include "delay.h"
/*
超声波测距模块，使用PB3作为输出高电平引脚，PB4作为输入引脚
*/
void ultra_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	
	
}

int32_t get_distance(void)
{
	uint32_t t,d;
	GPIO_SetBits(GPIOB,GPIO_Pin_3);
	delay_us(20);
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	t=0;
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==0)
	{
	t++;
		delay_us(1);
		if(t>1000)
			return -1;
	}
	t=0;
	while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)==1)
	{
	t++;
		delay_us(9);
		if(t>10000)
			return -2;
	}
	t=t/2;
	d=t*3;
	return d;
	

}
