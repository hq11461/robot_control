#include <stdio.h>
#include "stm32f4xx.h"
#include "delay.h"
#include "hc05.h"
#include "motor.h"
/*
����ģ�� PA2\PA3��������������ڣ���5v��Դ
*/
void urast2_init(uint32_t baud)
{
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
  /* Configure PG6 and PG8 in output pushpull mode */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2| GPIO_Pin_3;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Enable GPIO clock */
 
   /* Connect USART pins to AF�� */
   GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);//PA2��������
   GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);//PA3��������

  USART_InitStructure.USART_BaudRate = baud;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART2, &USART_InitStructure);
  
  USART_ITConfig(USART2,USART_IT_RXNE, ENABLE);


	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
  
  /* Enable USART */
    USART_Cmd(USART2, ENABLE);

}
#include "string.h"

void usart2_send(char *pstr)//����2���ͺ���
{
char *p = pstr;
	
	while(*p!='\0')
	{
	
	 USART_SendData(USART2,*p);
while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);
	 USART_ClearFlag(USART2,USART_IT_TXE);
		p++;
		
	}
}



void ble_config_set(void)//����ATָ���ʼ��
{

	usart2_send("AT\r\n");
	
	delay_ms(500);
	usart2_send("AT+NAMEcoolbay.he\r\n");
	delay_ms(500);
	usart2_send("AT+RESET\r\n");
	delay_ms(2000);
}
uint16_t dddddddd=0;

//void USART2_IRQHandler(void)//������������1��ӡ
//{
// uint8_t d;
//                                           
//	if(USART_GetITStatus(USART2,USART_IT_RXNE)==SET)
//		
//		d=USART_ReceiveData(USART2);
//		USART_SendData(USART1,d);//����1����pc
//					switch(d)
//					{case 50:run(80,1000);break;  //d=50ʱǰ���ٶ�80��ǰ��ʱ��1000ms
//					 case 56:back(50,1000);break;
//					 case 52:Left(80,1000);break;
//					 case 54:Right(80,1000);break;
//					 case 53:brake(1000);break;
//					default: break;
//					}
//	 while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET)
//		 USART_ClearFlag(USART1,USART_IT_TXE);

//		
//	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//	}
//	if(USART_GetITStatus(USART2,USART_IT_TXE)==SET)
//	{
//		dddddddd++;
//		
//		
//	USART_ClearITPendingBit(USART2,USART_IT_TXE);
//	}
//	
//}


