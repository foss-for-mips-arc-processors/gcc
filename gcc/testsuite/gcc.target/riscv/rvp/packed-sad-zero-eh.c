/* { dg-do compile } */
/* { dg-options "-O2 -fexceptions -fnon-call-exceptions -fdump-tree-eh -fdump-rtl-peephole2" } */
/* { dg-skip-if "RTL test" { *-*-* } { "-flto" } { "" } } */

#include <riscv_packed_simd.h>

struct cleanup_state
{
  uint64_t *out;
  uint64_t value;
};

static void __attribute__ ((noipa))
remember (struct cleanup_state *state)
{
  *state->out = state->value;
}

/* The potentially throwing load has a local cleanup successor.  A late
   arithmetic simplification must not remove definitions needed there.  */
uint64_t __attribute__ ((noipa))
sad_with_cleanup (uint8x8_t a, uint8x8_t b, const uint64_t *probe,
		  uint64_t *out)
{
  struct cleanup_state state __attribute__ ((cleanup (remember))) = {out, 0};
  uint64_t loaded = *probe;
  return __riscv_pabdsumau_u8x8_u64 (state.value, a, b) + loaded;
}

/* { dg-final { scan-tree-dump "resx" "eh" } } */
