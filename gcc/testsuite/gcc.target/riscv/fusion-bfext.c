/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

unsigned int
fusion_shift_bitextract (unsigned int x, unsigned int y, unsigned int z)
{
    unsigned int t = x << 8;
    unsigned int a = y + z;
    t = t >> 4;
    return t + a;
}

/* { dg-final { scan-rtl-dump "RISCV_FUSE_BFEXT" "sched2" } } */
