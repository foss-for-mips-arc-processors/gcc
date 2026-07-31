/* { dg-do run } */
/* { dg-options "-O3" } */

#include <stdlib.h>

int test0(){
    float a, b;
    double c, d;    
    a = (float)rand()/(float)(RAND_MAX);
    b = (float)rand()/(float)(RAND_MAX);    
    c = (double)rand()/(double)(RAND_MAX);
    d = (double)rand()/(double)(RAND_MAX);    
    return (int)((double)a + (double)b + c + d);
}

int main() {
    int result = test0();
    return 0;
}
