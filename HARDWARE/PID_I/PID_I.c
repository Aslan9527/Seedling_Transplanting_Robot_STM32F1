#include "PID_I.h"

//����������У��

struct VAL_PIDI
{
    float SET_VAL;      //����ֵ
    float NOW_VAL;      //��ǰֵ
    float ERROR_VAL;    //ƫ��ֵET
    float ERROR_NEXT;   //��һ�ε�ƫ����E(T-1)
    float ERROR_LAST;   //����һ�ε�ƫ����E*(T-2)
    float Kp,Ki,Kd;     //���������֣�΢��ֵ
    float incermentVAL; //��PIDI��ʽ�������ֵ
} PIDI;

void PIDI_INIT()
{
    PIDI.SET_VAL = 0;
    PIDI.NOW_VAL = 0;
    PIDI.ERROR_VAL = 0;
    PIDI.ERROR_NEXT = 0;
    PIDI.ERROR_LAST = 0;
    PIDI.incermentVAL = 0;
    PIDI.Kp = 120.0;
    PIDI.Ki = 2.0; 
    PIDI.Kd = 20.0; 
}

float PIDI_realize_I(float VAL,float VAL0)
{
		float pError,dError,iError;
	
    PIDI.incermentVAL = VAL0;
	  pError = VAL;
	  iError = VAL + PIDI.ERROR_LAST;  //����ƫ����ϴ�ƫ��
    dError = VAL - PIDI.ERROR_LAST;
	
	  PIDI.ERROR_LAST = VAL;           //���汾��ƫ��
	
//	  if(VAL>3)
//		{
//      PIDI.NOW_VAL = 1.5*PIDI.Kp * pError + PIDI.Ki * iError + PIDI.Kd * dError;		
//		}
//		else
//		{	
      PIDI.NOW_VAL = PIDI.Kp * pError + PIDI.Ki * iError + PIDI.Kd * dError;
//		}
		
    PIDI.incermentVAL -= PIDI.NOW_VAL;
    return PIDI.incermentVAL;
}
float PIDI_realize_II(float VAL,float VAL0)
{
		float pError,dError,iError;
	
    PIDI.incermentVAL = VAL0;
	  pError = VAL;
	  iError = VAL + PIDI.ERROR_LAST;  //����ƫ����ϴ�ƫ��
    dError = VAL - PIDI.ERROR_LAST;
	
	  PIDI.ERROR_LAST = VAL;           //���汾��ƫ��
	
    PIDI.NOW_VAL = PIDI.Kp * pError + PIDI.Ki * iError + PIDI.Kd * dError;
    PIDI.incermentVAL += PIDI.NOW_VAL;
    return PIDI.incermentVAL;
}


