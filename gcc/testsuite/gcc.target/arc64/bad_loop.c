/* { dg-do run } */
/* { dg-options "-O2" } */

#include <string.h>
#include <stdlib.h>


/* Move the digits from W to REAR_PTR FRONT_PTR to W is used as a
   scratch area.  */
char *
bad_loop_example (char *front_ptr, char *w, char *rear_ptr, int thousand_len)
{
  int len = thousand_len;

  /* Copy existing string so that nothing gets overwritten.  */
  memmove (front_ptr, w, (rear_ptr - w));
  char *s = front_ptr + (rear_ptr - w);
  w = rear_ptr;

  /* Process all characters in the string.  */
  while (s > front_ptr)
    {
      *--w = *--s;
      if (--len == 0 && s > front_ptr)
	{
	  /* This part is a vital part to represent issue.  */
	  if (w != s)
	    *--w = '.';

	  /* Part that is not used but adding of this part couse compiler to
	     generate strange code.  */
	  if (thousand_len < 0)
	    break;
	}
    }
  return w;
}

int main (void)
{
  char buf[64] = {'\0'};

  char *scratch = buf;
  char *from = buf + 0x8;
  char *to = from + 0x1;

  int thousand_digits = 3;
  char *r;

  strcpy (from, "12345678\n");
  r = bad_loop_example (scratch, from, to, thousand_digits);

  if (r != from)
    __builtin_abort ();

  return 0;
}
