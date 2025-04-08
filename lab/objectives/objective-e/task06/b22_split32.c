
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

static const int R = 2;
static const int Q = 2;
static float weights[] = {
  0.33, 0.33,
  0.33, 0.33,
};


double COMPUTE_BYTES_NAME( int m0, int n0 ) {
  return (3*(m0*n0)+ ((2)*(2)))*sizeof(float);
}


double COMPUTE_FLOP_NAME( int m0, int n0 ) {
  return 2*m0*n0*(2)*(2);
}

void COMPUTE_NAME (int m0, int n0, float *x, float *y) {
for (int i0_o = 0; i0_o < m0; i0_o += 32) {
for (int r0 = 0; r0 < (R); r0 += 1) {
for (int j0 = 0; j0 < n0; j0 += 1) {
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 0);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 0) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 1);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 1) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 2);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 2) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 3);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 3) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 4);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 4) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 5);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 5) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 6);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 6) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 7);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 7) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 8);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 8) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 9);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 9) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 10);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 10) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 11);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 11) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 12);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 12) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 13);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 13) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 14);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 14) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 15);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 15) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 16);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 16) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 17);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 17) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 18);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 18) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 19);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 19) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 20);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 20) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 21);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 21) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 22);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 22) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 23);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 23) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 24);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 24) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 25);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 25) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 26);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 26) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 27);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 27) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 28);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 28) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 29);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 29) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 30);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 30) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 0 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 0 + (i0_o + 31);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 31) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 0);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 0) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 1);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 1) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 2);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 2) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 3);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 3) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 4);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 4) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 5);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 5) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 6);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 6) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 7);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 7) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 8);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 8) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 9);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 9) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 10);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 10) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 11);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 11) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 12);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 12) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 13);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 13) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 14);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 14) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 15);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 15) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 16);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 16) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 17);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 17) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 18);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 18) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 19);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 19) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 20);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 20) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 21);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 21) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 22);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 22) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 23);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 23) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 24);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 24) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 25);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 25) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 26);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 26) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 27);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 27) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 28);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 28) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 29);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 29) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 30);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 30) * n0;
    int y_ij_idx = y_ij_offset + j0;
    float *y_ij_addr = &y[y_ij_idx];
    float y_ij = *y_ij_addr;
    float res_wx = w_qr * x_iqjr;
    float acc_y_ij = y_ij + res_wx;
    *y_ij_addr = acc_y_ij;
    END_INSTRUMENTATION;
    }
    {
    BEGIN_INSTRUMENTATION;
    int w_qr_offset = 1 * (R);
    int w_qr_idx = w_qr_offset + r0;
    float *w_qr_addr = &weights[w_qr_idx];
    float w_qr = *w_qr_addr;
    int iq_shift = 1 + (i0_o + 31);
    int iq_row_wrap = iq_shift % m0;
    int jr_shift = r0 + j0;
    int jr_col_wrap = jr_shift % n0;
    int iq_offset = iq_row_wrap * n0;
    int x_iqjr_idx = iq_offset + jr_col_wrap;
    float *x_iqjr_addr = &x[x_iqjr_idx];
    float x_iqjr = *x_iqjr_addr;
    int y_ij_offset = (i0_o + 31) * n0;
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
