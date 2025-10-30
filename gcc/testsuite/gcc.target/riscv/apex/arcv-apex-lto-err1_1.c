
int apex_conflict (int, int);
#pragma intrinsic (apex_conflict, "conflict", 51, "XS")  /* Different opcode: 51 vs 50 */

int
use_conflict (int a, int b)
{
  return apex_conflict (a, b);
}
