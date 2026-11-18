typedef unsigned short u16;
typedef unsigned int u32;

u32
swap_unsigned (u32 value)
{
  return __builtin_bswap16 (value);
}

int
swap_signed (u32 value)
{
  return (short) __builtin_bswap16 (value);
}

u32
swap_shared (u16 *out, u32 value)
{
  u16 result = __builtin_bswap16 (value);
  *out = result;
  return value + result;
}
