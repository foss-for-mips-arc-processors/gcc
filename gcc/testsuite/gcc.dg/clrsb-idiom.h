#ifndef CLRSB_IDIOM_H
#define CLRSB_IDIOM_H

typedef unsigned int u32;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;

/* Keep the signed input cast alive independently of its sign-mask use.  */
#define DEFINE_OWNERSHIP(SUFFIX, U, S, W) \
int __attribute__ ((noipa)) \
clrsb_signed_input##SUFFIX (U u, S *saved) \
{ \
  S x = (S) u; \
  *saved = x; \
  U mask = (U) 0 - (u >> ((W) - 1)); \
  return __builtin_clzg (u ^ mask, W) - 1; \
} \
int __attribute__ ((noipa)) \
clrsb_shared_outer##SUFFIX (S x, U *saved) \
{ \
  U u = (U) x; \
  U folded = x < 0 ? ~u : u; \
  *saved = folded; \
  return __builtin_clzg (folded, W) - 1; \
}

DEFINE_OWNERSHIP (32, u32, s32, 32)
DEFINE_OWNERSHIP (64, u64, s64, 64)

#ifndef CLRSB_OWNERSHIP_ONLY
#define DEFINE_POSITIVE(SUFFIX, U, S, W) \
int __attribute__ ((noipa)) \
clrsb_total##SUFFIX (U u) \
{ \
  U mask = (U) 0 - (u >> ((W) - 1)); \
  return __builtin_clzg (u ^ mask, W) - 1; \
} \
int __attribute__ ((noipa)) \
clrsb_conditional##SUFFIX (S x) \
{ \
  U u = (U) x; \
  return __builtin_clzg (x < 0 ? ~u : u, W) - 1; \
} \
int __attribute__ ((noipa)) \
clrsb_wrong_zero##SUFFIX (U u) \
{ \
  U mask = (U) 0 - (u >> ((W) - 1)); \
  return __builtin_clzg (u ^ mask, (W) - 1) - 1; \
} \
int __attribute__ ((noipa)) \
clrsb_wrong_shift##SUFFIX (U u) \
{ \
  U mask = (U) 0 - (u >> ((W) - 2)); \
  return __builtin_clzg (u ^ mask, W) - 1; \
}

DEFINE_POSITIVE (32, u32, s32, 32)
DEFINE_POSITIVE (64, u64, s64, 64)
#endif

#endif
