#include "pid.h"
#include "stdlib.h"
#include "math.h"

/* ����ԪPID��ʼ������,���ڶ�vPID�����ֵ�����޸�ǰ���     */
/* NEURALPID vPID������ԪPID���������ʵ�����ݽ����뱣��   */
/* float vMax,float vMin�����̱����������Сֵ�����̷�Χ��   */
/*����ṹ��͹�����*/
struct SNPID
{
  u16 setpoint;               /*�趨ֵ*/
  float kcoef;                  /*��Ԫ�������*/
  float kp;                     /*����ѧϰ�ٶ�*/
  float ki;                     /*����ѧϰ�ٶ�*/
  float kd;                     /*΢��ѧϰ�ٶ�*/
  float lasterror;              /*ǰһ��ƫ��*/
  float preerror;               /*ǰ����ƫ��*/
  float result;                 /*���ֵ*/
  float wp;                     /*������Ȩϵ��*/
  float wi;                     /*���ּ�Ȩϵ��*/
  float wd;                     /*΢�ּ�Ȩϵ��*/
//  float deadband;               /*����*/
//  float output;                 /*�ٷֱ����ֵ*/
//  float maximum;                /*���ֵ������*/
//  float minimum;                /*���ֵ������*/
}PID;

void NeuralPIDInitialization()
{
  PID.setpoint=0;                    /*�趨ֵ*/
//	Ч���ϼ�
	PID.kcoef=0.5;                    /*��Ԫ�������*/
  PID.kp=0.85;                        /*����ѧϰ�ٶ�*/
  PID.ki=0;                          /*����ѧϰ�ٶ�*/
  PID.kd=0.25;                        /*΢��ѧϰ�ٶ�*/
  PID.lasterror=0;                   /*ǰһ��ƫ��*/
  PID.preerror=0;                    /*ǰ����ƫ��*/
  PID.result=0;                      /*PID���������*/
  PID.wp=0.1;                       /*������Ȩϵ��*/
  PID.wi=0.1;                       /*���ּ�Ȩϵ��*/
  PID.wd=0.1;                       /*΢�ּ�Ȩϵ��*/
}

/* ���������������PID���������������ͷ�ʽʵ��                    */
/* NEURALPID vPID��������PID���������ʵ�����ݽ����뱣��           */
/* float pv�����̲���ֵ��������Ӧ�Ĳ������ݣ����ڿ��Ʒ���          */
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
  //����Ԫѧϰ
	NeureLearningRules(error,PID.result,x);

  PID.preerror=PID.lasterror;
  PID.lasterror=error;
	return PID.result;
}

/*����Ԫѧϰ������*/
static void NeureLearningRules(float zk,float uk,float *xi)

{
  PID.wi=PID.wi+PID.ki*zk*uk*xi[0];
  PID.wp=PID.wp+PID.kp*zk*uk*xi[1];
  PID.wd=PID.wd+PID.kd*zk*uk*xi[2];
//	printf("pidresult=%f    pidwp=%f    pidwi=%f     pidwd=%f   \r\n",PID.result,PID.wp,PID.wi,PID.wd);
}




