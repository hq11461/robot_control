#ifndef __USART_H
#define __USART_H 	

#define  MYDEBUG    1

#ifdef   MYDEBUG     //�Ƿ���봮�ڵ��� ������д���1��Ϣ��� ��������usmart����
#define  DEBUG       printf
#endif

void urast1_init(uint32_t baud);
void USART1_IRQHandler(void);
#endif
