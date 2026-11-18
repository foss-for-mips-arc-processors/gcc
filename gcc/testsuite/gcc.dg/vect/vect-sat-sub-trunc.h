#ifndef VECT_SAT_SUB_TRUNC_H
#define VECT_SAT_SUB_TRUNC_H

#include <stdint.h>

void __attribute__ ((noipa))
sat_sub_16_8 (uint8_t *restrict dst, const uint16_t *restrict x,
	      const uint16_t *restrict y, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      uint16_t a = x[i];
      uint16_t b = y[i];
      uint8_t d = (uint8_t) a - (uint8_t) b;
      dst[i] = a >= b ? d : 0;
    }
}

void __attribute__ ((noipa))
sat_sub_32_16_8 (uint8_t *restrict dst, const uint32_t *restrict x,
		 const uint32_t *restrict y, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      uint32_t a = x[i];
      uint32_t b = y[i];
      uint16_t d = (uint16_t) a - (uint16_t) b;
      dst[i] = a >= b ? (uint8_t) d : 0;
    }
}

/* The intermediate low byte is observable in a wider result.  */
void __attribute__ ((noipa))
sat_sub_wide (uint16_t *restrict dst, const uint16_t *restrict x,
	      const uint16_t *restrict y, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      uint16_t a = x[i];
      uint16_t b = y[i];
      uint8_t d = (uint8_t) a - (uint8_t) b;
      dst[i] = a >= b ? d : 0;
    }
}

void __attribute__ ((noipa))
sat_sub_boolean_result (_Bool *restrict dst, const uint16_t *restrict x,
			const uint16_t *restrict y, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      uint16_t a = x[i];
      uint16_t b = y[i];
      uint8_t d = (uint8_t) a - (uint8_t) b;
      dst[i] = a >= b ? (_Bool) d : 0;
    }
}

void __attribute__ ((noipa))
sat_sub_boolean_operands (uint8_t *restrict dst,
			 const uint16_t *restrict x,
			 const uint16_t *restrict y, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      uint16_t a = x[i];
      uint16_t b = y[i];
      uint8_t d = (_Bool) a - (_Bool) b;
      dst[i] = a >= b ? d : 0;
    }
}

/* Keep the raw 16-bit difference and comparison independently live.  */
void __attribute__ ((noipa))
sat_sub_shared (uint8_t *restrict dst, uint16_t *restrict raw,
		_Bool *restrict flag, const uint32_t *restrict x,
		const uint32_t *restrict y, unsigned int n)
{
  for (unsigned int i = 0; i < n; ++i)
    {
      uint32_t a = x[i];
      uint32_t b = y[i];
      uint16_t d = (uint16_t) a - (uint16_t) b;
      _Bool c = a >= b;
      dst[i] = c ? (uint8_t) d : 0;
      raw[i] = d;
      flag[i] = c;
    }
}

#endif
