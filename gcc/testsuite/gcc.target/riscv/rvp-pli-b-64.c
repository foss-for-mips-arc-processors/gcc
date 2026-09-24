/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */

/* Test PLI.B instruction for P-extension (RV64).
   PLI.B broadcasts an 8-bit immediate to all byte positions.  */

typedef unsigned long long uint64_t;

/* Replicated byte constants that should use pli.b.  */
uint64_t pli_b_42 (void) { return 0x4242424242424242ULL; }
/* { dg-final { scan-assembler {pli\.b\t[a-x0-9]+,66} } } */

uint64_t pli_b_7f (void) { return 0x7F7F7F7F7F7F7F7FULL; }
/* { dg-final { scan-assembler {pli\.b\t[a-x0-9]+,127} } } */

uint64_t pli_b_80 (void) { return 0x8080808080808080ULL; }
/* { dg-final { scan-assembler {pli\.b\t[a-x0-9]+,-128} } } */

/* 0 and -1 are SMALL_OPERAND, prefer li over pli.b.  */
uint64_t li_00 (void) { return 0x0000000000000000ULL; }
uint64_t li_ff (void) { return 0xFFFFFFFFFFFFFFFFULL; }

/* Negative tests: non-replicated byte patterns should NOT use pli.b.  */
uint64_t not_pli_b_mixed (void) { return 0x0102030405060708ULL; }
uint64_t not_pli_b_partial (void) { return 0x4242424242424200ULL; }

/* Only 3 replicated patterns (not 0/-1) should use pli.b.  */
/* { dg-final { scan-assembler-times {pli\.b} 3 } } */

/* Ensure the compiler does not use pli.b with immediates from not_pli_b_mixed.
   Note: we check for ",8}" to avoid matching ",-128}".  */
/* { dg-final { scan-assembler-not {pli\.b\t[a-x0-9]+,8$} } } */
