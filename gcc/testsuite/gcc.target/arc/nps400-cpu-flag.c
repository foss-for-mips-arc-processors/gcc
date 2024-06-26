/* { dg-do compile } */
/* { dg-skip-if "avoid conflicts with -mcpu options" { *-*-* } { "-mcpu=*" } { "-mcpu=nps400" } } */
/* { dg-options "-mcpu=nps400" } */

/* { dg-final { scan-assembler ".cpu NPS400" } } */
