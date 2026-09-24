/* { dg-do compile } */
/* { dg-options "-march=rv64gcb_p0p21 -mabi=lp64" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" "-O1" "-Og" "-Os" "-Oz" } } */

/* PV4QI (4-byte) reverse on RV64.  rev8 reverses all 8 bytes of a 64-bit
   register, so the 4-byte reverse needs a following "srli rd, rd, 32" to
   bring the reversed bytes into bits [31:0].  Without the RV64
   *bswap_pv4qi_rv64 pattern the vec_select:PV4QI emitted by
   riscv_expand_pext_vec_perm_const has no recognizer and ICEs at vregs.  */

typedef unsigned char uint8x4_t __attribute__((vector_size(4)));

uint8x4_t test_reverse_pv4qi(uint8x4_t a) {
    uint8x4_t result;
    result[0] = a[3];  result[1] = a[2];
    result[2] = a[1];  result[3] = a[0];
    return result;
}

/* Verify instruction counts */
/* { dg-final { scan-assembler-times "\\mrev8\\M" 1 } } */
