/* Verify the fusion-spec deviations fixed in arcv_ls_update:

   - Zbb andn/orn/xnor updates.  These negate a source operand, so the base
     register is not the first operand of the canonical RTL (andn/orn wrap a
     register in NOT; xnor is (not (xor ...))).  Per Fused_LD_OP [1] they must
     still fuse when the update reads the load's base register.

   - "[rs1, offset]" addressing.  The spec writes LOAD/STORE ... [rs1, offset],
     so a fused load/store may carry a constant displacement.

   - Fused_ST_OP [4]: a store fused with a two-source update must read *both*
     the base register and the stored value (I1.rs1 == I2.rs1 && I1.rs2 ==
     I2.rs2).  st_op_add/st_op_sub satisfy this; st_op_unrel reads an unrelated
     register as the second source and must therefore NOT fuse.  */

/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32im_zbb -mabi=ilp32 -fdump-rtl-sched2" { target rv32 } } */
/* { dg-options "-O2 -mtune=arc-v-rpx-100-series -march=rv64im_zbb -mabi=lp64 -fdump-rtl-sched2" { target rv64 } } */

/* Load + Zbb andn/orn/xnor: the base register is not RTL operand 0.  */
long
ld_andn (long *p, unsigned long x, long *sink)
{
  long v = *p;
  unsigned long q = (unsigned long) p & ~x;
  *sink = v;
  return (long) q;
}

long
ld_orn (long *p, unsigned long x, long *sink)
{
  long v = *p;
  unsigned long q = (unsigned long) p | ~x;
  *sink = v;
  return (long) q;
}

long
ld_xnor (long *p, unsigned long x, long *sink)
{
  long v = *p;
  unsigned long q = ~((unsigned long) p ^ x);
  *sink = v;
  return (long) q;
}

/* "[rs1, offset]" addressing on the fused load and store.  */
long
ld_off (long *p, unsigned long x, long *sink)
{
  long v = p[1];
  unsigned long q = (unsigned long) p + x;
  *sink = v;
  return (long) q;
}

unsigned long
st_off (long *p, long val)
{
  p[1] = val;
  return (unsigned long) p + 8;
}

/* Fused_ST_OP [4]: update reads the base and the stored value.  */
unsigned long
st_op_add (long *p, long d)
{
  *p = d;
  return (unsigned long) p + (unsigned long) d;
}

unsigned long
st_op_sub (long *p, long d)
{
  *p = d;
  return (unsigned long) p - (unsigned long) d;
}

/* Negative: update's second source is unrelated to the store, so it does not
   satisfy Fused_ST_OP [4] and must not fuse.  It contributes no fusion, so it
   also pins down the expected fusion count below.  */
unsigned long
st_op_unrel (long *p, long d, unsigned long x)
{
  *p = d;
  return (unsigned long) p + x;
}

/* Exactly the seven fusible pairs above must be recognised.  */
/* { dg-final { scan-rtl-dump-times "ARCV_FUSE_LS_UPDATE" 7 "sched2" } } */

/* The fixed updates must still be emitted as their expected instructions.  */
/* { dg-final { scan-assembler {\mandn\M} } } */
/* { dg-final { scan-assembler {\morn\M} } } */
/* { dg-final { scan-assembler {\mxnor\M} } } */
/* { dg-final { scan-assembler {\msub\M} } } */
