#include <stdio.h>
#include <stdlib.h>
#include "../common/instruments.h"

#ifndef COMPUTE_NAME
#define COMPUTE_NAME ssa_jacobi2d_21pt_baseline
#endif

#ifndef COMPUTE_FLOP_NAME
#define COMPUTE_FLOP_NAME ssa_jacobi2d_21pt_baseline_flop
#endif

#ifndef COMPUTE_BYTES_NAME
#define COMPUTE_BYTES_NAME ssa_jacobi2d_21pt_baseline_bytes
#endif

double COMPUTE_FLOP_NAME(int m0, int n0) {
  return 21 * 2 * m0 * n0;  // 21 neighbors (no corners) * (1 mul + 1 add)
}

double COMPUTE_BYTES_NAME(int m0, int n0) {
  return (3 * m0 * n0) * sizeof(float); // input + output + scratch
}

void COMPUTE_NAME(int m0, int n0, float *x, float *y) {
  const float coeff = 1.0f / 21.0f;

  for (int i0 = 0; i0 < m0; ++i0) {
    for (int j0 = 0; j0 < n0; ++j0) {
      BEGIN_INSTRUMENTATION;

      float acc = 0.0f;

      for (int di = -2; di <= 2; ++di) {
        for (int dj = -2; dj <= 2; ++dj) {
          // ❗ Skip corners
          if (abs(di) == 2 && abs(dj) == 2) continue;

          int ii = (i0 + di + m0) % m0;
          int jj = (j0 + dj + n0) % n0;

          int idx = ii * n0 + jj;
          acc += x[idx];
        }
      }

      int y_idx = i0 * n0 + j0;
      y[y_idx] = acc * coeff;

      END_INSTRUMENTATION;
    }
  }
}
