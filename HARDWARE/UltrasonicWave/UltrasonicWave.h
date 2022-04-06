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


void UltrasonicWave_Configuration(void);               //对超声波模块初始化

void StartMeasure_IN(void);                //开始测距，发送一个>10us的脉冲，然后测量返回的高电平时间
void StartMeasure_L(void); 
void StartMeasure_R(void); 



#endif /* __UltrasonicWave_H */

