/* TODO / XFAIL: sign- and zero-extending loads fused with a base-register
   update.

   The fusion spec's LOAD class for Fused_LD_OP [1] / Fused_LD_OP-IMM [2]
   covers all load encodings, including the sub-word loads (lb/lbu/lh/lhu, and
   lw on rv64) whose RTL wraps the memory operand in (sign_extend ...) or
   (zero_extend ...).  arcv_ls_update currently only accepts a bare MEM, so
   these do not fuse yet -- they are deferred for separate testing and
   benchmarking.  When support is added, remove the xfail markers below.  */

/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im_zbb -mabi=ilp32 -fdump-rtl-sched2" { target rv32 } } */
/* { dg-options "-O2 -mtune=arc-v-rpx-100-series -march=rv64im_zbb -mabi=lp64 -fdump-rtl-sched2" { target rv64 } } */

#define LDX(NAME, TYPE)					\
  long NAME (TYPE *p, unsigned long x, long *sink)	\
  {							\
    long v = *p;					\
    unsigned long q = (unsigned long) p + x;		\
    *sink = v;						\
    return (long) q;					\
  }

LDX (ld_sc, signed char)	/* lb  -> (sign_extend (mem)) */
LDX (ld_uc, unsigned char)	/* lbu -> (zero_extend (mem)) */
LDX (ld_ss, short)		/* lh  -> (sign_extend (mem)) */
LDX (ld_us, unsigned short)	/* lhu -> (zero_extend (mem)) */

/* All four extend-load + base-update pairs should fuse per the spec, but the
   implementation defers them for now.  */
/* { dg-final { scan-rtl-dump-times "ARCV_FUSE_LS_UPDATE" 4 "sched2" { xfail *-*-* } } } */
