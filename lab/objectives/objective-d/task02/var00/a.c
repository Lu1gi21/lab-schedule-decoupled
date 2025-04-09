
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

   for( int i0_o = 0; i0_o < m0; i0_o+=2) {
   for( int i0_i = 0; i0_i < 2; i0_i+=1) {
   for( int j0_o = 0; j0_o < n0; j0_o+=2) {
   for( int j0_i = 0; j0_i < 2; j0_i+=1) {
   for( int q0_o = 0; q0_o < Q; q0_o+=2) {
   for( int q0_i = 0; q0_i < 2; q0_i+=1) {
   for( int r0_o = 0; r0_o < R; r0_o+=2) {
   for( int r0_i = 0; r0_i < 2; r0_i+=1) {

            int   w_qr_offset = (q0_o + q0_i)*(R);
            int   w_qr_idx    = w_qr_offset + (r0_o + r0_i);
            float *w_qr_addr  = &weights[w_qr_idx]; // &weights + w_qr_idx
            float w_qr        = *w_qr_addr;                   // read weight at (q,r)

            int    iq_shift    = (q0_o + q0_i)+(i0_o + i0_i);
            int    iq_row_wrap = iq_shift % m0;
            int    jr_shift    = (r0_o + r0_i)+(j0_o + j0_i);
            int    jr_col_wrap = jr_shift % n0;
            int    iq_offset   = iq_row_wrap * n0;
            int    x_iqjr_idx  = iq_offset + jr_col_wrap;
            float *x_iqjr_addr = &x[x_iqjr_idx];
            float  x_iqjr      = *x_iqjr_addr; // read x at ((i+q),(j+r))

            int    y_ij_offset = (i0_o + i0_i)*n0;
            int    y_ij_idx    = y_ij_offset+(j0_o + j0_i);
            float *y_ij_addr   = &y[y_ij_idx];
        
            float y_ij      = *y_ij_addr;                          // read y at (i,j)
            float res_wx    = w_qr * x_iqjr;                        // multiply x by the weight
            float acc_y_ij  = y_ij + res_wx;                        // accumulate the result
            *y_ij_addr      = acc_y_ij;                             // write the result back

}
}
}
}
}
}
}
}
}