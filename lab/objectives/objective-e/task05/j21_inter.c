
#include <stdio.h>
#include <stdlib.h>

#include "instruments.h"

#ifndef COMPUTE_NAME
#define COMPUTE_NAME baseline
#endif

#ifndef COMPUTE_FLOP_NAME
#define COMPUTE_FLOP_NAME baseline_flop
#endif

#ifndef COMPUTE_BYTES_NAME
#define COMPUTE_BYTES_NAME baseline_bytes
#endif

static const int R = 9;
static const int Q = 9;
static float weights[] = {
  0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 0.0, 0.2, 0.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 0.0, 0.4, 0.0, 0.0, 0.0, 0.0,
  0.1, 0.2, 0.3, 0.4, 1.0, 0.4, 0.3, 0.2, 0.1,
  0.0, 0.0, 0.0, 0.0, 0.4, 0.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 0.0, 0.3, 0.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 0.0, 0.2, 0.0, 0.0, 0.0, 0.0,
  0.0, 0.0, 0.0, 0.0, 0.1, 0.0, 0.0, 0.0, 0.0,
};


double COMPUTE_BYTES_NAME( int m0, int n0 ) {
  return (3*(m0*n0)+ ((9)*(9)))*sizeof(float);
}


double COMPUTE_FLOP_NAME( int m0, int n0 ) {
  return 2*m0*n0*(9)*(9);
}

void COMPUTE_NAME (int m0, int n0, float *x, float *y) {
for (int i0 = 0; i0 < m0; i0 += 1) {
for (int r0 = 0; r0 < (R); r0 += 1) {
for (int j0 = 0; j0 < n0; j0 += 1) {
for (int q0 = 0; q0 < (Q); q0 += 1) {
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = q0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = q0 + i0;
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = i0 * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
}
}
}
}
}
