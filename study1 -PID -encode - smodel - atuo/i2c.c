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
	delay_us(5);//����ʱ����ǯסi2c����
}

void i2c_stop(void)
{
	sad_pin_mode1(GPIO_Mode_OUT);
    SCL_W=1;
	SDA_W=0;
	delay_us(5);
	SDA_W=1;//����ǯסi2c����
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
	ack=1;//��Ӧ���ź�
	}
	else
	{
	ack=0;//��Ӧ���ź�
	}
	
	 SCL_W=0;//������æ
	delay_us(5);
	return ack;
	
}

//uint8_t at24c02_write(uint8_t addr,uint8_t *pbuf,uint8_t len)
//{
//	uint8_t ack;
//	i2c_start();//��ʼ�ź�
//	i2c_sendbyte(0xA0);//�����豸��ַ
//	ack=i2c_wait_ack();
//	if(ack)
//	{printf("�豸��ַ����\r\n");
//		return -1;
//	}
//	
//	i2c_sendbyte(addr);//�������ݵ�ַ
//	ack=i2c_wait_ack();
//	if(ack)
//	{printf("���ݵ�ַ����\r\n");
//		return -2;
//	}	
//		
//	while(len--)
//		{
//		i2c_sendbyte(*pbuf);//�������ݵ�ַ
//		ack=i2c_wait_ack();
//		if(ack)
//		{printf("���ݷ��ʹ���\r\n");
//		return -3;
//		}	
//		}
//i2c_stop();//ֹͣ�ź�
//		printf("��ӡ���\r\n");
//}

