/* { dg-do compile } */
/* { dg-options "-O2 -mcpu=hs5x -mll64 -mno-fpmov" } */
/* { dg-require-effective-target hs5x } */

/* Force a 64 bit aligned double precision data array structure buffer.
   This guarantees that the base address is a clean multiple of 8 enabling
   ldd/std operations. */
double src_array[4] __attribute__((aligned(8))) = {1.0, 2.0, 3.0, 4.0};
double dest_array[4] __attribute__((aligned(8))) = {0.0, 0.0, 0.0, 0.0};

void test_scaling_block (void)
{
  /* Loading a base pointer pointer register and indexing sequentially 
     forces the backend to generate scaled addressing modes. */
  dest_array[0] = src_array[0]; /* Triggers flat ldd and std */
  dest_array[1] = src_array[1]; /* Triggers ldd.as and std.as with offset 2 */
  dest_array[2] = src_array[2]; /* Triggers ldd.as and std.as with offset 4 */
  dest_array[3] = src_array[3]; /* Triggers ldd.as and std.as with offset 6 */
}

/* { dg-final { scan-assembler "ldd\\s+r.,\\\[r.\\\]" { target arc64*-*-* } } }   */
/* { dg-final { scan-assembler "std\\s+r.,\\\[r.\\\]" { target arc64*-*-* } } }  */

/* Verify that the address scaling suffix is cleanly appended with 
   the correct 2-byte instruction multiplier offsets (2, 4, and 6) */
/* { dg-final { scan-assembler "ldd.as\\s+r.,\\\[r.,2\\\]" { target arc64*-*-* } } }  */
/* { dg-final { scan-assembler "std.as\\s+r.,\\\[r.,2\\\]" { target arc64*-*-* } } } */
/* { dg-final { scan-assembler "ldd.as\\s+r.,\\\[r.,4\\\]" { target arc64*-*-* } } }  */
/* { dg-final { scan-assembler "std.as\\s+r.,\\\[r.,4\\\]" { target arc64*-*-* } } }  */
/* { dg-final { scan-assembler "ldd.as\\s+r.,\\\[r.,6\\\]" { target arc64*-*-* } } }  */
/* { dg-final { scan-assembler "std.as\\s+r.,\\\[r.,6\\\]" { target arc64*-*-* } } } */

/* Checkl for un-merged 32bit scalar loads or stores that are still there */
/* { dg-final { scan-assembler-not "ld_s" { target arc64*-*-* } } } */
/* { dg-final { scan-assembler-not "st_s" { target arc64*-*-* } } } */
