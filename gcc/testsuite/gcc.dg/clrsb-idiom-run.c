/* { dg-do run } */
/* { dg-options "-O2" } */
/* { dg-require-effective-target int32 } */
/* { dg-require-effective-target longlong64 } */

#include "clrsb-idiom.h"

static int __attribute__ ((noipa, optimize ("O0")))
reference (u64 value, unsigned int width)
{
  unsigned int bit = width - 1;
  unsigned int sign = (value >> bit) & 1;
  int count = 0;
  while (bit != 0)
    {
      --bit;
      if (((value >> bit) & 1) != sign)
	break;
      ++count;
    }
  return count;
}

static void
check (u64 bits)
{
  u32 word = (u32) bits;
  s32 x = word <= 0x7fffffffu ? (s32) word : -1 - (s32) ~word;
  s64 y = (bits <= 0x7fffffffffffffffULL
	   ? (s64) bits : -1 - (s64) ~bits);
  s32 saved32[3] = { 12345, 0, -12345 };
  s64 saved64[3] = { 12345, 0, -12345 };
  u32 raw32[3] = { 0x12345678u, 0, 0x87654321u };
  u64 raw64[3] = { 0x123456789abcdef0ULL, 0, 0xfedcba9876543210ULL };
  int expected32 = reference (word, 32);
  int expected64 = reference (bits, 64);
  u32 folded32 = x < 0 ? 0xffffffffu - word : word;
  u64 folded64 = y < 0 ? ~0ULL - bits : bits;

  if (clrsb_total32 (word) != expected32
      || clrsb_conditional32 (x) != expected32
      || clrsb_signed_input32 (word, saved32 + 1) != expected32
      || clrsb_shared_outer32 (x, raw32 + 1) != expected32
      || clrsb_total64 (bits) != expected64
      || clrsb_conditional64 (y) != expected64
      || clrsb_signed_input64 (bits, saved64 + 1) != expected64
      || clrsb_shared_outer64 (y, raw64 + 1) != expected64
      || saved32[1] != x || saved64[1] != y
      || raw32[1] != folded32 || raw64[1] != folded64
      || saved32[0] != 12345 || saved32[2] != -12345
      || saved64[0] != 12345 || saved64[2] != -12345
      || raw32[0] != 0x12345678u || raw32[2] != 0x87654321u
      || raw64[0] != 0x123456789abcdef0ULL
      || raw64[2] != 0xfedcba9876543210ULL)
    __builtin_abort ();
}

int
main (void)
{
  check (0);
  check (~0ULL);
  for (unsigned int bit = 0; bit != 64; ++bit)
    {
      u64 power = 1ULL << bit;
      check (power);
      check (power - 1);
      check (power + 1);
      check (~power);
      check (~power - 1);
      check (~power + 1);
    }
  u32 state = 0x6d2b79f5u;
  for (unsigned int i = 0; i != 1024; ++i)
    {
      state = state * 1664525u + 1013904223u;
      u32 high = state;
      state = state * 1664525u + 1013904223u;
      check (((u64) high << 32) | state);
    }
  return 0;
}
