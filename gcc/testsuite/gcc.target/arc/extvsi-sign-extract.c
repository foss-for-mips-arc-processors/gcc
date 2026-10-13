/* { dg-do run } */
/* { dg-options "-O2 -mcpu=em -save-temps" } */

#include <stdio.h>
#include <stdlib.h>

/* Test multi-bit Extraction Pattern (*extvsi_n_0).  */
struct bitstruct {
  unsigned a : 21;
  unsigned b : 8;
  unsigned c : 2;
  int d : 17;
} __attribute__((packed));

static volatile struct bitstruct bits = {
  .a = 0x100,
  .b = 0x2f,
  .c = 0,
  .d = 0
};

volatile int global_d;

/* Test snigle-bit Extraction Pattern (*extvsi_1_0).  */
struct source_struct {
  int target_bit : 1;
  unsigned int padding : 31;
} __attribute__((packed));

static volatile struct source_struct data = {
  .target_bit = 1,
  .padding = 0xabcdef
};

volatile int destination;

int
main (void)
{
  /* 1. Execute Multi-bit Sign-Extract Test */
  global_d = bits.d;
  if (global_d != 0)
    {
      printf ("FAIL: Multi-bit extract (*extvsi_n_0) failed. Expected 0, got %d\n", global_d);
      abort ();
    }

  /* 2. Execute Single-bit Sign-Extract Test */
  destination = data.target_bit;
  if (destination != -1)
    {
      printf ("FAIL: Single-bit extract (*extvsi_1_0) failed. Expected -1, got %d\n", destination);
      abort ();
    }

  printf ("PASS: Both sign-extract patterns executed successfully.\n");
  return 0;
}

/* Check that the extvsi_n_0 split got triggered. */
/* { dg-final { scan-assembler "bmsk.*,16" } } */
/* { dg-final { scan-assembler "bxor.*,16" } } */
/* { dg-final { scan-assembler "sub.*,65536" } } */

/* Check that the extvsi_1_0 split got triggered. */
/* { dg-final { scan-assembler "bmsk.*,0" } } */
/* { dg-final { scan-assembler "neg" } } */
