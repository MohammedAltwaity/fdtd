#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* M_PI is not in ISO C, so it is missing under -std=c99 / -std=c11
 * and on MSVC. Provide it if the platform did not. */
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "fdtd-macro-tmz.h"
#include "ezinc.h"
#include "config.h"

static double cdtds, ppw = 0;

/* initialize source-function variables */
void ezIncInit(Grid *g) {

  // printf("Enter the points per wavelength for Ricker source: ");
  // scanf(" %lf", &ppw);

  ppw = PPW;

  cdtds = Cdtds;
  return;
}

/* calculate source function at given time and location */
double ezInc(double time, double location) {
  double arg;

  if (ppw <= 0) {
    fprintf(stderr,
           "ezInc: ezIncInit() must be called before ezInc.\n"
           "       Points per wavelength must be positive.\n");
    exit(-1);
  }

  arg = M_PI * ((cdtds * time - location) / ppw - 1.0);
  arg = arg * arg;
  return (1.0 - 2.0 * arg) * exp(-arg);
}