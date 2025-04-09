#This generator works for an order of i j q r but none of the others
# moving on to D from advice of Luigi


import sys
from ast import *

sec_one = """
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
static const int R = {R};
static const int Q = {Q};
"""

weights_code = """static float weights[] = {W};
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
            float *w_qr_addr  = &weights[w_qr_idx];
            float w_qr        = *w_qr_addr;

            int    iq_shift    = q0 + i0;
            int    iq_row_wrap = iq_shift % m0;
            int    jr_shift    = r0 + j0;
            int    jr_col_wrap = jr_shift % n0;
            int    x_iqjr_idx  = iq_row_wrap * n0 + jr_col_wrap;
            float *x_iqjr_addr = &x[x_iqjr_idx];
            float  x_iqjr      = *x_iqjr_addr;

            int    y_ij_idx    = i0*n0 + j0;
            float *y_ij_addr   = &y[y_ij_idx];
        
            float y_ij      = *y_ij_addr;
            float res_wx    = w_qr * x_iqjr;
            float acc_y_ij  = y_ij + res_wx;
            *y_ij_addr      = acc_y_ij;
"""


loop_ends = """
    } // close j0 loop
  } // close i0 loop
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
                q_val = self.CompileExpr(params[0], env)
                r_val = self.CompileExpr(params[1], env)
                return sec_one.format(Q=q_val, R=r_val)
            case Expr("[weights]", params):
                w = self.CompileExpr(params, env)
                return weights_code.format(W=w)
            case Expr("[sec_two]", _):
                return sec_two
            case Expr("[unrolled_loop]", params):
                """
                We generate a block for each unrolled q0 iteration, e.g.:
                  { // q0=0
                    BEGIN_INSTRUMENTATION; // loop:q0
                    for (int r0=0; r0<R; r0++) {
                      ...
                    }
                    END_INSTRUMENTATION; // loop:q0
                  }
                """
                index_var = self.CompileExpr(params[0], env) 
                bound     = params[1].value
                r0_loop   = params[2]
                comps     = params[3] 
                code = ""
                for unroll_idx in range(bound):
                    code += f"    {{ // {index_var}={unroll_idx}\n"
                    code += "      BEGIN_INSTRUMENTATION; // loop:q0\n"
                    
                    loop_text = self.CompileExpr(r0_loop, env)
                    code += "      " + loop_text.strip() + "\n"
                    comp_block = self.CompileExpr(comps, env)
                    comp_block = comp_block.replace("q0", str(unroll_idx))
                    suffix = f"_{unroll_idx}"
                    for base_name in [
                        "w_qr_offset",
                        "w_qr_idx",
                        "w_qr_addr",
                        "w_qr",
                        "iq_shift",
                        "iq_row_wrap",
                        "jr_shift",
                        "jr_col_wrap",
                        "x_iqjr_idx",
                        "x_iqjr_addr",
                        "x_iqjr",
                        "res_wx",
                        "acc_y_ij",
                    ]:
                        comp_block = comp_block.replace(base_name, f"{base_name}{suffix}")
                    for line in comp_block.strip().split("\n"):
                        code += "        " + line + "\n"
                    code += "      }\n"
                    code += "      END_INSTRUMENTATION; // loop:q0\n"
                    code += "    }\n\n"
                return code
            case Expr("[loop]", params):
                index_var = self.CompileExpr(params[0], env)
                bound_str = self.CompileExpr(params[1], env)
                return f"for( int {index_var} = 0; {index_var} < {bound_str}; {index_var}++) {{\n"
            case Expr("[computations]"):
                return computations
            case Expr("[loop_ends]", _):
                return loop_ends
            case _:
                raise Exception('Error, unexpected expression ' + repr(e))
    
    def CompileStmt(self, s, env, cont):
        match s:
            case Expr(value):
                return self.CompileExpr(value, env) + self.CompileStmts(cont, env)
            case _:
                raise Exception("Error, unexpected statement " + repr(s))
            
    def CompileStmts(self, ss, env):
        if not ss:
            return ""
        [s, *rest] = ss
        return self.CompileStmt(s, env, rest)

    def CompileCode(self, p):
        match p:
            case Module(body):
                return self.CompileStmts(body, {})
            case _:
                raise Exception("Error, unexpected AST " + repr(p))

def main():
    if len(sys.argv) != 3:
        print(f"Use as: python3 {sys.argv[0]} <outputFile> <operation>")
        exit(-1)
  
    output_file_name = sys.argv[1]
    operation_file   = sys.argv[2]

    with open(operation_file, 'r') as opf:

        R, Q = opf.readline().strip().split()
        R_val = int(R)
        Q_val = int(Q)

        weights_arr = []
        for _ in range(R_val):
            row_vals = opf.readline().strip().split()
            weights_arr.extend(row_vals)

        weights_str = "{" + ",".join(weights_arr) + ",}"


        loop_order = opf.readline().strip().split()

        unroll_var = None
        next_line = opf.readline().strip()
        if next_line.startswith('unroll'):
            unroll_var = next_line.split()[1]


    iterators = {
        'i0': 'm0',
        'j0': 'n0',
        'q0': 'Q',
        'r0': 'R'
    }
    unroll_bounds = {'q0': Q_val, 'r0': R_val}


    boiler1      = Expr("[sec_one]", [Constant(Q_val), Constant(R_val)])
    weights_expr = Expr("[weights]", Constant(weights_str))
    boiler2      = Expr("[sec_two]", [])

    i = 0
    loops = []
    while i < len(loop_order):
        var = loop_order[i]
        if var == unroll_var:
            bound_val = unroll_bounds[var]
            r0_loop = Expr("[loop]", [Constant("r0"), Constant("R")])
            comp_nodes = Expr("[computations]", [])
            unrolled = Expr("[unrolled_loop]", [Constant(var), Constant(bound_val), r0_loop, comp_nodes])
            loops.append(unrolled)
            i += 2
        else:

            bound_str = iterators[var]
            loops.append(Expr("[loop]", [Constant(var), Constant(bound_str)]))
            i += 1


    close_loops = Expr("[loop_ends]", [])


    combined_ast = boiler1
    combined_ast = BinOp(combined_ast, Add(), weights_expr)
    combined_ast = BinOp(combined_ast, Add(), boiler2)
    for ln in loops:
        combined_ast = BinOp(combined_ast, Add(), ln)
    combined_ast = BinOp(combined_ast, Add(), close_loops)

    top_expr = Expr(combined_ast, [])
    mod = Module([top_expr])
    c = CompileC()
    final_code = c.CompileCode(mod)

    with open(output_file_name, "w") as out:
        out.write(final_code)

if __name__ == '__main__':
    main()