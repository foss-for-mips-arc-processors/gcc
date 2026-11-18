typedef unsigned long long u64;
typedef long long s64;

u64 __attribute__ ((noipa))
acc_unsigned (unsigned int a, unsigned int b, u64 acc)
{
  return acc + a + b;
}

u64 __attribute__ ((noipa))
acc_signed (int a, int b, u64 acc)
{
  return acc + (s64) a + (s64) b;
}

u64 __attribute__ ((noipa))
acc_one_unsigned (unsigned int a, u64 acc)
{
  return acc + a;
}

u64 __attribute__ ((noipa))
acc_one_signed (int a, u64 acc)
{
  return acc + (s64) a;
}

u64 __attribute__ ((noipa))
add_unsigned (unsigned int a, unsigned int b)
{
  return (u64) a + b;
}

s64 __attribute__ ((noipa))
add_signed (int a, int b)
{
  return (s64) a + b;
}
