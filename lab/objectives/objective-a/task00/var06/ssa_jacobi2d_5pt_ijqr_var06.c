#include <stdio.h>
#include <stdlib.h>
#include "../common/instruments.h"

#ifndef COMPUTE_NAME
#define COMPUTE_NAME ssa_jacobi2d_5pt_ijqr_var06
#endif

#ifndef COMPUTE_FLOP_NAME
#define COMPUTE_FLOP_NAME ssa_jacobi2d_5pt_ijqr_var06_flop
#endif

#ifndef COMPUTE_BYTES_NAME
#define COMPUTE_BYTES_NAME ssa_jacobi2d_5pt_ijqr_var06_bytes
#endif

double COMPUTE_FLOP_NAME(int m0, int n0) {
  return 5 * 2 * m0 * n0;  // 5-point stencil: 5 adds, 1 mul per output
}

double COMPUTE_BYTES_NAME(int m0, int n0) {
  return (3 * m0 * n0 + 5) * sizeof(float);  // input, output, scratch + 5 neighbors
}

void COMPUTE_NAME(int m0, int n0, float *x, float *y) {
  for (int i0 = 0; i0 < m0; ++i0) {
    for (int j0 = 0; j0 < n0; ++j0) {
      BEGIN_INSTRUMENTATION;

      int up    = ((i0 - 1 + m0) % m0) * n0 + j0;
      int down  = ((i0 + 1) % m0) * n0 + j0;
      int left  = i0 * n0 + (j0 - 1 + n0) % n0;
      int right = i0 * n0 + (j0 + 1) % n0;
      int mid   = i0 * n0 + j0;

      float acc = x[up] + x[down] + x[left] + x[right] + x[mid];
      y[mid] = acc * 0.2f;

      END_INSTRUMENTATION;
    }
  }
}
