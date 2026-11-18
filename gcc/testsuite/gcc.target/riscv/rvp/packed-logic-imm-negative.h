#include "packed-logic-imm.h"

/* Small lanes do not imply that the full scalar mask is encodable.  */
v4qi
nonimmediate_bytes (v4qi x)
{
  return x & (v4qi) { 127, 127, 127, 127 };
}

v2hi
nonimmediate_halfwords (v2hi x)
{
  return x | (v2hi) { 127, 127 };
}

v2si
nonimmediate_words (v2si x)
{
  return x ^ (v2si) { 2048, -2049u };
}
