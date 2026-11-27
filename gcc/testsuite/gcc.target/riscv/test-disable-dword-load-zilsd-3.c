/* { dg-do compile { target rv32 } } */
/* { dg-options "-march=rv32gc_zilsd -mtune=mips-m8500 -mabi=ilp32d -mno-double-align -mno-rv32-dword-ld" { target { rv32 } } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-Os" "-O1" "-Og" "-g" "-Oz" } } */

extern void abort (void);

typedef unsigned long long ull;

__attribute__ ((noipa)) ull
bump (ull x, ull y)
{
  return x + y + 1;
}

__attribute__ ((noipa)) ull
pressure (const ull *p)
{
  ull v0 = p[0], v1 = p[1], v2 = p[2], v3 = p[3], v4 = p[4];
  ull v5 = p[5], v6 = p[6], v7 = p[7], v8 = p[8], v9 = p[9];

  ull t = bump (v0, v9);		/* v0..v9 are all live across this */

  return v0 + v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8 + v9 + t;
}

/* { dg-final { scan-assembler {\tsd\t\S+,\d+\(sp\)} } } */
/* { dg-final { scan-assembler {\tlw\t\S+,\d+\(sp\)} } } */

/* { dg-final { scan-assembler-not "ld" } } */
