#ifndef __UltrasonicWave_H
#define	__UltrasonicWave_H

#define	TRIG_PORT       GPIOC		//TRIG       
#define	ECHO_PORT       GPIOC		//ECHO 
#define	TRIG_PIN        GPIO_Pin_8   //TRIG  
#define	TRIG_PIN1       GPIO_Pin_2   //TRIG 
#define	TRIG_PIN2       GPIO_Pin_6   //TRIG 
#define	ECHO_PIN        GPIO_Pin_7	//ECHO 
#define	ECHO_PIN1       GPIO_Pin_1	//ECHO   
#define	ECHO_PIN2       GPIO_Pin_5	//ECHO   


void UltrasonicWave_Configuration(void);               //�Գ�����ģ���ʼ��

void StartMeasure_IN(void);                //��ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
void StartMeasure_L(void); 
void StartMeasure_R(void); 



#endif /* __UltrasonicWave_H */

