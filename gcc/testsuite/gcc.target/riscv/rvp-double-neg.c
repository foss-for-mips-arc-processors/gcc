/* { dg-do compile } */
/* { dg-options "-march=rv32gcp0p21 -mabi=ilp32" } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-O0" } } */

/* Test negd (double signed negate) instruction.  The middle-end emits the
   canonical (minus:DI (const_int 0) reg) negation form on RV32 + RVP, which
   must be recognized instead of ICEing at recog.cc during "RTL pass: vregs".
   (At -O0 the same form is emitted as "subd rd, x0, rs2".)  */

long long double_neg(long long a)
{
    return -a;
}

/* { dg-final { scan-assembler-times {\mnegd\M} 1 } } */
