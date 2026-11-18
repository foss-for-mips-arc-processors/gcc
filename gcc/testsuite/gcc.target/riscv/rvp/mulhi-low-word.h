#include "round-mulhi.h"

typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;
#define FN __attribute__ ((noipa))

#define SCALAR(NAME, TA, TB, TW, ROUND) \
u32 FN \
low_##NAME (TA a, TB b) \
{ \
  return (u32) (((TW) a * (TW) b + ((TW) ROUND << 31)) >> 32); \
} \
u64 FN \
zero_##NAME (TA a, TB b) \
{ \
  return (u32) (((TW) a * (TW) b + ((TW) ROUND << 31)) >> 32); \
} \
i64 FN \
sign_##NAME (TA a, TB b) \
{ \
  return (i32) (((TW) a * (TW) b + ((TW) ROUND << 31)) >> 32); \
} \
void FN \
store_##NAME (u32 *p, TA a, TB b) \
{ \
  *p = (u32) (((TW) a * (TW) b + ((TW) ROUND << 31)) >> 32); \
}

SCALAR (s, i32, i32, i64, 0)
SCALAR (u, u32, u32, u64, 0)
SCALAR (su, i32, u32, i64, 0)
SCALAR (rs, i32, i32, i64, 1)
SCALAR (ru, u32, u32, u64, 1)
SCALAR (rsu, i32, u32, i64, 1)

u32 FN
low_us (u32 a, i32 b)
{
  return (u32) (((i64) a * (i64) b) >> 32);
}

u32 FN
low_rus (u32 a, i32 b)
{
  return (u32) (((i64) a * (i64) b + 0x80000000LL) >> 32);
}

u64 FN
keep_full (u64 a, u64 b)
{
  u32 low = (u32) (((i64) (i32) a * (i64) (u32) b
		   + 0x80000000LL) >> 32);
  return ((a ^ b) & 0xffffffff00000000ULL) | low;
}

u32 FN
masked_su (i32 a, u32 b)
{
  return (u32) (((i64) a * (i64) (b & 0xffff00ffU)
		+ 0x80000000LL) >> 32);
}

#if defined (__riscv_p) && __riscv_xlen == 64
#include <riscv_packed_simd.h>

/* FULL and SHARED observe both result lanes.  PACKED observes only the
   low lane, and BOTH also explicitly zero-extends the first input.  */
#define PACKED(NAME, OP, SC, TA, TB) \
u64 FN \
full_##NAME (u64 a, u32 b) \
{ \
  u64 bits = b, result; \
  TA va; \
  TB vb; \
  __builtin_memcpy (&va, &a, 8); \
  __builtin_memcpy (&vb, &bits, 8); \
  TA vr = OP (va, vb); \
  __builtin_memcpy (&result, &vr, 8); \
  return result; \
} \
u32 FN \
packed_##NAME (u64 a, u32 b) \
{ \
  u64 bits = b; \
  TA va; \
  TB vb; \
  __builtin_memcpy (&va, &a, 8); \
  __builtin_memcpy (&vb, &bits, 8); \
  TA vr = OP (va, vb); \
  return vr[0]; \
} \
u32 FN \
both_##NAME (u32 a, u32 b) \
{ \
  u64 abits = a, bbits = b; \
  TA va; \
  TB vb; \
  __builtin_memcpy (&va, &abits, 8); \
  __builtin_memcpy (&vb, &bbits, 8); \
  TA vr = OP (va, vb); \
  return vr[0]; \
} \
u32 FN \
builtin_##NAME (u32 a, u32 b) \
{ \
  return SC (a, b); \
} \
u32 FN \
shared_##NAME (u64 a, u32 b, u64 *p) \
{ \
  u64 bits = b; \
  TA va; \
  TB vb; \
  __builtin_memcpy (&va, &a, 8); \
  __builtin_memcpy (&vb, &bits, 8); \
  TA vr = OP (va, vb); \
  __builtin_memcpy (p, &vr, 8); \
  return vr[0]; \
}

PACKED (s, __riscv_pmulh_i32x2, __riscv_mulh_i32, int32x2_t, int32x2_t)
PACKED (u, __riscv_pmulhu_u32x2, __riscv_mulhu_u32, uint32x2_t, uint32x2_t)
PACKED (su, __riscv_pmulhsu_i32x2, __riscv_mulhsu_i32, int32x2_t, uint32x2_t)
PACKED (rs, __riscv_pmulhr_i32x2, __riscv_mulhr_i32, int32x2_t, int32x2_t)
PACKED (ru, __riscv_pmulhru_u32x2, __riscv_mulhru_u32, uint32x2_t, uint32x2_t)
PACKED (rsu, __riscv_pmulhrsu_i32x2, __riscv_mulhrsu_i32, int32x2_t, uint32x2_t)
#endif
