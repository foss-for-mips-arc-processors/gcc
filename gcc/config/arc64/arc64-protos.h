#ifndef GCC_ARC64_PROTOS_H
#define GCC_ARC64_PROTOS_H

extern int arc64_epilogue_uses (int);
extern HOST_WIDE_INT arc64_initial_elimination_offset (unsigned, unsigned);
extern void arc64_init_expanders (void);
extern rtx arc64_return_addr (int, rtx);
extern HOST_WIDE_INT arc64_regmode_natural_size (machine_mode);

#ifdef RTX_CODE

extern machine_mode arc64_select_cc_mode (enum rtx_code, rtx, rtx);
extern bool arc64_check_mov_const (HOST_WIDE_INT );
extern bool arc64_split_mov_const (rtx *);
extern bool arc64_can_use_return_insn_p (void);

#endif /* RTX_CODE */

#endif /* GCC_ARC64_PROTOS_H */
