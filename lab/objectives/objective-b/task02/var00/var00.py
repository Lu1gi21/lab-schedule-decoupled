sec_one = """#include <stdio.h>
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
static const int R = _#_;
static const int Q = _$_;
static float weights[] =
"""


weights = """{
_$_
};
"""

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
        // BEGIN_INSTRUMENTATION; // loop:r0
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

class Generator:
    transformation = None
    split_var = None
    var0 = None
    var1 = None
    factor = None
    Q = 0
    R = 0
    weights = []
    loop_order = None

    def __init__(self, schedule_path, operation_path):
        self.read_schedule(schedule_path)
        self.read_operation(operation_path)
        
    def read_schedule(self, path):
        schedule_file = open(path, 'r')
        
        self.transformation, self.split_var, self.var0, self.var1, self.factor = schedule_file.read().split(" ")

        schedule_file.close()
    
    def read_operation(self, operation_path):
        operation_file = open(operation_path, 'r')

        self.R, self.Q = operation_file.readline().strip().split(" ")

        for i in range(int(self.R)):
            self.weights += [s for s in operation_file.readline().strip().split(" ") if s]

        self.loop_order = [s for s in operation_file.readline().strip().split(" ") if s]

        operation_file.close()

    def insert_Q_R(self):
        global sec_one
        sec_one = sec_one.replace("_#_", self.R)
        sec_one = sec_one.replace("_$_", self.Q)

    def convert_weights(self):
        global weights
        
        weight_string = ""
        for w in self.weights:
            weight_string += (" " + w + ",")
        weights = weights.replace("_$_", weight_string)

    def generate(self, path):
        out_file = open(path, 'a')

        out_file.seek(0)
        out_file.truncate()

        self.insert_Q_R()
        out_file.write(sec_one)
        
        self.convert_weights()
        out_file.write(weights)

        out_file.write(sec_two)
        
        for var in self.loop_order:
            match var:
                case "i0":
                    out_file.write(loop_i)
                case "j0":
                    out_file.write(loop_j)
                case "q0":
                    out_file.write(loop_q)
                case "r0":
                    out_file.write(loop_r)

        out_file.write(computations)
        out_file.write(loop_ends)

        out_file.close()



def main():
    generator = Generator("split_i_io_ii_4.schedule", "conv_4x3_ijqr.operation")
    generator.generate("var00.c")

if __name__ == '__main__':
    main()