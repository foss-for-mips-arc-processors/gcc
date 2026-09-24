/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64 -O2" } */

/* Test PLI.H instruction for P-extension (RV64).
   PLI.H broadcasts a 10-bit signed immediate [-512, 511] to all halfwords.  */

typedef unsigned long long uint64_t;

/* Replicated halfword constants in range [-512, 511].  */
uint64_t pli_h_42 (void) { return 0x0042004200420042ULL; }
uint64_t pli_h_1ff (void) { return 0x01FF01FF01FF01FFULL; }
uint64_t pli_h_fe00 (void) { return 0xFE00FE00FE00FE00ULL; }
uint64_t pli_h_1 (void) { return 0x0001000100010001ULL; }
uint64_t pli_h_ff (void) { return 0x00FF00FF00FF00FFULL; }
uint64_t pli_h_ff00 (void) { return 0xFF00FF00FF00FF00ULL; }
uint64_t pli_h_fffe (void) { return 0xFFFEFFFEFFFEFFFEULL; }

/* Not replicated: should NOT use pli.h.  */
uint64_t not_pli_h_diff (void) { return 0x0042004200420043ULL; }

/* Verify the specific patterns we expect.  Using scan-assembler for
   individual immediates rather than a total count, as optimization
   may use pli.h as an intermediate step for constructing other values.  */
/* { dg-final { scan-assembler {pli\.h\t[a-x0-9]+,66} } } */
/* { dg-final { scan-assembler {pli\.h\t[a-x0-9]+,511} } } */
/* { dg-final { scan-assembler {pli\.h\t[a-x0-9]+,-512} } } */
/* { dg-final { scan-assembler {pli\.h\t[a-x0-9]+,1} } } */
/* { dg-final { scan-assembler {pli\.h\t[a-x0-9]+,255} } } */
/* { dg-final { scan-assembler {pli\.h\t[a-x0-9]+,-256} } } */
/* { dg-final { scan-assembler {pli\.h\t[a-x0-9]+,-2} } } */

/* Negative test: not_pli_h_diff should not use pli.h with immediate 67.  */
/* { dg-final { scan-assembler-not {pli\.h\t[a-x0-9]+,67} } } */
