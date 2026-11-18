typedef unsigned long long u64;

u64 __attribute__ ((noipa))
return_zero (void)
{
  return 0;
}

u64 __attribute__ ((noipa))
even_zero (void)
{
  register u64 value asm ("a4") = 0;
  asm volatile ("" : "+r" (value));
  return value;
}

u64 __attribute__ ((noipa))
partial_high (unsigned int high)
{
  u64 value = (u64) high << 32;
  asm volatile ("" : "+r" (value));
  return value;
}

u64 __attribute__ ((noipa))
partial_low (unsigned int low)
{
  u64 value = low;
  asm volatile ("" : "+r" (value));
  return value;
}

u64 __attribute__ ((noipa))
odd_words (void)
{
  register unsigned int low asm ("a3") = 0;
  register unsigned int high asm ("a4") = 0;
  asm volatile ("" : "+r" (low), "+r" (high));
  return low | ((u64) high << 32);
}
