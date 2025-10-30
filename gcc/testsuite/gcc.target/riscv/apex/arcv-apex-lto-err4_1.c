
int apex_multi_mismatch (int, int);
#pragma intrinsic (apex_multi_mismatch, "insn_different", 21, "XS")  /* All different */

int
use_multi_mismatch (int a)
{
  return apex_multi_mismatch (a, 10);
}
