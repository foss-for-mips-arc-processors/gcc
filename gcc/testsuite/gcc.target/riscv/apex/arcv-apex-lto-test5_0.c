/* { dg-lto-do link } */
/* { dg-lto-options { { -flto -O2 -fdump-tree-optimized -save-temps } } } */

/* Test that intrinsics optimized away don't cause crashes during LTO.
   This test registers multiple intrinsics but only uses some of them,
   allowing the optimizer to remove the unused ones. */

int func_apex_used1 (int, int);
#pragma intrinsic (func_apex_used1, "insn_apex_used1", 1, "XC")

int func_apex_unused (int, int);
#pragma intrinsic (func_apex_unused, "insn_apex_unused", 2, "XS")

int func_apex_used2 (int, int);
#pragma intrinsic (func_apex_used2, "insn_apex_used2", 3, "XC")

extern int bar (int);

static int
func_apex_unused_helper (int a, int b)
{
  return func_apex_unused (a, b);
}

int
main (void)
{
  /* Only use func_apex_used1 and func_apex_used2.
     func_apex_unused should be optimized away. */
  int x = func_apex_used1 (5, 10);
  int y = func_apex_used2 (x, 15);
  return bar (y);
}

/* Verify that only the used intrinsics appear in the optimized output. */
/* { dg-final { scan-ltrans-tree-dump "func_apex_used1" "optimized" } } */
/* { dg-final { scan-ltrans-tree-dump "func_apex_used2" "optimized" } } */
/* { dg-final { scan-ltrans-tree-dump "func_apex_from_other" "optimized" } } */

/* Verify that the unused intrinsic is NOT in the optimized output. */
/* { dg-final { scan-ltrans-tree-dump-not "func_apex_unused" "optimized" } } */
/* { dg-final { scan-ltrans-tree-dump-not "func_apex_also_unused" "optimized" } } */

/* Verify that only used intrinsics have .extInstruction directives. */
/* { dg-final { scan-ltrans-assembler "\\.extInstruction insn_apex_used1,1,XC" } } */
/* { dg-final { scan-ltrans-assembler "\\.extInstruction insn_apex_used2,3,XC" } } */
/* { dg-final { scan-ltrans-assembler "\\.extInstruction insn_apex_from_other,4,XS" } } */

/* Verify the actual instruction usage in assembly. */
/* { dg-final { scan-ltrans-assembler-times "insn_apex_used1\\s+a\[0-9\]+,a\[0-9\]+,10" 1 } } */
/* { dg-final { scan-ltrans-assembler-times "insn_apex_used2\\s+a\[0-9\]+,a\[0-9\]+,15" 1 } } */
/* { dg-final { scan-ltrans-assembler-times "insn_apex_from_other\\s+a\[0-9\]+,a\[0-9\]+,20" 1 } } */
