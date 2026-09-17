
int func_apex_xs (int, int);
#pragma intrinsic (func_apex_xs, "insn_apex_xs", 2, "XS")

extern int foo (int);

int
foo (int val)
{
  return func_apex_xs (val, 3);
}

