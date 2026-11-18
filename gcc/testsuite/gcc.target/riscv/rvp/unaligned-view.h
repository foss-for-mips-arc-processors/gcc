/* View conversions of weakly aligned vectors must use the packed move
   expansion rather than a stack temporary.  */

#define LOAD(NAME, TYPE, SIZE, ALIGN) \
  typedef unsigned TYPE u_##NAME \
    __attribute__ ((vector_size (SIZE))); \
  typedef signed TYPE s_##NAME __attribute__ ((vector_size (SIZE))); \
  typedef u_##NAME a_##NAME __attribute__ ((aligned (ALIGN), may_alias)); \
  __attribute__ ((noinline, noclone)) u_##NAME \
  load_##NAME (const a_##NAME *p) \
  { \
    return (u_##NAME) ~(s_##NAME) *p; \
  }

#define LOAD_MODES(ALIGN) \
  LOAD (b4_##ALIGN, char, 4, ALIGN) \
  LOAD (h2_##ALIGN, short, 4, ALIGN) \
  LOAD (b8_##ALIGN, char, 8, ALIGN) \
  LOAD (h4_##ALIGN, short, 8, ALIGN) \
  LOAD (w2_##ALIGN, int, 8, ALIGN)

LOAD_MODES (1)
LOAD_MODES (2)
LOAD_MODES (4)

#undef LOAD_MODES
#undef LOAD
