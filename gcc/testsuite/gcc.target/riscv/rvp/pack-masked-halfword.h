typedef unsigned long long u64;

#define LOW_HALVES 0x0000ffff0000ffffULL
#define HIGH_HALVES 0xffff0000ffff0000ULL
#define ATTR __attribute__ ((noipa))

u64 ATTR
pack_even_halves (u64 a, u64 b)
{
  return (a & LOW_HALVES) | ((b << 16) & HIGH_HALVES);
}

u64 ATTR
pack_even_odd_halves (u64 a, u64 b)
{
  return (a & LOW_HALVES) | (b & HIGH_HALVES);
}

u64 ATTR
pack_odd_even_halves (u64 a, u64 b)
{
  return ((a >> 16) & LOW_HALVES) | ((b << 16) & HIGH_HALVES);
}

u64 ATTR
pack_odd_halves (u64 a, u64 b)
{
  return ((a >> 16) & LOW_HALVES) | (b & HIGH_HALVES);
}

u64 ATTR
mask_even_halves (u64 a)
{
  return a & LOW_HALVES;
}

u64 ATTR
mask_odd_halves (u64 a)
{
  return a & HIGH_HALVES;
}

u64 ATTR
shift_even_halves (u64 a)
{
  return (a << 16) & HIGH_HALVES;
}

u64 ATTR
shift_odd_halves (u64 a)
{
  return (a >> 16) & LOW_HALVES;
}
