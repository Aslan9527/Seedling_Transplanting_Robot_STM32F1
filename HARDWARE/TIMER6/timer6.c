#include "timer6.h"
#include "led.h"
#include "delay.h"
#include "usart.h"

void TIM6_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);          //时钟使能
	
  TIM_DeInit(TIM6);
	
	TIM_TimeBaseStructure.TIM_Period = arr;                      //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc;                    //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);              //根据指定的参数初始化TIMx的时间基数单位
 
  TIM_ClearFlag(TIM6, TIM_FLAG_Update);							    		   /* 清除溢出中断标志 */				 
}

float Distance_IN;     //计算出的距离    
float Distance_L;      //计算出的距离    
float Distance_R;      //计算出的距离 

int averge_distance;
/*
 * 函数名：UltrasonicWave_Configuration
 * 描述  ：超声波模块的初始化
 */
void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;		       
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = TRIG_PIN_1|TRIG_PIN_2|TRIG_PIN_3;					 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		            //设为推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(TRIG_PORT,&GPIO_InitStructure);	                    

  GPIO_InitStructure.GPIO_Pin = ECHO_PIN_1|ECHO_PIN_2|ECHO_PIN_3;				     
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		        
  GPIO_Init(ECHO_PORT,&GPIO_InitStructure);						           
}

/*
 * 函数名：UltrasonicWave_StartMeasure
 * 描述  ：开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
 */
void UltrasonicWave_StartMeasure(int choose)
{
	if(choose==1)
	{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN_1); 		  //送>10US的高电平
  delay_us(20);		                      //延时20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN_1);

  while(!GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN_1));	             //等待高电平 
  TIM_Cmd(TIM6, ENABLE);                                           //开启时钟	
  while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN_1))	               //等待低电平
	{
		if(TIM_GetCounter(TIM6)>150)
		{
			break;
		}	
	}
  TIM_Cmd(TIM6, DISABLE);			                                     //定时器6失能
	
  Distance_IN=TIM_GetCounter(TIM6)*34/200.0;				    //计算距离
	
  TIM_SetCounter(TIM6,0);
	}
	else if(choose==2)
	{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN_2); 		  //送>10US的高电平
  delay_us(20);		                      //延时20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN_2);

  while(!GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN_2));	             //等待高电平 
  TIM_Cmd(TIM6, ENABLE);                                           //开启时钟	
  while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN_2))               //等待低电平
	{
		if(TIM_GetCounter(TIM6)>90)    //15.3
		{
			break;
		}		
	}
  TIM_Cmd(TIM6, DISABLE);			                                     //定时器6失能
	
  Distance_L=TIM_GetCounter(TIM6)*34/200.0;				    //计算距离
	
  TIM_SetCounter(TIM6,0);
	}
	else if(choose==3)
	{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN_3); 		  //送>10US的高电平
  delay_us(20);		                      //延时20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN_3);

  while(!GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN_3));	             //等待高电平 
  TIM_Cmd(TIM6, ENABLE);                                           //开启时钟	
  while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN_3))	               //等待低电平
	{
		if(TIM_GetCounter(TIM6)>90)  
		{
			break;
		}		
	}
  TIM_Cmd(TIM6, DISABLE);			                                     //定时器6失能
	
  Distance_R=TIM_GetCounter(TIM6)*34/200.0;			    //计算距离
	
  TIM_SetCounter(TIM6,0);
	}	
}

void StartMeasure_IN(void)
{
  UltrasonicWave_StartMeasure(1);
}
void StartMeasure_L(void)
{
  UltrasonicWave_StartMeasure(2);
}
void StartMeasure_R(void)
{
  UltrasonicWave_StartMeasure(3);
}


