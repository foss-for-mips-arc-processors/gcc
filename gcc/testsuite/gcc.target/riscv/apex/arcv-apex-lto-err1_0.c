/* { dg-lto-do link } */
/* { dg-lto-options { { -flto -O2 } } } */

int apex_conflict (int, int);
#pragma intrinsic (apex_conflict, "conflict", 50, "XS")

extern int use_conflict (int, int);

int
main (void)
{
  return apex_conflict (1, 2) + use_conflict (5, 10);
}

/* { dg-lto-warning "APEX builtin 'apex_conflict' already registered with different opcode: 0x32 vs 0x33" "" { target *-*-* } 4 } */
/* { dg-lto-error "APEX builtin 'apex_conflict' has conflicting definitions across compilation units" "" { target *-*-* } 4 } */
