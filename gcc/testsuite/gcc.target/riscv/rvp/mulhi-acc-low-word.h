typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;
#define FN __attribute__ ((noipa))

u32 FN
low_su (u32 c, i32 a, u32 b)
{
  return c + (u32) (((i64) a * (i64) b) >> 32);
}

u32 FN
low_rsu (u32 c, i32 a, u32 b)
{
  return c + (u32) (((i64) a * (i64) b + 0x80000000LL) >> 32);
}

u32 FN
low_us (u32 c, u32 a, i32 b)
{
  return c + (u32) (((i64) a * (i64) b) >> 32);
}

u32 FN
low_rus (u32 c, u32 a, i32 b)
{
  return c + (u32) (((i64) a * (i64) b + 0x80000000LL) >> 32);
}

u64 FN
zero_su (u32 c, i32 a, u32 b)
{
  return (u32) (c + (u32) (((i64) a * (i64) b) >> 32));
}

u64 FN
zero_rsu (u32 c, i32 a, u32 b)
{
  return (u32) (c + (u32) (((i64) a * (i64) b + 0x80000000LL) >> 32));
}

void FN
store_su (u32 *p, u32 c, i32 a, u32 b)
{
  *p = c + (u32) (((i64) a * (i64) b) >> 32);
}

void FN
store_rsu (u32 *p, u32 c, i32 a, u32 b)
{
  *p = c + (u32) (((i64) a * (i64) b + 0x80000000LL) >> 32);
}

u64 FN
keep_full (u64 c, u64 a, u64 b)
{
  u32 low = (u32) c
	    + (u32) (((i64) (i32) a * (i64) (u32) b) >> 32);
  return ((c ^ a ^ b) & 0xffffffff00000000ULL) | low;
}

u32 FN
masked_su (u32 c, i32 a, u32 b)
{
  return c + (u32) (((i64) a * (i64) (b & 0xffff00ffU)) >> 32);
}

#if defined (__riscv_p) && __riscv_xlen == 64
#include <riscv_packed_simd.h>

/* Both lanes of FULL and SHARED are observable.  B's zero upper word
   must survive even when its ABI argument has nonzero upper bits.  */
#define PACKED(NAME, OP, TC, TA, TB) \
u64 FN \
full_##NAME (u64 c, u64 a, u32 b) \
{ \
  u64 bits = b, result; \
  TC vc; \
  TA va; \
  TB vb; \
  __builtin_memcpy (&vc, &c, 8); \
  __builtin_memcpy (&va, &a, 8); \
  __builtin_memcpy (&vb, &bits, 8); \
  TC vr = OP (vc, va, vb); \
  __builtin_memcpy (&result, &vr, 8); \
  return result; \
} \
u32 FN \
packed_##NAME (u64 c, u64 a, u32 b) \
{ \
  u64 bits = b; \
  TC vc; \
  TA va; \
  TB vb; \
  __builtin_memcpy (&vc, &c, 8); \
  __builtin_memcpy (&va, &a, 8); \
  __builtin_memcpy (&vb, &bits, 8); \
  TC vr = OP (vc, va, vb); \
  return vr[0]; \
} \
u32 FN \
shared_##NAME (u64 c, u64 a, u32 b, u64 *p) \
{ \
  u64 bits = b; \
  TC vc; \
  TA va; \
  TB vb; \
  __builtin_memcpy (&vc, &c, 8); \
  __builtin_memcpy (&va, &a, 8); \
  __builtin_memcpy (&vb, &bits, 8); \
  TC vr = OP (vc, va, vb); \
  __builtin_memcpy (p, &vr, 8); \
  return vr[0]; \
}

PACKED (s, __riscv_pmhacc_i32x2, int32x2_t, int32x2_t, int32x2_t)
PACKED (u, __riscv_pmhaccu_u32x2, uint32x2_t, uint32x2_t, uint32x2_t)
PACKED (su, __riscv_pmhaccsu_i32x2, int32x2_t, int32x2_t, uint32x2_t)
PACKED (rs, __riscv_pmhracc_i32x2, int32x2_t, int32x2_t, int32x2_t)
PACKED (ru, __riscv_pmhraccu_u32x2, uint32x2_t, uint32x2_t, uint32x2_t)
PACKED (rsu, __riscv_pmhraccsu_i32x2, int32x2_t, int32x2_t, uint32x2_t)
#endif
