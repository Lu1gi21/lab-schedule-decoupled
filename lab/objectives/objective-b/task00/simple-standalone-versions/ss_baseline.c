/*
  This is the SSA version of the baseline implementation.
  Each operation is broken down into explicit steps with clear variable assignments.

  - richard.m.veras@ou.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include "../common/instruments.h"

#ifndef COMPUTE_NAME
#define COMPUTE_NAME ssa_baseline
#endif

#ifndef COMPUTE_FLOP_NAME
#define COMPUTE_FLOP_NAME ssa_baseline_flop
#endif

#ifndef COMPUTE_BYTES_NAME
#define COMPUTE_BYTES_NAME ssa_baseline_bytes
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
          
          // Compute weight access
          int w_qr_offset = q0*(R);
          int w_qr_idx = w_qr_offset + r0;
          float *w_qr_addr = &weights[w_qr_idx];
          float w_qr = *w_qr_addr;
          
          // Compute x array access
          int iq_shift = q0 + i0;
          int iq_row_wrap = iq_shift % m0;
          int jr_shift = r0 + j0;
          int jr_col_wrap = jr_shift % n0;
          int x_row_offset = iq_row_wrap * n0;
          int x_iqjr_idx = x_row_offset + jr_col_wrap;
          float *x_iqjr_addr = &x[x_iqjr_idx];
          float x_iqjr = *x_iqjr_addr;
          
          // Compute y array access and update
          int y_ij_offset = i0 * n0;
          int y_ij_idx = y_ij_offset + j0;
          float *y_ij_addr = &y[y_ij_idx];
          float y_ij = *y_ij_addr;
          float res_wx = w_qr * x_iqjr;
          float acc_y_ij = y_ij + res_wx;
          *y_ij_addr = acc_y_ij;
          
          END_INSTRUMENTATION; // loop:r0
        }
      }
    }
  }
} 