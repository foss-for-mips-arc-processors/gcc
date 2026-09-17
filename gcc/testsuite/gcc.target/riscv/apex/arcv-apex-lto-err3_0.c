/* Test LTO error detection for instruction format mismatch */
/* { dg-lto-do link } */
/* { dg-lto-options { { -flto -O2 } } } */

int apex_format_mismatch (int, int);
#pragma intrinsic (apex_format_mismatch, "format_test", 20, "XS")

extern int use_format_mismatch (int);

int
main (void)
{
  return apex_format_mismatch (1, 2) + use_format_mismatch (5);
}

/* { dg-lto-warning "APEX builtin 'apex_format_mismatch' already registered with different instruction formats: 0xe2 vs 0xe8" "" { target *-*-* } 5 } */
/* { dg-lto-error "APEX builtin 'apex_format_mismatch' has conflicting definitions across compilation units" "" { target *-*-* } 5 } */
