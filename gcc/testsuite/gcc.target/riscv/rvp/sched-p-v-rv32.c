/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-flto" } { "" } } */
/* { dg-options "-O2 -march=rv32gcpv -mabi=ilp32d -mlittle-endian -fschedule-insns -fschedule-insns2 -fdump-rtl-sched1 -fdump-rtl-sched2" } */

#include "sched-p-shared.h"

/* { dg-final { scan-assembler-times {\tpmulhr\.h\t} 13 } } */
/* { dg-final { scan-assembler {\tvadd\.vx\t} } } */
/* { dg-final { scan-rtl-dump-times {;; Function sched_} 13 "sched1" } } */
/* { dg-final { scan-rtl-dump-times {;; Function sched_} 13 "sched2" } } */
/* { dg-final { scan-rtl-dump {UNSPEC_PMULHR} "sched1" } } */
/* { dg-final { scan-rtl-dump {UNSPEC_PMULHR} "sched2" } } */
