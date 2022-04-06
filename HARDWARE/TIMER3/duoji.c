#include "duoji.h"
/*******************************************************************************
* �� �� ��         : pwm_init
* ��������		   : IO�˿ڼ�TIM3��ʼ������	   
*******************************************************************************/
void TIM3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;   //����һ���ṹ�������������ʼ��GPIO
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//����һ���ṹ�������������ʼ����ʱ��
	TIM_OCInitTypeDef TIM_OCInitStructure;//����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

	/* ����ʱ�� */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//  A 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //TIM3 PA 6 7 

	/*  ����GPIO��ģʽ��IO�� */     //���1
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;// PA 6 7
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//�������
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
	//TIM3��ʱ����ʼ��
	TIM_TimeBaseInitStructure.TIM_Period = arr; //PWM Ƶ��=72000/(199+1)=36Khz//�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;//����������ΪTIMxʱ��Ƶ��Ԥ��Ƶֵ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseInitStructure);

	//PWM��ʼ��	  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM���ʹ��
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;

	TIM_OC1Init(TIM3,&TIM_OCInitStructure);//ע��˴���ʼ��ʱTIM_OC1Init������TIM_OCInit������������Ϊ�̼���İ汾��һ����
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ�ܻ���ʧ��TIMx��CCR1�ϵ�Ԥװ�ؼĴ���
	
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //A6 ��ת A7 ����
	
	TIM_Cmd(TIM3,ENABLE);//ʹ�ܻ���ʧ��TIMx����
}


