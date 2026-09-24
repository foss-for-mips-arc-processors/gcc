/* { dg-do compile } */
/* { dg-options "-march=rv64gcb_p0p21 -mabi=lp64d -O2 -Wno-riscv-implicit-extension-version" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

typedef unsigned short V __attribute__((vector_size(8)));

V a = { 0x1, 0x2, 0x3, 0x4 };
V b = { 0x3, 0x4, 0x3, 0x4 };

V test_shuffle(void) {
    V mask = { 0, 4, 2, 6};
    return __builtin_shuffle(a, b, mask);
}

V test_shuffle_2(void) {
    V mask = { 0, 5, 2, 7};
    return __builtin_shuffle(a, b, mask);
}

V test_shuffle_3(void) {
    V mask = { 1, 4, 3, 6};
    return __builtin_shuffle(a, b, mask);
}

V test_shuffle_4(void) {
    V mask = { 1, 5, 3, 7};
    return __builtin_shuffle(a, b, mask);
}

/* { dg-final { scan-assembler-times "\\mppaire\\.h\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mppaireo\\.h\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mppairoe\\.h\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mppairo\\.h\\M" 1 } } */
