#include <math.h>
#include "fdtd-macro-tmz.h"
#include "fdtd-alloc1.h"
#include "fdtd-proto1.h"
#include "config.h"

// This is from the page 196 Schneider book

//we used 2d array for the hx and hy becuase the exist at each node in the grid[vecotr field ahs compoent in all points in sapce]
void gridInit(Grid *g) {
  double imp0 = 377.0;
  int mm, nn;

  Type = tmZGrid;
  SizeX = 101;     // x size of domain
  SizeY = 81;      // y size of domain
  MaxTime = 300;   // duration of simulation
  Cdtds = 1.0 / sqrt(2.0); // Courant number

  /* Memory allocation */
  ALLOC_2D(g->hx,   SizeX,     SizeY - 1, double);
  ALLOC_2D(g->chxh, SizeX,     SizeY - 1, double);
  ALLOC_2D(g->chxe, SizeX,     SizeY - 1, double);

  ALLOC_2D(g->hy,   SizeX - 1, SizeY,     double);
  ALLOC_2D(g->chyh, SizeX - 1, SizeY,     double);
  ALLOC_2D(g->chye, SizeX - 1, SizeY,     double);

  ALLOC_2D(g->ez,   SizeX,     SizeY,     double);
  ALLOC_2D(g->ceze, SizeX,     SizeY,     double);
  ALLOC_2D(g->cezh, SizeX,     SizeY,     double);

  /* Set electric-field update coefficients */
  for (mm = 0; mm < SizeX; mm++) {
    for (nn = 0; nn < SizeY; nn++) {
      Ceze(mm, nn) = 1.0;
      Cezh(mm, nn) = Cdtds * imp0;
    }
  }

  /* Set magnetic-field update coefficients */
  for (mm = 0; mm < SizeX; mm++) {
    for (nn = 0; nn < SizeY - 1; nn++) {
      Chxh(mm, nn) = 1.0;
      Chxe(mm, nn) = Cdtds / imp0;
    }
  }

  for (mm = 0; mm < SizeX - 1; mm++) {
    for (nn = 0; nn < SizeY; nn++) {
      Chyh(mm, nn) = 1.0;
      Chye(mm, nn) = Cdtds / imp0;
    }
  }


    /* =========================================================================
   * PEC (Perfect Electric Conductor) PLATE INSERTION
   * Set Ez update coefficients to 0 along a vertical line.
   * ========================================================================= */
#if 1  /* CHANGE TO 0 TO ROLL BACK TO FREE-SPACE GRID (NO PEC) */
  /* Center X inside the Total Field box: (40 + 75) / 2 = 57 */
  mm = (TF_FIRST_NODE_X + TF_LAST_NODE_X) / 2; 

  /* Span Y inside the Total Field box with a 5-cell margin off the TF boundary */
  int margin_y = 5; 
  for (nn = TF_FIRST_NODE_Y + margin_y; nn <= TF_LAST_NODE_Y - margin_y; nn++) { 
    Ceze(mm, nn) = 0.0;
    Cezh(mm, nn) = 0.0;
  }
#endif


  return;
}