
int func_apex_xc (int, int);
#pragma intrinsic (func_apex_xc, "insn_apex_xc", 21, "XC")

int func_apex_xi (int);
#pragma intrinsic (func_apex_xi, "insn_apex_xi", 20, "XI")

int func_apex_xs (int, int);
#pragma intrinsic (func_apex_xs, "insn_apex_xs", 32, "XS")

int func_apex_xd (int, int);
#pragma intrinsic (func_apex_xd, "insn_apex_xd", 50, "XD")

extern int foo (int);

int
foo (int val)
{
  int a = func_apex_xd (6, 7);
  int b = func_apex_xs (val, 8);
  int c = func_apex_xi (9);
  int d = func_apex_xc (val, 10);
  return a + b + c + d;
}

