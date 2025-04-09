/*
  This is a simple implementation of an unoptimized sort.

  - richard.m.veras@ou.edu

*/


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
static const int R = 4;
static const int Q = 3;

/* Weights of the Filter.
 - We are going to linearize this 2d array in row major order.
 - The following code illustrates the layout of the data
   and the relationship between a 2D array and its linearized
   counterpart.

  int NUMROWS=2;
  int NUMROWS=3;
 
  Arr2D[NUMROWS][NUMCOLS]=
                       // j= 0  1  2
                           {{a, b, c}, //  <-- i = 0
                            {d, e, f}}; // <-- i = 1
  Arr1D[NUMROWS*NUMCOLS];

  for( i=0; i<NUMROWS; ++i)
    for( j=0; j<NUMCOLS; ++j)
      Arr1D[i*NUMCOLS+j] = Arr2D[i][j]

 
      //   Arr1D[NUMROWS*NUMCOLS] |--->
      //         j=0  1  2
      //          {a, b, d,  <-- i=0
      //	   e, f, g   <-- i=1

*/

//weights[(Q)][(R)]
//weights[(Q)*(R)]
static float weights[] =
  //r=0    1     2     3
  {-1.1, -1.1,  1.2, -2.1,  // q=0
   -1.1, -2.1, -1.2,  2.2,  // q=1
   -2.1,  0.1,  0.2,  1.2}; // q=2




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


/*
  X and Y are linearized as 1D arrays in memory
  with m0 number of rows and n0 number of columns.
  They are row major order, which means that elements
  on the same row, but adjacent columns are next to
  each other in memory.

  m0 == 4; 0 <= i < m0
  n0 == 7; 0 <= j < n0
  
  y[m0*n0]
  x[m0*n0]
  

 Logical view of X or Y 
   \ j=0 1 2 3 4 5 6 n0
    \ _______________
i= 0 | a b c d e f g
 = 1 | h i j k l m n
 = 2 | o p q r s t u
 = 3 | v q x y z A B
   m0

Indices to Addresses
   
 i | j | &x[i*n0+j]
 __________________
 0 | 0 | &x[0]
 0 | 1 | &x[1]
 0 | 6 | &x[6]
 1 | 0 | &x[7]
 2 | 0 | &x[14]
 2 | 1 | &x[15]
 3 | 6 | &x[27]

 

  Layout in memory
 
 Addr   | Value
 ______________
 &x[0]  | a
 &x[1]  | b
 &x[3]  | c
 &x[4]  | d
 &x[5]  | e
 &x[6]  | f
 &x[7]  | g
 &x[8]  | h
 &x[14] | o
 &x[15] | p
 &x[27] | B
  
 */




void COMPUTE_NAME( int m0,
		   int n0,
		   float *x,
		   float *y )

{

  // BEGIN_INSTRUMENTATION; // func:compute_name
  for( int i0 = 0; i0 < m0; ++i0 )
    {
      // BEGIN_INSTRUMENTATION; // loop:i0
      for( int j0 = 0; j0 < n0; ++j0 )
	{
	  // BEGIN_INSTRUMENTATION; // loop:j0
	  for( int q0 = 0; q0 < (Q); ++q0 )
	  {
	    // BEGIN_INSTRUMENTATION; // loop:q0
	    for( int r0 = 0; r0 < (R); ++r0 )
	      {
		BEGIN_INSTRUMENTATION; // loop:r0
		/*
		  NOTE: While this may seems really tedious to split the operations (and even address computations)
		        the code will better match the assembly, and opportunities for optimizations across loops
			will be more obvious to you (and the compiler). For example, some of these values will change
			between iterations of certain loops, and others won't. This would reveal opportunities for
			precomputing values outside of the fastest moving loop.

		  NOTE: Each one of these computations will roughly correspond to 1 micro-operation on a modern CPU,
		        but will likely be fused with several others to from 1 fetchable instruction.

			Additionally, a lot of computation (micro-operations) are spent on index calculation. Without
			restructuring the loops this can become a bottleneck on the execution engine. Transformations
			such as unrolling replace many of the additions/multiplications of variables with constants that
			can be folded or simplified.
		*/
		

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
		
		END_INSTRUMENTATION; // loop:r0
	      }
	    // END_INSTRUMENTATION; // loop:q0
	  }
	  // END_INSTRUMENTATION; // loop:j0
	}
      // END_INSTRUMENTATION; // loop:r0
    }
  // END_INSTRUMENTATION; // func:compute_name
  

}
