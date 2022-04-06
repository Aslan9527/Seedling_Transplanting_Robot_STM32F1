#include "motor.h"
#include "led.h"
#include "delay.h"

void Motor_Init(void)
{
    GPIO_InitTypeDef GPIO_Initstructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//GPIO E

    GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_Initstructure.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
    GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;//��50mhz
    GPIO_Init(GPIOE,&GPIO_Initstructure);
	
    GPIO_ResetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
}

void Motor_Direction(Motor_Dir direction)
{	
		if(direction==FRONT)  //ǰ��
		{
			//��ǰ
			Front_Left_1=1;
			Front_Left_0=0;
			//��ǰ
			Front_Right_1=1;
			Front_Right_0=0;
			//���
			Back_Left_1=1;
			Back_Left_0=0;
			//�Һ�
			Back_Right_1=1;
			Back_Right_0=0;
		}

		if(direction==BACK)  //����
		{
			//��ǰ
			Front_Left_1=0;
			Front_Left_0=1;
			//��ǰ
			Front_Right_1=0;
			Front_Right_0=1;
			//���
			Back_Left_1=0;
			Back_Left_0=1;
			//�Һ�
			Back_Right_1=0;
			Back_Right_0=1;
		}
		
		if(direction==LEFT)  //���
		{
			//��ǰ
			Front_Left_1=0;
			Front_Left_0=1;
			//��ǰ
			Front_Right_1=1;
			Front_Right_0=0;
			//���
			Back_Left_1=1;
			Back_Left_0=0;
			//�Һ�
			Back_Right_1=0;
			Back_Right_0=1;
		}
		
		if(direction==RIGHT)  //�ҽ�
		{
			//��ǰ
			Front_Left_1=1;
			Front_Left_0=0;
			//��ǰ
			Front_Right_1=0;
			Front_Right_0=1;
			//���
			Back_Left_1=0;
			Back_Left_0=1;
			//�Һ�
			Back_Right_1=1;
			Back_Right_0=0;
		}
		
		if(direction==STOP)  //ֹͣ
		{
			//��ǰ
			Front_Left_1=0;
			Front_Left_0=0;
			//��ǰ
			Front_Right_1=0;
			Front_Right_0=0;
			//���
			Back_Left_1=0;
			Back_Left_0=0;
			//�Һ�
			Back_Right_1=0;
			Back_Right_0=0;
		}

}

