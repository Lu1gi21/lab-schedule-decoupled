/*
  This is the SSA version of the complex split i with interchange implementation.
  Each operation is broken down into explicit steps with clear variable assignments.

  - richard.m.veras@ou.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include "instruments.h"

#ifndef COMPUTE_NAME
#define COMPUTE_NAME ssa_complex_split_i
#endif

#ifndef COMPUTE_FLOP_NAME
#define COMPUTE_FLOP_NAME ssa_complex_split_i_flop
#endif

#ifndef COMPUTE_BYTES_NAME
#define COMPUTE_BYTES_NAME ssa_complex_split_i_bytes
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
  for(int i0_o = 0; i0_o < m0; i0_o+=4) {
    for(int j0 = 0; j0 < n0; ++j0) {
      for(int i0_i = 0; i0_i < 4; ++i0_i) {
        for(int q0 = 0; q0 < (Q); ++q0) {
          BEGIN_INSTRUMENTATION; // loop:q0
          
          // Common y array access computation
          int y_ij_offset = (i0_o + i0_i) * n0;
          int y_ij_idx = y_ij_offset + j0;
          float *y_ij_addr = &y[y_ij_idx];
          float y_ij = *y_ij_addr;
          
          // r0 = 0
          {
            // Compute weight access for r0=0
            int w_qr_offset = q0*(R);
            int w_qr_idx = w_qr_offset + 0;
            float *w_qr_addr = &weights[w_qr_idx];
            float w_qr = *w_qr_addr;
            
            // Compute x array access for r0=0
            int iq_shift = q0 + (i0_o + i0_i);
            int iq_row_wrap = iq_shift % m0;
            int jr_shift = 0 + j0;
            int jr_col_wrap = jr_shift % n0;
            int x_row_offset = iq_row_wrap * n0;
            int x_iqjr_idx = x_row_offset + jr_col_wrap;
            float *x_iqjr_addr = &x[x_iqjr_idx];
            float x_iqjr = *x_iqjr_addr;
            
            float res_wx = w_qr * x_iqjr;
            y_ij += res_wx;
          }
          
          // r0 = 1
          {
            // Compute weight access for r0=1
            int w_qr_offset = q0*(R);
            int w_qr_idx = w_qr_offset + 1;
            float *w_qr_addr = &weights[w_qr_idx];
            float w_qr = *w_qr_addr;
            
            // Compute x array access for r0=1
            int iq_shift = q0 + (i0_o + i0_i);
            int iq_row_wrap = iq_shift % m0;
            int jr_shift = 1 + j0;
            int jr_col_wrap = jr_shift % n0;
            int x_row_offset = iq_row_wrap * n0;
            int x_iqjr_idx = x_row_offset + jr_col_wrap;
            float *x_iqjr_addr = &x[x_iqjr_idx];
            float x_iqjr = *x_iqjr_addr;
            
            float res_wx = w_qr * x_iqjr;
            y_ij += res_wx;
          }
          
          // r0 = 2
          {
            // Compute weight access for r0=2
            int w_qr_offset = q0*(R);
            int w_qr_idx = w_qr_offset + 2;
            float *w_qr_addr = &weights[w_qr_idx];
            float w_qr = *w_qr_addr;
            
            // Compute x array access for r0=2
            int iq_shift = q0 + (i0_o + i0_i);
            int iq_row_wrap = iq_shift % m0;
            int jr_shift = 2 + j0;
            int jr_col_wrap = jr_shift % n0;
            int x_row_offset = iq_row_wrap * n0;
            int x_iqjr_idx = x_row_offset + jr_col_wrap;
            float *x_iqjr_addr = &x[x_iqjr_idx];
            float x_iqjr = *x_iqjr_addr;
            
            float res_wx = w_qr * x_iqjr;
            y_ij += res_wx;
          }
          
          // r0 = 3
          {
            // Compute weight access for r0=3
            int w_qr_offset = q0*(R);
            int w_qr_idx = w_qr_offset + 3;
            float *w_qr_addr = &weights[w_qr_idx];
            float w_qr = *w_qr_addr;
            
            // Compute x array access for r0=3
            int iq_shift = q0 + (i0_o + i0_i);
            int iq_row_wrap = iq_shift % m0;
            int jr_shift = 3 + j0;
            int jr_col_wrap = jr_shift % n0;
            int x_row_offset = iq_row_wrap * n0;
            int x_iqjr_idx = x_row_offset + jr_col_wrap;
            float *x_iqjr_addr = &x[x_iqjr_idx];
            float x_iqjr = *x_iqjr_addr;
            
            float res_wx = w_qr * x_iqjr;
            y_ij += res_wx;
          }
          
          // Write back accumulated result
          *y_ij_addr = y_ij;
          
          END_INSTRUMENTATION; // loop:q0
        }
      }
    }
  }
} 