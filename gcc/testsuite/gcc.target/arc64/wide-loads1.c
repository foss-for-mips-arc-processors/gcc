/* { dg-options "-O2 -mcpu=hs68 -ftree-vectorize" } */
extern int arr[16];
extern int dst[16];

/* Check if we use the 128bit loads and stores for the array copies.  */
void copyme (void)
{
  dst[0] = arr[0];
  dst[1] = arr[1];
  dst[2] = arr[2];
  dst[3] = arr[3];
  dst[4] = arr[4];
  dst[5] = arr[5];
  dst[6] = arr[6];
  dst[7] = arr[7];
  dst[8] = arr[8];
  dst[9] = arr[9];
  dst[10] = arr[10];
  dst[11] = arr[11];
  dst[12] = arr[12];
  dst[13] = arr[13];
  dst[14] = arr[14];
  dst[15] = arr[15];
}

/* { dg-final { scan-assembler-times "lddl" 4 } } */
/* { dg-final { scan-assembler-times "stdl" 4 } } */
