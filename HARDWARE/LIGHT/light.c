#include "light.h"

void GuangDian_Init(void)    //光电传感器初始化
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //使能PF端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
 GPIO_Init(GPIOD, &GPIO_InitStructure);			
}

void OpenMv_Init(void)    //光电传感器初始化
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PF端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;				 
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
 GPIO_Init(GPIOA, &GPIO_InitStructure);		
}
