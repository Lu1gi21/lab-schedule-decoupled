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
                return f"   for( int {index} = 0; {index} < {bound}; {index}++) {{\n"
            case Expr("[computations]"):
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


class Scheduler:
    def __init__(self, commands):
        self.commands = commands

    def apply_schedule(self, ast):
        for cmd in self.commands:
            tokens = cmd.split()
            if tokens[0] == "split": ast = self.split(ast, *tokens[1:])
            elif tokens[0] == "interchange": ast = self.interchange(ast, *tokens[1:])
            elif tokens[0] == "unroll": ast = self.unroll(ast, tokens[1])
        return ast
    
    def split(self, ast, old_index, outer, inner, factor):
        def transform(node):
            match node:
            case Expr("[loop]", [Constant(i), Constant(b)]) if i == old_index:
                outer_loop = Expr("[loop]", [Constant(outer), Constant(f"{b}//{factor}")]) 
                inter_loop = Expr("[loop]", [Constant(inner), Constant(factor)])
                return BinOp(outer_loop, Add(), inner_loop)
            case: BinOp(left, Add(), right): return BinOp(transformation(left), Add(), transform(right))
            case _: return node
        return transform(ast)

    def interchange(self, ast, i1, i2):
        def _is_loop(node, idx):
            return isinstance(node, Expr) and node.label == "[loop]" and node.params[0].value == idx

        def swap(node):
            if isinstance(node, BinOp):
                l, r = node.left, node.right
                if _is_loop(l, i1) and _is_loop(r, i2):
                    return BinOp(r, Add(), l)
                else:
                    return BinOp(swap(l), Add(), swap(r))
            return node

        return swap(ast)

    def unroll(self, ast, idx):
        def _is_loop(node, idx):
            return isinstance(node, Expr) and node.label == "[loop]" and node.params[0].value == idx

        def transform(node):
            if isinstance(node, BinOp):
                l, r = node.left, node.right
                if _is_loop(l, idx):
                    return BinOp(r, Add(), r)  # naive factor=2
                return BinOp(transform(l), Add(), transform(r))
            return node

        return transform(ast)
            
def main():
  if len(sys.argv) != 3:
    print(f"Use as: python3 {sys.argv[0]} <outputFile> <operation>")
    exit(-1)
  
  output_file_name = sys.argv[1]
  operation_file = sys.argv[2]

  with open(operation_file, 'r') as op:
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

  iterators = {
      'i0' : 'm0',
      'j0' : 'n0',
      'q0' : 'Q',
      'r0' : 'R'
  }

  boiler1 = Expr("[sec_one]", [Constant(Q), Constant(R)])
  weights = Expr("[weights]", Constant(weights_str))
  boiler2 = Expr("[sec_two]", [])
  loop1 = Expr("[loop]", [Constant(loop_order[0]), Constant(iterators[loop_order[0]])])
  loop2 = Expr("[loop]", [Constant(loop_order[1]), Constant(iterators[loop_order[1]])])
  loop3 = Expr("[loop]", [Constant(loop_order[2]), Constant(iterators[loop_order[2]])])
  loop4 = Expr("[loop]", [Constant(loop_order[3]), Constant(iterators[loop_order[3]])])
  compute = Expr("[computations]", [])
  endLoop = Expr("[loop_ends]", [])

  ast = boiler1
  for part in [weights_node, boiler2] + loops + [compute, endLoop]:
    ast = BinOp(ast, Add(), part)

  sechedule_cmds = [
    "split j0 j0_o j0_i 2",
    "interchange r0 j0_i",
    "unroll j0_i"
  ]

  scheduler = Scheduler(schedule_cmds)
  transformed_ast = scheduler.apply_schedule(ast)

  mod = Module([transformed_ast])
  c = CompileC()
  code = c.CompileCode(mod)


  with open(output_file_name, "w") as out:
    out.write(code)

  exit(0)
      

if __name__ == '__main__':
    main()