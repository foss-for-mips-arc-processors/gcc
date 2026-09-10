/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" } } */
/* { dg-options "-march=rv32i_zba -mabi=ilp32" { target rv32 } } */
/* { dg-options "-march=rv64i_zba -mabi=lp64" { target rv64 } } */

void bar (void *);

void foo ()
  {
    char baz[4104];
    bar (baz);
  }

/* { dg-final { scan-assembler-not "sh\[123\]add" } } */
