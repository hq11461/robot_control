#include <stdio.h>
#include "stm32f4xx.h"
#include "delay.h"
#include "i2c.h"
void at24c02_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
  /* Configure PG6 and PG8 in output pushpull mode */
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void sad_pin_mode1(GPIOMode_TypeDef GPIO_Mode)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
  /* Configure PG6 and PG8 in output pushpull mode */
   GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void i2c_start(void)
{
	sad_pin_mode1(GPIO_Mode_OUT);
    SCL_W=1;
	SDA_W=1;
	delay_us(5);
	SDA_W=0;
	delay_us(5);
	SCL_W=1;
	delay_us(5);//拉低时钟线钳住i2c总线
}

void i2c_stop(void)
{
	sad_pin_mode1(GPIO_Mode_OUT);
    SCL_W=1;
	SDA_W=0;
	delay_us(5);
	SDA_W=1;//拉高钳住i2c总线
	delay_us(5);
	
}

void i2c_sendbyte(uint8_t byte)
{
	sad_pin_mode1(GPIO_Mode_OUT);
	int32_t i;
    SCL_W=0;
	SDA_W=0;
	delay_us(5);
	for(i=7;i>=0;i--)
	{
	if(byte&(1<<i))
		{
		 SDA_W=1;
		}
		else
		{
		SDA_W=0;	
		}
		delay_us(5);
		
		SCL_W=1;
		delay_us(5);
		
		 SCL_W=0;
		 delay_us(5);
		
	}
	
}

uint8_t i2c_wait_ack(void)
{
	uint8_t ack=0;
	sad_pin_mode1(GPIO_Mode_IN);
    SCL_W=1;

	delay_us(5);
	if(SDA_R)
	{
	ack=1;//无应答信号
	}
	else
	{
	ack=0;//有应答信号
	}
	
	 SCL_W=0;//总线在忙
	delay_us(5);
	return ack;
	
}

//uint8_t at24c02_write(uint8_t addr,uint8_t *pbuf,uint8_t len)
//{
//	uint8_t ack;
//	i2c_start();//起始信号
//	i2c_sendbyte(0xA0);//发送设备地址
//	ack=i2c_wait_ack();
//	if(ack)
//	{printf("设备地址错误\r\n");
//		return -1;
//	}
//	
//	i2c_sendbyte(addr);//发送数据地址
//	ack=i2c_wait_ack();
//	if(ack)
//	{printf("数据地址错误\r\n");
//		return -2;
//	}	
//		
//	while(len--)
//		{
//		i2c_sendbyte(*pbuf);//发送数据地址
//		ack=i2c_wait_ack();
//		if(ack)
//		{printf("数据发送错误\r\n");
//		return -3;
//		}	
//		}
//i2c_stop();//停止信号
//		printf("打印完成\r\n");
//}

