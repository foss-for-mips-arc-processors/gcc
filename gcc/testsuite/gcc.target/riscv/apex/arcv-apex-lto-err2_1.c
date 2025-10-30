
int apex_insn_mismatch (int, int);
#pragma intrinsic (apex_insn_mismatch, "insn_b", 100, "XD")  /* Different instruction name */

int
use_insn_mismatch (int a, int b)
{
  return apex_insn_mismatch (a, b);
}
