#include <stdio.h>
#include <stdlib.h>
#include "../common/instruments.h"

#ifndef COMPUTE_NAME
#define COMPUTE_NAME baseline
#endif

#ifndef COMPUTE_FLOP_NAME
#define COMPUTE_FLOP_NAME baseline_flop
#endif

#ifndef COMPUTE_BYTES_NAME
#define COMPUTE_BYTES_NAME baseline_bytes
#endif

// Dimensions of the Filter
static const int R = 2;
static const int Q = 2;

// weights[(Q)*(R)] in row-major order
static float weights[] = {
    0.25, 0.25,
    0.25, 0.25
};

double COMPUTE_FLOP_NAME(int m0, int n0) {
  return 2 * m0 * n0 * Q * R;
}

double COMPUTE_BYTES_NAME(int m0, int n0) {
  return (3 * m0 * n0 + Q * R) * sizeof(float);
}

void COMPUTE_NAME(int m0, int n0, float *x, float *y) {
  for (int i0 = 0; i0 < m0; ++i0) {
    for (int j0 = 0; j0 < n0; ++j0) {
      int y_offset = i0 * n0;
      int y_idx = y_offset + j0;
      float y_val = y[y_idx];

      for (int q0 = 0; q0 < Q; ++q0) {
        for (int r0 = 0; r0 < R; ++r0) {
          BEGIN_INSTRUMENTATION;
      
          int w_idx = q0 * R + r0;
          float *w_ptr = &weights[w_idx];
          float w_val = *w_ptr;
      
          int iq = q0 + i0;
          int iq_wrap = iq % m0;
          int jr = r0 + j0;
          int jr_wrap = jr % n0;
      
          int x_idx = iq_wrap * n0 + jr_wrap;
          float *x_ptr = &x[x_idx];
          float x_val = *x_ptr;
      
          int y_idx = i0 * n0 + j0;
          float *y_ptr = &y[y_idx];
          float y_val = *y_ptr;
      
          float prod = w_val * x_val;
          float result = y_val + prod;
      
          *y_ptr = result;
      
          END_INSTRUMENTATION;
        }
      }      
    }
  }
}

