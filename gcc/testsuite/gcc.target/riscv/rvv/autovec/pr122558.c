/* { dg-do compile } */
/* { dg-options "-O3 -ftree-vectorize -mabi=lp64d -march=rv64gcv -mrvv-max-lmul=dynamic -fdump-tree-vect-all" } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O2" "-Os" "-Og" "-Oz" } } */

#include <stdint-gcc.h>

void dct( int16_t d[16], int16_t dct[16] )
{
    int16_t tmp[16];
    for( int i = 0; i < 4; i++ )
    {
        int s03 = d[i*4+0] + d[i*4+3];
        int s12 = d[i*4+1] + d[i*4+2];
        int d03 = d[i*4+0] - d[i*4+3];
        int d12 = d[i*4+1] - d[i*4+2];
        tmp[0*4+i] =   s03 +   s12;
        tmp[1*4+i] = 2*d03 +   d12;
        tmp[2*4+i] =   s03 -   s12;
        tmp[3*4+i] =   d03 - 2*d12;
    }
    for( int i = 0; i < 4; i++ )
    {
        int s03 = tmp[i*4+0] + tmp[i*4+3];
        int s12 = tmp[i*4+1] + tmp[i*4+2];
        int d03 = tmp[i*4+0] - tmp[i*4+3];
        int d12 = tmp[i*4+1] - tmp[i*4+2];

        dct[i*4+0] =   s03 +   s12;
        dct[i*4+1] = 2*d03 +   d12;
        dct[i*4+2] =   s03 -   s12;
        dct[i*4+3] =   d03 - 2*d12;
    }
}

/* { dg-final { scan-tree-dump "LOOP VECTORIZED" "vect" } } */
/* { dg-final { scan-tree-dump "Choosing vector mode RVVMF2QI" "vect" } } */

