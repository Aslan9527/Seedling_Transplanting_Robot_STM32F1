#ifndef __MOTOR_H
#define __MOTOR_H

#include "sys.h"


//��ǰ
#define Front_Left_1 PEout(8)
#define Front_Left_0 PEout(9)
//��ǰ
#define Front_Right_1 PEout(10)
#define Front_Right_0 PEout(11)
//���
#define Back_Left_1 PEout(12)
#define Back_Left_0 PEout(13)
//�Һ�
#define Back_Right_1 PEout(14)
#define Back_Right_0 PEout(15)

typedef enum
{
	FRONT = 0,   //�ߵ�ƽ˳ʱ��
	BACK  = 1,  //�͵�ƽ��ʱ��
	LEFT  = 2,   //�ߵ�ƽ˳ʱ��
	RIGHT = 3,  //�͵�ƽ��ʱ��	
	STOP  = 4,	
}Motor_Dir;  //���з���

void Motor_Init(void);
void Motor_Direction(Motor_Dir direction);

#endif



