/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-Oz" "-Os" "-Og" } } */
/* { dg-options "-mtune=arc-v-rmx-500-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

void
foo (int *a)
{
  a[2] = a[1] * a[0];
}

void
bar (int *a)
{
  int *addr = (int *) (a[1] * a[2]);
  *addr = 0;
}

int
baz (int *a)
{
  int *addr = (int *) (a[1] * a[2]);
  return *addr;
}

/* { dg-final { scan-rtl-dump "(?s);; Function foo.*?;;\\s+1-->.*i\\s+\\d+\\s+.*\\*.*:\\(arcv.*?;;\\s+2-->.*\\\[.*\\+0x8\\\]=" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s);; Function bar.*?;;\\s+1-->.*i\\s+\\d+\\s+.*\\*.*:\\(arcv.*?;;\\s+6-->.*\\\[.*\\\]=0" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s);; Function baz.*?;;\\s+1-->.*i\\s+\\d+\\s+.*\\*.*:\\(arcv.*?;;\\s+6-->.*=\\\[.*\\\]" "sched2" } } */
