#include "PID_II.h"

//用于超声波测距校正

//增量式PIDII
//定距离PID
struct VAL_PIDII
{
    float SET_VAL;      //设置值
    float NOW_VAL;      //当前值
    float ERROR_VAL;    //偏差值ET
    float ERROR_NEXT;   //上一次的偏差量E(T-1)
    float ERROR_LAST;   //再上一次的偏差量E*(T-2)
    float Kp,Ki,Kd;     //比例，积分，微分值
    float incermentVAL; //，用PIDII公式算出来的值
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
	  iError = VAL + PIDII.ERROR_LAST;  //本次偏差加上次偏差
    dError = VAL - PIDII.ERROR_LAST;
	
	  PIDII.ERROR_LAST = VAL;           //保存本次偏差
	
    PIDII.NOW_VAL = PIDII.Kp * pError + PIDII.Ki * iError + PIDII.Kd * dError;
	
    PIDII.incermentVAL -= PIDII.NOW_VAL;
    return PIDII.incermentVAL;
}
float PIDII_realize_II(float VAL,float VAL0)
{
		float pError,dError,iError;
	
    PIDII.incermentVAL = VAL0;
	  pError = VAL;
	  iError = VAL + PIDII.ERROR_LAST;  //本次偏差加上次偏差
    dError = VAL - PIDII.ERROR_LAST;
	
	  PIDII.ERROR_LAST = VAL;           //保存本次偏差
	
    PIDII.NOW_VAL = PIDII.Kp * pError + PIDII.Ki * iError + PIDII.Kd * dError;
	
    PIDII.incermentVAL += PIDII.NOW_VAL;
    return PIDII.incermentVAL;
}
