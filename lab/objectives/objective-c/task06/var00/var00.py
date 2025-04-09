#!/usr/bin/env python3


#############################
#           This is for unrolling q0 from a operation file
#           THis one uses the eoc and ast
##############################





import sys
from ast import *

#defenitions

class Compile2CLint:
    def compile2C(self, p):
        match p:
            case Module(body):
                return self.compile_stmts(body)
            case _:
                raise Exception(f'Unhandled node type: {type(p).__name__}')

class Compile2CLvar(Compile2CLint):
    pass  



class BenchedProgram:
    __match_args__ = ("compute_func", "flop_func", "byte_func")
    def __init__(self, compute_func, flop_func, byte_func):
        self.compute_func = compute_func
        self.flop_func = flop_func
        self.byte_func = byte_func



#codegen part

class LoopUnroller:
    def __init__(self, Q, R, loop_order, weights):
        self.Q = Q
        self.R = R
        self.weights = weights
        self.loop_order = loop_order
        self.q_index = loop_order.index('q0')
        self.pre_q = loop_order[:self.q_index]
        self.post_q = loop_order[self.q_index+1:]

    def generate_code(self):
        
        weight_rows = []
        for q in range(self.Q):
            rows = ", ".join(f"{weight:.1f}" for weight in self.weights[q])
            weight_rows.append(f"    {rows},  // q={q}")
        weights_str = ",\n".join( weight_rows)
        
        return f"""#include <stdio.h>
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

static const int R = {self.R};
static const int Q = {self.Q};

static float weights[] = {{
    {weights_str}
}};

double COMPUTE_FLOP_NAME(int m0, int n0) {{
    return 2 * m0 * n0 * {self.Q} * {self.R};
}}

double COMPUTE_BYTES_NAME(int m0, int n0) {{
    return (3 * (m0 * n0) + ({self.Q} * {self.R})) * sizeof(float);
}}

void COMPUTE_NAME(int m0, int n0, float *x, float *y) {{
    // BEGIN_INSTRUMENTATION; // func:compute_name
{self.generate_loops()}
    // END_INSTRUMENTATION; // func:compute_name
}}
"""

    def generate_loops(self):
        code = []
        indent = "    "
        
        # Generate pre-q loops
        for var in self.pre_q:
            bound = self.get_bound(var)
            code.append(f"{indent}for(int {var} = 0; {var} < {bound}; ++{var}) {{")
            code.append(f"{indent}    // BEGIN_INSTRUMENTATION; // loop:{var}")
            indent += "    "
        
        # Generate unrolled q blocks
        code.append(f"{indent}// Unrolled q0 iterations (Q={self.Q})")
        for q in range(self.Q):
            code.append(f"{indent}{{ // q0={q}")
            code.append(f"{indent}    BEGIN_INSTRUMENTATION; // loop:q0")
            code.extend(self.generate_post_loops(indent + "    ", q))
            code.append(f"{indent}    END_INSTRUMENTATION; // loop:q0")
            code.append(f"{indent}}}")
        
        # Close pre-q loops
        for var in reversed(self.pre_q):
            indent = indent[:-4]
            code.append(f"{indent}    END_INSTRUMENTATION; // loop:{var}")
            code.append(f"{indent}}}")
        
        return "\n".join(code)

    def generate_post_loops(self, indent, q):
        code = []
        current_indent = indent
        post_vars = self.post_q.copy()
        
        # Generate closing q loop stuff
        for var in post_vars:
            bound = self.get_bound(var)
            code.append(f"{current_indent}for(int {var} = 0; {var} < {bound}; ++{var}) {{")
            code.append(f"{current_indent}    // BEGIN_INSTRUMENTATION; // loop:{var}")
            current_indent += "    "
        
        # SSA section
        code.append(f"{current_indent}// Computation for q0={q}")
        code.append(f"{current_indent}int w_qr_offset_{q} = {q} * R;")
        code.append(f"{current_indent}int w_qr_idx_{q} = w_qr_offset_{q} + r0;")
        code.append(f"{current_indent}float *w_qr_addr_{q} = &weights[w_qr_idx_{q}];")
        code.append(f"{current_indent}float w_qr_{q} = *w_qr_addr_{q};")
        code.append("")
        code.append(f"{current_indent}int iq_shift_{q} = {q} + i0;")
        code.append(f"{current_indent}int iq_row_wrap_{q} = iq_shift_{q} % m0;")
        code.append(f"{current_indent}int jr_shift_{q} = r0 + j0;")
        code.append(f"{current_indent}int jr_col_wrap_{q} = jr_shift_{q} % n0;")
        code.append(f"{current_indent}int x_iqjr_idx_{q} = iq_row_wrap_{q} * n0 + jr_col_wrap_{q};")
        code.append(f"{current_indent}float *x_iqjr_addr_{q} = &x[x_iqjr_idx_{q}];")
        code.append(f"{current_indent}float x_iqjr_{q} = *x_iqjr_addr_{q};")
        code.append("")
        code.append(f"{current_indent}int y_ij_idx = i0 * n0 + j0;")
        code.append(f"{current_indent}float *y_ij_addr = &y[y_ij_idx];")
        code.append(f"{current_indent}float y_ij = *y_ij_addr;")
        code.append(f"{current_indent}float res_wx_{q} = w_qr_{q} * x_iqjr_{q};")
        code.append(f"{current_indent}float acc_y_ij_{q} = y_ij + res_wx_{q};")
        code.append(f"{current_indent}*y_ij_addr = acc_y_ij_{q};")
        
        # Close q loop stuff
        for var in reversed(post_vars):
            current_indent = current_indent[:-4]
            code.append(f"{current_indent}    END_INSTRUMENTATION; // loop:{var}")
            code.append(f"{current_indent}}}")
        
        return code

    def get_bound(self, var):
        return {
            'i0': 'm0',
            'j0': 'n0',
            'q0': 'Q',
            'r0': 'R'
        }.get(var, '1')







def main():
    if len(sys.argv) != 4:
        print("Usage: python3 eoc_q.py <output.c> <operation.txt> <unroll.schedule>")
        sys.exit(1)

    # Read operation file
    with open(sys.argv[2]) as f:
        lines = [line.strip() for line in f if line.strip()]
    
    # Read and validate schedule file
    with open(sys.argv[3]) as f:
        schedule = [line.strip() for line in f if line.strip()]
    
    if not any(line.startswith("unroll q0") for line in schedule):
        raise ValueError("I will only do 'unroll q0'")

    Q, R = map(int, lines[0].split())
    #
    weights = []
    for line in lines[1:-1]:
        row = list(map(float, line.strip().split()))
        if len(row) != R:
            raise ValueError("The lenght of R and the matrix do not match, terminating")
        weights.append(row)
    loop_order = lines[-1].split()
    
    if len(weights) != Q:
        raise ValueError(f"Expected {Q} weight rows, got {len(weights)}")

    if 'q0' not in loop_order:
        raise ValueError("Loop order must contain q0")


    unroller = LoopUnroller(Q, R, loop_order, weights)
    code = unroller.generate_code()


    with open(sys.argv[1], 'w') as f:
        f.write(code)

if __name__ == "__main__":
    main()