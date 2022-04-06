#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

#define	TRIG_PORT     	 GPIOG		    //TRIG       
#define	ECHO_PORT      	 GPIOG		    //ECHO 

#define	TRIG_PIN_1       GPIO_Pin_2   //TRIG       
#define	ECHO_PIN_1       GPIO_Pin_3	  //ECHO  

#define	TRIG_PIN_2       GPIO_Pin_4   //TRIG       
#define	ECHO_PIN_2       GPIO_Pin_5	  //ECHO 

#define	TRIG_PIN_3       GPIO_Pin_6   //TRIG       
#define	ECHO_PIN_3       GPIO_Pin_7	  //ECHO 

void TIM6_Int_Init(u16 arr,u16 psc);
void UltrasonicWave_Configuration(void);               //�Գ�����ģ���ʼ��
void UltrasonicWave_StartMeasure(int choose);          //��ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
void StartMeasure_L(void);
void StartMeasure_R(void);
void StartMeasure_IN(void);

#endif
