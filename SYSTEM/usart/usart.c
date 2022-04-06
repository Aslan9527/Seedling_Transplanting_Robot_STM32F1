#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif


//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		
		if((USART_RX_STA&0x8000)==0)//����δ���
			{
			if(USART_RX_STA&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else USART_RX_STA|=0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}   		 
     } 
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
#endif	

void USART2_Init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //GPIOA9����ΪUSART1
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
    USART_DeInit(USART2);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  USART_Init(USART2, &USART_InitStructure); //��ʼ������1
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure); //����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�  

  USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2
}

u8 Re_buf[11],counter = 0;
u8 jiasudu[6],jiaosudu[6],jiaodu[6],wendu[2];
float Angle[3],Accelerate[3],Palstance[3],Temperature;
float Now_Angle;

void USART2_IRQHandler(void)
{
   if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	 {
	     Re_buf[counter]= USART_ReceiveData(USART2);

		   if(counter == 0&&Re_buf[0] != 0x55) return;
			 
			 counter++;
			 if(counter == 11)
			 {		
				  counter = 0;
			    switch(Re_buf[1])
					{
					  case 0x51:
							jiasudu[0] = Re_buf[2];
						  jiasudu[1] = Re_buf[3];
						  jiasudu[2] = Re_buf[4];
						  jiasudu[3] = Re_buf[5];
						  jiasudu[4] = Re_buf[6];
						  jiasudu[5] = Re_buf[7];
						  wendu[0]   = Re_buf[8];
						  wendu[1]   = Re_buf[9];
						  
						
						  Accelerate[0] = ((short)((jiasudu[1])<<8|jiasudu[0]))/32768.0*16.0;//X����ٶ�
							Accelerate[1] = ((short)((jiasudu[3])<<8|jiasudu[2]))/32768.0*16.0;//Y����ٶ�
						  Accelerate[2] = ((short)((jiasudu[5])<<8|jiasudu[4]))/32768.0*16.0;//Z����ٶ�
						  Temperature = ((short)((wendu[1]<<8)|wendu[0]))/340 + 36.53;
						
						break;
						
						case 0x52:
							jiaosudu[0] = Re_buf[2];
						  jiaosudu[1] = Re_buf[3];
						  jiaosudu[2] = Re_buf[4];
						  jiaosudu[3] = Re_buf[5];
						  jiaosudu[4] = Re_buf[6];
						  jiaosudu[5] = Re_buf[7];
						  wendu[0]   = Re_buf[8];
						  wendu[1]   = Re_buf[9];
              
							 
						  Palstance[0] = ((short)((jiaosudu[1]<<8)|jiaosudu[0]))/32768.0*2000;//X����ٶ�
						  Palstance[1] = ((short)((jiaosudu[3]<<8)|jiaosudu[2]))/32768.0*2000;//Y����ٶ�
						  Palstance[2] = ((short)((jiaosudu[5]<<8)|jiaosudu[4]))/32768.0*2000;//Z����ٶ�
							Temperature = ((short)((wendu[1]<<8)|wendu[0]))/340 + 36.53;
						break;
						
						case 0x53:
							jiaodu[0] = Re_buf[2];
						  jiaodu[1] = Re_buf[3];
						  jiaodu[2] = Re_buf[4];
						  jiaodu[3] = Re_buf[5];
						  jiaodu[4] = Re_buf[6];
						  jiaodu[5] = Re_buf[7];
						  wendu[0]   = Re_buf[8];
						  wendu[1]   = Re_buf[9];
						
						  Angle[0] = ((short)((jiaodu[1]<<8)|jiaodu[0]))/32768.0*180;//x��Ƕ�
              Angle[1] = ((short)((jiaodu[3]<<8)|jiaodu[2]))/32768.0*180;//Y��Ƕ�
	            Angle[2] = ((short)((jiaodu[5]<<8)|jiaodu[4]))/32768.0*180;//Z��Ƕ�
						  Temperature = ((short)((wendu[1]<<8)|wendu[0]))/340 + 36.53;
						break;
					}
			 }
	 }
	 Now_Angle=Angle[2];
	 USART_ClearITPendingBit(USART2, USART_IT_RXNE);
}

////////////////////////////////////////////////////////����3����//////////////////////////////////////////////////////////////////////////////
u16 pos_x,pos_y;

#if EN_USART3_RX   					//���ʹ���˽���
u8 USART3_RX_BUF[USART3_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u16 USART3_RX_STA=0;
void USART3_Init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   				//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure); 						//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���USART2
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    USART_Cmd(USART3, ENABLE);
}
int com_data;
int openmv[5];//stm32������������
int OpenMV_X;          /*OPENMV X �ᷴ������*/
int OpenMV_Y;   /*OPENMV ����        */
int Lm;
void USART3_IRQHandler(void)
{
   if(USART_GetITStatus(USART3,USART_IT_RXNE) != RESET)
	 {
      com_data = USART3->DR;
			Openmv_Receive_Data(com_data);     //openmv���ݴ�����
			Openmv_Data();		
	 
	 USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	 }
}
int m;
void Openmv_Receive_Data(int data)//����Openmv������������
{
	static int state = 0;
	if(state==0&&data==0xb3)
	{
		state=1;
		openmv[0]=data;
	}
	else if(state==1&&data==0xb3)
	{
		state=2;
		openmv[1]=data;
	}
	else if(state==2)
	{
		state=3;
		openmv[2]=data;
	}
	else if(state==3)
	{
		state = 4;
		openmv[3]=data;
	}
	else if(state==4)		//����Ƿ���ܵ�������־
	{
        if(data == 0x5B)
        {
            state = 0;
            openmv[4]=data;
            Openmv_Data();
        }
        else if(data != 0x5B)
        {
            state = 0;
            for(m=0;m<5;m++)
            {
                openmv[m]=0x00;
            }           
        }
	}    
	else
		{
			state = 0;
            for(m=0;m<5;m++)
            {
                openmv[m]=0x00;
            }
		}
		//printf("%d,%d\r\n",OpenMV_X,OpenMV_Y);
}
void Openmv_Data(void)
{
    OpenMV_X=openmv[2];
    OpenMV_Y=openmv[3];
}
#endif
