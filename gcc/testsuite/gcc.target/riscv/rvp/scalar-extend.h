typedef unsigned long long extend_uint64;
typedef long long extend_int64;

#ifndef EXTEND_DECLARE_ONLY

__attribute__ ((noipa)) extend_uint64
extend_uwadda (extend_uint64 c, unsigned int a, unsigned int b)
{
  return c + ((extend_uint64) a + b);
}

__attribute__ ((noipa)) extend_uint64
extend_swadda (extend_uint64 c, int a, int b)
{
  return c + (extend_uint64) ((extend_int64) a + b);
}

__attribute__ ((noipa)) extend_uint64
extend_uwsuba (extend_uint64 c, unsigned int a, unsigned int b)
{
  return c + ((extend_uint64) a - (extend_uint64) b);
}

__attribute__ ((noipa)) extend_uint64
extend_swsuba (extend_uint64 c, int a, int b)
{
  return c + (extend_uint64) ((extend_int64) a - b);
}

__attribute__ ((noipa)) extend_uint64
extend_u_add (extend_uint64 c, unsigned int a)
{
  return c + a;
}

__attribute__ ((noipa)) extend_uint64
extend_s_add (extend_uint64 c, int a)
{
  return c + (extend_uint64) (extend_int64) a;
}
#else
extern extend_uint64 extend_uwadda (extend_uint64, unsigned int, unsigned int);
extern extend_uint64 extend_swadda (extend_uint64 c, int a, int b);
extern extend_uint64 extend_uwsuba (extend_uint64, unsigned int, unsigned int);
extern extend_uint64 extend_swsuba (extend_uint64 c, int a, int b);
extern extend_uint64 extend_u_add (extend_uint64 c, unsigned int a);
extern extend_uint64 extend_s_add (extend_uint64 c, int a);
#endif

#ifndef EXTEND_DECLARE_ONLY
#define EXTEND_REG(S, T, R) \
  __attribute__ ((noipa)) R \
  extend_##S##0 (T x) \
  { \
    return x; \
  } \
  __attribute__ ((noipa)) R \
  extend_##S##1 (unsigned int unused, T x) \
  { \
    return x; \
  } \
  __attribute__ ((noipa)) R \
  extend_##S##2 (unsigned int unused0, unsigned int unused1, T x) \
  { \
    return x; \
  } \
  __attribute__ ((noipa)) R \
  extend_##S##m (const T *x) \
  { \
    return *x; \
  }
#else
#define EXTEND_REG(S, T, R) \
  extern R extend_##S##0 (T); \
  extern R extend_##S##1 (unsigned int, T); \
  extern R extend_##S##2 (unsigned int, unsigned int, T); \
  extern R extend_##S##m (const T *);
#endif
EXTEND_REG (u, unsigned int, extend_uint64)
EXTEND_REG (s, int, extend_int64)
#undef EXTEND_REG

/* Generic scalar pair operations must use the scalar ABI word order.  */
#ifndef EXTEND_DECLARE_ONLY

__attribute__ ((noipa)) extend_uint64
extend_add64 (extend_uint64 a, extend_uint64 b)
{
  return a + b;
}

__attribute__ ((noipa)) extend_uint64
extend_sub64 (extend_uint64 a, extend_uint64 b)
{
  return a - b;
}

__attribute__ ((noipa)) extend_uint64
extend_neg64 (extend_uint64 a)
{
  return -a;
}

__attribute__ ((noipa)) extend_uint64
extend_umul (unsigned int a, unsigned int b)
{
  return (extend_uint64) a * b;
}

__attribute__ ((noipa)) extend_int64
extend_smul (int a, int b)
{
  return (extend_int64) a * b;
}

__attribute__ ((noipa)) extend_int64
extend_sumul (int a, unsigned int b)
{
  return (extend_int64) a * b;
}

__attribute__ ((noipa)) extend_uint64
extend_uadd (unsigned int a, unsigned int b)
{
  return (extend_uint64) a + b;
}

__attribute__ ((noipa)) extend_uint64
extend_usub (unsigned int a, unsigned int b)
{
  return (extend_uint64) a - (extend_uint64) b;
}

__attribute__ ((noipa)) extend_int64
extend_sadd (int a, int b)
{
  return (extend_int64) a + b;
}

__attribute__ ((noipa)) extend_int64
extend_ssub (int a, int b)
{
  return (extend_int64) a - b;
}

__attribute__ ((noipa)) extend_uint64
extend_umacc (extend_uint64 c, unsigned int a, unsigned int b)
{
  return c + (extend_uint64) a * b;
}

__attribute__ ((noipa)) extend_uint64
extend_smacc (extend_uint64 c, int a, int b)
{
  return c + (extend_uint64) ((extend_int64) a * b);
}

__attribute__ ((noipa)) extend_uint64
extend_sumacc (extend_uint64 c, int a, unsigned int b)
{
  return c + (extend_uint64) ((extend_int64) a * b);
}

__attribute__ ((noipa)) extend_uint64
extend_umsub (extend_uint64 c, unsigned int a, unsigned int b)
{
  return c - (extend_uint64) a * b;
}

__attribute__ ((noipa)) extend_uint64
extend_smsub (extend_uint64 c, int a, int b)
{
  return c - (extend_uint64) ((extend_int64) a * b);
}
#else
extern extend_uint64 extend_add64 (extend_uint64 a, extend_uint64 b);
extern extend_uint64 extend_sub64 (extend_uint64 a, extend_uint64 b);
extern extend_uint64 extend_neg64 (extend_uint64 a);
extern extend_uint64 extend_umul (unsigned int a, unsigned int b);
extern extend_int64 extend_smul (int a, int b);
extern extend_int64 extend_sumul (int a, unsigned int b);
extern extend_uint64 extend_uadd (unsigned int a, unsigned int b);
extern extend_uint64 extend_usub (unsigned int a, unsigned int b);
extern extend_int64 extend_sadd (int a, int b);
extern extend_int64 extend_ssub (int a, int b);
extern extend_uint64 extend_umacc (extend_uint64, unsigned int, unsigned int);
extern extend_uint64 extend_smacc (extend_uint64 c, int a, int b);
extern extend_uint64 extend_sumacc (extend_uint64 c, int a, unsigned int b);
extern extend_uint64 extend_umsub (extend_uint64, unsigned int, unsigned int);
extern extend_uint64 extend_smsub (extend_uint64 c, int a, int b);
#endif

/* Packed arithmetic intermediates also return ordinary scalar pairs.  */
#ifndef EXTEND_DECLARE_ONLY

__attribute__ ((noipa)) extend_int64
extend_dot (unsigned int a, unsigned int b)
{
  return ((extend_int64) (short) a * (short) b
          + (extend_int64) (short) (a >> 16) * (short) (b >> 16));
}

__attribute__ ((noipa)) extend_int64
extend_cross_dot (unsigned int a, unsigned int b)
{
  return ((extend_int64) (short) a * (short) (b >> 16)
          + (extend_int64) (short) (a >> 16) * (short) b);
}

__attribute__ ((noipa)) extend_int64
extend_difference (unsigned int a, unsigned int b)
{
  return ((extend_int64) (short) a * (short) b
          - (extend_int64) (short) (a >> 16) * (short) (b >> 16));
}

__attribute__ ((noipa)) extend_int64
extend_cross_difference (unsigned int a, unsigned int b)
{
  return ((extend_int64) (short) a * (short) (b >> 16)
          - (extend_int64) (short) (a >> 16) * (short) b);
}

#define EXTEND_SCALED(NAME, T, SHIFT) \
  __attribute__ ((noipa)) T \
  NAME (unsigned int a, unsigned int b) \
  { \
    return (int) (((extend_int64) (int) a * (short) (b >> SHIFT)) >> 16); \
  }
EXTEND_SCALED (extend_scaled_low, extend_int64, 0)
EXTEND_SCALED (extend_scaled_high, extend_int64, 16)
EXTEND_SCALED (extend_scaled_low_si, int, 0)
EXTEND_SCALED (extend_scaled_high_si, int, 16)
#undef EXTEND_SCALED

#else
extern extend_int64 extend_dot (unsigned int, unsigned int);
extern extend_int64 extend_cross_dot (unsigned int, unsigned int);
extern extend_int64 extend_difference (unsigned int, unsigned int);
extern extend_int64 extend_cross_difference (unsigned int, unsigned int);
extern extend_int64 extend_scaled_low (unsigned int, unsigned int);
extern extend_int64 extend_scaled_high (unsigned int, unsigned int);
extern int extend_scaled_low_si (unsigned int, unsigned int);
extern int extend_scaled_high_si (unsigned int, unsigned int);
#endif
