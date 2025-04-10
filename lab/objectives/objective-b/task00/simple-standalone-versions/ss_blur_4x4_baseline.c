#include <stdio.h>
#include <stdlib.h>
#include "../common/instruments.h"

#ifndef COMPUTE_NAME
#define COMPUTE_NAME ss_blur_4x4_baseline
#endif

#ifndef COMPUTE_FLOP_NAME
#define COMPUTE_FLOP_NAME ss_blur_4x4_baseline_flop
#endif

#ifndef COMPUTE_BYTES_NAME
#define COMPUTE_BYTES_NAME ss_blur_4x4_baseline_bytes
#endif

// Dimensions of the Filter
static const int R = 4;
static const int Q = 4;

// weights[(Q)*(R)] in row-major order
static float weights[] = {
    0.33, 0.33, 0.33, 0.33,
    0.33, 0.33, 0.33, 0.33,
    0.33, 0.33, 0.33, 0.33,
    0.33, 0.33, 0.33, 0.33
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
      int y_idx = i0 * n0 + j0;
      float acc = 0.0f;

      for (int q0 = 0; q0 < Q; ++q0) {
        for (int r0 = 0; r0 < R; ++r0) {
          BEGIN_INSTRUMENTATION;
          int x_i = (i0 + q0) % m0;
          int x_j = (j0 + r0) % n0;
          acc += weights[q0 * R + r0] *
          x[x_i * n0 + x_j];


          END_INSTRUMENTATION;
        }
      }
      y[i0 * n0 + j0] = acc;
    }
  }
}
