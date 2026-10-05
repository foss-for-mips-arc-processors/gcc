/* { dg-do compile } */
/* { dg-options "-std=c99 -fpointer-chasing -march=rv64gc_xmipslsp -mtune=mips-i8500 -mno-double-align" { target { rv64 } } } */
/* { dg-skip-if "" { *-*-* } { "-ansi" "-pedantic" "-O0" "-Os" "-O1" "-Og" "-g" "-Oz" } } */

typedef struct mylist
{
  struct mylist *next;
  long value;
} MYLIST;

MYLIST *test1(MYLIST *start, long value)
{
  while (start && start->value != value)
    start = start->next;
 
  return start;
}

/* { dg-final { scan-assembler-times "ldp" 1 } } */
