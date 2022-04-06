#include "UltrasonicWave.h"
#include "usart.h"
#include "timer2.h"
#include "delay.h"

float Distance_IN;      //计算出的距离    
float Distance_L;      //计算出的距离    
float Distance_R;      //计算出的距离    


/*
 * 函数名：UltrasonicWave_Configuration
 * 描述  ：超声波模块的初始化
 * 输入  ：无
 * 输出  ：无	
 */
void UltrasonicWave_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	  EXTI_InitTypeDef EXTI_InitStructure;
   	NVIC_InitTypeDef NVIC_InitStructure;
	
	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//关闭jtag
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
     
    GPIO_InitStructure.GPIO_Pin = TRIG_PIN|TRIG_PIN1|TRIG_PIN2;					 //PC8接TRIG
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //设为推挽输出模式
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
    GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	                 //初始化外设GPIO 

    GPIO_InitStructure.GPIO_Pin = ECHO_PIN|ECHO_PIN1|ECHO_PIN2;				     //PC7接ECH0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		 //设为输入
    GPIO_Init(ECHO_PORT,&GPIO_InitStructure);						 //初始化GPIOA
	
	  //GPIOC.7	  中断线以及中断初始化配置
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource7);

 	  EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
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
			
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;					//子优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  

	  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//子优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
}

void EXTI9_5_IRQHandler(void)
{
	   delay_us(15);		                      //延时10us
     if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	   {
			 TIM_SetCounter(TIM2,0);
			 TIM_Cmd(TIM2, ENABLE);                                             //开启时钟
		
			 while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	                 //等待低电平

			 TIM_Cmd(TIM2, DISABLE);			                                 //定时器2失能
//			 Distance_IN=TIM_GetCounter(TIM2)*5*34/200.0;									 //计算距离&&UltrasonicWave_Distance<150
			 Distance_IN=TIM_GetCounter(TIM2)*34/20.0;
//		if(Distance_IN>0)
//		{
////			printf("3:%f cm\r\n",Distance_IN);
//		}	
	    EXTI_ClearITPendingBit(EXTI_Line7);  //清除EXTI7线路挂起位
    }
	
	  if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	  {
			TIM_SetCounter(TIM2,0);
			TIM_Cmd(TIM2, ENABLE);                                             //开启时钟
		
			while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN2));	                 //等待低电平

			TIM_Cmd(TIM2, DISABLE);			                                 //定时器2失能
			Distance_R=TIM_GetCounter(TIM2)*5*34/200.0;									 //计算距离&&UltrasonicWave_Distance<150
		
			if(Distance_R>0)
			{
				printf("distance_R:%f cm\r\n",Distance_R);
			}
	   EXTI_ClearITPendingBit(EXTI_Line5);  //清除EXTI7线路挂起位
   }
}


void EXTI1_IRQHandler(void)
{
	   delay_us(15);		                      //延时10us
     if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	   {
			 TIM_SetCounter(TIM2,0);
			 TIM_Cmd(TIM2, ENABLE);                                             //开启时钟
		
			 while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN1));	                 //等待低电平

			 TIM_Cmd(TIM2, DISABLE);			                                 //定时器2失能
			 Distance_L=TIM_GetCounter(TIM2)*5*34/200.0;									 //计算距离&&UltrasonicWave_Distance<150
		
		  if(Distance_L>0)
		  {
				 printf("distance_L:%f cm\r\n",Distance_L);
		  }	
	   EXTI_ClearITPendingBit(EXTI_Line1);  //清除EXTI7线路挂起位
    }
}

/*
 * 函数名：UltrasonicWave_StartMeasure
 * 描述  ：开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
 * 输入  ：无
 * 输出  ：无	
 */
void StartMeasure_IN(void)
{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN); 		  //送>10US的高电平RIG_PORT,TRIG_PIN这两个在define中有?
  delay_us(20);		                      //延时20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
	printf("2\r\n");
}

void StartMeasure_L(void)
{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN1); 		  //送>10US的高电平RIG_PORT,TRIG_PIN这两个在define中有?
  delay_us(20);		                      //延时20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN1);	
}
void StartMeasure_R(void)
{
  GPIO_SetBits(TRIG_PORT,TRIG_PIN2); 		  //送>10US的高电平RIG_PORT,TRIG_PIN这两个在define中有?
  delay_us(20);		                      //延时20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN2);	
}

