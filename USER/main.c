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

/**********�� �� 20201227*********/

extern float Now_Angle;                        //��ǰ�����ǽǶ�
extern float Distance_IN,Distance_L,Distance_R;  //��������������
extern int OpenMV_X,OpenMV_Y;                  //OPENMV X �ᷴ������

int main(void)
{		
	delay_init();	    	            //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	              //���ڳ�ʼ��Ϊ115200
	USART2_Init(115200);	          //�����Ǵ��ڳ�ʼ��
	USART3_Init(9600);              //OpenMv��ʼ��
 	LED_Init();			                //LED�˿ڳ�ʼ��
	KEY_Init();                     //������ʼ��
  GuangDian_Init();               //����ʼ��
	OLED_Init();                    //OLED��ʼ��
	OLED_Clear();	                  //OLED����
  Display();                      //��ʾ���������
  PIDI_INIT();                    //����������У��
  PIDII_INIT();	                  //���ڳ��������У��
  Motor_Init();                   //�����ʼ��
  TIM4_PWM_Init(999,71);          //1khz  ���PWM
	TIM6_Int_Init(5000,719);        //10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms 
  TIM3_PWM_Init(1999,719);        //�����ʼ��
	UltrasonicWave_Configuration();	//��������ʼ��
  TIM_SetCompare1(TIM3,1750);	//����
	TIM_SetCompare2(TIM3,1750);	//��ת
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
//	  printf("Distance_L��%f cm\r\n",Distance_L);	
//		
//		delay_ms(400);
//		StartMeasure_R();	
//	  printf("Distance_R��%f cm\r\n",Distance_R);		
   //printf("Now_Angle��%f\r\n",Now_Angle);		
	}	 
}

