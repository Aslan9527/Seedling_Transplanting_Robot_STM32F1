#include "PID_II.h"

//���ڳ��������У��

//����ʽPIDII
//������PID
struct VAL_PIDII
{
    float SET_VAL;      //����ֵ
    float NOW_VAL;      //��ǰֵ
    float ERROR_VAL;    //ƫ��ֵET
    float ERROR_NEXT;   //��һ�ε�ƫ����E(T-1)
    float ERROR_LAST;   //����һ�ε�ƫ����E*(T-2)
    float Kp,Ki,Kd;     //���������֣�΢��ֵ
    float incermentVAL; //����PIDII��ʽ�������ֵ
} PIDII;

void PIDII_INIT()
{
    PIDII.SET_VAL = 0;
    PIDII.NOW_VAL = 0;
    PIDII.ERROR_VAL = 0;
    PIDII.ERROR_NEXT = 0;
    PIDII.ERROR_LAST = 0;
    PIDII.incermentVAL = 0;
    PIDII.Kp = 70.0;
    PIDII.Ki = 1.0;
    PIDII.Kd = 10.0;
}

float PIDII_realize_I(float VAL,float VAL0)
{
		float pError,dError,iError;
	
    PIDII.incermentVAL = VAL0;
	  pError = VAL;
	  iError = VAL + PIDII.ERROR_LAST;  //����ƫ����ϴ�ƫ��
    dError = VAL - PIDII.ERROR_LAST;
	
	  PIDII.ERROR_LAST = VAL;           //���汾��ƫ��
	
    PIDII.NOW_VAL = PIDII.Kp * pError + PIDII.Ki * iError + PIDII.Kd * dError;
	
    PIDII.incermentVAL -= PIDII.NOW_VAL;
    return PIDII.incermentVAL;
}
float PIDII_realize_II(float VAL,float VAL0)
{
		float pError,dError,iError;
	
    PIDII.incermentVAL = VAL0;
	  pError = VAL;
	  iError = VAL + PIDII.ERROR_LAST;  //����ƫ����ϴ�ƫ��
    dError = VAL - PIDII.ERROR_LAST;
	
	  PIDII.ERROR_LAST = VAL;           //���汾��ƫ��
	
    PIDII.NOW_VAL = PIDII.Kp * pError + PIDII.Ki * iError + PIDII.Kd * dError;
	
    PIDII.incermentVAL += PIDII.NOW_VAL;
    return PIDII.incermentVAL;
}
