/* regression test for a bug in ldst_bonding for mcpu=mips-i8500
   tries to fuse a store and a load causing segfault */
/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64imad -mtune=mips-i8500 -mabi=lp64d" } */

typedef short a;
typedef int b;
typedef a c;
typedef b d;
struct e {
  c f;
  c g;
  c h;
  c i;
  c j;
  d flags;
  int k;
  c l;
  c m;
  c n;
  c o;
  c q;
  c r;
  c s;
  c t;
} u(struct e *p) {
  p->t = p->g;
};
