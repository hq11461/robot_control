#include <stdio.h>
#include "stm32f4xx.h"

void urast1_init(uint32_t baud)
{
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
  /* Enable GPIO clock */
  
  
 
  
   /* Connect USART pins to AF7 */
   GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
   GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);

  USART_InitStructure.USART_BaudRate = baud;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1, &USART_InitStructure);
  
  USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);


	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
  
  /* Enable USART */
    USART_Cmd(USART1, ENABLE);

}

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;
int fputc(int ch, FILE *f) 
	{
     USART_SendData(USART1,ch);
while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
		
		return ch;
	}
void _sys_exit(int return_code) {
label: goto label; /* endless loop */
}



void USART1_IRQHandler(void)
{
uint8_t d;

if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
{
	
	d=USART_ReceiveData(USART1);
	USART_SendData(USART1,d);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	
//	    if(d=='1')
//		GPIO_SetBits(GPIOB, GPIO_Pin_0);
USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}
	
}

