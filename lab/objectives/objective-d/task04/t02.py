import sys
from ast import *


sec_one = """
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
static const int R = {R};
static const int Q = {Q};
"""


weights = """static float weights[] = {W};
"""

sec_two = """
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

loop_ends = "}"


class Expr:
    __match_args__  = ("label", "params")
    def __init__(self, label, params):
        self.label = label
        self.params = params

class CompileC:
    def CompileExpr(self, e, env):
        match e:
            case Constant(v):
                return v
            case BinOp(left, Add(), right):
                l = self.CompileExpr(left, env)
                r = self.CompileExpr(right, env)
                return l + r
            case Expr("[sec_one]", params):
                q = self.CompileExpr(params[0], env)
                r = self.CompileExpr(params[1], env)
                return sec_one.format(Q = q, R = r)
            case Expr("[weights]", params):
                w = self.CompileExpr(params, env)
                return weights.format(W = w)
            case Expr("[sec_two]", params):
                return sec_two
            case Expr("[loop]", params):
                index = self.CompileExpr(params[0], env)
                bound = self.CompileExpr(params[1], env)
                factor = self.CompileExpr(params[2], env)
                return f"   for( int {index} = 0; {index} < {bound}; {index}+={factor}) {{\n"
            case Expr("[computations]", params):
                global computations
                if self.CompileExpr(params[0], env):
                    splits = self.CompileExpr(params[1], env)
                    for v, k in splits.items():
                        s_var = v
                        var0 = k[0]
                        var1 = k[1]
                        computations = computations.replace(s_var, f"({var0} + {var1})")
                return computations
            case Expr("[loop_ends]", params):
                return loop_ends
            case _:
                raise Exception('Error, unexpected expreession' + repr(e))
    
    def CompileStmt(self, s, env, cont):
        match s:
            case Expr(value):
                return self.CompileExpr(value, env) + self.CompileStmts(cont, env)
            case _:
                raise Exception("Error, unexpected statement" + repr(s))
            
    def CompileStmts(self, ss, env):
        match ss:
            case []:
                return ""
            case {}:
                return ""
            case [s, *ss]:
                return self.CompileStmt(s, env, ss)
            
    def CompileCode(self, p):
        match p:
            case Module(body):
                return self.CompileStmts(body, {})
            case _:
                raise Exception("Error, unexpected body" + repr(p))

def BuildLoops(loops):
    if len(loops) == 1:
        return loops[0]
    else:
        return BinOp(loops[0], Add(), BuildLoops(loops[1:]))

def main():
  if len(sys.argv) != 4:
    print(f"Use as: python3 {sys.argv[0]} <outputFile> <operation> <schedule>")
    exit(-1)
  
  output_file_name = sys.argv[1]
  operation_file = sys.argv[2]
  schedule_file = sys.argv[3]

  operation = open(operation_file, 'r')

  R, Q = operation.readline().strip().split(" ")

  weights_arr = []

  weights_str = "{"

  for i in range(int(R)):
      weights_arr += [s for s in operation.readline().strip().split(" ") if s]

  for w in weights_arr:
      weights_str += w + ","
  weights_str += "}"

  loop_order = [s for s in operation.readline().strip().split(" ") if s]

  operation.close()

  transformations = []
  split_vars = {}
  interchanges = {}

  with open(schedule_file, 'r') as scheudle:
    for line in scheudle:
        transformations.append(line.strip().split(" "))

  for t in transformations:
      match t[0]:
          case 'split':
              split_vars[t[1]] = [t[2], t[3], t[4]]
          case 'interchange':
              interchanges[t[1]] = t[2]
          case 'unroll':
              continue
          case _:
              raise Exception("Error, unexpected transformation type")

  is_split = len(split_vars) > 0

  iterators = {
      'i0' : 'm0',
      'j0' : 'n0',
      'q0' : 'Q',
      'r0' : 'R'
  }

  boiler1 = Expr("[sec_one]", [Constant(Q), Constant(R)])
  weights = Expr("[weights]", Constant(weights_str))
  boiler2 = Expr("[sec_two]", [])

  loop_array = []

  for l in loop_order:
    if l in split_vars:
      loop_array.append(Expr("[loop]", [Constant(split_vars[l][0]), Constant(iterators[l]), Constant(split_vars[l][2])]))
      loop_array.append(Expr("[loop]", [Constant(split_vars[l][1]), Constant(split_vars[l][2]), Constant(1)]))
    else:
      loop_array.append(Expr("[loop]", [Constant(l), Constant(iterators[l]), Constant(1)]))


  compute = Expr("[computations]", [Constant(is_split), Constant(split_vars)])

  global loop_ends
  for i in loop_array:
      loop_ends += "\n}"

  endLoop = Expr("[loop_ends]", [])


  boilers = BinOp(boiler1, Add(), BinOp(weights, Add(), boiler2))

  loops = BuildLoops(loop_array)

  ast = Expr(BinOp(boilers, Add(), BinOp(loops, Add(), BinOp(compute, Add(), endLoop))), [])

  mod = Module([ast])

  c = CompileC()

  code = c.CompileCode(mod)


  out = open(output_file_name, "w")
  out.write(code)
  out.close()

  exit(0)
      


if __name__ == '__main__':
    main()