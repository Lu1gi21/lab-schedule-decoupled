sec_one = """#include <stdio.h>
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

// Dimensions of the Filter
static const int R = 3;
static const int Q = 4;
static float weights[] =
"""


weights = """{
1
};"""

sec_two = """
double COMPUTE_FLOP_NAME( int m0, int n0 )
{
  return 2*m0*n0*(Q)*(R);
}

/*
  1 read           for x vector   (m*n)
  1 read + 1 write for y vector 2*(m*n)
  1 read for the weights (Q*R)
*/
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
"""

loop_i = """
    for( int i0 = 0; i0 < m0; ++i0 ){
      // BEGIN_INSTRUMENTATION; // loop:i0
"""

loop_j ="""
    for( int j0 = 0; j0 < n0; ++j0 ){
	    // BEGIN_INSTRUMENTATION; // loop:j0
"""

loop_q = """
	for( int q0 = 0; q0 < (Q); ++q0 ){
	    // BEGIN_INSTRUMENTATION; // loop:q0
"""	

loop_r = """        
    for( int r0 = 0; r0 < (R); ++r0 ){
		BEGIN_INSTRUMENTATION; // loop:r0
"""

computations = """
	    	int   w_qr_offset = q0*(R);
    		int   w_qr_idx    = w_qr_offset + r0;
	    	float *w_qr_addr  = &weights[w_qr_idx]; // &weights + w_qr_idx
		    float w_qr        = *w_qr_addr;                   // read weight at (q,r)

    		int    iq_shift    = q0+i0;
	    	int    iq_row_wrap = iq_shift % m0;
		    int    jr_shift    = r0+j0;
    		int    jr_col_wrap = jr_shift % n0;
	    	int    iq_offset   = iq_row_wrap * n0;
		    int    x_iqjr_idx  = iq_offset + jr_col_wrap;
    		float *x_iqjr_addr = &x[x_iqjr_idx];
	    	float  x_iqjr      = *x_iqjr_addr; // read x at ((i+q),(j+r))

		    int    y_ij_offset = i0*n0;
		    int    y_ij_idx    = y_ij_offset+j0;
		    float *y_ij_addr   = &y[y_ij_idx];
		
    		float y_ij      = *y_ij_addr;                          // read y at (i,j)
	    	float res_wx    = w_qr * x_iqjr;                        // multiply x by the weight
		    float acc_y_ij  = y_ij + res_wx;                        // accumulate the result
		    *y_ij_addr      = acc_y_ij;                             // write the result back
"""

loop_ends = """            
		END_INSTRUMENTATION; // loop:r0
	      }
	    // END_INSTRUMENTATION; // loop:q0
	  }
	  // END_INSTRUMENTATION; // loop:j0
	}
      // END_INSTRUMENTATION; // loop:i0
    }
  // END_INSTRUMENTATION; // func:compute_name
  

}
"""

def write_to_file(path):
    out_file = open(path, 'a')

    out_file.seek(0)
    out_file.truncate()

    out_file.write(sec_one)
    out_file.write(weights)
    out_file.write(sec_two)
    out_file.write(loop_i)
    out_file.write(loop_j)
    out_file.write(loop_q)
    out_file.write(loop_r)
    out_file.write(computations)
    out_file.write(loop_ends)

    out_file.close()



def main():
    write_to_file("var00.c")

if __name__ == '__main__':
    main()