#include <stdio.h>
#include "stm32f4xx.h"
#include  "delay.h"

void delay_ms(uint32_t n)
{
while(n--)
{
SysTick->CTRL = 0; // Disable SysTick
SysTick->LOAD = (180000000/1000)-1; // Count from 255 to 0 (256 cycles)
SysTick->VAL = 0; // Clear current value as well as count flag
SysTick->CTRL = 5; // Enable SysTick timer with processor clock
while ((SysTick->CTRL & 0x10000)==0);// Wait until count flag is set

}
SysTick->CTRL = 0; // Disable SysTi
}

void delay_us(uint32_t n)
{
while(n--)
{
SysTick->CTRL = 0; // Disable SysTick
SysTick->LOAD = (180000000/1000000)-1; // Count from 255 to 0 (256 cycles)
SysTick->VAL = 0; // Clear current value as well as count flag
SysTick->CTRL = 5; // Enable SysTick timer with processor clock
while ((SysTick->CTRL & 0x10000)==0);// Wait until count flag is set

}
SysTick->CTRL = 0; // Disable SysTi
}
