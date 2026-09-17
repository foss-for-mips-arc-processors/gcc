/* { dg-do compile } */
/* { dg-options "-O2 -funroll-all-loops -fvariable-expansion-in-unroller -fsplit-exit-in-unroller -fdump-rtl-loop2_unroll-details -ffast-math" } */
/* { dg-require-effective-target hard_float } */

/* This testcase combines loop-exit-split1.c and var-expand1.c.  */

struct list_node {
  struct list_node *next;
  float data;
};

float
list_reverse (struct list_node *list)
{
  struct list_node *next = 0, *tmp;
  float accum = 0;
  #pragma GCC unroll 4
  while (list)
    {
      accum += list->data;
      list = list->next;
    }
  
  return accum;
}

/* { dg-final { scan-rtl-dump-times "Expanding Accumulator" 1 "loop2_unroll" } } */
/* { dg-final { scan-rtl-dump-times "18:.*: optimized: loop unrolled 3 times" 1 "loop2_unroll" } } */
/* { dg-final { scan-rtl-dump-times ";; Splitting loop exit for loop 1" 1 "loop2_unroll" } } */
/* { dg-final { scan-rtl-dump-times ";; Found definition of \\\(reg \[0-9\]+" 2 "loop2_unroll" } } */
/* { dg-final { scan-rtl-dump-times ";; added \[0-9\]+ to list of pseudos to replace" 2 "loop2_unroll" } } */
/* { dg-final { scan-rtl-dump-times ";; Split exit edge " 4 "loop2_unroll" } } */
/* { dg-final { scan-rtl-dump-times ";; replacing DU-chain for reg \[0-9\]+" 4 "loop2_unroll" } } */
