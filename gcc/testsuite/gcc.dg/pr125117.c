/* { dg-do run } */
/* { dg-options "-O0" } */

#include <string.h>
#include <stdlib.h>

#define OFFSET 32

char buffer[128];
char expected[64];

void
foo (char *dest, char *src, size_t n)
{
  if (n == 64)
    __builtin_memmove (dest, src, n);
}

int
main ()
{
  memset (buffer, -2, sizeof (buffer));
  memset (buffer + OFFSET, -1, sizeof (buffer) - OFFSET);
  memset (expected, -2, sizeof (expected));
  memset (expected + OFFSET / 2, -1, OFFSET + OFFSET / 2);
  foo (buffer, buffer + OFFSET / 2, 64);
  if (memcmp (expected, buffer, 64) != 0)
    abort ();

  return 0;
}
