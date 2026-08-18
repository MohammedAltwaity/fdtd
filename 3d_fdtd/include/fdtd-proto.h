#ifndef _FDTD_PROTO2_H
#define _FDTD_PROTO2_H 

#include "fdtd-grid1.h"

/* Function prototypes */
void abcInit(Grid *g);
void abc(Grid *g);

void gridInit1d(Grid *g); 
void gridInit(Grid *g);

void snapshotInit2d(Grid *g);
void snapshot2d(Grid *g);

void tfsfInit(Grid *g);
void tfsfUpdate(Grid *g); 

//from old 2
void updateE2d(Grid *g);
void updateH2d(Grid *g);

//for the 3d case
void updateH(Grid *g);
void updateE(Grid *g);


void snapshot3dInit(Grid *g);
void snapshot3d(Grid *g);



#endif