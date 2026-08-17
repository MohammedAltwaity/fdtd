/* Header file to accompany ezinc.c */

#ifndef _EZINC_H
#define _EZINC_H
#include "fdtd-grid1.h"


void ezIncInit(Grid *g);
double ezInc(double time, double location);
#endif /* matches #ifndef _EZINC2_H */