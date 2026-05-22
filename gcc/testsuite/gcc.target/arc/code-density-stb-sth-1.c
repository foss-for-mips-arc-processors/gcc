/* { dg-do compile } */
/* { dg-require-effective-target arcem } */
/* { dg-options "-Os -mno-code-density" } */

volatile char vchar;
volatile short vshort;

void
test_no_stb_s (char x)
{
  vchar = x;
}

void
test_no_sth_s (short x)
{
  vshort = x;
}

/* { dg-final { scan-assembler-not "stb_s\\s+r\[0-9\]" } } */
/* { dg-final { scan-assembler-not "sth_s\\s+r\[0-9\]" } } */
/* { dg-final { scan-assembler "stb\\s+r\[0-9\]" } } */
/* { dg-final { scan-assembler "sth(\\.as)?\\s+r\[0-9\]" } } */
