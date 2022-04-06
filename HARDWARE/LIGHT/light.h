#ifndef __LIGHT_H
#define	__LIGHT_H

#include "sys.h"


#define  Gd_left_in     GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)   //
#define  Gd_right_in    GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)   //


#define  Gd_right_out   GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)   //  接反了 
#define  Gd_left_out    GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)   //

#define  Red            GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)   //检测到红色输入高电平
#define  other          GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)   //

void GuangDian_Init(void);

#endif 


