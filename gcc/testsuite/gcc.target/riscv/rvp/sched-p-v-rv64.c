/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-flto" } { "" } } */
/* { dg-options "-O2 -march=rv64gcpv -mabi=lp64d -mlittle-endian -fschedule-insns -fschedule-insns2 -fdump-rtl-sched1 -fdump-rtl-sched2" } */

#include "sched-p-shared.h"

/* { dg-final { scan-assembler-times {\tpmulh\.w\t} 13 } } */
/* { dg-final { scan-assembler {\tvadd\.vx\t} } } */
/* { dg-final { scan-rtl-dump-times {;; Function sched_} 13 "sched1" } } */
/* { dg-final { scan-rtl-dump-times {;; Function sched_} 13 "sched2" } } */
/* { dg-final { scan-rtl-dump {UNSPEC_PMULH} "sched1" } } */
/* { dg-final { scan-rtl-dump {UNSPEC_PMULH} "sched2" } } */
