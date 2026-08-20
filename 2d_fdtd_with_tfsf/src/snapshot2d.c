#include <stdio.h>
#include <stdlib.h>
#include "fdtd-macro-tmz.h"
#include "config.h"

static int temporalStride = -2, frame = 0, startTime,
  startNodeX, endNodeX, spatialStrideX,
  startNodeY, endNodeY, spatialStrideY;

  //initializing the base name instead of promping the user
static char basename[80] = "sim";

void snapshotInit2d(Grid *g) {
  
  int choice;
  
  // printf("Do you want 2D snapshots? (1=yes, 0=no) ");
  // scanf("%d", &choice);
  choice = CHOICE;


  if (choice == 0) {
    temporalStride = -1;
    return;
  }

  printf("Duration of simulation is %d steps.\n\n", MaxTime);

  printf("In x direction grid has %d total nodes"
        " (ranging from 0 to %d).\n", SizeX, SizeX - 1);

  // printf("Enter start time and temporal stride: ");
  // scanf(" %d %d", &startTime, &temporalStride);


  startTime = START_TIME;
  temporalStride = TEMPORAL_STRIDE;


  // printf("In x direction grid has %d total nodes"
  //       " (ranging from 0 to %d).\n", SizeX, SizeX - 1);

  // printf("Enter first node, last node, and spatial stride: ");
  // scanf(" %d %d %d", &startNodeX, &endNodeX, &spatialStrideX);

  startNodeX = XFIRST_NODE;
  endNodeX = XLAST_NODE;
  spatialStrideX = XSPACIAL_STRIDE;
  


  // printf("In y direction grid has %d total nodes"
  //       " (ranging from 0 to %d).\n", SizeY, SizeY - 1);
  // printf("Enter first node, last node, and spatial stride: ");
  // scanf(" %d %d %d", &startNodeY, &endNodeY, &spatialStrideY);

   startNodeY = YFIRST_NODE;
   endNodeY = YLAST_NODE;
   spatialStrideY = YSPACIAL_STRIDE;



  // printf("Enter the base name: ");
  // scanf(" %s", basename);
 

  

  return;
}

void snapshot2d(Grid *g) {
  int mm, nn;
  float dim1, dim2, temp;
  char filename[100];
  FILE *out;

  /* ensure temporal stride set to a reasonable value */
  if (temporalStride == -1) {
    return;
  } if (temporalStride < -1) {
    fprintf(stderr,
      "snapshot2d: snapshotInit2d must be called before snapshot.\n"
      "            Temporal stride must be set to positive value.\n");
    exit(-1);
  }

  /* get snapshot if temporal conditions met */
  if (Time >= startTime && 
      (Time - startTime) % temporalStride == 0) {
    snprintf(filename, sizeof(filename), "%s.%d",
	     basename, frame++);
    out = fopen(filename, "wb");
    if (out == NULL) {
      perror(filename);
      exit(-1);
    }

    /* write dimensions to output file -- 
     * express dimensions as floats */
    dim1 = (endNodeX - startNodeX) / spatialStrideX + 1;
    dim2 = (endNodeY - startNodeY) / spatialStrideY + 1;
    fwrite(&dim1, sizeof(float), 1, out);  
    fwrite(&dim2, sizeof(float), 1, out);  

    /* write remaining data */
    for (nn = endNodeY; nn >= startNodeY; nn -= spatialStrideY)   
      for (mm = startNodeX; mm <= endNodeX; mm += spatialStrideX) {
	temp = (float)Ez(mm, nn); // store data as a float   
	fwrite(&temp, sizeof(float), 1, out); // write the float
      }

    fclose(out);  // close file
  }

  return;
}