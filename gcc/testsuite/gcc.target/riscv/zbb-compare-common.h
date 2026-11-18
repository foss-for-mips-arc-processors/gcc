__attribute__ ((noipa)) int
ule_all (unsigned long a, unsigned long b)
{
  return (a <= 4) & (b <= 4);
}

__attribute__ ((noipa)) int
ule_any (unsigned long a, unsigned long b)
{
  return (a <= 4) | (b <= 4);
}

__attribute__ ((noipa)) int
slt_all (long a, long b)
{
  return (a < 5) & (b < 5);
}

__attribute__ ((noipa)) int
slt_any (long a, long b)
{
  return (a < 5) | (b < 5);
}

/* RV64 compares sign-extended argument values but returns an SImode flag.  */
__attribute__ ((noipa)) int
u32_ule_all (unsigned int a, unsigned int b)
{
  return (a <= 4) & (b <= 4);
}

__attribute__ ((noipa)) int
u32_ule_any (unsigned int a, unsigned int b)
{
  return (a <= 4) | (b <= 4);
}
