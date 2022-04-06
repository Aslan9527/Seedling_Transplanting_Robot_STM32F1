#ifndef __MOTOR_H
#define __MOTOR_H

#include "sys.h"


//左前
#define Front_Left_1 PEout(8)
#define Front_Left_0 PEout(9)
//右前
#define Front_Right_1 PEout(10)
#define Front_Right_0 PEout(11)
//左后
#define Back_Left_1 PEout(12)
#define Back_Left_0 PEout(13)
//右后
#define Back_Right_1 PEout(14)
#define Back_Right_0 PEout(15)

typedef enum
{
	FRONT = 0,   //高电平顺时针
	BACK  = 1,  //低电平逆时针
	LEFT  = 2,   //高电平顺时针
	RIGHT = 3,  //低电平逆时针	
	STOP  = 4,	
}Motor_Dir;  //运行方向

void Motor_Init(void);
void Motor_Direction(Motor_Dir direction);

#endif



