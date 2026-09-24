/* { dg-do compile { target riscv64*-*-* } } */
/* { dg-options "-march=rv64gcp -mabi=lp64d -O2" } */

#include <riscv_packed_simd.h>

int8_t
get_nonconstant (int8x4_t value, unsigned int index)
{
  /* { dg-error "constant in range" "" { target *-*-* } .+1 } */
  return __riscv_pget_i8x4_i8 (value, index);
}

int8_t
get_out_of_range (int8x4_t value)
{
  /* { dg-error "constant in range" "" { target *-*-* } .+1 } */
  return __riscv_pget_i8x4_i8 (value, 4);
}

int8x4_t
set_nonconstant (int8x4_t value, int8_t element, unsigned int index)
{
  /* { dg-error "constant in range" "" { target *-*-* } .+1 } */
  return __riscv_pset_i8_i8x4 (value, element, index);
}

int8x4_t
set_out_of_range (int8x4_t value, int8_t element)
{
  /* { dg-error "constant in range" "" { target *-*-* } .+1 } */
  return __riscv_pset_i8_i8x4 (value, element, 4);
}

int8x4_t
subvector_get_nonconstant (int8x8_t value, unsigned int index)
{
  /* { dg-error "constant in range" "" { target *-*-* } .+1 } */
  return __riscv_pget_i8x8_i8x4 (value, index);
}

int8x4_t
subvector_get_out_of_range (int8x8_t value)
{
  /* { dg-error "constant in range" "" { target *-*-* } .+1 } */
  return __riscv_pget_i8x8_i8x4 (value, 2);
}

int8x8_t
subvector_set_nonconstant (int8x8_t value, int8x4_t subvector,
			   unsigned int index)
{
  /* { dg-error "constant in range" "" { target *-*-* } .+1 } */
  return __riscv_pset_i8x4_i8x8 (value, subvector, index);
}

int8x8_t
subvector_set_out_of_range (int8x8_t value, int8x4_t subvector)
{
  /* { dg-error "constant in range" "" { target *-*-* } .+1 } */
  return __riscv_pset_i8x4_i8x8 (value, subvector, 2);
}
