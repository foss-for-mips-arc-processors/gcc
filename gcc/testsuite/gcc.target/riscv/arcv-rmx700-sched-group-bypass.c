/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Oz" "-Os" "-Og" } } */
/* { dg-options "-mtune=arc-v-rmx-500-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2-details -marc-v-rmx-500-series-advanced-fusion" } */

void
foo (short *a, short b, int *c, int d)
  {
    int f;

    for (f = 0; f < d; f++)
      c[f] = a[f] * b;
  }

/* check that 1--> a=x*y and 2--> [z] = a are present */
/* { dg-final { scan-rtl-dump {(?m);;\s+1-->(?:(?!\n).)*: i\s+(\d+)\s+([a-z][a-z0-9]+)=(?:(?!\n).)*\*(?:(?!\n).)*MPY[^\n]*\n(?:[^\n]*\n)*?;;\s+2-->(?:(?!\n).)*: i[[:space:]]+[0-9]+[[:space:]]+\[[^\]]+\]=\2} "sched2" } } */
