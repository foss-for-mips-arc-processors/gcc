
int func_apex_from_other (int, int);
#pragma intrinsic (func_apex_from_other, "insn_apex_from_other", 4, "XS")

int func_apex_also_unused (int, int);
#pragma intrinsic (func_apex_also_unused, "insn_apex_also_unused", 5, "XC")

static int
func_apex_also_unused_helper (int a, int b)
{
  return func_apex_also_unused (a, b);
}

int
bar (int val)
{
  /* Only use func_apex_from_other.
     func_apex_also_unused should be optimized away. */
  return func_apex_from_other (val, 20);
}
