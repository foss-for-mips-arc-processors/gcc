/* { dg-do run } */
/* { dg-skip-if "" { *-*-* } { "-mcpu=*" } { "-mcpu=hs38_linux" } } */
/* { dg-options "-O3 -mcpu=hs38_linux -save-temps -fdump-rtl-expand" } */

typedef int v2si __attribute__ ((vector_size (8)));

int __attribute__ ((noinline, noclone))
sum_v2si (v2si x)
{
  return x[0] + x[1];
}

short __attribute__ ((noinline, noclone))
sum_hi (short *p, int n)
{
  short s = 0;
  for (int i = 0; i < n; i++)
    s += p[i];
  return s;
}

unsigned int m;
#define N 128
unsigned int a[N];

unsigned int __attribute__ ((noipa))
df_count_refs (_Bool include_defs)
{
  int size = 0;
  for (unsigned int regno = 0; regno < m; regno++)
    if (include_defs)
      size += a[regno];
  return size;
}

int
main (void)
{
  v2si v = { 40, 2 };
  short h[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };

  if (sum_v2si (v) != 42)
    __builtin_abort ();
  if (sum_hi (h, 8) != 36)
    __builtin_abort ();

  for (unsigned i = 0; i < N; i++)
    a[i] = i;
  m = 17;
  if (df_count_refs (1) != 136)
    __builtin_abort ();

  return 0;
}

/* { dg-final { scan-rtl-dump "unspec:DI \\\[\\n\[^\\n\]*\\n\[^\\n\]*UNSPEC_ARC_DMPYWH" "expand" } } */
/* { dg-final { scan-rtl-dump "unspec:DI \\\[\\n\[^\\n\]*\\n\[^\\n\]*UNSPEC_ARC_QMPYH" "expand" } } */

/* register pair must use an even destination.  */
/* { dg-final { scan-assembler-not "dmpywh\\s+r\[0-9\]*\[13579\]," } } */
/* { dg-final { scan-assembler-not "qmpyh\\s+r\[0-9\]*\[13579\]," } } */
