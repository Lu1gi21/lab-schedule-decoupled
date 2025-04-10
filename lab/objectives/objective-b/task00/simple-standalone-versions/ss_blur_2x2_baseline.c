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
        int y_idx = i0 * n0 + j0;
        float acc = 0.0f;
  
        for (int q0 = 0; q0 < Q; ++q0) {
          for (int r0 = 0; r0 < R; ++r0) {
            BEGIN_INSTRUMENTATION;
  
            acc += weights[q0 * R + r0] *
                    X[((i0 + q0) % m0) * n0 + ((j0 + r0) % n0)];
  
            END_INSTRUMENTATION;
          }
        }
        y[i0 * n0 + j0] = acc; // store result _after_ accumulation
      }
    }
    // for (int i = 0; i < m0 * n0; ++i) {
    //     printf("y[%d] = %f\n", i, y[i]);
    // }    
  }
  