#ifndef __PID_I_H
#define __PID_I_H
#include "sys.h"




void PIDI_INIT(void);
float PIDI_realize_I(float VAL,float VAL0);
float PIDI_realize_II(float VAL,float VAL0);

#endif










