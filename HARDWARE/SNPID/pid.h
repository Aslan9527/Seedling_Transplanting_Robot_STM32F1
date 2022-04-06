#ifndef _PID_H
#define _PID_H
#include "stdlib.h"
#include "math.h"
#include "sys.h"

void NeuralPIDInitialization(void);
static void NeureLearningRules(float zk,float uk,float *xi);
float NeuralPID(u16 setpoint,float actualspeed);

#endif
