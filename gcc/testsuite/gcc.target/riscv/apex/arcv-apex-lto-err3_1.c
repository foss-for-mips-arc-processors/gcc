
int apex_format_mismatch (int, int);
#pragma intrinsic (apex_format_mismatch, "format_test", 20, "XC")  /* Different format: XC vs XS */

int
use_format_mismatch (int a)
{
  return apex_format_mismatch (a, 10);
}
