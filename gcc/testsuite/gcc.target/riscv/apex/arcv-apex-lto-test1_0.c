/* { dg-lto-do link } */
/* { dg-lto-options { { -flto -O2 -fdump-tree-optimized -save-temps } } } */

int func_apex_xd (int, int);
#pragma intrinsic (func_apex_xd, "insn_apex_xd", 50, "XD")

int func_apex_xs (int, int);
#pragma intrinsic (func_apex_xs, "insn_apex_xs", 32, "XS")

int func_apex_xi (int);
#pragma intrinsic (func_apex_xi, "insn_apex_xi", 20, "XI")

int func_apex_xc (int, int);
#pragma intrinsic (func_apex_xc, "insn_apex_xc", 21, "XC")

extern int foo (int);

int
main (void)
{
  int x = func_apex_xd (1,2);
  int y = func_apex_xs (x, 3);
  int z = func_apex_xi (4);
  int w = func_apex_xc (y, 5);
  
  return foo (y) + w + z;
}

/* Verify that APEX intrinsic calls survive LTO optimization. */
/* { dg-final { scan-ltrans-tree-dump "func_apex_xd" "optimized" } } */
/* { dg-final { scan-ltrans-tree-dump "func_apex_xs" "optimized" } } */
/* { dg-final { scan-ltrans-tree-dump "func_apex_xi" "optimized" } } */
/* { dg-final { scan-ltrans-tree-dump "func_apex_xc" "optimized" } } */

/* Verify that the correct custom instructions are emitted in assembly. */
/* { dg-final { scan-ltrans-assembler "\\.extInstruction insn_apex_xd,50,XD" } } */
/* { dg-final { scan-ltrans-assembler "\\.extInstruction insn_apex_xs,32,XS" } } */
/* { dg-final { scan-ltrans-assembler "\\.extInstruction insn_apex_xi,20,XI" } } */
/* { dg-final { scan-ltrans-assembler "\\.extInstruction insn_apex_xc,21,XC" } } */

/* { dg-final { scan-ltrans-assembler-times "insn_apex_xd\\s+a\[0-9\]+,a\[0-9\]+,a\[0-9\]+" 2 } } */
/* { dg-final { scan-ltrans-assembler-times "insn_apex_xs\\s+a\[0-9\]+,a\[0-9\]+,3" 1 } } */
/* { dg-final { scan-ltrans-assembler-times "insn_apex_xi\\s+a\[0-9\]+,4" 1 } } */
/* { dg-final { scan-ltrans-assembler-times "insn_apex_xc\\s+a\[0-9\]+,a\[0-9\]+,5" 1 } } */

/* { dg-final { scan-ltrans-assembler-times "insn_apex_xs\\s+a\[0-9\]+,a\[0-9\]+,8" 1 } } */
/* { dg-final { scan-ltrans-assembler-times "insn_apex_xi\\s+a\[0-9\]+,9" 1 } } */
/* { dg-final { scan-ltrans-assembler-times "insn_apex_xc\\s+a\[0-9\]+,a\[0-9\]+,10" 1 } } */

