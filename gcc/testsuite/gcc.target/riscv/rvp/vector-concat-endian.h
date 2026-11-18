typedef unsigned long long concat_uint64;
typedef unsigned char concat_q4 __attribute__ ((vector_size (4)));
typedef unsigned short concat_h2 __attribute__ ((vector_size (4)));
typedef unsigned short concat_h4 __attribute__ ((vector_size (8)));
typedef unsigned int concat_w2 __attribute__ ((vector_size (8)));

#if !defined (CONCAT_CASE) || CONCAT_CASE == 0
__attribute__ ((noipa)) concat_h2
concat_h_ctor (unsigned int a, unsigned int b)
{
  return (concat_h2) { a, b };
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 1
__attribute__ ((noipa)) concat_h2
concat_h_ctor_signed (int a, int b)
{
  return (concat_h2) { a, b };
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 2
__attribute__ ((noipa)) concat_h2
concat_h_ctor_eo (unsigned int a, unsigned int b)
{
  return (concat_h2) { a, b >> 16 };
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 3
__attribute__ ((noipa)) concat_h2
concat_h_ctor_oe (unsigned int a, unsigned int b)
{
  return (concat_h2) { a >> 16, b };
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 4
__attribute__ ((noipa)) concat_h2
concat_h_ctor_oo (unsigned int a, unsigned int b)
{
  return (concat_h2) { a >> 16, b >> 16 };
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 5
__attribute__ ((noipa)) concat_h2
concat_h_mul (concat_h2 a, concat_h2 b)
{
  return a * b;
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 6
__attribute__ ((noipa)) unsigned int
concat_h_mul0 (concat_h2 a, concat_h2 b)
{
  concat_h2 r = a * b;
  return r[0];
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 7
__attribute__ ((noipa)) unsigned int
concat_h_mul1 (concat_h2 a, concat_h2 b)
{
  concat_h2 r = a * b;
  return r[1];
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 8
__attribute__ ((noipa)) concat_h2
concat_h_mac (concat_h2 c, concat_h2 a, concat_h2 b)
{
  return c + a * b;
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 9
__attribute__ ((noipa)) unsigned int
concat_h_mac0 (concat_h2 c, concat_h2 a, concat_h2 b)
{
  concat_h2 r = c + a * b;
  return r[0];
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 10
__attribute__ ((noipa)) unsigned int
concat_h_mac1 (concat_h2 c, concat_h2 a, concat_h2 b)
{
  concat_h2 r = c + a * b;
  return r[1];
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 11
__attribute__ ((noipa)) concat_h2
concat_h_shared (concat_h2 c, concat_h2 a, concat_h2 b)
{
  concat_h2 p = a * b;
  __asm__ volatile ("" : "+r" (p));
  concat_h2 r = c + p;
  return (concat_h2) { p[0], r[1] };
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 12
__attribute__ ((noipa)) concat_uint64
concat_h_live0 (concat_h2 c, concat_h2 a, concat_h2 b)
{
  concat_h2 r = c + a * b;
  __asm__ volatile ("" : "+r" (r) : "r" (c));
  unsigned int original;
  __builtin_memcpy (&original, &c, sizeof (original));
  return ((concat_uint64) original << 32) | r[0];
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 13
__attribute__ ((noipa)) concat_uint64
concat_h_live1 (concat_h2 c, concat_h2 a, concat_h2 b)
{
  concat_h2 r = c + a * b;
  __asm__ volatile ("" : "+r" (r) : "r" (c));
  unsigned int original;
  __builtin_memcpy (&original, &c, sizeof (original));
  return ((concat_uint64) original << 32) | r[1];
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 14
__attribute__ ((noipa)) concat_h2
concat_h_identity (concat_h2 a)
{
  return a;
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 15
__attribute__ ((noipa)) concat_h2
concat_h_memory (const concat_h2 *a, const concat_h2 *b)
{
  return *a * *b;
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 16
__attribute__ ((noipa)) concat_w2
concat_w_ctor (unsigned int a, unsigned int b)
{
  return (concat_w2) { a, b };
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 17
__attribute__ ((noipa)) concat_w2
concat_w_ctor_signed (int a, int b)
{
  return (concat_w2) { a, b };
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 18
__attribute__ ((noipa)) concat_w2
concat_w_ctor_eo (concat_uint64 a, concat_uint64 b)
{
  return (concat_w2) { a, b >> 32 };
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 19
__attribute__ ((noipa)) concat_w2
concat_w_ctor_oe (concat_uint64 a, concat_uint64 b)
{
  return (concat_w2) { a >> 32, b };
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 20
__attribute__ ((noipa)) concat_w2
concat_w_ctor_oo (concat_uint64 a, concat_uint64 b)
{
  return (concat_w2) { a >> 32, b >> 32 };
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 21
__attribute__ ((noipa)) concat_w2
concat_w_mul (concat_w2 a, concat_w2 b)
{
  return a * b;
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 22
__attribute__ ((noipa)) unsigned int
concat_w_mul0 (concat_w2 a, concat_w2 b)
{
  concat_w2 r = a * b;
  return r[0];
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 23
__attribute__ ((noipa)) unsigned int
concat_w_mul1 (concat_w2 a, concat_w2 b)
{
  concat_w2 r = a * b;
  return r[1];
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 24
__attribute__ ((noipa)) concat_w2
concat_w_mac (concat_w2 c, concat_w2 a, concat_w2 b)
{
  return c + a * b;
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 25
__attribute__ ((noipa)) unsigned int
concat_w_mac0 (concat_w2 c, concat_w2 a, concat_w2 b)
{
  concat_w2 r = c + a * b;
  return r[0];
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 26
__attribute__ ((noipa)) unsigned int
concat_w_mac1 (concat_w2 c, concat_w2 a, concat_w2 b)
{
  concat_w2 r = c + a * b;
  return r[1];
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 27
__attribute__ ((noipa)) concat_w2
concat_w_shared (concat_w2 c, concat_w2 a, concat_w2 b)
{
  concat_w2 p = a * b;
  __asm__ volatile ("" : "+r" (p));
  concat_w2 r = c + p;
  return (concat_w2) { p[0], r[1] };
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 28
__attribute__ ((noipa)) concat_uint64
concat_w_live0 (concat_w2 c, concat_w2 a, concat_w2 b)
{
  concat_w2 r = c + a * b;
  __asm__ volatile ("" : "+r" (r) : "r" (c));
  unsigned int original = c[0] ^ c[1];
  return ((concat_uint64) original << 32) | r[0];
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 29
__attribute__ ((noipa)) concat_uint64
concat_w_live1 (concat_w2 c, concat_w2 a, concat_w2 b)
{
  concat_w2 r = c + a * b;
  __asm__ volatile ("" : "+r" (r) : "r" (c));
  unsigned int original = c[0] ^ c[1];
  return ((concat_uint64) original << 32) | r[1];
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 30
__attribute__ ((noipa)) concat_w2
concat_w_identity (concat_w2 a)
{
  return a;
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 31
__attribute__ ((noipa)) concat_w2
concat_w_memory (const concat_w2 *a, const concat_w2 *b)
{
  return *a * *b;
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 32
__attribute__ ((noipa)) concat_uint64
concat_original_wide (concat_h2 c, concat_h2 a, concat_h2 b)
{
  unsigned int original;
  __builtin_memcpy (&original, &c, sizeof (original));
  concat_h2 r = c + a * b;
  return ((concat_uint64) original << 32) | r[0];
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 33
__attribute__ ((noipa)) concat_h2
concat_h_set0 (concat_h2 a, unsigned int value)
{
  a[0] = value;
  return a;
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 34
__attribute__ ((noipa)) concat_h2
concat_h_set1 (concat_h2 a, unsigned int value)
{
  a[1] = value;
  return a;
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 35
__attribute__ ((noipa)) concat_w2
concat_w_set0 (concat_w2 a, unsigned int value)
{
  a[0] = value;
  return a;
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 36
__attribute__ ((noipa)) concat_w2
concat_w_set1 (concat_w2 a, unsigned int value)
{
  a[1] = value;
  return a;
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 37
__attribute__ ((noipa)) concat_q4
concat_narrow_low (concat_h2 a, concat_h2 b)
{
  concat_h4 joined = { a[0], a[1], b[0], b[1] };
  return __builtin_convertvector (joined, concat_q4);
}
#endif

#if !defined (CONCAT_CASE) || CONCAT_CASE == 38
__attribute__ ((noipa)) concat_q4
concat_narrow_high (concat_h2 a, concat_h2 b)
{
  concat_h4 joined = { a[0], a[1], b[0], b[1] };
  joined >>= 8;
  return __builtin_convertvector (joined, concat_q4);
}
#endif
