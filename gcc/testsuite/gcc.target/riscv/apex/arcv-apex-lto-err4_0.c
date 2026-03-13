/* Test LTO error detection for multiple mismatches */
/* { dg-lto-do link } */
/* { dg-lto-options { { -flto -O2 } } } */

int apex_multi_mismatch (int, int);
#pragma intrinsic (apex_multi_mismatch, "insn_original", 20, "XD")

extern int use_multi_mismatch (int);

int
main (void)
{
  return apex_multi_mismatch (1, 2) + use_multi_mismatch (5);
}

/* { dg-lto-warning "APEX builtin 'apex_multi_mismatch' already registered with different mnemonic: 'insn_original' vs 'insn_different'" "" { target *-*-* } 5 } */
/* { dg-lto-warning "APEX builtin 'apex_multi_mismatch' already registered with different opcode: 0x14 vs 0x15" "" { target *-*-* } 5 } */
/* { dg-lto-warning "APEX builtin 'apex_multi_mismatch' already registered with different instruction formats: 0x1 vs 0x2" "" { target *-*-* } 5 } */
/* { dg-lto-error "APEX builtin 'apex_multi_mismatch' has conflicting definitions across compilation units" "" { target *-*-* } 5 } */
