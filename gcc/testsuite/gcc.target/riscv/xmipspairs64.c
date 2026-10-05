/* { dg-do compile } */
/* { dg-options "-std=c99 -march=rv64gc_xmipslsp -mtune=mips-i8500 -mno-double-align" { target { rv64 } } } */
/* { dg-skip-if "" { *-*-* } { "-ansi" "-pedantic" "-O0" "-O1" "-Os" "-Og" "-Oz" } } */

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

/* { dg-final { scan-assembler-times "mips.lwp" 1 } } */
/* { dg-final { scan-assembler-times "mips.swp" 1 } } */
/* { dg-final { scan-assembler-times "mips.ldp" 5 } } */
/* { dg-final { scan-assembler-times "mips.sdp" 5 } } */
