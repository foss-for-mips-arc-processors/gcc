/* { dg-do compile { target rv32 } } */
/* { dg-options "-march=rv32gc_zilsd -mtune=mips-m8500 -mabi=ilp32d -mno-double-align -mno-rv32-dword-ld" { target { rv32 } } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-Os" "-O1" "-Og" "-g" "-Oz" } } */

void test_load_store_64bit(long long *src, long long *dst) {
    /* Should generate ld instruction */
    long long value = *src;

    /* Should generate sd instruction */
    *dst = value;
}

/* { dg-final { scan-assembler-times "lw\t" 2 } } */
/* { dg-final { scan-assembler-times "sd\t" 1 } } */
/* { dg-final { scan-assembler-not "ld" } } */
