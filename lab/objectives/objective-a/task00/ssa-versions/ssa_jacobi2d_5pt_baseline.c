#include <stdio.h>
#include <stdlib.h>
#include "../common/instruments.h"

#ifndef COMPUTE_NAME
#define COMPUTE_NAME ssa_jacobi2d_5pt_baseline
#endif

#ifndef COMPUTE_FLOP_NAME
#define COMPUTE_FLOP_NAME ssa_jacobi2d_5pt_baseline_flop
#endif

#ifndef COMPUTE_BYTES_NAME
#define COMPUTE_BYTES_NAME ssa_jacobi2d_5pt_baseline_bytes
#endif

double COMPUTE_FLOP_NAME(int m0, int n0) {
  return 5 * 2 * m0 * n0;  // 5 adds, 1 multiply per output element
}

double COMPUTE_BYTES_NAME(int m0, int n0) {
  return (3 * m0 * n0 + 5) * sizeof(float);  // input + output + scratch + filter overhead
}

void COMPUTE_NAME(int m0, int n0, float *x, float *y) {
  for (int i0 = 0; i0 < m0; ++i0) {
    for (int j0 = 0; j0 < n0; ++j0) {
      BEGIN_INSTRUMENTATION;

      int i_up    = (i0 - 1 + m0) % m0;
      int i_down  = (i0 + 1) % m0;
      int j_left  = (j0 - 1 + n0) % n0;
      int j_right = (j0 + 1) % n0;

      int idx_mid   = i0 * n0 + j0;
      int idx_up    = i_up * n0 + j0;
      int idx_down  = i_down * n0 + j0;
      int idx_left  = i0 * n0 + j_left;
      int idx_right = i0 * n0 + j_right;

      float acc = x[idx_mid] + x[idx_up] + x[idx_down] + x[idx_left] + x[idx_right];
      y[idx_mid] = acc * 0.2f;

      END_INSTRUMENTATION;
    }
  }
}
