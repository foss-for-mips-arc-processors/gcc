/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gc_zba -mabi=lp64d -mfusion=expanded-ld -fno-lto -fdump-rtl-sched2" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Og" "-Os" "-Oz" "-flto" "-finline-functions" "-funroll-loops" "-ftracer" } } */
/* { dg-final { scan-rtl-dump-times "RISCV_FUSE_EXPANDED_LD" 5 "sched2" } } */

struct newtype
{
  long long a;
  char b;
};

long long fubar (struct newtype data[100], long long sum)
{
  int inc = 1;
  long long pt;

  for (int i = 0; i < 10; i++)
    {
       inc += i;
       pt += i;
       sum += pt;
       pt = data[inc + 1].a;
    }

  return sum;
}

struct newtype2
{
  long long a;
};

long long fubar2 (struct newtype2 data[100], long long sum)
{
  int inc = 1;
  long long pt;

  for (int i = 0; i < 10; i++)
    {
       inc += i;
       pt += i;
       sum += pt + 5;
       pt = data[inc + 1].a;
    }

  return sum;
}

long long fubar3 (struct newtype2 data[100], long long sum)
{
  int inc = 1;
  long long pt;

  for (int i = 0; i < 10; i++)
    {
       inc += i;
       pt += i;
       sum += pt + 5;
       pt = data[inc].a;
    }

  return sum;
}

struct newtype3
{
  unsigned int a;
  unsigned int b;
};

void foo (struct newtype3 data[5], unsigned int val);

void fubar4 (struct newtype3 data[5], unsigned int idx)
{
  foo (data, data[idx].a);
}

void fubar5 (struct newtype3 data[5], unsigned int idx)
{
  foo (data, data[idx].b);
}

void foo2 (char data[5], unsigned int val);

void fubar6 (char data[5], unsigned int idx)
{
  foo2 (data, data[idx]);
}
