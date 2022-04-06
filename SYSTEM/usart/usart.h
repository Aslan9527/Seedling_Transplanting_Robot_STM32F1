#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 



#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

#define USART2_REC_LEN  		200  													//定义最大接收字节数 200,串口2 
#define EN_USART2_RX 			1														//使能（1）/禁止（0）串口2接收

#define USART3_REC_LEN  		1000  													//定义最大接收字节数 200,串口2 
#define EN_USART3_RX 			1														//使能（1）/禁止（0）串口2接收

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u8  USART2_RX_BUF[USART2_REC_LEN];	
extern u8  USART3_RX_BUF[USART3_REC_LEN];	

extern u16 USART_RX_STA;         		//接收状态标记
extern u16 USART2_RX_STA; 
extern u16 USART3_RX_STA; 

//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
void USART2_Init(u32 bound);
void USART3_Init(u32 bound);
void Openmv_Receive_Data(int data);
void Openmv_Data(void);
#endif


