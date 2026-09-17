/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -ffp-contract=fast -mtune=arc-v-rhx-100-series -march=rv32ifd_zfh -mabi=ilp32d -fdump-rtl-sched2" } */

float fmadd_s (float a, float b, float c, float d)
{ return a * b + (c * d); }
float fmsub_s (float a, float b, float c, float d)
{ return a * b - (c * d); }
float fnmadd_s (float a, float b, float c, float d)
{ return -(a * b) - (c * d); }
float fnmsub_s (float a, float b, float c, float d)
{ return -(a * b) + (c * d); }

double fmadd_d (double a, double b, double c, double d)
{ return a * b + (c * d); }
double fmsub_d (double a, double b, double c, double d)
{ return a * b - (c * d); }
double fnmadd_d (double a, double b, double c, double d)
{ return -(a * b) - (c * d); }
double fnmsub_d (double a, double b, double c, double d)
{ return -(a * b) + (c * d); }

_Float16 fmadd_h (_Float16 a, _Float16 b, _Float16 c, _Float16 d)
{ return a * b + (c * d); }
_Float16 fmsub_h (_Float16 a, _Float16 b, _Float16 c, _Float16 d)
{ return a * b - (c * d); }
_Float16 fnmadd_h (_Float16 a, _Float16 b, _Float16 c, _Float16 d)
{ return -(a * b) - (c * d); }
_Float16 fnmsub_h (_Float16 a, _Float16 b, _Float16 c, _Float16 d)
{ return -(a * b) + (c * d); }

/* { dg-final { scan-rtl-dump "(?s)Function fmadd_s .*?2-->.*\\{fa0\\*fa1\\+fa2\\}" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s)Function fmsub_s .*?2-->.*\\{fa0\\*fa1\\+-fa2\\}" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s)Function fnmadd_s .*?2-->.*\\{-fa0\\*fa1\\+-fa2\\}" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s)Function fnmsub_s .*?2-->.*\\{fa2\\*fa3\\+-fa0\\}" "sched2" } } */

/* { dg-final { scan-rtl-dump "(?s)Function fmadd_d .*?2-->.*\\{fa0\\*fa1\\+fa2\\}" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s)Function fmsub_d .*?2-->.*\\{fa0\\*fa1\\+-fa2\\}" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s)Function fnmadd_d .*?2-->.*\\{-fa0\\*fa1\\+-fa2\\}" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s)Function fnmsub_d .*?2-->.*\\{fa2\\*fa3\\+-fa0\\}" "sched2" } } */

/* { dg-final { scan-rtl-dump "(?s)Function fmadd_h .*?2-->.*\\{fa0\\*fa1\\+fa2\\}" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s)Function fmsub_h .*?2-->.*\\{fa0\\*fa1\\+-fa2\\}" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s)Function fnmadd_h .*?2-->.*\\{-fa0\\*fa1\\+-fa2\\}" "sched2" } } */
/* { dg-final { scan-rtl-dump "(?s)Function fnmsub_h .*?2-->.*\\{fa2\\*fa3\\+-fa0\\}" "sched2" } } */
