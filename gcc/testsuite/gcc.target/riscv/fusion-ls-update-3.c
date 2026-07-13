/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im_zbb -mabi=ilp32 -fdump-rtl-sched2" { target rv32 } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv64im_zbb -mabi=lp64 -fdump-rtl-sched2" { target rv64 } } */

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

/* Check the fusion string is present for each function.  */
/* { dg-final { scan-rtl-dump {;; Function st_addi \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function st_andi \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function st_ori \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function st_xori \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function st_slli \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function st_srli \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function st_srai \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function st_slti \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function st_sltiu \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function st_clz \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function st_ctz \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function st_rev8 \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function ld_add \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function ld_sub \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function ld_and \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function ld_or \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function ld_xor \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function ld_sll \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function ld_srl \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function ld_sra \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function ld_slt \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function ld_sltu \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function ld_min \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function ld_max \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function ld_minu \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
/* { dg-final { scan-rtl-dump {;; Function ld_maxu \((?:(?!;; Function).)*RISCV_FUSE_LS_UPDATE} "sched2" } } */
