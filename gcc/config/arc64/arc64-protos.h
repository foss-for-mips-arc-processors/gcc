#ifndef GCC_ARC64_PROTOS_H
#define GCC_ARC64_PROTOS_H

int arc64_epilogue_uses (int);
poly_int64 arc64_initial_elimination_offset (unsigned, unsigned);
void arc64_init_expanders (void);
machine_mode arc64_select_cc_mode (RTX_CODE, rtx, rtx);
rtx arc64_return_addr (int, rtx);
poly_uint64 arc64_regmode_natural_size (machine_mode);

#endif /* GCC_ARC64_PROTOS_H */
