#include <riscv_packed_simd.h>

#if __riscv_xlen == 32
typedef int16x2_t packed_t;
#define PACKED_MUL __riscv_pmulhr_i16x2
#else
typedef int32x2_t packed_t;
#define PACKED_MUL __riscv_pmulh_i32x2
#endif

#ifdef __riscv_vector
#include <riscv_vector.h>
#define UPDATE_VECTOR(P, N, X) \
  do \
    { \
      vint32m1_t value = __riscv_vle32_v_i32m1 (P, N); \
      value = __riscv_vadd_vx_i32m1 (value, X, N); \
      __riscv_vse32_v_i32m1 (P, value, N); \
    } \
  while (0)
#else
#define UPDATE_VECTOR(P, N, X)
#endif

/* Use direct P builtins through the intrinsic wrappers, retaining the
   complete packed result.  The scalar memory operation, and the RVV
   operations when enabled, exercise mixed instruction scheduling.  */
#define TEST(NAME, TUNE) \
packed_t __attribute__ ((noipa, target ("tune=" TUNE))) \
sched_##NAME (packed_t a, packed_t b, unsigned long *c, \
	      int32_t *v, unsigned long n) \
{ \
  packed_t result = PACKED_MUL (a, b); \
  *c += 3; \
  UPDATE_VECTOR (v, n, result[0]); \
  return result; \
}

TEST (generic, "generic")
TEST (generic_ooo, "generic-ooo")
TEST (sifive7, "sifive-7-series")
TEST (sifive_p400, "sifive-p400-series")
TEST (sifive_p600, "sifive-p600-series")
TEST (ascalon, "tt-ascalon-d8")
TEST (nanhu, "xiangshan-nanhu")
TEST (kunminghu, "xiangshan-kunminghu")
TEST (spacemit, "spacemit-x60")
TEST (p8700, "mips-p8700")
TEST (andes23, "andes-23-series")
TEST (andes25, "andes-25-series")
TEST (andes45, "andes-45-series")
