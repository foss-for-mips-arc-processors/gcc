
int func_apex_xc (int, int);
#pragma intrinsic (func_apex_xc, "insn_apex_xc", 21, "XC")

int func_apex_xi (int);
#pragma intrinsic (func_apex_xi, "insn_apex_xi", 20, "XI")

int
bar (int a, int b)
{
  int c = func_apex_xi (4);
  int d = func_apex_xc (a, 5);
  return b + c + d;
}

