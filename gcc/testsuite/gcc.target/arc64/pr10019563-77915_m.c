/* { dg-do run } */
/* { dg-options "-O2 -mcpu=hs5x -mfpu=fpud" } */
/* { dg-require-effective-target hs5x } */

/* Standard success is return 0 */

/* Force 64 bit address alignment */
volatile double a = 10.0;
volatile double b = 5.0;

int main() {
    double res = a - b;
    if (res == 5.0)
        return 0;
    return 1;
}

