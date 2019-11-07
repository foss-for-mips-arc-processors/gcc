#include "tconfig.h"
#include "tsystem.h"
#include "coretypes.h"
#include "tm.h"
#include "libgcc_tm.h"

#define L_muldi3
#define L_divdi3
#define L_moddi3
#define L_umoddi3
#define L_udivdi3
#define L_udivmoddi4

#undef LIBGCC2_UNITS_PER_WORD
#define LIBGCC2_UNITS_PER_WORD 4

#include "libgcc2.c"
