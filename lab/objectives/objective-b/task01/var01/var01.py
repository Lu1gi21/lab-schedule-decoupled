#!/usr/bin/env python3









#############################
#           This is for unrolling r0 from a operation file
##############################



import sys

def generate_unrolled_r0_code(op_file, output_file):
    with open(op_file, 'r') as f:
        lines = [line.strip() for line in f.readlines() if line.strip()]
    
    Q, R = map(int, lines[0].split())
    loop_order = lines[-1].split()
    weight_lines = []
    
    if 'r0' not in loop_order:
        raise ValueError("Loop order must contain r0 for unrolling")
        
    r_index = loop_order.index('r0')
    pre_r = loop_order[:r_index]
    post_r = loop_order[r_index+1:]
    
    for i in range(Q):
        values = lines[1+i].split()
        formatted = ", ".join(values)
        if i < Q-1:
            formatted += ","
        weight_lines.append(f"    {formatted}  // q={i}")
    
    weights_str = "\n".join(weight_lines)
    
    loop_code = []
    indent_level = 4
    current_indent = " " * indent_level
    instrumentation_stack = []

    # Generate pre-r loops
    for var in pre_r:
        bound = "m0" if var == "i0" else "n0" if var == "j0" else "Q" if var == "q0" else "R"
        loop_code.append(f"{current_indent}for(int {var} = 0; {var} < {bound}; ++{var}) {{")
        loop_code.append(f"{current_indent}    // BEGIN_INSTRUMENTATION; // loop:{var}")
        instrumentation_stack.append(var)
        current_indent += "    "
        indent_level += 4

    # Generate unrolled r0 blocks with post-r loops
    loop_code.append(f"{current_indent}// Unrolled r0 loop (R={R} iterations)")
    unrolled_blocks = generate_r0_blocks(R, post_r).split('\n')
    for block in unrolled_blocks:
        loop_code.append(f"{current_indent}{block}")

    # Close pre-r loops
    for var in reversed(pre_r):
        current_indent = current_indent[:-4]
        loop_code.append(f"{current_indent}    // END_INSTRUMENTATION; // loop:{var}")
        loop_code.append(f"{current_indent}}}")

    loop_code_str = "\n".join(loop_code)

    code = f"""#include <stdio.h>
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

static const int R = {R};
static const int Q = {Q};

static float weights[] = {{
{weights_str}
}};

double COMPUTE_FLOP_NAME(int m0, int n0) {{
    return 2 * m0 * n0 * Q * R;
}}

double COMPUTE_BYTES_NAME(int m0, int n0) {{
    return (3 * (m0 * n0) + (Q * R)) * sizeof(float);
}}

void COMPUTE_NAME(int m0, int n0, float *x, float *y) {{
    // BEGIN_INSTRUMENTATION; // func:compute_name
{loop_code_str}
    // END_INSTRUMENTATION; // func:compute_name
}}
"""

    with open(output_file, 'w') as f:
        f.write(code)

def generate_r0_blocks(R, post_r):
    blocks = []
    for r in range(R):
        block_lines = []
        block_lines.append(f"{{ // r0={r}")
        block_lines.append(f"    BEGIN_INSTRUMENTATION; // loop:r0")
        
        indent = "    "
        current_indent = indent
        instrumentation_stack = []
        
        # Generate post_r loops
        for var in post_r:
            bound = "m0" if var == "i0" else "n0" if var == "j0" else "Q" if var == "q0" else "R"
            block_lines.append(f"{current_indent}for(int {var} = 0; {var} < {bound}; ++{var}) {{")
            block_lines.append(f"{current_indent}    // BEGIN_INSTRUMENTATION; // loop:{var}")
            instrumentation_stack.append(var)
            current_indent += "    "
        
        # Computation code inside post_r loops
        computation_code = [
            f"int w_qr_offset_{r} = q0 * R;",
            f"int w_qr_idx_{r} = w_qr_offset_{r} + {r};",
            f"float *w_qr_addr_{r} = &weights[w_qr_idx_{r}];",
            f"float w_qr_{r} = *w_qr_addr_{r};",
            f"",
            f"int iq_shift_{r} = q0 + i0;",
            f"int iq_row_wrap_{r} = iq_shift_{r} % m0;",
            f"int jr_shift_{r} = {r} + j0;",
            f"int jr_col_wrap_{r} = jr_shift_{r} % n0;",
            f"int x_iqjr_idx_{r} = iq_row_wrap_{r} * n0 + jr_col_wrap_{r};",
            f"float *x_iqjr_addr_{r} = &x[x_iqjr_idx_{r}];",
            f"float x_iqjr_{r} = *x_iqjr_addr_{r};",
            f"",
            f"int y_ij_idx = i0 * n0 + j0;",
            f"float *y_ij_addr = &y[y_ij_idx];",
            f"float y_ij = *y_ij_addr;",
            f"float res_wx_{r} = w_qr_{r} * x_iqjr_{r};",
            f"float acc_y_ij_{r} = y_ij + res_wx_{r};",
            f"*y_ij_addr = acc_y_ij_{r};"
        ]
        
        for line in computation_code:
            block_lines.append(f"{current_indent}{line}")
        
        # Close post_r loops
        for var in reversed(post_r):
            current_indent = current_indent[:-4]
            block_lines.append(f"{current_indent}    // END_INSTRUMENTATION; // loop:{var}")
            block_lines.append(f"{current_indent}}}")
        
        block_lines.append(f"    END_INSTRUMENTATION; // loop:r0")
        block_lines.append(f"}}")
        blocks.append("\n".join(block_lines))
    
    return "\n".join(blocks)

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python3 generator.py <output.c> <operation.txt> <unroll.schedule>")
        sys.exit(1)
    
    output_file = sys.argv[1]
    op_file = sys.argv[2]
    schedule_file = sys.argv[3]
    
    # Read and validate schedule file
    with open(schedule_file, 'r') as f:
        schedule = [line.strip() for line in f if line.strip()]
    
    if not any(line.startswith("unroll r0") for line in schedule):
        raise ValueError("I will only do unroll r0'")
    
    generate_unrolled_r0_code(op_file, output_file)
    
    
#this follows the same execution pattern as the previous variant.