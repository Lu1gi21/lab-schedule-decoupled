/*
  This is a simple implementation of an unoptimized sort.

  - richard.m.veras@ou.edu

*/


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

// Dimensions of the Filter
static const int R = 4;
static const int Q = 4;


//weights[(Q)][(R)]
//weights[(Q)*(R)]
static float weights[] =
  //r=0    1      2      3
  {0.33,  0.33,  0.33,  0.33,  // q=0
   0.33,  0.33,  0.33,  0.33,  // q=1
   0.33,  0.33,  0.33,  0.33,  // q=2
   0.33,  0.33,  0.33,  0.33}; // q=3




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
  for( int i0_o = 0; i0_o < m0; i0_o+=4 )
    {
      // BEGIN_INSTRUMENTATION; // loop:i0_o
      for( int i0_i = 0; i0_i < 4; ++i0_i )
	{
	  // BEGIN_INSTRUMENTATION; // loop:i0_i
	  for( int j0 = 0; j0 < n0; ++j0 )
	    {
	      // BEGIN_INSTRUMENTATION; // loop:j0
	      for( int q0 = 0; q0 < (Q); ++q0 )
		{
		  // BEGIN_INSTRUMENTATION; // loop:q0
		  for( int r0 = 0; r0 < (R); ++r0 )
		    {
		      BEGIN_INSTRUMENTATION; // loop:r0
		      y[(i0_o+i0_i)*n0+j0]  += weights[q0*(R)+r0] *
			x[ ((q0+(i0_o+i0_i))%m0)*n0 + ((r0+j0)%n0)  ];
		      END_INSTRUMENTATION; // loop:r0
		    }
		  // END_INSTRUMENTATION; // loop:q0
		}
	      // END_INSTRUMENTATION; // loop:j0
	    }
	  // END_INSTRUMENTATION; // loop:i0_i
	}
      // END_INSTRUMENTATION; // loop:i0_o
    }
  // END_INSTRUMENTATION; // func:compute_name
  

}
