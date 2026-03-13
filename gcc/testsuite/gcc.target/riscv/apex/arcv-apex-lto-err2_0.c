/* Test LTO error detection for instruction name mismatch */
/* { dg-lto-do link } */
/* { dg-lto-options { { -flto -O2 } } } */

int apex_insn_mismatch (int, int);
#pragma intrinsic (apex_insn_mismatch, "insn_a", 100, "XD")

extern int use_insn_mismatch (int, int);

int
main (void)
{
  return apex_insn_mismatch (1, 2) + use_insn_mismatch (5, 10);
}

/* { dg-lto-warning "APEX builtin 'apex_insn_mismatch' already registered with different mnemonic: 'insn_a' vs 'insn_b'" "" { target *-*-* } 5 } */
/* { dg-lto-error "APEX builtin 'apex_insn_mismatch' has conflicting definitions across compilation units" "" { target *-*-* } 5 } */
