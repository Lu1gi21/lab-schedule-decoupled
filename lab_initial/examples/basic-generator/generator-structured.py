#!/usr/bin/env python3
#
#
# An example code generator that only produces one very
# specific operation with no operation file or schedule
#
# NOTE: This is only slightly more modularized than the baseline generator.
#
#
# ./generator-baseline.py <output file>
# ./generator-baseline.py <output file> [operation file]
# ./generator-baseline.py <output file> [operation file] [schedule]





import sys
from ast import *



prog_prolog = """
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
"""

# Note: the flop calculation should be generated
# as these values may change for different weights.
prog_flop ="""
double COMPUTE_FLOP_NAME( int m0, int n0 )
{{
  return 2*m0*n0*({Q})*({R});
}}
"""

# Note: the flop calculation should be generated
# as these values may change for different weights.
prog_byte = """
double COMPUTE_BYTES_NAME( int m0, int n0 )
{{
  return (3*(m0*n0)+ (({Q})*({R})))*sizeof(float);
}}
"""

# Note: the core computation (nest of loops) should be built
# from an AST rather than hardcoded.
prog_compute = """
void COMPUTE_NAME( int m0,
		   int n0,
		   float *x,
		   float *y )

{{

float weights[] =
  //r=0    1     2     3
  {{-1.1, -1.1,  1.2, -2.1,  // q=0
   -1.1, -2.1, -1.2,  2.2,  // q=1
   -2.1,  0.1,  0.2,  1.2}}; // q=2

  for( int i0 = 0; i0 < m0; ++i0 )
    {{
      for( int j0 = 0; j0 < n0; ++j0 )
	{{
	  for( int q0 = 0; q0 < ({Q}); ++q0 )
	  {{
	    for( int r0 = 0; r0 < ({R}); ++r0 )
	      {{
		BEGIN_INSTRUMENTATION; // loop:r0
		y[i0*n0+j0]  += weights[q0*({R})+r0] *
		  x[ ((q0+i0)%m0)*n0 + ((r0+j0)%n0)  ];
		END_INSTRUMENTATION; // loop:r0
	      }}
	  }}
	}}
    }}
}}
"""



# Note: these are just sketches of what new AST Nodes can be
# In reality we can build entirely on top of the EoC interpreter
# which in turn builds entirely on Python's AST module.
#
# The challenge is striking a balance of reusing this infrastructure
# while making it easier to ultimately do schedule transformations
# that we are interested in. 
class BenchedProgram:
  __match_args__ = ("func_comp","func_flop","func_byte")
  def __init__(self,func_comp,func_flop,func_byte):
    self.func_comp = func_comp
    self.func_flop = func_flop
    self.func_byte = func_byte
    
# Note: Ideas of how this could be done. Alternatively,
#   it might better to leverage the "Function"-functionality
#   from EoC. In fact we can really leverage the Function and
#   Call mechanisms that the EoC/Python AST provides us to specicalize
#   even down to the loops (ie. treat loops as functions) and memory
#   accesses.
class FuncCompute:
  __match_args__ = ("q","r","body")
  def __init__(self,q,r,body):
    self.q=q
    self.r=r
    self.body=body

class FuncFlop:
  __match_args__ = ("q","r","body")
  def __init__(self,q,r,body):
    self.q=q
    self.r=r
    self.body=body

class FuncByte:
  __match_args__ = ("q","r","body")
  def __init__(self,q,r,body):
    self.q=q
    self.r=r
    self.body=body


# NOTE: We can lean into the fact that for this operation
# we do not (sort of) have loop-carried depedencies. We do
# have a dependency in the Q and R loops that are
# accumulating to y, but we can re-order these loops
# (sort of, we have floating point round-off error, but that
# is typically acceptable). This is a long winded way of
# saying that we do not need to preserve loop or index ordering
# which opens the door for a special for loop, the forall.
class ForAll:
  __match_args__ = ("index_var","index_cond","index_update","body")
  def __init__(self,index_var,index_cond,index_update,body):
    pass


# See also: interp_Larray
class ReadFromMemory():
  pass
class AssignToMemory():
  pass

# This version is for InterpLvar to inherit from
# and is ripped from Essentials of Compilation
class Compile2CLint:
  def compile2C_exp(self, e, env):
    match e:
      case BinOp(left, Add(), right):
        l = self.compile2C_exp(left, env); r = self.compile2C_exp(right, env)
        return "({l}) + ({r})".format(l=l,r=r)
      case BinOp(left, Sub(), right):
        l = self.compile2C_exp(left, env); r = self.compile2C_exp(right, env)
        return "({l}) - ({r})".format(l=l,r=r)
      case UnaryOp(USub(), v):
        return "({c})".format(c=self.compile2C_exp(v, env))
      case Constant(value):
        return "({v})".format(v=value)
      case Call(Name('input_int'), []):
        return "(*input_int++)"
      case _:
        raise Exception('error in compile2C_exp, unexpected ' + repr(e))

  # The cont parameter is a list of statements that are the
  # continuaton of the current statement s.
  # We use this continuation-passing approach because
  # it enables the handling of Goto in compile2C_Cif.py.
  def compile2C_stmt(self, s, env, cont):
    match s:
      case Expr(Call(Name('print'), [arg])):
        val = "printf({c});\n".format(c=self.compile2C_exp(arg, env))
        return val + self.compile2C_stmts(cont, env)
      case Expr(value):
        val = "{c};\n".format(c=self.compile2C_exp(value, env))
        return val + self.compile2C_stmts(cont, env)
      case _:
        raise Exception('error in compile2C_stmt, unexpected ' + repr(s))
    
  def compile2C_stmts(self, ss, env):
    match ss:
      case []:
        return ""
      case {}:
        return ""
      case [s, *ss]:
        return self.compile2C_stmt(s, env, ss)

  def compile2C(self, p):
    match p:
      case Module(body):
        return self.compile2C_stmts(body, {})
      case _:
        raise Exception('error in compile2C, unexpected ' + repr(p))



class Compile2CLvar(Compile2CLint):
  def compile2C_exp(self, e, env):
    match e:
      case Name(id):
        return env[id]
      case _:
        return super().compile2C_exp(e, env)

  def compile2C_stmt(self, s, env, cont):
    match s:
      case Assign([Name(id)], value):
        env[id] = self.compile2C_exp(value, env)
        return self.compile2C_stmts(cont, env)
      case _:
        return super().compile2C_stmt(s, env, cont)

  def compile2C(self, p):
    match p:
      case Module(body):
        return self.compile2C_stmts(body, {})
      case FuncCompute(q,r,b):
        return prog_compute.format(Q=q,R=r)
      case FuncFlop(q,r,b):
        return prog_flop.format(Q=q,R=r)
      case FuncByte(q,r,b):
        return prog_byte.format(Q=q,R=r)
      case BenchedProgram( c,b,f):
        return prog_prolog + "\n" \
          + self.compile2C(f) + "\n" \
          + self.compile2C(b) + "\n" \
          + self.compile2C(c)

      case _:
        raise Exception('compile2C: unexpected ' + repr(p))
  
  
  
def main():
    
    if len(sys.argv) != 2:
        print("{pn} <outfile> <operation>".format(pn=sys.argv[0]))
        print("{pn} <outfile> <operation> <schedule>".format(pn=sys.argv[0]))
        print("Not supported....yet.")
        exit(-1)
    
    outfile_name   = sys.argv[1]
    # operation_name = sys.argv[2]
    # schedule_name  = sys.argv[3]

    q=3
    r=4
    p = BenchedProgram(FuncCompute(q,r,{}),FuncByte(q,r,{}),FuncFlop(q,r,{}))
    c = Compile2CLvar()    
    rs = c.compile2C(p)
    
    f = open(outfile_name, "w")
    f.write(rs)
    f.close()

    ########################################
    # Piecemeal tracing through a compiler #
    ########################################
    #
    #c = Compile2CLint()    
    #eight = Constant(8)
    #print("{n}:@{c}\n".format(n=0,c=c.compile2C_exp(eight,{})))
    #neg_eight = UnaryOp(USub(), eight)
    #print("{n}:{c}\n".format(n=1,c=c.compile2C_exp(neg_eight,{})))
    #read = Call(Name('input_int'), [])
    #print("{n}:{c}\n".format(n=2,c=c.compile2C_exp(read,{})))
    #ast1_1 = BinOp(read, Add(), neg_eight)
    #print("{n}:{c}\n".format(n=3,c=c.compile2C_exp(ast1_1,{})))
    #pr = Expr(Call(Name('print'), [ast1_1]))
    #print("{n}:{c}\n".format(n=4,c=c.compile2C_stmt(pr,{},{})))
    #p = Module([pr])
    #print("{n}:{c}\n".format(n=5,c=c.compile2C(p)))
    #rs = c.compile2C(p)
    #print("=============")




    
if __name__ == "__main__":
    main()

