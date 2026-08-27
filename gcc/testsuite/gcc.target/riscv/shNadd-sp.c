/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" } } */
/* { dg-options "-march=rv32i_zba" { target rv32 } } */
/* { dg-options "-march=rv64i_zba" { target rv64 } } */

void bar (void *);

void foo ()
  {
    char baz[4104];
    bar (baz);
  }

/* { dg-final { scan-assembler-not "sh\[123\]add" } } */
