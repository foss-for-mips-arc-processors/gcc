typedef signed char s8x4 __attribute__ ((vector_size (4)));
typedef unsigned char u8x4 __attribute__ ((vector_size (4)));
typedef short s16x2 __attribute__ ((vector_size (4)));
typedef unsigned short u16x2 __attribute__ ((vector_size (4)));
typedef short s16x4 __attribute__ ((vector_size (8)));
typedef unsigned short u16x4 __attribute__ ((vector_size (8)));
typedef int s32x2 __attribute__ ((vector_size (8)));
typedef unsigned int u32x2 __attribute__ ((vector_size (8)));

#define WIDEN(NAME, S, U, WS, WU) \
  __attribute__ ((noinline, noclone)) WS \
  widen_mul_s_##NAME (S a, S b) \
  { \
    return __builtin_convertvector (a, WS) \
           * __builtin_convertvector (b, WS); \
  } \
  __attribute__ ((noinline, noclone)) WU \
  widen_mul_u_##NAME (U a, U b) \
  { \
    return __builtin_convertvector (a, WU) \
           * __builtin_convertvector (b, WU); \
  } \
  __attribute__ ((noinline, noclone)) WS \
  widen_mul_su_##NAME (S a, U b) \
  { \
    return __builtin_convertvector (a, WS) \
           * __builtin_convertvector (b, WS); \
  } \
  __attribute__ ((noinline, noclone)) WS \
  widen_mul_us_##NAME (U a, S b) \
  { \
    return __builtin_convertvector (a, WS) \
           * __builtin_convertvector (b, WS); \
  } \
  __attribute__ ((noinline, noclone)) WS \
  widen_add_s_##NAME (S a, S b) \
  { \
    return __builtin_convertvector (a, WS) \
           + __builtin_convertvector (b, WS); \
  } \
  __attribute__ ((noinline, noclone)) WS \
  widen_sub_s_##NAME (S a, S b) \
  { \
    return __builtin_convertvector (a, WS) \
           - __builtin_convertvector (b, WS); \
  } \
  __attribute__ ((noinline, noclone)) WU \
  widen_add_u_##NAME (U a, U b) \
  { \
    return __builtin_convertvector (a, WU) \
           + __builtin_convertvector (b, WU); \
  } \
  __attribute__ ((noinline, noclone)) WU \
  widen_sub_u_##NAME (U a, U b) \
  { \
    return __builtin_convertvector (a, WU) \
           - __builtin_convertvector (b, WU); \
  } \
  __attribute__ ((noinline, noclone)) WU \
  widen_mac_s_##NAME (WU acc, S a, S b) \
  { \
    WS wa = __builtin_convertvector (a, WS); \
    WS wb = __builtin_convertvector (b, WS); \
    return acc + (WU) (wa * wb); \
  } \
  __attribute__ ((noinline, noclone)) WU \
  widen_mac_u_##NAME (WU acc, U a, U b) \
  { \
    WU wa = __builtin_convertvector (a, WU); \
    WU wb = __builtin_convertvector (b, WU); \
    return acc + wa * wb; \
  } \
  __attribute__ ((noinline, noclone)) WU \
  widen_mac_su_##NAME (WU acc, S a, U b) \
  { \
    WS wa = __builtin_convertvector (a, WS); \
    WS wb = __builtin_convertvector (b, WS); \
    return acc + (WU) (wa * wb); \
  } \
  __attribute__ ((noinline, noclone)) WU \
  widen_mac_us_##NAME (WU acc, U a, S b) \
  { \
    WS wa = __builtin_convertvector (a, WS); \
    WS wb = __builtin_convertvector (b, WS); \
    return acc + (WU) (wa * wb); \
  } \
  __attribute__ ((noinline, noclone)) WU \
  widen_msub_s_##NAME (WU acc, S a, S b) \
  { \
    WS wa = __builtin_convertvector (a, WS); \
    WS wb = __builtin_convertvector (b, WS); \
    return acc - (WU) (wa * wb); \
  } \
  __attribute__ ((noinline, noclone)) WU \
  widen_shared_##NAME (WU acc, S a, S b) \
  { \
    WS wa = __builtin_convertvector (a, WS); \
    WS wb = __builtin_convertvector (b, WS); \
    return acc + (WU) (wa * wb) + (WU) wa; \
  } \
  __attribute__ ((noinline, noclone)) WU \
  widen_reverse_##NAME (WU acc, U a, U b) \
  { \
    WS wa = __builtin_convertvector ((S) a, WS); \
    WS wb = __builtin_convertvector ((S) b, WS); \
    return acc + (WU) (wa * wb); \
  }

WIDEN (b, s8x4, u8x4, s16x4, u16x4)
WIDEN (h, s16x2, u16x2, s32x2, u32x2)

#undef WIDEN
