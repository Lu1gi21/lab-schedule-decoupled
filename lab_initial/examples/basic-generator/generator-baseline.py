#!/usr/bin/env python3
#
#
# An example code generator that only produces one very
# specific operation with no operation file or schedule
#
#
#
#
# ./generator-baseline.py <output file>
# ./generator-baseline.py <output file> [operation file]
# ./generator-baseline.py <output file> [operation file] [schedule]



import sys


prog = """
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

float weights[] =
  //r=0    1     2     3
  {-1.1, -1.1,  1.2, -2.1,  // q=0
   -1.1, -2.1, -1.2,  2.2,  // q=1
   -2.1,  0.1,  0.2,  1.2}; // q=2

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
		y[i0*n0+j0]  += weights[q0*(R)+r0] *
		  x[ ((q0+i0)%m0)*n0 + ((r0+j0)%n0)  ];
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

"""




def main():
    if len(sys.argv) != 2:
        print("{pn} <outfile> <operation>".format(pn=sys.argv[0]))
        print("{pn} <outfile> <operation> <schedule>".format(pn=sys.argv[0]))
        print("Not supported....yet.")
        exit(-1)
    
    outfile_name   = sys.argv[1]
    # operation_name = sys.argv[2]
    # schedule_name  = sys.argv[3]
    
    f = open(outfile_name, "w")
    f.write(prog)
    f.close()

if __name__ == "__main__":
    main()

