#ifndef __USART_H
#define __USART_H 	

#define  MYDEBUG    1

#ifdef   MYDEBUG     //是否进入串口调试 进入会有串口1信息输出 并可以用usmart调试
#define  DEBUG       printf
#endif

void urast1_init(uint32_t baud);
void USART1_IRQHandler(void);
#endif
