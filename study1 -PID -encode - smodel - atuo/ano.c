#include <stdio.h>
#include <stm32f4xx.h>
#include "delay.h"
#include "ursat.h"
#include "ano.h"


#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)	  ) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )

uint8_t testdatatosend[50];

void UART1_SendByte1(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//发送数据是状态寄存为会自动清零 无需软件清零
}


void UART1_Transmit(uint8_t *Array,uint16_t Length)
{
	uint8_t i;
	for(i=0;i<Length;i++)
	{
		UART1_SendByte1(Array[i]);//发送数据  且数据存在数组里
	}
	
}



void Test_Send_User(uint16_t data1, uint16_t data2, uint16_t data3,uint16_t data4,uint16_t data5,uint16_t data6,uint16_t data7,uint16_t data8,uint16_t data9,uint16_t data10)	
{
	uint8_t _cnt=0;
	
	testdatatosend[_cnt++]=0xAA;
	testdatatosend[_cnt++]=0x05;
	testdatatosend[_cnt++]=0xAF;
	testdatatosend[_cnt++]=0xF1;
	testdatatosend[_cnt++]=0;
 
	testdatatosend[_cnt++]=BYTE1(data1);
	testdatatosend[_cnt++]=BYTE0(data1);
	
	testdatatosend[_cnt++]=BYTE1(data2);
	testdatatosend[_cnt++]=BYTE0(data2);
	
	testdatatosend[_cnt++]=BYTE1(data3);
	testdatatosend[_cnt++]=BYTE0(data3);
	
	testdatatosend[_cnt++]=BYTE1(data4);
	testdatatosend[_cnt++]=BYTE0(data4);
	
	testdatatosend[_cnt++]=BYTE1(data5);
	testdatatosend[_cnt++]=BYTE0(data5);
	
	testdatatosend[_cnt++]=BYTE1(data6);
	testdatatosend[_cnt++]=BYTE0(data6);
	
	testdatatosend[_cnt++]=BYTE1(data7);
	testdatatosend[_cnt++]=BYTE0(data7);
	
	testdatatosend[_cnt++]=BYTE1(data8);
	testdatatosend[_cnt++]=BYTE0(data8);
	
	testdatatosend[_cnt++]=BYTE1(data9);
	testdatatosend[_cnt++]=BYTE0(data9);
	
	testdatatosend[_cnt++]=BYTE1(data10);
	testdatatosend[_cnt++]=BYTE0(data10);
	
	
 
	testdatatosend[4] = _cnt-5;
	
	uint8_t sum = 0;	
	for(uint8_t i=0;i<_cnt;i++)
		sum += testdatatosend[i];
	
	testdatatosend[_cnt++]=sum;	
 
	UART1_Transmit(testdatatosend, _cnt);	
}


