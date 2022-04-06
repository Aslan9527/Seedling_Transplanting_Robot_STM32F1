#include "timer6.h"
#include "led.h"
#include "delay.h"
#include "usart.h"

void TIM6_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);          //ʱ��ʹ��
	
  TIM_DeInit(TIM6);
	
	TIM_TimeBaseStructure.TIM_Period = arr;                      //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc;                    //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;      //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);              //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
  TIM_ClearFlag(TIM6, TIM_FLAG_Update);							    		   /* �������жϱ�־ */				 
}

float Distance_IN;     //������ľ���    
float Distance_L;      //������ľ���    
float Distance_R;      //������ľ��� 

int averge_distance;
/*
 * ��������UltrasonicWave_Configuration
 * ����  ��������ģ��ĳ�ʼ��
 */
void UltrasonicWave_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;		       
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = TRIG_PIN_1|TRIG_PIN_2|TRIG_PIN_3;					 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		            //��Ϊ�������ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(TRIG_PORT,&GPIO_InitStructure);	                    

  GPIO_InitStructure.GPIO_Pin = ECHO_PIN_1|ECHO_PIN_2|ECHO_PIN_3;				     
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		        
  GPIO_Init(ECHO_PORT,&GPIO_InitStructure);						           
}

/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 */
void UltrasonicWave_StartMeasure(int choose)
{
	if(choose==1)
	{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN_1); 		  //��>10US�ĸߵ�ƽ
  delay_us(20);		                      //��ʱ20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN_1);

  while(!GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN_1));	             //�ȴ��ߵ�ƽ 
  TIM_Cmd(TIM6, ENABLE);                                           //����ʱ��	
  while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN_1))	               //�ȴ��͵�ƽ
	{
		if(TIM_GetCounter(TIM6)>150)
		{
			break;
		}	
	}
  TIM_Cmd(TIM6, DISABLE);			                                     //��ʱ��6ʧ��
	
  Distance_IN=TIM_GetCounter(TIM6)*34/200.0;				    //�������
	
  TIM_SetCounter(TIM6,0);
	}
	else if(choose==2)
	{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN_2); 		  //��>10US�ĸߵ�ƽ
  delay_us(20);		                      //��ʱ20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN_2);

  while(!GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN_2));	             //�ȴ��ߵ�ƽ 
  TIM_Cmd(TIM6, ENABLE);                                           //����ʱ��	
  while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN_2))               //�ȴ��͵�ƽ
	{
		if(TIM_GetCounter(TIM6)>90)    //15.3
		{
			break;
		}		
	}
  TIM_Cmd(TIM6, DISABLE);			                                     //��ʱ��6ʧ��
	
  Distance_L=TIM_GetCounter(TIM6)*34/200.0;				    //�������
	
  TIM_SetCounter(TIM6,0);
	}
	else if(choose==3)
	{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN_3); 		  //��>10US�ĸߵ�ƽ
  delay_us(20);		                      //��ʱ20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN_3);

  while(!GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN_3));	             //�ȴ��ߵ�ƽ 
  TIM_Cmd(TIM6, ENABLE);                                           //����ʱ��	
  while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN_3))	               //�ȴ��͵�ƽ
	{
		if(TIM_GetCounter(TIM6)>90)  
		{
			break;
		}		
	}
  TIM_Cmd(TIM6, DISABLE);			                                     //��ʱ��6ʧ��
	
  Distance_R=TIM_GetCounter(TIM6)*34/200.0;			    //�������
	
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


