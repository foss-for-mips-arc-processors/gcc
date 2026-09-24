/* { dg-do compile } */
/* { dg-options "-march=rv32gcbp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-O0" } } */

typedef signed char int8x4_t __attribute__((vector_size(4)));
typedef short int16x2_t __attribute__((vector_size(4)));

/* Test that PLI is used for replicated patterns that are not SMALL_OPERAND,
   while SMALL_OPERAND values like 0 and -1 prefer li.  */

/* -1 = 0xFFFFFFFF is a SMALL_OPERAND, prefer li over pli.b.  */
int8x4_t test_li_minus_one (void) {
    return (int8x4_t){-1, -1, -1, -1};
}

/* 5 = 0x05050505 is a replicated byte pattern, not SMALL_OPERAND.
   Should use pli.b.  */
int8x4_t test_pli_b_five (void) {
    return (int8x4_t){5, 5, 5, 5};
}

/* 1 = 0x01010101 is a replicated byte pattern, not SMALL_OPERAND.
   Should use pli.b.  */
int8x4_t test_pli_b_one (void) {
    return (int8x4_t){1, 1, 1, 1};
}

/* 100 = 0x00640064 is a replicated halfword pattern, not SMALL_OPERAND.
   Should use pli.h.  */
int16x2_t test_pli_h_hundred (void) {
    return (int16x2_t){100, 100};
}

/* -1 should use li, not pli.b.  */
/* { dg-final { scan-assembler "li\\t" } } */
/* { dg-final { scan-assembler-times "pli\\.b" 2 } } */
/* { dg-final { scan-assembler-times "pli\\.h" 1 } } */
