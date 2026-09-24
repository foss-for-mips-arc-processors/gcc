/* { dg-do compile } */
/* { dg-options "-march=rv64gcb_p0p21 -mabi=lp64d -O2 -Wno-riscv-implicit-extension-version" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Oz" "-Og" "-flto" } } */

typedef unsigned int V __attribute__((vector_size(8)));

V a = { 0x11111111, 0x22222222};
V b = { 0x33333333, 0x44444444};

V test_shuffle(void) {
    V mask = { 0, 2};
    return __builtin_shuffle(a, b, mask);
}

V test_shuffle_2(void) {
    V mask = { 0, 3};
    return __builtin_shuffle(a, b, mask);
}

V test_shuffle_3(void) {
    V mask = { 1, 2};
    return __builtin_shuffle(a, b, mask);
}

V test_shuffle_4(void) {
    V mask = { 1, 3};
    return __builtin_shuffle(a, b, mask);
}

/* { dg-final { scan-assembler-times "\\mpack\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mppaireo\\.w\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mppairoe\\.w\\M" 1 } } */
/* { dg-final { scan-assembler-times "\\mppairo\\.w\\M" 1 } } */
