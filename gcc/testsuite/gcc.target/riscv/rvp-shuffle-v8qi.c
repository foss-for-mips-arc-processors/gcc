/* { dg-do compile } */
/* { dg-options "-march=rv64gcb_p0p21 -mabi=lp64d -O2 -Wno-riscv-implicit-extension-version" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

typedef unsigned char V __attribute__((vector_size(8)));

V a = { 0x1, 0x2, 0x3, 0x4, 0x1, 0x2, 0x3, 0x4};
V b = { 0x3, 0x4, 0x3, 0x4, 0x1, 0x2, 0x3, 0x4 };

V test_shuffle(void) {
    V mask = { 0, 8, 2, 10, 4, 12, 6, 14};
    return __builtin_shuffle(a, b, mask);
}

V test_shuffle_2(void) {
    V mask = { 0, 9, 2, 11, 4, 13, 6, 15};
    return __builtin_shuffle(a, b, mask);
}

V test_shuffle_3(void) {
    V mask = { 1, 8, 3, 10, 5, 12, 7, 14};
    return __builtin_shuffle(a, b, mask);
}

V test_shuffle_4(void) {
    V mask = { 1, 9, 3, 11, 5, 13, 7, 15};
    return __builtin_shuffle(a, b, mask);
}

/* { dg-final { scan-assembler-times "\\mppaire\\.b\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mppaireo\\.b\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mppairoe\\.b\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mppairo\\.b\\M" 1 } } */
