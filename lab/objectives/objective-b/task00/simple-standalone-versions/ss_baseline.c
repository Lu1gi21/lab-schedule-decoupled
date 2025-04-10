/*
  This is the SSA version of the baseline implementation.
  Each operation is broken down into explicit steps with clear variable assignments.

  - richard.m.veras@ou.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include "../common/instruments.h"

#ifndef COMPUTE_NAME
#define COMPUTE_NAME ss_baseline
#endif

#ifndef COMPUTE_FLOP_NAME
#define COMPUTE_FLOP_NAME ss_baseline_flop
#endif

#ifndef COMPUTE_BYTES_NAME
#define COMPUTE_BYTES_NAME ss_baseline_bytes
#endif

// Dimensions of the Filter
static const int R = 4;
static const int Q = 3;

// Weights array in row major order
static float weights[] =
  //r=0    1     2     3
  {-1.1, -1.1,  1.2, -2.1,  // q=0
   -1.1, -2.1, -1.2,  2.2,  // q=1
   -2.1,  0.1,  0.2,  1.2}; // q=2

double COMPUTE_FLOP_NAME(int m0, int n0) {
  return 2*m0*n0*(Q)*(R);
}

double COMPUTE_BYTES_NAME(int m0, int n0) {
  return (3*(m0*n0)+ ((Q)*(R)))*sizeof(float);
}

void COMPUTE_NAME(int m0, int n0, float *x, float *y) {
  for(int i0 = 0; i0 < m0; ++i0) {
    for(int j0 = 0; j0 < n0; ++j0) {
      for(int q0 = 0; q0 < (Q); ++q0) {
        for(int r0 = 0; r0 < (R); ++r0) {
          BEGIN_INSTRUMENTATION; // loop:r0
          
          y[i0 * n0 + j0] += weights[q0][r0] *
              x[((q0 + i0) % m0) * n0 + ((r0 + j0) % n0)];
          
          END_INSTRUMENTATION; // loop:r0
        }
      }
    }
  }
} 