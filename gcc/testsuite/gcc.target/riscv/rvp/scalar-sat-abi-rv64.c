/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcp -mabi=lp64d" } */
/* { dg-skip-if "assembly only" { *-*-* } { "-flto" } { "" } } */
/* { dg-final { check-function-bodies "**" "" } } */

/* Packed word saturation leaves the upper physical word independently
   computed.  SI returns need ABI sign extension, including unsigned SI;
   explicit unsigned DI consumers instead need zero extension.  */

static inline unsigned int
sat_ua (unsigned int x, unsigned int y)
{
  unsigned int r = x + y;
  return r < x ? ~0U : r;
}

static inline unsigned int
sat_us (unsigned int x, unsigned int y)
{
  return x < y ? 0 : x - y;
}

static inline int
sat_sa (int x, int y)
{
  int r;
  if (__builtin_add_overflow (x, y, &r))
    return x < 0 ? (-2147483647 - 1) : 2147483647;
  return r;
}

static inline int
sat_ss (int x, int y)
{
  int r;
  if (__builtin_sub_overflow (x, y, &r))
    return x < 0 ? (-2147483647 - 1) : 2147483647;
  return r;
}

#define SAT_ABI(NAME, TYPE, WIDE) \
  __attribute__ ((noipa)) TYPE \
  abi_##NAME (TYPE x, TYPE y) \
  { \
    return sat_##NAME (x, y); \
  } \
  __attribute__ ((noipa)) WIDE \
  wide_##NAME (TYPE x, TYPE y) \
  { \
    return sat_##NAME (x, y); \
  } \
  __attribute__ ((noipa)) WIDE \
  trunc_##NAME (unsigned long long x, unsigned long long y) \
  { \
    return sat_##NAME ((TYPE) x, (TYPE) y); \
  }

SAT_ABI (ua, unsigned int, unsigned long long)
SAT_ABI (us, unsigned int, unsigned long long)
SAT_ABI (sa, int, long long)
SAT_ABI (ss, int, long long)
#undef SAT_ABI

/*
** abi_ua:
**  psaddu\.w\s+[a-z][a-z0-9]*,\s*(a0,\s*a1|a1,\s*a0)
**  sext\.w\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/
/*
** wide_ua:
**  psaddu\.w\s+[a-z][a-z0-9]*,\s*(a0,\s*a1|a1,\s*a0)
**  zext\.w\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/
/*
** trunc_ua:
**  psaddu\.w\s+[a-z][a-z0-9]*,\s*(a0,\s*a1|a1,\s*a0)
**  zext\.w\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/
/*
** abi_us:
**  pssubu\.w\s+[a-z][a-z0-9]*,\s*a0,\s*a1
**  sext\.w\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/
/*
** wide_us:
**  pssubu\.w\s+[a-z][a-z0-9]*,\s*a0,\s*a1
**  zext\.w\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/
/*
** trunc_us:
**  pssubu\.w\s+[a-z][a-z0-9]*,\s*a0,\s*a1
**  zext\.w\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/
/*
** abi_sa:
**  psadd\.w\s+[a-z][a-z0-9]*,\s*(a0,\s*a1|a1,\s*a0)
**  sext\.w\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/
/*
** wide_sa:
**  psadd\.w\s+[a-z][a-z0-9]*,\s*(a0,\s*a1|a1,\s*a0)
**  sext\.w\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/
/*
** trunc_sa:
**  psadd\.w\s+[a-z][a-z0-9]*,\s*(a0,\s*a1|a1,\s*a0)
**  sext\.w\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/
/*
** abi_ss:
**  pssub\.w\s+[a-z][a-z0-9]*,\s*a0,\s*a1
**  sext\.w\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/
/*
** wide_ss:
**  pssub\.w\s+[a-z][a-z0-9]*,\s*a0,\s*a1
**  sext\.w\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/
/*
** trunc_ss:
**  pssub\.w\s+[a-z][a-z0-9]*,\s*a0,\s*a1
**  sext\.w\s+a0,\s*[a-z][a-z0-9]*
**  ret
*/
