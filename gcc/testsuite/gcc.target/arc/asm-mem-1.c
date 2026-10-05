/* { dg-do compile } */
/* { dg-options "-O2" } */

typedef unsigned char qi;
typedef unsigned short hi;
typedef unsigned int si;
typedef unsigned long long di;

#define INDEX(T)						\
  void st_index_##T (T *p, int i, T v)				\
  { __asm__ ("st%U0 %1, %0" : "=m" (p[i]) : "r" (v)); }		\
  T ld_index_##T (T *p, int i)					\
  { T v; __asm__ ("ld%U1 %0, %1" : "=r" (v) : "m" (p[i])); return v; }

#define NEAR(T)							\
  void st_near_##T (T *p, T v)					\
  { __asm__ ("st %1, %0" : "=m" (p[3]) : "r" (v)); }		\
  T ld_near_##T (T *p)						\
  { T v; __asm__ ("ld %0, %1" : "=r" (v) : "m" (p[3])); return v; }

#define FAR(T, IDX)						\
  void st_far_##T (T *p, T v)					\
  { __asm__ ("st%U0 %1, %0" : "=m" (p[IDX]) : "r" (v)); }	\
  T ld_far_##T (T *p)						\
  { T v; __asm__ ("ld%U1 %0, %1" : "=r" (v) : "m" (p[IDX])); return v; }

#define GLOBAL(T, G)						\
  T G;								\
  void st_global_##T (T v)					\
  { __asm__ ("st%U0 %1, %0" : "=m" (G) : "r" (v)); }		\
  T ld_global_##T (void)					\
  { T v; __asm__ ("ld%U1 %0, %1" : "=r" (v) : "m" (G)); return v; }

INDEX (qi)
INDEX (hi)
INDEX (si)
INDEX (di)

NEAR (qi)
NEAR (hi)
NEAR (si)
NEAR (di)

FAR (hi, 200)
FAR (si, 100)

GLOBAL (si, gsi)

/* { dg-final { scan-assembler-not {\[r[0-9]+,r[0-9]+\]} } } */
/* { dg-final { scan-assembler-not {(ld|st)\.ab? } } } */

/* { dg-final { scan-assembler-times {st r[0-9]+, \[r[0-9]+,3\]} 1 } } */
/* { dg-final { scan-assembler-times {st r[0-9]+, \[r[0-9]+,6\]} 1 } } */
/* { dg-final { scan-assembler-times {st r[0-9]+, \[r[0-9]+,12\]} 1 } } */
/* { dg-final { scan-assembler-times {st r[0-9]+, \[r[0-9]+,24\]} 1 } } */
/* { dg-final { scan-assembler-times {ld r[0-9]+, \[r[0-9]+,3\]} 1 } } */
/* { dg-final { scan-assembler-times {ld r[0-9]+, \[r[0-9]+,6\]} 1 } } */
/* { dg-final { scan-assembler-times {ld r[0-9]+, \[r[0-9]+,12\]} 1 } } */
/* { dg-final { scan-assembler-times {ld r[0-9]+, \[r[0-9]+,24\]} 1 } } */

/* { dg-final { scan-assembler-times {st\.as r[0-9]+, \[r[0-9]+,200\]} 1 } } */
/* { dg-final { scan-assembler-times {ld\.as r[0-9]+, \[r[0-9]+,200\]} 1 } } */
/* { dg-final { scan-assembler-times {st\.as r[0-9]+, \[r[0-9]+,100\]} 1 } } */
/* { dg-final { scan-assembler-times {ld\.as r[0-9]+, \[r[0-9]+,100\]} 1 } } */
