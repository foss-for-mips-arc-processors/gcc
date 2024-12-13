/* { dg-do compile } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series" } */

int
f (int x)
{
  begin:
  if (x <= 3)
    goto begin;
}

/* { dg-final { scan-assembler "\\sli\\sa5,3\n\\sble\\sa0,a5,.L\[0-9\]+\n" } } */
