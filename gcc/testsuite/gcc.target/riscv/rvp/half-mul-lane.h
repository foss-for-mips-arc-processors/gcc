typedef unsigned short lane_u16x2 __attribute__ ((vector_size (4)));
typedef unsigned short lane_u16x4 __attribute__ ((vector_size (8)));

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define LOW_LANE 1
#else
#define LOW_LANE 0
#endif

/* Select the low halfword of a physical word on either endian target.  */
__attribute__ ((noipa)) unsigned int
pair_low (lane_u16x2 a, lane_u16x2 b)
{
  lane_u16x2 p = a * b;
  return p[LOW_LANE];
}

__attribute__ ((noipa)) unsigned int
quad_low (lane_u16x4 a, lane_u16x4 b)
{
  lane_u16x4 p = a * b;
  return p[LOW_LANE];
}
