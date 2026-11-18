/* { dg-do compile } */
/* { dg-options "-O2 -fexceptions -fnon-call-exceptions -fdump-tree-eh -fdump-rtl-peephole2" } */
/* { dg-skip-if "RTL test" { *-*-* } { "-flto" } { "" } } */

#include <riscv_packed_simd.h>

struct saved_sad
{
  uint64_t *out;
  uint64_t value;
};

static void __attribute__ ((noipa))
save_sad (struct saved_sad *state)
{
  *state->out = state->value;
}

/* The full result is still needed by the exceptional cleanup successor.  */
uint64_t __attribute__ ((noipa))
sad_word_with_cleanup (uint8x8_t a, uint8x8_t b,
		       const uint64_t *probe, uint64_t *out)
{
  struct saved_sad state __attribute__ ((cleanup (save_sad))) =
    {out, __riscv_pabdsumu_u8x8_u64 (a, b)};
  uint64_t loaded = *probe;
  return (uint32_t) state.value + loaded;
}

/* { dg-final { scan-tree-dump "resx" "eh" } } */
