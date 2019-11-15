/* libgcc routines for ARC64
   Copyright (C) 2019 Free Software Foundation, Inc.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3, or (at your
   option) any later version.

   GCC is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   Under Section 7 of GPL version 3, you are granted additional
   permissions described in the GCC Runtime Library Exception, version
   3.1, as published by the Free Software Foundation.

   You should have received a copy of the GNU General Public License and
   a copy of the GCC Runtime Library Exception along with this program;
   see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
   <http://www.gnu.org/licenses/>.  */


typedef          int  sint64_t   __attribute__ ((mode (DI)));
typedef unsigned int  uint64_t   __attribute__ ((mode (DI)));

sint64_t __muldi3 (sint64_t, sint64_t);

sint64_t
__muldi3 (sint64_t a, sint64_t b)
{
  sint64_t res = 0;
  uint64_t cnt = a;

  while (cnt)
    {
      if (cnt & 1)
        res += b;
      b <<= 1;
      cnt >>= 1;
    }
  return res;
}

/* Build DI version of libgcc functions. */
#undef LIBGCC2_UNITS_PER_WORD
#define LIBGCC2_UNITS_PER_WORD 4

#define L_divdi3
#define L_moddi3
#define L_umoddi3
#define L_udivdi3
#define L_udivmoddi4

#include "libgcc2.c"
