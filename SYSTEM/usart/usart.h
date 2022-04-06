#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 



#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

#define USART2_REC_LEN  		200  													//�����������ֽ��� 200,����2 
#define EN_USART2_RX 			1														//ʹ�ܣ�1��/��ֹ��0������2����

#define USART3_REC_LEN  		1000  													//�����������ֽ��� 200,����2 
#define EN_USART3_RX 			1														//ʹ�ܣ�1��/��ֹ��0������2����

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u8  USART2_RX_BUF[USART2_REC_LEN];	
extern u8  USART3_RX_BUF[USART3_REC_LEN];	

extern u16 USART_RX_STA;         		//����״̬���
extern u16 USART2_RX_STA; 
extern u16 USART3_RX_STA; 

//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
void USART2_Init(u32 bound);
void USART3_Init(u32 bound);
void Openmv_Receive_Data(int data);
void Openmv_Data(void);
#endif


