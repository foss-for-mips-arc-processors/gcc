/* { dg-do run } */
/* { dg-options "-O1 -mcpu=hs5x -mfpu=fpud" } */

#include <stdlib.h>

volatile double qwerty= 1.0;

volatile double input_pool[12] = {
  1,2,3,4,5,6,7,8,9,10,11,12
};

__attribute__((noinline))
void func2 (void)
{
  qwerty = 2.0;
}

__attribute__((noinline))
double func1 (double r1, double r2, double r3, 
	      double r4, double r5, double r6, 
	      double r7, double r8, double r9, 
	      double r10, double r11, double r12)
{
  double out1 = (r1 * 2.0) + (r2 * 1.0);
  double out2 = (r3 * 2.0) + (r4 * 1.0);
  double out3 = (r5 * 2.0) + (r6 * 1.0);
  double out4 = (r7 * 2.0) + (r8 * 1.0);
  double out5 = (r9 * 2.0) + (r10 * 1.0);
  double out6 = (r11 * 2.0) + (r12 * 1.0);
  double out7 = out1 + out2 + out3;
  double out8 = out4 + out5 + out6;
  double out9 = out7 + out8;

  func2 ();

  return out1 + out2 + out3 + out4 + out5 + 
	 out6 + out7 + out8 + out9;
}

int main (void)
{
  double val1  = input_pool[0];
  double val2  = input_pool[1];
  double val3  = input_pool[2];
  double val4  = input_pool[3];
  double val5  = input_pool[4];
  double val6  = input_pool[5];
  double val7  = input_pool[6];
  double val8  = input_pool[7];
  double val9  = input_pool[8];
  double val10 = input_pool[9];
  double val11 = input_pool[11]; /*is ok the order changed*/
  double val12 = input_pool[10];

  double runtime_result = func1 (val1, val2,
		  val3, val4, val5, val6, 
                  val7, val8, val9, val10,  
		  val11, val12);

  if (runtime_result == 1042.0)
    {
      return 0;
    }

  return 1;
}
