#include <stdio.h>
#include <stdlib.h>
#include "../common/instruments.h"

#ifndef COMPUTE_NAME
#define COMPUTE_NAME ssa_toeplitz_4x4_baseline
#endif

#ifndef COMPUTE_FLOP_NAME
#define COMPUTE_FLOP_NAME ssa_toeplitz_4x4_baseline_flop
#endif

#ifndef COMPUTE_BYTES_NAME
#define COMPUTE_BYTES_NAME ssa_toeplitz_4x4_baseline_bytes
#endif

// Filter dimensions
static const int R = 4;
static const int Q = 4;

// Hardcoded Toeplitz-style weights (e.g., same along diagonals or symmetric-ish)
static float weights[] = {
    0.25, 0.5,  0.5,  0.25,
    0.5,  1.0,  1.0,  0.5,
    0.5,  1.0,  1.0,  0.5,
    0.25, 0.5,  0.5,  0.25
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
      BEGIN_INSTRUMENTATION;

      float acc = 0.0f;

      for (int q0 = 0; q0 < Q; ++q0) {
        for (int r0 = 0; r0 < R; ++r0) {
          int w_idx = q0 * R + r0;
          float w_val = weights[w_idx];

          int x_i = (i0 + q0) % m0;
          int x_j = (j0 + r0) % n0;
          int x_idx = x_i * n0 + x_j;
          float x_val = x[x_idx];

          acc += w_val * x_val;
        }
      }

      int y_idx = i0 * n0 + j0;
      y[y_idx] = acc;

      END_INSTRUMENTATION;
    }
  }
}
