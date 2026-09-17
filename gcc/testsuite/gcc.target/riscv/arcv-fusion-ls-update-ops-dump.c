/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im_zbb -mabi=ilp32 -fdump-rtl-sched2" { target rv32 } } */
/* { dg-options "-O2 -mtune=arc-v-rpx-100-series -march=rv64im_zbb -mabi=lp64 -fdump-rtl-sched2" { target rv64 } } */

#if __SIZEOF_LONG__ == 8
# define BSWAPL __builtin_bswap64
#else
# define BSWAPL __builtin_bswap32
#endif

#define ST(NAME, EXPR)					\
  unsigned long NAME (long *p, long val)		\
  {							\
    *p = val;						\
    return (EXPR);					\
  }

ST (st_addi,  ((unsigned long) p + 8))			    /* arith    */
ST (st_andi,  ((unsigned long) p & 0xff))		    /* logical  */
ST (st_ori,   ((unsigned long) p | 0xff))		    /* logical  */
ST (st_xori,  ((unsigned long) p ^ 0xff))		    /* logical  */
ST (st_slli,  ((unsigned long) p << 3))			    /* shift    */
ST (st_srli,  ((unsigned long) p >> 3))			    /* shift    */
ST (st_srai,  ((unsigned long) ((long) p >> 3)))	    /* shift    */
ST (st_slti,  ((unsigned long) ((long) p < 99)))	    /* slt      */
ST (st_sltiu, ((unsigned long) ((unsigned long) p < 99u)))  /* slt      */
ST (st_clz,   (__builtin_clzl ((unsigned long) p)))	    /* clz      */
ST (st_ctz,   (__builtin_ctzl ((unsigned long) p)))	    /* ctz      */
ST (st_rev8,  (BSWAPL ((unsigned long) p)))		    /* bitmanip */

#define LD(NAME, EXPR)					\
  long NAME (long *p, unsigned long x, long *sink)	\
  {							\
    long v = *p;					\
    unsigned long q = (EXPR);				\
    *sink = v;						\
    return (long) q;					\
  }

LD (ld_add,  ((unsigned long) p + x))					     /* arith   */
LD (ld_sub,  ((unsigned long) p - x))					     /* arith   */
LD (ld_and,  ((unsigned long) p & x))					     /* logical */
LD (ld_or,   ((unsigned long) p | x))					     /* logical */
LD (ld_xor,  ((unsigned long) p ^ x))					     /* logical */
LD (ld_sll,  ((unsigned long) p << (x & 31)))				     /* shift   */
LD (ld_srl,  ((unsigned long) p >> (x & 31)))				     /* shift   */
LD (ld_sra,  ((unsigned long) ((long) p >> (x & 31))))			     /* shift   */
LD (ld_slt,  ((unsigned long) ((long) p < (long) x)))			     /* slt     */
LD (ld_sltu, ((unsigned long) ((unsigned long) p < x)))			     /* slt     */
LD (ld_min,  ((unsigned long) ((long) p < (long) x ? (long) p : (long) x)))  /* min     */
LD (ld_max,  ((unsigned long) ((long) p > (long) x ? (long) p : (long) x)))  /* max     */
LD (ld_minu, ((unsigned long) p < x ? (unsigned long) p : x))		     /* minu    */
LD (ld_maxu, ((unsigned long) p > x ? (unsigned long) p : x))		     /* maxu    */

/* { dg-final { scan-assembler {\madd\M} } } */
/* { dg-final { scan-assembler {\maddi\M} } } */
/* { dg-final { scan-assembler {\msub\M} } } */
/* { dg-final { scan-assembler {\mand\M} } } */
/* { dg-final { scan-assembler {\mandi\M} } } */
/* { dg-final { scan-assembler {\mor\M} } } */
/* { dg-final { scan-assembler {\mori\M} } } */
/* { dg-final { scan-assembler {\mxor\M} } } */
/* { dg-final { scan-assembler {\mxori\M} } } */
/* { dg-final { scan-assembler {\msll\M} } } */
/* { dg-final { scan-assembler {\mslli\M} } } */
/* { dg-final { scan-assembler {\msrl\M} } } */
/* { dg-final { scan-assembler {\msrli\M} } } */
/* { dg-final { scan-assembler {\msra\M} } } */
/* { dg-final { scan-assembler {\msrai\M} } } */
/* { dg-final { scan-assembler {\mslt\M} } } */
/* { dg-final { scan-assembler {\mslti\M} } } */
/* { dg-final { scan-assembler {\msltu\M} } } */
/* { dg-final { scan-assembler {\msltiu\M} } } */
/* { dg-final { scan-assembler {\mmin\M} } } */
/* { dg-final { scan-assembler {\mmax\M} } } */
/* { dg-final { scan-assembler {\mminu\M} } } */
/* { dg-final { scan-assembler {\mmaxu\M} } } */
/* { dg-final { scan-assembler {\mclz\M} } } */
/* { dg-final { scan-assembler {\mctz\M} } } */
/* { dg-final { scan-assembler {\mrev8\M} } } */
