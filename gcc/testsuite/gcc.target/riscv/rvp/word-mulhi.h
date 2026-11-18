typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;
#define FN __attribute__ ((noipa))

#define MIXED(NAME, TA, TB) \
u32 FN \
word_##NAME (TA a, TB b) \
{ \
  return ((i64) a * (i64) b) >> 32; \
} \
u64 FN \
word_##NAME##_zero (TA a, TB b) \
{ \
  return (u32) (((i64) a * (i64) b) >> 32); \
} \
i64 FN \
word_##NAME##_sign (TA a, TB b) \
{ \
  return ((i64) a * (i64) b) >> 32; \
} \
void FN \
word_##NAME##_store (u32 *p, TA a, TB b) \
{ \
  *p = ((i64) a * (i64) b) >> 32; \
} \
u32 FN \
word_##NAME##_shared (u64 *p, TA a, TB b) \
{ \
  i64 product = (i64) a * (i64) b; \
  *p = product; \
  return product >> 32; \
}

MIXED (su, i32, u32)
MIXED (us, u32, i32)

void FN
word_s_store (u32 *p, i32 a, i32 b)
{
  *p = ((i64) a * b) >> 32;
}

void FN
word_u_store (u32 *p, u32 a, u32 b)
{
  *p = ((u64) a * b) >> 32;
}

/* Unknown full-width values must not be treated as extended words.  */
u64 FN
unknown_product (u64 a, u64 b)
{
  return (a * b) >> 32;
}

u64 FN
unknown_left (u64 a, u32 b)
{
  return (a * b) >> 32;
}

i64 FN
shift31 (i32 a, u32 b)
{
  return ((i64) a * b) >> 31;
}

i64 FN
shift33 (i32 a, u32 b)
{
  return ((i64) a * b) >> 33;
}

u32 FN
word_masked (i32 a, u32 b)
{
  return ((i64) a * (b & 0xffff00ffU)) >> 32;
}

u32 FN
word_narrowed (u64 a, u64 b)
{
  return ((i64) (i32) a * (i64) (u32) b) >> 32;
}

u64 FN
word_logical (i32 a, u32 b)
{
  return ((u64) ((i64) a * b)) >> 32;
}

#define LOOP(NAME, TA, TB, TW) \
void FN \
word_##NAME##_loop (u32 *d, const TA *a, const TB *b, unsigned n) \
{ \
  for (unsigned i = 0; i < n; ++i) \
    d[i] = ((TW) a[i] * (TW) b[i]) >> 32; \
}

LOOP (s, i32, i32, i64)
LOOP (u, u32, u32, u64)
LOOP (su, i32, u32, i64)
LOOP (us, u32, i32, i64)
