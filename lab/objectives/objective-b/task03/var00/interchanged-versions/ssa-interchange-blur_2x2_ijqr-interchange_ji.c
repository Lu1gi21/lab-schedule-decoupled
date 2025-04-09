
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
static const int R = 2;
static const int Q = 2
;

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

float weights[] = {
	0.33, 0.33, 
	0.33, 0.33
};

  // BEGIN_INSTRUMENTATION; // func:compute_name
  for( int j0 = 0; j0 < n0; ++j0 )
    {
      // BEGIN_INSTRUMENTATION; // loop:j0
      for( int i0 = 0; i0 < m0; ++i0 )
	{
	  // BEGIN_INSTRUMENTATION; // loop:i0
	  for( int q0 = 0; q0 < (Q); ++q0 )
	  {
	    // BEGIN_INSTRUMENTATION; // loop:q0
	    for( int r0 = 0; r0 < (R); ++r0 )
	      {
		BEGIN_INSTRUMENTATION; // loop:r0
		float w_qr     = weights[q0*(R)+r0];                   // read weight at (q,r)
		float x_iqjr   = x[ ((q0+i0)%m0)*n0 + ((r0+j0)%n0)  ]; // read x at ((i+q),(j+r))
		float res_wx   = w_qr * x_iqjr;                        // multiply x by the weight
		float y_ij     = y[i0*n0+j0];                          // read y at (i,j)
		float acc_y_ij = y_ij + res_wx;                        // accumulate the result
		y[i0*n0+j0]    = acc_y_ij;                             // write the result back
		END_INSTRUMENTATION; // loop:r0
	      }
	    // END_INSTRUMENTATION; // loop:q0
	  }
	  // END_INSTRUMENTATION; // loop:i0
	}
      // END_INSTRUMENTATION; // loop:j0
    }
  // END_INSTRUMENTATION; // func:compute_name
  

}

