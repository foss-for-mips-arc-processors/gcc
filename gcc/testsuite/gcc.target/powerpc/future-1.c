/* { dg-do compile } */
/* { dg-options "-mdejagnu-cpu=future -O2" } */

/* Basic check to see if the compiler supports -mcpu=future and if it defines
   _ARCH_FUTURE.  */

#ifndef _ARCH_FUTURE
#error "-mcpu=future is not supported"
#endif

void foo (void)
{
}
