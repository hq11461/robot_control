#include "hongwai.h"
#include "motor.h"
#include "motion.h"

extern Motion_Struct motion_sign;

 void hongwai_Init(void)
 {
   GPIO_InitTypeDef  GPIO_InitStructure;
 /* GPIOG Peripheral clock enable */
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  /* Configure PG6 and PG8 in output pushpull mode */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
 }

void search(Motion_Struct *motion_sign)
{
	
	if (searchM == WHITE_AREA)
	{	if( (motion_sign->last_motion == 0) || (motion_sign->turnaround_elimination == 0))
		{	
			Motion_mutual(5)   ;
	motion_sign->firstenter = 1;
	motion_sign->next_motionL =0;	
	motion_sign->next_motionR =0;
	motion_sign->turnaround_elimination = 1 ;
		}
	}	
	
	else if(searchR  == WHITE_AREA)
	     motion_sign->next_motionL ++ ;			   
	else if (searchL == WHITE_AREA)
		 motion_sign->next_motionR ++ ;	
	
			
}
			
		

