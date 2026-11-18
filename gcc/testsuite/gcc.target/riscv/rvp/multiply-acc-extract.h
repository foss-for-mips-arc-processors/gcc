typedef unsigned short acc_v2 __attribute__ ((vector_size (4)));
typedef unsigned short acc_v4 __attribute__ ((vector_size (8)));

#define ACC_LANES(F) \
  F (acc_v2, pair, 0) \
  F (acc_v2, pair, 1) \
  F (acc_v4, quad, 0) \
  F (acc_v4, quad, 1) \
  F (acc_v4, quad, 2) \
  F (acc_v4, quad, 3)

#define ACC_add(P, C) ((P) + (C))
#define ACC_sub(P, C) ((C) - (P))
#define ACC_rsub(P, C) ((P) - (C))

#ifndef ACC_DECLARE_ONLY
#define ACC_ONE(V, N, I, O) \
  __attribute__ ((noipa)) unsigned int \
  N##_##O##_u##I (V c, V a, V b) \
  { \
    V p = a * b; \
    V r = ACC_##O (p, c); \
    return r[I]; \
  } \
  __attribute__ ((noipa)) int \
  N##_##O##_s##I (V c, V a, V b) \
  { \
    V p = a * b; \
    V r = ACC_##O (p, c); \
    return (short) r[I]; \
  } \
  __attribute__ ((noipa)) unsigned int \
  N##_##O##_product_shared_##I (V *out, V c, V a, V b) \
  { \
    V p = a * b; \
    *out = p; \
    V r = ACC_##O (p, c); \
    return r[I]; \
  } \
  __attribute__ ((noipa)) unsigned int \
  N##_##O##_result_shared_##I (V *out, V c, V a, V b) \
  { \
    V p = a * b; \
    V r = ACC_##O (p, c); \
    *out = r; \
    return r[I]; \
  } \
  __attribute__ ((noipa)) unsigned int \
  N##_##O##_acc_shared_##I (V *out, V c, V a, V b) \
  { \
    V p = a * b; \
    V r = ACC_##O (p, c); \
    *out = c; \
    return r[I]; \
  }
#else
#define ACC_ONE(V, N, I, O) \
  extern unsigned int N##_##O##_u##I (V, V, V); \
  extern int N##_##O##_s##I (V, V, V); \
  extern unsigned int N##_##O##_product_shared_##I (V *, V, V, V); \
  extern unsigned int N##_##O##_result_shared_##I (V *, V, V, V); \
  extern unsigned int N##_##O##_acc_shared_##I (V *, V, V, V);
#endif
#define ACC_EXPAND(V, N, I) \
  ACC_ONE (V, N, I, add) \
  ACC_ONE (V, N, I, sub) \
  ACC_ONE (V, N, I, rsub)
ACC_LANES (ACC_EXPAND)
#undef ACC_EXPAND
#undef ACC_ONE

#ifndef ACC_DECLARE_ONLY
#define ACC_DYNAMIC(V, N, O, MASK) \
  __attribute__ ((noipa)) unsigned int \
  N##_##O##_dynamic (V c, V a, V b, unsigned int index) \
  { \
    V p = a * b; \
    V r = ACC_##O (p, c); \
    return r[index & MASK]; \
  }
#else
#define ACC_DYNAMIC(V, N, O, MASK) \
  extern unsigned int N##_##O##_dynamic (V, V, V, unsigned int);
#endif
ACC_DYNAMIC (acc_v2, pair, add, 1)
ACC_DYNAMIC (acc_v2, pair, sub, 1)
ACC_DYNAMIC (acc_v2, pair, rsub, 1)
ACC_DYNAMIC (acc_v4, quad, add, 3)
ACC_DYNAMIC (acc_v4, quad, sub, 3)
ACC_DYNAMIC (acc_v4, quad, rsub, 3)
#undef ACC_DYNAMIC

/* Keep the complete original accumulator observable in the scalar result.
   Its register cannot simply be overwritten by a tied-output MACC.  */
#ifndef ACC_NO_LIVE
#ifndef ACC_DECLARE_ONLY
#define ACC_LIVE(I, O) \
  __attribute__ ((noipa)) unsigned long long \
  pair_##O##_live_##I (acc_v2 c, acc_v2 a, acc_v2 b) \
  { \
    unsigned int original; \
    __builtin_memcpy (&original, &c, sizeof (original)); \
    acc_v2 p = a * b; \
    acc_v2 r = ACC_##O (p, c); \
    return ((unsigned long long) original << 32) | r[I]; \
  }
#else
#define ACC_LIVE(I, O) \
  extern unsigned long long pair_##O##_live_##I (acc_v2, acc_v2, acc_v2);
#endif
ACC_LIVE (0, add)
ACC_LIVE (1, add)
ACC_LIVE (0, sub)
ACC_LIVE (1, sub)
ACC_LIVE (0, rsub)
ACC_LIVE (1, rsub)
#undef ACC_LIVE
#endif
