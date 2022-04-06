#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "motor.h" 
#include "light.h"
#include "PID_I.h"
#include "PID_II.h"
#include "timer6.h"
#include "oled.h"
#include "place.h"
#include "duoji.h"
#include "motor_move.h"
#include "timer4_motor_pwm.h"
#include "pid.h"

/**********王 城 20201227*********/

extern float Now_Angle;                        //当前陀螺仪角度
extern float Distance_IN,Distance_L,Distance_R;  //超声波测量距离
extern int OpenMV_X,OpenMV_Y;                  //OPENMV X 轴反馈坐标

int main(void)
{		
	delay_init();	    	            //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	              //串口初始化为115200
	USART2_Init(115200);	          //陀螺仪串口初始化
	USART3_Init(9600);              //OpenMv初始化
 	LED_Init();			                //LED端口初始化
	KEY_Init();                     //按键初始化
  GuangDian_Init();               //光电初始化
	OLED_Init();                    //OLED初始化
	OLED_Clear();	                  //OLED清屏
  Display();                      //显示不变的文字
  PIDI_INIT();                    //用于陀螺仪校正
  PIDII_INIT();	                  //用于超声波测距校正
  Motor_Init();                   //电机初始化
  TIM4_PWM_Init(999,71);          //1khz  电机PWM
	TIM6_Int_Init(5000,719);        //10Khz的计数频率，计数到5000为500ms 
  TIM3_PWM_Init(1999,719);        //舵机初始化
	UltrasonicWave_Configuration();	//超声波初始化
  TIM_SetCompare1(TIM3,1750);	//伸缩
	TIM_SetCompare2(TIM3,1750);	//旋转
	LED0=0;
	while(1)
	{
		//printf("%d%d\r\n",OpenMV_X,OpenMV_Y);
	  OLED_Show();
//		if(KEY0==0)
		if(Gd_right_out==0)			
		{
			Motor_start();
			Motor_turn_right();
			area_right();
			Motor_turn_left();
			area_left();	
			Motor_turn_right();
			area_right();
			Motor_turn_left();
			area_left();	
			Motor_turn_right();
			area_right();
			Motor_turn_back();		
		}	
//    if(KEY0==0)
		if(Gd_left_out==0)				
		{
			Motor_start();
			Motor_turn_right();
			area_right_1();
			Motor_turn_left();
			area_left_1();	
			Motor_turn_right();
			area_right_1();
			Motor_turn_left();
			area_left_1();	
			Motor_turn_right();
			area_right_1();
			Motor_turn_back();
		}		
		LED1=~LED1;
		delay_ms(100);
		StartMeasure_IN();
	  printf("Distance_IN:%f cm\r\n",Distance_IN);
		
//		delay_ms(400);
//		StartMeasure_L();
//	  printf("Distance_L：%f cm\r\n",Distance_L);	
//		
//		delay_ms(400);
//		StartMeasure_R();	
//	  printf("Distance_R：%f cm\r\n",Distance_R);		
   //printf("Now_Angle：%f\r\n",Now_Angle);		
	}	 
}

