/* { dg-do run } */
/* { dg-options "-O2 -mcpu=hs5x -mfpu=fpud -mll64" } */
/* { dg-require-effective-target hs5x } */

#include <stdlib.h>
volatile double a __attribute__((aligned(8))) = 1.2345678901234567;   
volatile double b __attribute__((aligned(8))) = 0.1234567890123456;   
volatile double exp_add __attribute__((aligned(8))) = 1.3580246791358023; 
volatile double exp_sub __attribute__((aligned(8))) = 1.1111111011111111; 

int main() {
    double res_add = a + b;
    double res_sub = a - b;

    if (res_add != exp_add || res_sub != exp_sub)
        abort();

    return 0; 
}
