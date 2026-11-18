typedef unsigned short extract_v2 __attribute__ ((vector_size (4)));
typedef unsigned short extract_v4 __attribute__ ((vector_size (8)));

#define EXTRACT_FUNCTIONS(F) \
  F (extract_v2, pair, 0) \
  F (extract_v2, pair, 1) \
  F (extract_v4, quad, 0) \
  F (extract_v4, quad, 1) \
  F (extract_v4, quad, 2) \
  F (extract_v4, quad, 3)

#ifndef EXTRACT_DECLARE_ONLY
#define EXTRACT(V, N, I) \
  __attribute__ ((noipa)) unsigned int \
  N##_mul_##I (V a, V b) \
  { \
    V p = a * b; \
    return p[I]; \
  } \
  __attribute__ ((noipa)) int \
  N##_signed_##I (V a, V b) \
  { \
    V p = a * b; \
    return (short) p[I]; \
  } \
  __attribute__ ((noipa)) unsigned int \
  N##_mac_##I (V acc, V a, V b) \
  { \
    V p = acc + a * b; \
    return p[I]; \
  } \
  __attribute__ ((noipa)) unsigned int \
  N##_plain_##I (V a) \
  { \
    return a[I]; \
  } \
  __attribute__ ((noipa)) unsigned int \
  N##_shared_##I (V *out, V a, V b) \
  { \
    V p = a * b; \
    *out = p; \
    return p[I]; \
  }
#else
#define EXTRACT(V, N, I) \
  extern unsigned int N##_mul_##I (V, V); \
  extern int N##_signed_##I (V, V); \
  extern unsigned int N##_mac_##I (V, V, V); \
  extern unsigned int N##_plain_##I (V); \
  extern unsigned int N##_shared_##I (V *, V, V);
#endif
EXTRACT_FUNCTIONS (EXTRACT)
#undef EXTRACT

#ifndef EXTRACT_DECLARE_ONLY
__attribute__ ((noipa)) unsigned int
pair_dynamic (extract_v2 a, extract_v2 b, unsigned int index)
{
  extract_v2 p = a * b;
  return p[index & 1];
}

__attribute__ ((noipa)) unsigned int
quad_dynamic (extract_v4 a, extract_v4 b, unsigned int index)
{
  extract_v4 p = a * b;
  return p[index & 3];
}
#else
extern unsigned int pair_dynamic (extract_v2, extract_v2, unsigned int);
extern unsigned int quad_dynamic (extract_v4, extract_v4, unsigned int);
#endif
