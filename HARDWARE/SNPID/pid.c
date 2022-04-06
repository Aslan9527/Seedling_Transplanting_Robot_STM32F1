#include "pid.h"
#include "stdlib.h"
#include "math.h"

/* 单神经元PID初始化操作,需在对vPID对象的值进行修改前完成     */
/* NEURALPID vPID，单神经元PID对象变量，实现数据交换与保存   */
/* float vMax,float vMin，过程变量的最大最小值（量程范围）   */
/*定义结构体和公用体*/
struct SNPID
{
  u16 setpoint;               /*设定值*/
  float kcoef;                  /*神经元输出比例*/
  float kp;                     /*比例学习速度*/
  float ki;                     /*积分学习速度*/
  float kd;                     /*微分学习速度*/
  float lasterror;              /*前一拍偏差*/
  float preerror;               /*前两拍偏差*/
  float result;                 /*输出值*/
  float wp;                     /*比例加权系数*/
  float wi;                     /*积分加权系数*/
  float wd;                     /*微分加权系数*/
//  float deadband;               /*死区*/
//  float output;                 /*百分比输出值*/
//  float maximum;                /*输出值的上限*/
//  float minimum;                /*输出值的下限*/
}PID;

void NeuralPIDInitialization()
{
  PID.setpoint=0;                    /*设定值*/
//	效果较佳
	PID.kcoef=0.5;                    /*神经元输出比例*/
  PID.kp=0.85;                        /*比例学习速度*/
  PID.ki=0;                          /*积分学习速度*/
  PID.kd=0.25;                        /*微分学习速度*/
  PID.lasterror=0;                   /*前一拍偏差*/
  PID.preerror=0;                    /*前两拍偏差*/
  PID.result=0;                      /*PID控制器结果*/
  PID.wp=0.1;                       /*比例加权系数*/
  PID.wi=0.1;                       /*积分加权系数*/
  PID.wd=0.1;                       /*微分加权系数*/
}

/* 神经网络参数自整定PID控制器，以增量型方式实现                    */
/* NEURALPID vPID，神经网络PID对象变量，实现数据交换与保存           */
/* float pv，过程测量值，对象响应的测量数据，用于控制反馈          */
float NeuralPID(u16 setpoint,float actualspeed)
{
  float x[3];
  float w[3];
  float sabs;
  float error;
  float deltaResult;
  PID.setpoint=setpoint;
  error=PID.setpoint-actualspeed;
	
    x[0]=error;
    x[1]=error-PID.lasterror;
    x[2]=error-PID.lasterror*2+PID.preerror;
    sabs=fabs(PID.wi)+fabs(PID.wp)+fabs(PID.wd);
	
		w[0]=PID.wi/sabs;
    w[1]=PID.wp/sabs;
    w[2]=PID.wd/sabs;
	
    deltaResult=(w[0]*x[0]+w[1]*x[1]+w[2]*x[2])*PID.kcoef;
//		printf("x0=%f    x1=%f    x2=%f     sabs=%f   \r\n",x[0],x[1],x[2],sabs);

//		printf("w0=%f    w1=%f    w2=%f     deltaResult=%f   \r\n",w[0],w[1],w[2],deltaResult);
    PID.result+=deltaResult;

//	printf("vPID->result=%f \r\n",PID.result);
  //单神经元学习
	NeureLearningRules(error,PID.result,x);

  PID.preerror=PID.lasterror;
  PID.lasterror=error;
	return PID.result;
}

/*单神经元学习规则函数*/
static void NeureLearningRules(float zk,float uk,float *xi)

{
  PID.wi=PID.wi+PID.ki*zk*uk*xi[0];
  PID.wp=PID.wp+PID.kp*zk*uk*xi[1];
  PID.wd=PID.wd+PID.kd*zk*uk*xi[2];
//	printf("pidresult=%f    pidwp=%f    pidwi=%f     pidwd=%f   \r\n",PID.result,PID.wp,PID.wi,PID.wd);
}




