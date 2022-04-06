#include "place.h"
#include "motor_move.h"
#include "light.h"
#include "motor.h"
#include "timer6.h"
#include "PID_I.h"
#include "PID_II.h"
#include "delay.h"
#include "oled.h"
#include "usart.h"

extern float Now_Angle;                         //当前陀螺仪角度
extern int Motorspeed_LF,Motorspeed_RF,Motorspeed_LB,Motorspeed_RB;
extern int Motorspeed_1_4,Motorspeed_2_3;
extern int Motorspeed_1_3,Motorspeed_2_4;
extern int Motorspeed_1_2,Motorspeed_3_4;
extern int Motorspeed_1,Motorspeed_2,Motorspeed_3,Motorspeed_4;
extern float Distance_IN,Distance_L,Distance_R;  //超声波测量距离
extern int OpenMV_X,OpenMV_Y;                  //OPENMV X 轴反馈坐标
int Put_Angle[10]={1750,1773,1818,1860,1905,1950,1950,1950,1950,1750};  //放置苗转的角度 8 伸 9 缩
int times=1; //舵机旋转状态次数

void area_right(void)
{
	while(1)
	{

		OLED_Show();
		Motor_Direction(RIGHT);
		
		StartMeasure_IN();

//	  printf("w:%f\r\n",Now_Angle);
//	  printf("w:%d\r\n",Distance_IN);	
//	  printf("w:%d\r\n",OpenMV_Y);			
		Motorspeed_1_2=PIDI_realize_I(Now_Angle,Motor_speed);   //正 减 加速
		Motorspeed_3_4=PIDI_realize_II(Now_Angle,Motor_speed);    
		
		if(Distance_IN<24)
		{		
			Motorspeed_1=PIDII_realize_I(Distance_IN-SR_inside_width,Motorspeed_1_2);  //正 加 减速
			Motorspeed_2=PIDII_realize_II(Distance_IN-SR_inside_width,Motorspeed_1_2);    
			Motorspeed_3=PIDII_realize_II(Distance_IN-SR_inside_width,Motorspeed_3_4);   
			Motorspeed_4=PIDII_realize_I(Distance_IN-SR_inside_width,Motorspeed_3_4);    

			if(Motorspeed_1<Motor_Max) Motorspeed_1=Motor_Max;
			if(Motorspeed_1>Motor_Min) Motorspeed_1=Motor_Min;
			if(Motorspeed_2<Motor_Max) Motorspeed_2=Motor_Max;
			if(Motorspeed_2>Motor_Min) Motorspeed_2=Motor_Min;
			if(Motorspeed_3<Motor_Max) Motorspeed_3=Motor_Max;
			if(Motorspeed_3>Motor_Min) Motorspeed_3=Motor_Min;
			if(Motorspeed_4<Motor_Max) Motorspeed_4=Motor_Max;
			if(Motorspeed_4>Motor_Min) Motorspeed_4=Motor_Min;
			
			TIM_SetCompare1(TIM4,Motorspeed_1);	
			TIM_SetCompare2(TIM4,Motorspeed_2);
			TIM_SetCompare3(TIM4,Motorspeed_3);
			TIM_SetCompare4(TIM4,Motorspeed_4);						
		}
		else
		{
			if(Motorspeed_1_2<Motor_Max) Motorspeed_1_2=Motor_Max;
			if(Motorspeed_1_2>Motor_Min) Motorspeed_1_2=Motor_Min;
			if(Motorspeed_3_4<Motor_Max) Motorspeed_3_4=Motor_Max;
			if(Motorspeed_3_4>Motor_Min) Motorspeed_3_4=Motor_Min;
			
			TIM_SetCompare1(TIM4,Motorspeed_1_2);	
			TIM_SetCompare2(TIM4,Motorspeed_1_2);
			TIM_SetCompare3(TIM4,Motorspeed_3_4);
			TIM_SetCompare4(TIM4,Motorspeed_3_4);				
		}	

		if(OpenMV_Y>=40)
		{
		  Put_R(times);
		}
		
		if(Gd_left_out==1&&Gd_right_out==1)
		{
			delay_ms(20);	
			Motor_Direction(STOP);
			delay_ms(150);				
			break;					
		}			
	}
}
void area_left(void)
{
	while(1)
	{	
		OLED_Show();
		Motor_Direction(LEFT);
		
		StartMeasure_IN();
		
//	  printf("w:%f\r\n",Now_Angle);
//	  printf("w:%d\r\n",Distance_IN);
//	  printf("w:%d\r\n",OpenMV_Y);		
		Motorspeed_1_2=PIDI_realize_II(Now_Angle,Motor_speed);   //减
		Motorspeed_3_4=PIDI_realize_I(Now_Angle,Motor_speed);    
		
		if(Distance_IN<24)
		{		
			Motorspeed_1=PIDII_realize_II(Distance_IN-SR_inside_width,Motorspeed_1_2);  //加 
			Motorspeed_2=PIDII_realize_I(Distance_IN-SR_inside_width,Motorspeed_1_2);    
			Motorspeed_3=PIDII_realize_I(Distance_IN-SR_inside_width,Motorspeed_3_4);   
			Motorspeed_4=PIDII_realize_II(Distance_IN-SR_inside_width,Motorspeed_3_4);    

			if(Motorspeed_1<Motor_Max) Motorspeed_1=Motor_Max;
			if(Motorspeed_1>Motor_Min) Motorspeed_1=Motor_Min;
			if(Motorspeed_2<Motor_Max) Motorspeed_2=Motor_Max;
			if(Motorspeed_2>Motor_Min) Motorspeed_2=Motor_Min;
			if(Motorspeed_3<Motor_Max) Motorspeed_3=Motor_Max;
			if(Motorspeed_3>Motor_Min) Motorspeed_3=Motor_Min;
			if(Motorspeed_4<Motor_Max) Motorspeed_4=Motor_Max;
			if(Motorspeed_4>Motor_Min) Motorspeed_4=Motor_Min;
			
			TIM_SetCompare1(TIM4,Motorspeed_1);	
			TIM_SetCompare2(TIM4,Motorspeed_2);
			TIM_SetCompare3(TIM4,Motorspeed_3);
			TIM_SetCompare4(TIM4,Motorspeed_4);						
		}
		else
		{
			if(Motorspeed_1_2<Motor_Max) Motorspeed_1_2=Motor_Max;
			if(Motorspeed_1_2>Motor_Min) Motorspeed_1_2=Motor_Min;
			if(Motorspeed_3_4<Motor_Max) Motorspeed_3_4=Motor_Max;
			if(Motorspeed_3_4>Motor_Min) Motorspeed_3_4=Motor_Min;
			
			TIM_SetCompare1(TIM4,Motorspeed_1_2);	
			TIM_SetCompare2(TIM4,Motorspeed_1_2);
			TIM_SetCompare3(TIM4,Motorspeed_3_4);
			TIM_SetCompare4(TIM4,Motorspeed_3_4);				
		}	
		
		if(OpenMV_Y>=55)
		{
		  Put_L(times);
		}
		
		if(Gd_left_out==1&&Gd_right_out==1)
		{
			delay_ms(20);	
			Motor_Direction(STOP);
			delay_ms(150);				
			break;						
		}			
	}
}

void area_right_1(void)
{
	while(1)
	{
		OLED_Show();
		Motor_Direction(RIGHT);
		
		StartMeasure_IN();

//	  printf("w:%f\r\n",Now_Angle);
//	  printf("w:%d\r\n",Distance_IN);	
//	  printf("w:%d\r\n",OpenMV_Y);			
		Motorspeed_1_2=PIDI_realize_I(Now_Angle,Motor_speed);   //正 减 加速
		Motorspeed_3_4=PIDI_realize_II(Now_Angle,Motor_speed);    
		
		if(Distance_IN<24)
		{		
			Motorspeed_1=PIDII_realize_I(Distance_IN-SR_inside_width,Motorspeed_1_2);  //正 加 减速
			Motorspeed_2=PIDII_realize_II(Distance_IN-SR_inside_width,Motorspeed_1_2);    
			Motorspeed_3=PIDII_realize_II(Distance_IN-SR_inside_width,Motorspeed_3_4);   
			Motorspeed_4=PIDII_realize_I(Distance_IN-SR_inside_width,Motorspeed_3_4);    

			if(Motorspeed_1<Motor_Max) Motorspeed_1=Motor_Max;
			if(Motorspeed_1>Motor_Min) Motorspeed_1=Motor_Min;
			if(Motorspeed_2<Motor_Max) Motorspeed_2=Motor_Max;
			if(Motorspeed_2>Motor_Min) Motorspeed_2=Motor_Min;
			if(Motorspeed_3<Motor_Max) Motorspeed_3=Motor_Max;
			if(Motorspeed_3>Motor_Min) Motorspeed_3=Motor_Min;
			if(Motorspeed_4<Motor_Max) Motorspeed_4=Motor_Max;
			if(Motorspeed_4>Motor_Min) Motorspeed_4=Motor_Min;
			
			TIM_SetCompare1(TIM4,Motorspeed_1);	
			TIM_SetCompare2(TIM4,Motorspeed_2);
			TIM_SetCompare3(TIM4,Motorspeed_3);
			TIM_SetCompare4(TIM4,Motorspeed_4);						
		}
		else
		{
			if(Motorspeed_1_2<Motor_Max) Motorspeed_1_2=Motor_Max;
			if(Motorspeed_1_2>Motor_Min) Motorspeed_1_2=Motor_Min;
			if(Motorspeed_3_4<Motor_Max) Motorspeed_3_4=Motor_Max;
			if(Motorspeed_3_4>Motor_Min) Motorspeed_3_4=Motor_Min;
			
			TIM_SetCompare1(TIM4,Motorspeed_1_2);	
			TIM_SetCompare2(TIM4,Motorspeed_1_2);
			TIM_SetCompare3(TIM4,Motorspeed_3_4);
			TIM_SetCompare4(TIM4,Motorspeed_3_4);				
		}	
		
		if(Gd_left_out==1&&Gd_right_out==1)
		{
			delay_ms(20);	
			Motor_Direction(STOP);
			delay_ms(150);				
			break;					
		}			
	}
}
void area_left_1(void)
{
	while(1)
	{	
		OLED_Show();
		Motor_Direction(LEFT);
		
		StartMeasure_IN();
		
//	  printf("w:%f\r\n",Now_Angle);
//	  printf("w:%d\r\n",Distance_IN);
//	  printf("w:%d\r\n",OpenMV_Y);		
		Motorspeed_1_2=PIDI_realize_II(Now_Angle,Motor_speed);   //减
		Motorspeed_3_4=PIDI_realize_I(Now_Angle,Motor_speed);    
		
		if(Distance_IN<24)
		{		
			Motorspeed_1=PIDII_realize_II(Distance_IN-SR_inside_width,Motorspeed_1_2);  //加 
			Motorspeed_2=PIDII_realize_I(Distance_IN-SR_inside_width,Motorspeed_1_2);    
			Motorspeed_3=PIDII_realize_I(Distance_IN-SR_inside_width,Motorspeed_3_4);   
			Motorspeed_4=PIDII_realize_II(Distance_IN-SR_inside_width,Motorspeed_3_4);    

			if(Motorspeed_1<Motor_Max) Motorspeed_1=Motor_Max;
			if(Motorspeed_1>Motor_Min) Motorspeed_1=Motor_Min;
			if(Motorspeed_2<Motor_Max) Motorspeed_2=Motor_Max;
			if(Motorspeed_2>Motor_Min) Motorspeed_2=Motor_Min;
			if(Motorspeed_3<Motor_Max) Motorspeed_3=Motor_Max;
			if(Motorspeed_3>Motor_Min) Motorspeed_3=Motor_Min;
			if(Motorspeed_4<Motor_Max) Motorspeed_4=Motor_Max;
			if(Motorspeed_4>Motor_Min) Motorspeed_4=Motor_Min;
			
			TIM_SetCompare1(TIM4,Motorspeed_1);	
			TIM_SetCompare2(TIM4,Motorspeed_2);
			TIM_SetCompare3(TIM4,Motorspeed_3);
			TIM_SetCompare4(TIM4,Motorspeed_4);						
		}
		else
		{
			if(Motorspeed_1_2<Motor_Max) Motorspeed_1_2=Motor_Max;
			if(Motorspeed_1_2>Motor_Min) Motorspeed_1_2=Motor_Min;
			if(Motorspeed_3_4<Motor_Max) Motorspeed_3_4=Motor_Max;
			if(Motorspeed_3_4>Motor_Min) Motorspeed_3_4=Motor_Min;
			
			TIM_SetCompare1(TIM4,Motorspeed_1_2);	
			TIM_SetCompare2(TIM4,Motorspeed_1_2);
			TIM_SetCompare3(TIM4,Motorspeed_3_4);
			TIM_SetCompare4(TIM4,Motorspeed_3_4);				
		}	
	
		if(Gd_left_out==1&&Gd_right_out==1)
		{
			delay_ms(20);	
			Motor_Direction(STOP);
			delay_ms(150);				
			break;						
		}			
	}
}

void Put_R(int num)
{
  Motor_Direction(STOP);	
	
	TIM_SetCompare1(TIM3,Put_Angle[8]);	//伸
	delay_ms(200);
	TIM_SetCompare2(TIM3,Put_Angle[num]);
	delay_ms(700);
	TIM_SetCompare1(TIM3,Put_Angle[9]);	//缩
	delay_ms(1000);
	
	while(OpenMV_Y>=10)
	{
		Motor_Direction(RIGHT);

		Motorspeed_1_2=PIDI_realize_I(Now_Angle,Motor_Slow_speed);   //正 减 加速
		Motorspeed_3_4=PIDI_realize_II(Now_Angle,Motor_Slow_speed);    
		
		if(Motorspeed_1_2<Motor_Max) Motorspeed_1_2=Motor_Max;
		if(Motorspeed_1_2>Motor_Min) Motorspeed_1_2=Motor_Min;
		if(Motorspeed_3_4<Motor_Max) Motorspeed_3_4=Motor_Max;
		if(Motorspeed_3_4>Motor_Min) Motorspeed_3_4=Motor_Min;
		
		TIM_SetCompare1(TIM4,Motorspeed_1_2);	
		TIM_SetCompare2(TIM4,Motorspeed_1_2);
		TIM_SetCompare3(TIM4,Motorspeed_3_4);
		TIM_SetCompare4(TIM4,Motorspeed_3_4);				
	}	
	times++;
}

void Put_L(int num)
{
  Motor_Direction(STOP);	
	
	TIM_SetCompare1(TIM3,Put_Angle[8]);	//伸
	delay_ms(200);
	TIM_SetCompare2(TIM3,Put_Angle[num]);
	delay_ms(700);
	TIM_SetCompare1(TIM3,Put_Angle[9]);	//缩
	delay_ms(1000);
	
	while(OpenMV_Y>=10)
	{
		Motor_Direction(LEFT);
		
		Motorspeed_1_2=PIDI_realize_II(Now_Angle,Motor_Slow_speed);   //减
		Motorspeed_3_4=PIDI_realize_I(Now_Angle,Motor_Slow_speed);    
		
		if(Motorspeed_1_2<Motor_Max) Motorspeed_1_2=Motor_Max;
		if(Motorspeed_1_2>Motor_Min) Motorspeed_1_2=Motor_Min;
		if(Motorspeed_3_4<Motor_Max) Motorspeed_3_4=Motor_Max;
		if(Motorspeed_3_4>Motor_Min) Motorspeed_3_4=Motor_Min;
		
		TIM_SetCompare1(TIM4,Motorspeed_1_2);	
		TIM_SetCompare2(TIM4,Motorspeed_1_2);
		TIM_SetCompare3(TIM4,Motorspeed_3_4);
		TIM_SetCompare4(TIM4,Motorspeed_3_4);						
	}	
	times++;
}
