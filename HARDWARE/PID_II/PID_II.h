#ifndef __PID_II_H
#define __PID_II_H
#include "sys.h"




void PIDII_INIT(void);
float PIDII_realize_I(float VAL,float VAL0);
float PIDII_realize_II(float VAL,float VAL0);

#endif










