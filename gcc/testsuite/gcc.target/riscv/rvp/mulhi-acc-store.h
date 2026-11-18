typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;
#define FN __attribute__ ((noipa))

#define STORE(NAME, TA, TB, TW, BIAS) \
void FN \
memory_##NAME (u32 *p, TA a, TB b) \
{ \
  *p += (u32) (((TW) a * (TW) b + (BIAS)) >> 32); \
}

STORE (s, i32, i32, i64, 0)
STORE (u, u32, u32, u64, 0)
STORE (su, i32, u32, i64, 0)
STORE (us, u32, i32, i64, 0)
STORE (rs, i32, i32, i64, 0x80000000LL)
STORE (ru, u32, u32, u64, 0x80000000ULL)
STORE (rsu, i32, u32, i64, 0x80000000LL)
STORE (rus, u32, i32, i64, 0x80000000LL)

/* Unlike the word updates above, this addition preserves the carry.  */
void FN
wide_sum (u64 *p, i32 a, i32 b)
{
  *p += (u32) (((i64) a * b) >> 32);
}

void FN
shared_high (u32 *p, u32 *saved, i32 a, i32 b)
{
  u32 high = ((i64) a * b) >> 32;
  *saved = high;
  *p += high;
}

void FN
volatile_sum (volatile u32 *p, i32 a, i32 b)
{
  *p += (u32) (((i64) a * b) >> 32);
}

void FN
shift31 (u32 *p, i32 a, i32 b)
{
  *p += (u32) (((i64) a * b) >> 31);
}

void FN
unknown_inputs (u32 *p, u64 a, u64 b)
{
  *p += (u32) ((a * b) >> 32);
}

#if defined (__riscv_p) && __riscv_xlen == 64
#include <riscv_packed_simd.h>

/* Keep full packed results observable in SHARED, including their upper
   lane.  STORE consumes only the low lane but still writes a full GPR.  */
#define PACKED(NAME, OP, TA, TB) \
void FN \
packed_##NAME (u32 *p, u64 a, u64 b) \
{ \
  TA va; \
  TB vb; \
  __builtin_memcpy (&va, &a, 8); \
  __builtin_memcpy (&vb, &b, 8); \
  TA high = OP (va, vb); \
  *p += (u32) high[0]; \
} \
void FN \
shared_##NAME (u32 *p, u64 *saved, u64 a, u64 b) \
{ \
  TA va; \
  TB vb; \
  __builtin_memcpy (&va, &a, 8); \
  __builtin_memcpy (&vb, &b, 8); \
  TA high = OP (va, vb); \
  __builtin_memcpy (saved, &high, 8); \
  *p += (u32) high[0]; \
}

PACKED (s, __riscv_pmulh_i32x2, int32x2_t, int32x2_t)
PACKED (u, __riscv_pmulhu_u32x2, uint32x2_t, uint32x2_t)
PACKED (su, __riscv_pmulhsu_i32x2, int32x2_t, uint32x2_t)
PACKED (rs, __riscv_pmulhr_i32x2, int32x2_t, int32x2_t)
PACKED (ru, __riscv_pmulhru_u32x2, uint32x2_t, uint32x2_t)
PACKED (rsu, __riscv_pmulhrsu_i32x2, int32x2_t, uint32x2_t)
#endif
