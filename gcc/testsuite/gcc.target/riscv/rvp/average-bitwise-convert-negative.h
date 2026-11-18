typedef signed char s8x8 __attribute__ ((vector_size (8)));
typedef unsigned char u8x8 __attribute__ ((vector_size (8)));
typedef unsigned short u16x4 __attribute__ ((vector_size (8)));

/* Reinterpreting the operands as wider lanes permits carries between
   the original bytes.  A byte average would discard those carries.  */
u16x4 __attribute__ ((noipa))
pun_xor (s8x8 a, s8x8 b)
{
  return (u16x4) (a & b) + (u16x4) ((a ^ b) >> 1);
}

u16x4 __attribute__ ((noipa))
pun_carry (s8x8 a, s8x8 b)
{
  return (u16x4) (a >> 1) + (u16x4) (b >> 1)
    + (u16x4) ((a & b) & 1);
}

/* The shift inputs must agree in signedness.  */
u8x8 __attribute__ ((noipa))
mixed_shift (s8x8 a, u8x8 b)
{
  return (u8x8) (a >> 1) + (b >> 1) + (((u8x8) a & b) & 1);
}
