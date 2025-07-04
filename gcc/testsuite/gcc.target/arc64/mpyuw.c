/* { dg-do compile } */
/* { dg-options "-O2 -dp" } */

// Should produce 4-byte mpyuw using the "mpyuw b, b, s12" variant.
unsigned eleven_bits(unsigned short x)
{
  /* { dg-final { scan-assembler "mpyuw\\s+r0,r0,1237\\s+.+\[c=..\\s+l=4\]\\s+umulhisi3i/2" } } */
  return (unsigned) x * 1237;
}

// Should be 8 bytes because it doesn't fit in a 12-byte signed integer encoding.
unsigned sixteen_bits(unsigned short x)
{
  /* { dg-final { scan-assembler "mpyuw\\s+r0,r0,2237\\s+.+\[c=..\\s+l=8\]\\s+umulhisi3i/3" } } */
  return (unsigned) x * 2237;
}
