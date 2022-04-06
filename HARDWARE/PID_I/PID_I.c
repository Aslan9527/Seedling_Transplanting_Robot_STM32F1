#include "PID_I.h"

//用于陀螺仪校正

struct VAL_PIDI
{
    float SET_VAL;      //设置值
    float NOW_VAL;      //当前值
    float ERROR_VAL;    //偏差值ET
    float ERROR_NEXT;   //上一次的偏差量E(T-1)
    float ERROR_LAST;   //再上一次的偏差量E*(T-2)
    float Kp,Ki,Kd;     //比例，积分，微分值
    float incermentVAL; //用PIDI公式算出来的值
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
	  iError = VAL + PIDI.ERROR_LAST;  //本次偏差加上次偏差
    dError = VAL - PIDI.ERROR_LAST;
	
	  PIDI.ERROR_LAST = VAL;           //保存本次偏差
	
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
	  iError = VAL + PIDI.ERROR_LAST;  //本次偏差加上次偏差
    dError = VAL - PIDI.ERROR_LAST;
	
	  PIDI.ERROR_LAST = VAL;           //保存本次偏差
	
    PIDI.NOW_VAL = PIDI.Kp * pError + PIDI.Ki * iError + PIDI.Kd * dError;
    PIDI.incermentVAL += PIDI.NOW_VAL;
    return PIDI.incermentVAL;
}


