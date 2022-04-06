#include "motor_move.h"
#include "light.h"
#include "motor.h"
#include "timer6.h"
#include "PID_I.h"
#include "PID_II.h"
#include "delay.h"
#include "oled.h"
#include "usart.h"

extern float Distance_IN,Distance_L,Distance_R; //超声波测量距离
extern float Now_Angle; 

int Motorspeed_LF,Motorspeed_RF,Motorspeed_LB,Motorspeed_RB;
int Motorspeed_1_4,Motorspeed_2_3;
int Motorspeed_1_3,Motorspeed_2_4;
int Motorspeed_1_2,Motorspeed_3_4;
int Motorspeed_1,Motorspeed_2,Motorspeed_3,Motorspeed_4;

void Motor_start(void)
{
	while(1) //启动区域
	{
		OLED_Show();
		Motor_Direction(FRONT);

		Motorspeed_1_3=PIDI_realize_I(Now_Angle,Motor_speed_2);   //正 减 加速
		Motorspeed_2_4=PIDI_realize_II(Now_Angle,Motor_speed_2);    
		
		if(Motorspeed_1_3<Motor_Max)  Motorspeed_1_3=Motor_Max;
		if(Motorspeed_1_3>Motor_Min)  Motorspeed_1_3=Motor_Min;
		if(Motorspeed_2_4<Motor_Max)  Motorspeed_2_4=Motor_Max;
		if(Motorspeed_2_4>Motor_Min)  Motorspeed_2_4=Motor_Min;		
		
		TIM_SetCompare1(TIM4,Motorspeed_1_3);	
		TIM_SetCompare2(TIM4,Motorspeed_2_4);
		TIM_SetCompare3(TIM4,Motorspeed_1_3);
		TIM_SetCompare4(TIM4,Motorspeed_2_4);				
	
		if(Gd_left_in==0)
		{
			delay_ms(400);		
			break;	
		}		
	}
}

void Motor_turn_right(void)
{
	                        /*  前进 */
	while(1)  //未到垄
	{
		OLED_Show();
		if(Gd_left_in==0&&Gd_right_in==1)  
		{
			Motor_Direction(FRONT);
			
			StartMeasure_L();

			Motorspeed_1_3=PIDI_realize_I(Now_Angle,Motor_speed);   //正 加 减速
			Motorspeed_2_4=PIDI_realize_II(Now_Angle,Motor_speed);    
			
			if(Distance_L<14)
			{		
				Motorspeed_1=PIDII_realize_II(Distance_L-SR_outside_width,Motorspeed_1_3);  //正 加减速
				Motorspeed_2=PIDII_realize_I(Distance_L-SR_outside_width,Motorspeed_2_4);    
				Motorspeed_3=PIDII_realize_I(Distance_L-SR_outside_width,Motorspeed_1_3);   
				Motorspeed_4=PIDII_realize_II(Distance_L-SR_outside_width,Motorspeed_2_4); 

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
				if(Motorspeed_1_3<Motor_Max) Motorspeed_1_3=Motor_Max;
				if(Motorspeed_1_3>Motor_Min) Motorspeed_1_3=Motor_Min;
				if(Motorspeed_2_4<Motor_Max) Motorspeed_2_4=Motor_Max;
				if(Motorspeed_2_4>Motor_Min) Motorspeed_2_4=Motor_Min;					
				
				TIM_SetCompare1(TIM4,Motorspeed_1_3);	
				TIM_SetCompare2(TIM4,Motorspeed_2_4);
				TIM_SetCompare3(TIM4,Motorspeed_1_3);
				TIM_SetCompare4(TIM4,Motorspeed_2_4);				
			}
	  }
    if(Gd_left_in==0&&Gd_right_in==0)			
		{
			delay_ms(100);	
			break;						
		}		
	}

	while(1)  //未过垄
	{
		OLED_Show();
		if(Gd_left_in==0&&Gd_right_in==0)
		{
			Motor_Direction(FRONT);
			
		  StartMeasure_L();

			Motorspeed_1_3=PIDI_realize_I(Now_Angle,Motor_speed);   //正 加 减速
			Motorspeed_2_4=PIDI_realize_II(Now_Angle,Motor_speed);    
			
			if(Distance_L<14)
			{		
				Motorspeed_1=PIDII_realize_II(Distance_L-SR_outside_width,Motorspeed_1_3);  //正 加减速
				Motorspeed_2=PIDII_realize_I(Distance_L-SR_outside_width,Motorspeed_2_4);    
				Motorspeed_3=PIDII_realize_I(Distance_L-SR_outside_width,Motorspeed_1_3);   
				Motorspeed_4=PIDII_realize_II(Distance_L-SR_outside_width,Motorspeed_2_4);    

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
				if(Motorspeed_1_3<Motor_Max) Motorspeed_1_3=Motor_Max;
				if(Motorspeed_1_3>Motor_Min) Motorspeed_1_3=Motor_Min;
				if(Motorspeed_2_4<Motor_Max) Motorspeed_2_4=Motor_Max;
				if(Motorspeed_2_4>Motor_Min) Motorspeed_2_4=Motor_Min;		
				
				TIM_SetCompare1(TIM4,Motorspeed_1_3);	
				TIM_SetCompare2(TIM4,Motorspeed_2_4);
				TIM_SetCompare3(TIM4,Motorspeed_1_3);
				TIM_SetCompare4(TIM4,Motorspeed_2_4);				
			}
	  }
		if(Gd_left_in==0&&Gd_right_in==1)			//过垄
		{
			delay_ms(30);	
			Motor_Direction(STOP);
			delay_ms(150);
			break;						
		}		
	}
	                             /*******右转*********/	
	while(1)
	{
		OLED_Show();		
		if(Gd_right_out==1)
		{
			Motor_Direction(RIGHT);	
			
			Motorspeed_1_2=PIDI_realize_I(Now_Angle,Motor_Max_speed);   //正 加 减速
			Motorspeed_3_4=PIDI_realize_II(Now_Angle,Motor_Max_speed);  

			if(Motorspeed_1_2<Motor_Max) Motorspeed_1_2=Motor_Max;
			if(Motorspeed_1_2>Motor_Min) Motorspeed_1_2=Motor_Min;
			if(Motorspeed_3_4<Motor_Max) Motorspeed_3_4=Motor_Max;
			if(Motorspeed_3_4>Motor_Min) Motorspeed_3_4=Motor_Min;		
			
		  TIM_SetCompare1(TIM4,Motorspeed_1_2);	
			TIM_SetCompare2(TIM4,Motorspeed_1_2);
			TIM_SetCompare3(TIM4,Motorspeed_3_4);
			TIM_SetCompare4(TIM4,Motorspeed_3_4);				
		}
		else
    {
			delay_ms(100);			
			break;				
		}
	}
}

void Motor_turn_left(void)
{
	                             /*  前进 */
	while(1)  //未到垄
	{
		OLED_Show();
		if(Gd_left_in==1&&Gd_right_in==0)  
		{
			Motor_Direction(FRONT);
			
			StartMeasure_R();

			Motorspeed_1_3=PIDI_realize_I(Now_Angle,Motor_speed);   //正 加 减速
			Motorspeed_2_4=PIDI_realize_II(Now_Angle,Motor_speed);    
			
			if(Distance_R<14)
			{		
				Motorspeed_1=PIDII_realize_I(Distance_R-SR_outside_width,Motorspeed_1_3);  //正 加减速
				Motorspeed_2=PIDII_realize_II(Distance_R-SR_outside_width,Motorspeed_2_4);    
				Motorspeed_3=PIDII_realize_II(Distance_R-SR_outside_width,Motorspeed_1_3);   
				Motorspeed_4=PIDII_realize_I(Distance_R-SR_outside_width,Motorspeed_2_4);    

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
				if(Motorspeed_1_3<Motor_Max) Motorspeed_1_3=Motor_Max;
				if(Motorspeed_1_3>Motor_Min) Motorspeed_1_3=Motor_Min;
				if(Motorspeed_2_4<Motor_Max) Motorspeed_2_4=Motor_Max;
				if(Motorspeed_2_4>Motor_Min) Motorspeed_2_4=Motor_Min;				
				
				TIM_SetCompare1(TIM4,Motorspeed_1_3);	
				TIM_SetCompare2(TIM4,Motorspeed_2_4);
				TIM_SetCompare3(TIM4,Motorspeed_1_3);
				TIM_SetCompare4(TIM4,Motorspeed_2_4);				
			}
	  }
		if(Gd_left_in==0&&Gd_right_in==0)			
		{
			delay_ms(200);	
			break;						
		}		
	}
	
	while(1)  //未过垄
	{
		OLED_Show();
		if(Gd_left_in==0&&Gd_right_in==0)
		{
			Motor_Direction(FRONT);
			
			StartMeasure_R();

			Motorspeed_1_3=PIDI_realize_I(Now_Angle,Motor_speed);   //正 加 减速
			Motorspeed_2_4=PIDI_realize_II(Now_Angle,Motor_speed);    
			
			if(Distance_R<14)
			{		
				Motorspeed_1=PIDII_realize_I(Distance_R-SR_outside_width,Motorspeed_1_3);  //正 加减速
				Motorspeed_2=PIDII_realize_II(Distance_R-SR_outside_width,Motorspeed_2_4);    
				Motorspeed_3=PIDII_realize_II(Distance_R-SR_outside_width,Motorspeed_1_3);   
				Motorspeed_4=PIDII_realize_I(Distance_R-SR_outside_width,Motorspeed_2_4);    

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
				if(Motorspeed_1_3<Motor_Max) Motorspeed_1_3=Motor_Max;
				if(Motorspeed_1_3>Motor_Min) Motorspeed_1_3=Motor_Min;
				if(Motorspeed_2_4<Motor_Max) Motorspeed_2_4=Motor_Max;
				if(Motorspeed_2_4>Motor_Min) Motorspeed_2_4=Motor_Min;	
				
				TIM_SetCompare1(TIM4,Motorspeed_1_3);	
				TIM_SetCompare2(TIM4,Motorspeed_2_4);
				TIM_SetCompare3(TIM4,Motorspeed_1_3);
				TIM_SetCompare4(TIM4,Motorspeed_2_4);				
			}
	  }
		if(Gd_left_in==1&&Gd_right_in==0)			//过垄
		{
			delay_ms(10);	
			Motor_Direction(STOP);
			delay_ms(150);
			break;						
		}		
	}
	                             /*******左转*********/	
	while(1)
	{
		OLED_Show();		
		if(Gd_left_out==1)
		{
			Motor_Direction(LEFT);
			
			Motorspeed_1_2=PIDI_realize_II(Now_Angle,Motor_Slow_speed);   //正 加 减速
			Motorspeed_3_4=PIDI_realize_I(Now_Angle,Motor_Slow_speed);  

			if(Motorspeed_1_2<Motor_Max)  Motorspeed_1_2=Motor_Max;
			if(Motorspeed_1_2>Motor_Min)  Motorspeed_1_2=Motor_Min;
			if(Motorspeed_3_4<Motor_Max)  Motorspeed_3_4=Motor_Max;
			if(Motorspeed_3_4>Motor_Min)  Motorspeed_3_4=Motor_Min;	
			
		  TIM_SetCompare1(TIM4,Motorspeed_1_2);	
			TIM_SetCompare2(TIM4,Motorspeed_1_2);
			TIM_SetCompare3(TIM4,Motorspeed_3_4);
			TIM_SetCompare4(TIM4,Motorspeed_3_4);				
		}
		else
    {
			delay_ms(100);				
			break;				
		}	
	}	
}

 void Motor_turn_back(void)
{
	                             /*******左转*********/	
	while(1)
	{
		OLED_Show();		
		if(Gd_left_out==1)
		{
			Motor_Direction(LEFT);		
			Motorspeed_1_2=PIDI_realize_II(Now_Angle,Motor_speed_4);   //正 加 减速
			Motorspeed_3_4=PIDI_realize_I(Now_Angle,Motor_speed_4);  

			if(Motorspeed_1_2<Motor_Max)  Motorspeed_1_2=Motor_Max;
			if(Motorspeed_1_2>Motor_Min)  Motorspeed_1_2=Motor_Min;
			if(Motorspeed_3_4<Motor_Max)  Motorspeed_3_4=Motor_Max;
			if(Motorspeed_3_4>Motor_Min)  Motorspeed_3_4=Motor_Min;	
			
		  TIM_SetCompare1(TIM4,Motorspeed_1_2);	
			TIM_SetCompare2(TIM4,Motorspeed_1_2);
			TIM_SetCompare3(TIM4,Motorspeed_3_4);
			TIM_SetCompare4(TIM4,Motorspeed_3_4);				
		}
		else
    {
			delay_ms(200);	
			break;				
		}
	}
	
	while(1)
	{
		OLED_Show();
		Motor_Direction(LEFT);
		
		StartMeasure_IN();

		Motorspeed_1_2=PIDI_realize_II(Now_Angle,Motor_speed_3);   //正 减 加速
		Motorspeed_3_4=PIDI_realize_I(Now_Angle,Motor_speed_3);    
		
		if(Distance_IN<14)
		{		
			Motorspeed_1=PIDII_realize_II(Distance_IN-SR_inside_width,Motorspeed_1_2);  //正 加 减速
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
			delay_ms(40);	
			Motor_Direction(STOP);
			delay_ms(150);					
			break;					
		}			
	}	
	
	while(1)
	{
		//printf("w:%f\r\n",Now_Angle);
		OLED_Show();
		if(Gd_left_in==0)  
		{
			Motor_Direction(BACK);
			
			StartMeasure_L();

			Motorspeed_1_3=PIDI_realize_II(Now_Angle,Motor_speed_2);   //加
			Motorspeed_2_4=PIDI_realize_I(Now_Angle,Motor_speed_2);    
			
			if(Distance_L<14)
			{				
				Motorspeed_1=PIDII_realize_I(Distance_L-SR_outside_width,Motorspeed_1_3);  // 减
				Motorspeed_2=PIDII_realize_II(Distance_L-SR_outside_width,Motorspeed_2_4);    
				Motorspeed_3=PIDII_realize_II(Distance_L-SR_outside_width,Motorspeed_1_3);   
				Motorspeed_4=PIDII_realize_I(Distance_L-SR_outside_width,Motorspeed_2_4);    

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
				if(Motorspeed_1_3<Motor_Max) Motorspeed_1_3=Motor_Max;
				if(Motorspeed_1_3>Motor_Min) Motorspeed_1_3=Motor_Min;
				if(Motorspeed_2_4<Motor_Max) Motorspeed_2_4=Motor_Max;
				if(Motorspeed_2_4>Motor_Min) Motorspeed_2_4=Motor_Min;
				
				TIM_SetCompare1(TIM4,Motorspeed_1_3);	
				TIM_SetCompare2(TIM4,Motorspeed_2_4);
				TIM_SetCompare3(TIM4,Motorspeed_1_3);
				TIM_SetCompare4(TIM4,Motorspeed_2_4);				
			}	
	 }
   else
	 {
			delay_ms(80);	
			Motor_Direction(STOP);
			delay_ms(150);
	    TIM_SetCompare2(TIM3,1750);		 
			break;			
	 }
 }	
}
//////////////////////////////////////////////////////
void Speed_Add_Back(void)
{
	int m,t,speed;
	speed=Motor_speed_8;
	
	for(t=0;t<=9;t++)
	{
		for(m=0;m<200;m++)
		{
			Motor_Direction(BACK);
			
			StartMeasure_L();

			Motorspeed_1_3=PIDI_realize_II(Now_Angle,speed);   //加
			Motorspeed_2_4=PIDI_realize_I(Now_Angle,speed);    
			
			if(Distance_L<14)
			{		
				Motorspeed_1=PIDII_realize_I(Distance_L-SR_outside_width,Motorspeed_1_3);  // 减
				Motorspeed_2=PIDII_realize_II(Distance_L-SR_outside_width,Motorspeed_2_4);    
				Motorspeed_3=PIDII_realize_II(Distance_L-SR_outside_width,Motorspeed_1_3);   
				Motorspeed_4=PIDII_realize_I(Distance_L-SR_outside_width,Motorspeed_2_4);    

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
				if(Motorspeed_1_3<Motor_Max) Motorspeed_1_3=Motor_Max;
				if(Motorspeed_1_3>Motor_Min) Motorspeed_1_3=Motor_Min;
				if(Motorspeed_2_4<Motor_Max) Motorspeed_2_4=Motor_Max;
				if(Motorspeed_2_4>Motor_Min) Motorspeed_2_4=Motor_Min;
				
				TIM_SetCompare1(TIM4,Motorspeed_1_3);	
				TIM_SetCompare2(TIM4,Motorspeed_2_4);
				TIM_SetCompare3(TIM4,Motorspeed_1_3);
				TIM_SetCompare4(TIM4,Motorspeed_2_4);				
			}
		}
		speed-=50;
  }	
}

