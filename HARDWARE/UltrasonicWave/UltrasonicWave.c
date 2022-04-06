#include "UltrasonicWave.h"
#include "usart.h"
#include "timer2.h"
#include "delay.h"

float Distance_IN;      //������ľ���    
float Distance_L;      //������ľ���    
float Distance_R;      //������ľ���    


/*
 * ��������UltrasonicWave_Configuration
 * ����  ��������ģ��ĳ�ʼ��
 * ����  ����
 * ���  ����	
 */
void UltrasonicWave_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	  EXTI_InitTypeDef EXTI_InitStructure;
   	NVIC_InitTypeDef NVIC_InitStructure;
	
	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//�ر�jtag
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
     
    GPIO_InitStructure.GPIO_Pin = TRIG_PIN|TRIG_PIN1|TRIG_PIN2;					 //PC8��TRIG
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
    GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	                 //��ʼ������GPIO 

    GPIO_InitStructure.GPIO_Pin = ECHO_PIN|ECHO_PIN1|ECHO_PIN2;				     //PC7��ECH0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //��Ϊ����
    GPIO_Init(ECHO_PORT,&GPIO_InitStructure);						 //��ʼ��GPIOA
	
	  //GPIOC.7	  �ж����Լ��жϳ�ʼ������
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7);

 	  EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource1);

 	  EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

 	  EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);						
			
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//�����ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  

	  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//�����ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

void EXTI9_5_IRQHandler(void)
{
	   delay_us(15);		                      //��ʱ10us
     if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	   {
			 TIM_SetCounter(TIM2,0);
			 TIM_Cmd(TIM2, ENABLE);                                             //����ʱ��
		
			 while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	                 //�ȴ��͵�ƽ

			 TIM_Cmd(TIM2, DISABLE);			                                 //��ʱ��2ʧ��
//			 Distance_IN=TIM_GetCounter(TIM2)*5*34/200.0;									 //�������&&UltrasonicWave_Distance<150
			 Distance_IN=TIM_GetCounter(TIM2)*34/20.0;
//		if(Distance_IN>0)
//		{
////			printf("3:%f cm\r\n",Distance_IN);
//		}	
	    EXTI_ClearITPendingBit(EXTI_Line7);  //���EXTI7��·����λ
    }
	
	  if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	  {
			TIM_SetCounter(TIM2,0);
			TIM_Cmd(TIM2, ENABLE);                                             //����ʱ��
		
			while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN2));	                 //�ȴ��͵�ƽ

			TIM_Cmd(TIM2, DISABLE);			                                 //��ʱ��2ʧ��
			Distance_R=TIM_GetCounter(TIM2)*5*34/200.0;									 //�������&&UltrasonicWave_Distance<150
		
			if(Distance_R>0)
			{
				printf("distance_R:%f cm\r\n",Distance_R);
			}
	   EXTI_ClearITPendingBit(EXTI_Line5);  //���EXTI7��·����λ
   }
}


void EXTI1_IRQHandler(void)
{
	   delay_us(15);		                      //��ʱ10us
     if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	   {
			 TIM_SetCounter(TIM2,0);
			 TIM_Cmd(TIM2, ENABLE);                                             //����ʱ��
		
			 while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN1));	                 //�ȴ��͵�ƽ

			 TIM_Cmd(TIM2, DISABLE);			                                 //��ʱ��2ʧ��
			 Distance_L=TIM_GetCounter(TIM2)*5*34/200.0;									 //�������&&UltrasonicWave_Distance<150
		
		  if(Distance_L>0)
		  {
				 printf("distance_L:%f cm\r\n",Distance_L);
		  }	
	   EXTI_ClearITPendingBit(EXTI_Line1);  //���EXTI7��·����λ
    }
}

/*
 * ��������UltrasonicWave_StartMeasure
 * ����  ����ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
 * ����  ����
 * ���  ����	
 */
void StartMeasure_IN(void)
{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN); 		  //��>10US�ĸߵ�ƽ�TRIG_PORT,TRIG_PIN��������define����?
  delay_us(20);		                      //��ʱ20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
	printf("2\r\n");
}

void StartMeasure_L(void)
{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN1); 		  //��>10US�ĸߵ�ƽ�TRIG_PORT,TRIG_PIN��������define����?
  delay_us(20);		                      //��ʱ20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN1);	
}
void StartMeasure_R(void)
{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN2); 		  //��>10US�ĸߵ�ƽ�TRIG_PORT,TRIG_PIN��������define����?
  delay_us(20);		                      //��ʱ20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN2);	
}

