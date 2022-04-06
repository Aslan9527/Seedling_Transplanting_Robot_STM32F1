#include "motor.h"
#include "led.h"
#include "delay.h"

void Motor_Init(void)
{
    GPIO_InitTypeDef GPIO_Initstructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//GPIO E

    GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Initstructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;//以50mhz
    GPIO_Init(GPIOE,&GPIO_Initstructure);
	
    GPIO_ResetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
}

void Motor_Direction(Motor_Dir direction)
{	
		if(direction==FRONT)  //前进
		{
			//左前
			Front_Left_1=1;
			Front_Left_0=0;
			//右前
			Front_Right_1=1;
			Front_Right_0=0;
			//左后
			Back_Left_1=1;
			Back_Left_0=0;
			//右后
			Back_Right_1=1;
			Back_Right_0=0;
		}

		if(direction==BACK)  //后退
		{
			//左前
			Front_Left_1=0;
			Front_Left_0=1;
			//右前
			Front_Right_1=0;
			Front_Right_0=1;
			//左后
			Back_Left_1=0;
			Back_Left_0=1;
			//右后
			Back_Right_1=0;
			Back_Right_0=1;
		}
		
		if(direction==LEFT)  //左进
		{
			//左前
			Front_Left_1=0;
			Front_Left_0=1;
			//右前
			Front_Right_1=1;
			Front_Right_0=0;
			//左后
			Back_Left_1=1;
			Back_Left_0=0;
			//右后
			Back_Right_1=0;
			Back_Right_0=1;
		}
		
		if(direction==RIGHT)  //右进
		{
			//左前
			Front_Left_1=1;
			Front_Left_0=0;
			//右前
			Front_Right_1=0;
			Front_Right_0=1;
			//左后
			Back_Left_1=0;
			Back_Left_0=1;
			//右后
			Back_Right_1=1;
			Back_Right_0=0;
		}
		
		if(direction==STOP)  //停止
		{
			//左前
			Front_Left_1=0;
			Front_Left_0=0;
			//右前
			Front_Right_1=0;
			Front_Right_0=0;
			//左后
			Back_Left_1=0;
			Back_Left_0=0;
			//右后
			Back_Right_1=0;
			Back_Right_0=0;
		}

}

