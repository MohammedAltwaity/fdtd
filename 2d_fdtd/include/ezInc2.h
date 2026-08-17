/* Header file to accompany ezinc2.c */

#ifndef _EZINC2_H
#define _EZINC2_H

#include "fdtd-grid1.h"


void ezIncInit(Grid *g);
double ezInc(double time, double location);

#endif /* matches #ifndef _EZINC2_H */