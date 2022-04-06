#include "duoji.h"
/*******************************************************************************
* 函 数 名         : pwm_init
* 函数功能		   : IO端口及TIM3初始化函数	   
*******************************************************************************/
void TIM3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;   //声明一个结构体变量，用来初始化GPIO
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//声明一个结构体变量，用来初始化定时器
	TIM_OCInitTypeDef TIM_OCInitStructure;//根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	/* 开启时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//  A 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //TIM3 PA 6 7 

	/*  配置GPIO的模式和IO口 */     //舵机1
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;// PA 6 7
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
	//TIM3定时器初始化
	TIM_TimeBaseInitStructure.TIM_Period = arr; //PWM 频率=72000/(199+1)=36Khz//设置自动重装载寄存器周期的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;//设置用来作为TIMx时钟频率预分频值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseInitStructure);

	//PWM初始化	  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM输出使能
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;

	TIM_OC1Init(TIM3,&TIM_OCInitStructure);//注意此处初始化时TIM_OC1Init而不是TIM_OCInit，否则会出错。因为固件库的版本不一样。
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能或者失能TIMx在CCR1上的预装载寄存器
	
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //A6 旋转 A7 伸缩
	
	TIM_Cmd(TIM3,ENABLE);//使能或者失能TIMx外设
}


