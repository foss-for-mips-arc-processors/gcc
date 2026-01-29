/* { dg-do compile } */
/* { dg-options "-O2 -funroll-all-loops -fno-variable-expansion-in-unroller -fsplit-exit-in-unroller -fdump-rtl-loop2_unroll-details" } */

/* Reduced from Coremark's core_list_reverse () function.  */

struct list_node {
  struct list_node *next;
};

struct list_node *
list_reverse (struct list_node *list)
{
  struct list_node *next = 0, *tmp;
  #pragma GCC unroll 4
  while (list)
    {
      tmp = list->next;
      list->next = next;
      next = list;
      list = tmp;
    }
  
  return next;
}

/* { dg-final { scan-rtl-dump-times "15:.*: optimized: loop unrolled 3 times" 1 "loop2_unroll" } } */
/* { dg-final { scan-rtl-dump-times ";; Splitting loop exit for loop 1" 1 "loop2_unroll" } } */
/* { dg-final { scan-rtl-dump-times ";; Found definition of \\\(reg \[0-9\]+ \\\[ list \\\]\\\)" 1 "loop2_unroll" } } */
/* { dg-final { scan-rtl-dump-times ";; added \[0-9\]+ to list of pseudos to replace" 1 "loop2_unroll" } } */
/* { dg-final { scan-rtl-dump-times ";; Split exit edge " 4 "loop2_unroll" } } */
/* { dg-final { scan-rtl-dump-times ";; replacing DU-chain for reg \[0-9\]+" 3 "loop2_unroll" } } */
