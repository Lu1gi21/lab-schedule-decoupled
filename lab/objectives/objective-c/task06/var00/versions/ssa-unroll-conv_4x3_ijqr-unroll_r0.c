
#include <stdio.h>
#include <stdlib.h>

#include "../../../../../lab_initial/instruments.h"

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
static const int R = 3;
static const int Q = 4;
static float weights[] = {-1.1,-1.1,1.2,-2.1,-1.1,-2.1,-1.2,2.2,-2.1,0.1,0.2,1.2,};

double COMPUTE_FLOP_NAME( int m0, int n0 )
{
  return 2*m0*n0*(Q)*(R);
}

double COMPUTE_BYTES_NAME( int m0, int n0 )
{
  return (3*(m0*n0)+ ((Q)*(R)))*sizeof(float);
}

void COMPUTE_NAME( int m0,
           int n0,
           float *x,
           float *y )

{
  // BEGIN_INSTRUMENTATION; // func:compute_name

for( int i0 = 0; i0 < m0; i0++) {
for( int j0 = 0; j0 < n0; j0++) {
for( int q0 = 0; q0 < Q; q0++) {
    { // r0=0
      BEGIN_INSTRUMENTATION; // loop:q0
      for( int r0 = 0; r0 < R; r0++) {
        int   w_qr_0_offset_0 = 0*(R);
                    int   w_qr_0_idx_0    = w_qr_0_offset_0 + r0;
                    float *w_qr_0_addr_0  = &weights[w_qr_0_idx_0];
                    float w_qr_0        = *w_qr_0_addr_0;
        
                    int    iq_shift_0    = 0 + i0;
                    int    iq_row_wrap_0 = iq_shift_0 % m0;
                    int    jr_shift_0    = r0 + j0;
                    int    jr_col_wrap_0 = jr_shift_0 % n0;
                    int    x_iqjr_0_idx_0  = iq_row_wrap_0 * n0 + jr_col_wrap_0;
                    float *x_iqjr_0_addr_0 = &x[x_iqjr_0_idx_0];
                    float  x_iqjr_0      = *x_iqjr_0_addr_0;
        
                    int    y_ij_idx    = i0*n0 + j0;
                    float *y_ij_addr   = &y[y_ij_idx];
                
                    float y_ij      = *y_ij_addr;
                    float res_wx_0    = w_qr_0 * x_iqjr_0;
                    float acc_y_ij_0  = y_ij + res_wx_0;
                    *y_ij_addr      = acc_y_ij_0;
      }
      END_INSTRUMENTATION; // loop:q0
    }

    { // r0=1
      BEGIN_INSTRUMENTATION; // loop:q0
      for( int r0 = 0; r0 < R; r0++) {
        int   w_qr_1_offset_1 = 1*(R);
                    int   w_qr_1_idx_1    = w_qr_1_offset_1 + r0;
                    float *w_qr_1_addr_1  = &weights[w_qr_1_idx_1];
                    float w_qr_1        = *w_qr_1_addr_1;
        
                    int    iq_shift_1    = 1 + i0;
                    int    iq_row_wrap_1 = iq_shift_1 % m0;
                    int    jr_shift_1    = r0 + j0;
                    int    jr_col_wrap_1 = jr_shift_1 % n0;
                    int    x_iqjr_1_idx_1  = iq_row_wrap_1 * n0 + jr_col_wrap_1;
                    float *x_iqjr_1_addr_1 = &x[x_iqjr_1_idx_1];
                    float  x_iqjr_1      = *x_iqjr_1_addr_1;
        
                    int    y_ij_idx    = i0*n0 + j0;
                    float *y_ij_addr   = &y[y_ij_idx];
                
                    float y_ij      = *y_ij_addr;
                    float res_wx_1    = w_qr_1 * x_iqjr_1;
                    float acc_y_ij_1  = y_ij + res_wx_1;
                    *y_ij_addr      = acc_y_ij_1;
      }
      END_INSTRUMENTATION; // loop:q0
    }

    { // r0=2
      BEGIN_INSTRUMENTATION; // loop:q0
      for( int r0 = 0; r0 < R; r0++) {
        int   w_qr_2_offset_2 = 2*(R);
                    int   w_qr_2_idx_2    = w_qr_2_offset_2 + r0;
                    float *w_qr_2_addr_2  = &weights[w_qr_2_idx_2];
                    float w_qr_2        = *w_qr_2_addr_2;
        
                    int    iq_shift_2    = 2 + i0;
                    int    iq_row_wrap_2 = iq_shift_2 % m0;
                    int    jr_shift_2    = r0 + j0;
                    int    jr_col_wrap_2 = jr_shift_2 % n0;
                    int    x_iqjr_2_idx_2  = iq_row_wrap_2 * n0 + jr_col_wrap_2;
                    float *x_iqjr_2_addr_2 = &x[x_iqjr_2_idx_2];
                    float  x_iqjr_2      = *x_iqjr_2_addr_2;
        
                    int    y_ij_idx    = i0*n0 + j0;
                    float *y_ij_addr   = &y[y_ij_idx];
                
                    float y_ij      = *y_ij_addr;
                    float res_wx_2    = w_qr_2 * x_iqjr_2;
                    float acc_y_ij_2  = y_ij + res_wx_2;
                    *y_ij_addr      = acc_y_ij_2;
      }
      END_INSTRUMENTATION; // loop:q0
    }


    } // close j0 loop
  } // close i0 loop
}

