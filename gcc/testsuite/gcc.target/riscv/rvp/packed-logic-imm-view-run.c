/* { dg-do run } */
/* { dg-options "-O3 -mlittle-endian" } */

#include "packed-logic-imm-view.h"

typedef void (*view_fn) (unsigned char *, const unsigned char *);

int __attribute__ ((optimize ("O0")))
main (void)
{
  const view_fn functions[] = {
    bytes_and, bytes_or, bytes_xor,
    halves_and, halves_or, halves_xor,
    words_and, words_or, words_xor
  };
  const unsigned char mask[] = { 255, 7, 0, 0, 0, 248, 255, 255 };
  const unsigned int offsets[][2] = {
    { 0, 32 }, { 1, 32 }, { 4, 33 }, { 24, 24 }, { 24, 20 }, { 20, 24 }
  };
  unsigned int state = 1;
  for (unsigned int i = 0; i < 256; ++i)
    for (unsigned int layout = 0; layout < 6; ++layout)
      for (unsigned int f = 0; f < 9; ++f)
	{
	  unsigned char actual[64], expected[64], value[8];
	  for (unsigned int j = 0; j < 64; ++j)
	    {
	      state = state * 1664525u + 1013904223u;
	      actual[j] = expected[j] = state >> 24;
	    }
	  unsigned int in = offsets[layout][0];
	  unsigned int out = offsets[layout][1];
	  for (unsigned int j = 0; j < 8; ++j)
	    value[j] = expected[in + j];
	  for (unsigned int j = 0; j < 8; ++j)
	    {
	      unsigned char result;
	      if (f % 3 == 0)
		result = value[j] & mask[j];
	      else if (f % 3 == 1)
		result = value[j] | mask[j];
	      else
		result = value[j] ^ mask[j];
	      expected[out + j] = result;
	      expected[out + 8 + j] = value[j];
	    }
	  functions[f] (actual + out, actual + in);
	  for (unsigned int j = 0; j < 64; ++j)
	    if (actual[j] != expected[j])
	      __builtin_abort ();
	}
  return 0;
}
