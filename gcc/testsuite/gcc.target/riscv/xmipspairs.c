/* { dg-do compile } */
/* { dg-options "-march=rv32gc_xmipslsp -mtune=mips-m8500" { target { rv32 } } } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Os" "-Og" "-Oz" } } */

#define MYTEST(name, mytype) \
void test1 ## name (mytype *a, mytype *total) \
{ \
  mytype b = *a++; \
  mytype c = *a; \
  *total = b + c; \
} \
void test2 ## name (mytype *s, mytype a, mytype b) \
{ \
  *s++ = a; \
  *s = b; \
}

MYTEST(1, long long)
MYTEST(2, unsigned long long)
MYTEST(3, long)
MYTEST(4, unsigned long)
MYTEST(5, int)
MYTEST(6, unsigned long)

/* { dg-final { scan-assembler-times "mips.lwp" 6 } } */
/* { dg-final { scan-assembler-times "mips.swp" 10 } } */
