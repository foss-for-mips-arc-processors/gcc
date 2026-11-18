/* { dg-do run } */
/* { dg-options "-O3" } */

#include <stdarg.h>

typedef unsigned long long u64;
typedef u64 v1du __attribute__ ((vector_size (8)));

static v1du __attribute__ ((noipa))
arithmetic (v1du a, v1du b)
{
  return (a + b) ^ (a - b) ^ (a * b);
}

static v1du __attribute__ ((noipa))
logic (v1du a, v1du b, unsigned int shift)
{
  return ((a ^ b) >> (shift & 63)) | ((a & b) << (shift & 63));
}

static v1du __attribute__ ((noipa))
select_value (v1du a, v1du b)
{
  return (a < b) & (a - b);
}

static v1du __attribute__ ((noipa))
initialize (u64 a)
{
  return (v1du) { a };
}

static u64 __attribute__ ((noipa))
extract (v1du a)
{
  return a[0];
}

static void __attribute__ ((noipa))
memory (void *out, const void *in, volatile v1du *save)
{
  v1du a;
  __builtin_memcpy (&a, in, sizeof (a));
  *save = a;
  a = *save;
  __builtin_memcpy (out, &a, sizeof (a));
}

static v1du __attribute__ ((noipa))
odd_arguments (unsigned int x, v1du a, unsigned int y, v1du b)
{
  return a - b + (v1du) { (u64) x + y };
}

static v1du __attribute__ ((noipa))
stack_arguments (v1du a, v1du b, v1du c, v1du d, v1du e, v1du f,
		 v1du g, v1du h, v1du i, v1du j, v1du k, v1du l)
{
  return (a + b) ^ (c - d) ^ (e + f) ^ (g - h) ^ (i + j) ^ (k - l);
}

static v1du __attribute__ ((noipa))
variadic (unsigned int n, ...)
{
  va_list args;
  va_start (args, n);
  v1du sum = { 0 };
  for (unsigned int i = 0; i < n; ++i)
    sum += va_arg (args, v1du);
  va_end (args);
  return sum;
}

int __attribute__ ((optimize ("O0")))
main (void)
{
  u64 state = 0x987654321ULL;
  for (unsigned int r = 0; r < 64; ++r)
    {
      v1du a[12];
      u64 sum = 0;
      for (unsigned int i = 0; i < 12; ++i)
	{
	  state ^= state << 13;
	  state ^= state >> 7;
	  state ^= state << 17;
	  a[i][0] = state;
	  sum += state;
	}
      u64 x = a[0][0], y = a[1][0];
      if (arithmetic (a[0], a[1])[0] != ((x + y) ^ (x - y) ^ (x * y))
	  || select_value (a[0], a[1])[0] != (x < y ? x - y : 0)
	  || extract (initialize (x)) != x)
	__builtin_abort ();
      for (unsigned int s = 0; s < 128; ++s)
	if (logic (a[0], a[1], s)[0]
	    != (((x ^ y) >> (s & 63)) | ((x & y) << (s & 63))))
	  __builtin_abort ();
      if (odd_arguments ((unsigned int) x, a[0], (unsigned int) y, a[1])[0]
	  != x - y + (u64) (unsigned int) x + (unsigned int) y
	  || stack_arguments (a[0], a[1], a[2], a[3], a[4], a[5],
			      a[6], a[7], a[8], a[9], a[10], a[11])[0]
	     != ((a[0][0] + a[1][0]) ^ (a[2][0] - a[3][0])
		 ^ (a[4][0] + a[5][0]) ^ (a[6][0] - a[7][0])
		 ^ (a[8][0] + a[9][0]) ^ (a[10][0] - a[11][0]))
	  || variadic (12, a[0], a[1], a[2], a[3], a[4], a[5],
		       a[6], a[7], a[8], a[9], a[10], a[11])[0] != sum
	  || variadic (0)[0] != 0)
	__builtin_abort ();
      for (unsigned int offset = 0; offset < 8; ++offset)
	{
	  unsigned char in[24], out[24];
	  volatile v1du save;
	  for (unsigned int i = 0; i < 24; ++i)
	    in[i] = out[i] = 0x5a;
	  __builtin_memcpy (in + 8 + offset, &x, sizeof (x));
	  memory (out + 8 + offset, in + 8 + offset, &save);
	  for (unsigned int i = 0; i < 24; ++i)
	    if (in[i] != out[i])
	      __builtin_abort ();
	  if (save[0] != x)
	    __builtin_abort ();
	}
    }
  return 0;
}
