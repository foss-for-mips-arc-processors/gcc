/* { dg-lto-do link } */
/* { dg-lto-options { { -flto -O0 -fdump-tree-optimized -save-temps } } } */

int func_apex_xc (int, int);
#pragma intrinsic (func_apex_xc, "insn_apex_xc", 1, "XC")

extern int foo (int);

int
main (void)
{
  int x = func_apex_xc (1, 2);
  return foo (x);
}

/* Verify that APEX intrinsic calls survive LTO optimization. */
/* { dg-final { scan-ltrans-tree-dump "func_apex_xc" "optimized" } } */
/* { dg-final { scan-ltrans-tree-dump "func_apex_xs" "optimized" } } */

/* Verify that the correct custom instructions are emitted in assembly. */
/* { dg-final { scan-ltrans-assembler "\\.extInstruction insn_apex_xc,1,XC" } } */
/* { dg-final { scan-ltrans-assembler "\\.extInstruction insn_apex_xs,2,XS" } } */

/* { dg-final { scan-ltrans-assembler-times "insn_apex_xc\\s+a\[0-9\]+,+a\[0-9\]+,2" 1 } } */
/* { dg-final { scan-ltrans-assembler-times "insn_apex_xs\\s+a\[0-9\]+,a\[0-9\]+,3" 1 } } */
