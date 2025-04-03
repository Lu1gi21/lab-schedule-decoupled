# Simple Standalone + Interchange
#
# interchange
#
# colemanbixler@ou.edu 

import sys
import ipdb

prog = """
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

float weights[] = {-1.1, -1.1,  1.2, -2.1, -1.1, -2.1, -1.2,  2.2, -2.1,  0.1,  0.2,  1.2};

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
	  // END_INSTRUMENTATION; // loop:j0
	}
      // END_INSTRUMENTATION; // loop:i0
    }
  // END_INSTRUMENTATION; // func:compute_name
  

}

"""

def main():
    if len(sys.argv) < 2 or len(sys.argv) > 4:
        # print("{pn} <outfile> <operation>".format(pn=sys.argv[0]))
        # print("{pn} <outfile> <operation> <schedule>".format(pn=sys.argv[0]))
        print(f"Length of {len(sys.argv)}: Not supported.")
        exit(-1)
    
    # ensure prog works in all of main
    global prog
    
    # loop and comment strings for interchanging
    loop_strs = {
      "i0" : "for( int i0 = 0; i0 < m0; ++i0 )",
      "j0" : "for( int j0 = 0; j0 < n0; ++j0 )",
      "q0" : "for( int q0 = 0; q0 < (Q); ++q0 )",
      "r0" : "for( int r0 = 0; r0 < (R); ++r0 )"
    }
    
    
    comment_strs = {
      "i0" : "// loop:i0",
      "j0" : "// loop:j0",
      "q0" : "// loop:q0",
      "r0" : "// loop:r0"
    }
    
    placeholder = "******************************"
    
    # init strings
    weights_init = "float weights[] = {-1.1, -1.1,  1.2, -2.1, -1.1, -2.1, -1.2,  2.2, -2.1,  0.1,  0.2,  1.2};"
    R_init = "static const int R = 4;"
    Q_init = "static const int Q = 3;"
    
    # name of outfile
    outfile_name = sys.argv[1]
    
    if len(sys.argv) > 2:
      # name of operation file
      operation_name = sys.argv[2]
      
      # open (& close) operation file and format input
      f = open(f"../operations/{operation_name}", "r")
      operation_lines = f.readlines()
      operation_matrix = [line.split(" ") for line in operation_lines]
      f.close()
      
      # parse input data from operation
      new_R, new_Q = operation_matrix[0][0], operation_matrix[0][1]
      new_weights = []
      for row in operation_matrix[1:-1]:
        for idx, val in enumerate(row):
          if idx == 0: 
            new_weights.append("\n\t" + val)
          else: 
            new_weights.append(val.replace("\n", ""))
      new_weights_str = "{" + ", ".join(new_weights) + "\n};"
      
      # put data into new initialization strings and replace the old ones
      new_R_init = f"static const int R = {new_R};"
      new_Q_init = f"static const int Q = {new_Q};"
      new_weights_init = f"float weights[] = {new_weights_str}"
      prog = prog.replace(R_init, new_R_init)
      prog = prog.replace(Q_init, new_Q_init)
      prog = prog.replace(weights_init, new_weights_init)
    
    if len(sys.argv) > 3:
      # name of schedule file
      schedule_name  = sys.argv[3]
      
      # open (& close) schedule file and format input
      f = open(f"../interchanges/{schedule_name}", "r")
      schedule_lines = f.readlines()
      schedule_matrix = [line.split(" ") for line in schedule_lines]
      f.close()
      
      # check for invalid input
      if len(schedule_lines) > 1:
        print("Unsupported: Multiple Line Schedule")
        exit(-1)
      elif schedule_matrix[0][0] != "interchange":
        print("Unsupported: Not Interchange")
        exit(-1)
      else:
        # parse input from schedule operation
        chosen_schedule = schedule_matrix[0][0]
        loop_1, loop_2 = schedule_matrix[0][1], schedule_matrix[0][2]
        first_loop, second_loop = loop_strs[loop_1], loop_strs[loop_2]
        first_comment, second_comment = comment_strs[loop_1], comment_strs[loop_2]
        
        # replace loops and comments
        ## loops
        prog = prog.replace(first_loop, placeholder)
        prog = prog.replace(second_loop, first_loop)
        prog = prog.replace(placeholder, second_loop)
        ## comments
        prog = prog.replace(first_comment, placeholder)
        prog = prog.replace(second_comment, first_comment)
        prog = prog.replace(placeholder, second_comment)
        
    # write to output program
    f = open(f"interchanged-versions/{outfile_name}", "w")
    f.write(prog)
    f.close()

if __name__ == "__main__":
    main()

