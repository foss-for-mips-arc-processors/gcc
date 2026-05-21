/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-g" "-flto" "-O0" "-O1" "-O3" "-Oz" "-Os" } } */
/* { dg-options "-O2 -mtune=arc-v-rhx-100-series -march=rv32ifd_zfh -mabi=ilp32d -fdump-rtl-sched2" } */

struct two_d {
  double a, b;
};
struct two_f {
  float a, b;
};
struct two_h {
  _Float16 a, b;
};

double load_pair_d(struct two_d *p) { return p->a + p->b; }
float load_pair_f(struct two_f *p) { return p->a + p->b; }
_Float16 load_pair_h(struct two_h *p) { return p->a + p->b; }

void store_pair_d(struct two_d *p, double a, double b) {
  p->a = a;
  p->b = b;
}
void store_pair_f(struct two_f *p, float a, float b) {
  p->a = a;
  p->b = b;
}
void store_pair_h(struct two_h *p, _Float16 a, _Float16 b) {
  p->a = a;
  p->b = b;
}

/* { dg-final { scan-rtl-dump-not "ARCV_FUSE_ADJACENT_LOAD" "sched2" } } */
/* { dg-final { scan-rtl-dump-not "ARCV_FUSE_ADJACENT_STORE" "sched2" } } */
