#ifndef __HC05_H
#define __HC05_H 			   


void urast2_init(uint32_t baud);
void usart2_send(char *pstr);
void ble_config_set(void);
void USART2_IRQHandler(void);

#define up   '2'
#define upo  '22'

#endif
