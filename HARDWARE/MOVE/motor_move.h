#ifndef __MOTORMOVE_H
#define	__MOTORMOVE_H

#define SR_outside_width   7
#define SR_inside_width    13

#define Motor_speed        350

#define Motor_Max_speed    400
#define Motor_Slow_speed   500

#define Motor_speed_1      100
#define Motor_speed_2      200
#define Motor_speed_3      300
#define Motor_speed_4      400
#define Motor_speed_5      500
#define Motor_speed_6      600
#define Motor_speed_7      700
#define Motor_speed_8      800
#define Motor_speed_9      900

#define Motor_Min          750
#define Motor_Max          30

void Motor_start(void);

void Motor_turn_right(void);
void Motor_turn_left(void);
void Motor_turn_back(void);

void Speed_Add_Back(void);
	
#endif


