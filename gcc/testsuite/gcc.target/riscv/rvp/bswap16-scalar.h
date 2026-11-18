typedef unsigned short u16;
typedef unsigned int u32;

void
swap_store (u16 *out, u32 value)
{
  *out = __builtin_bswap16 (value);
}

void
swap_volatile (volatile u16 *out, const volatile u16 *in)
{
  *out = __builtin_bswap16 (*in);
}

