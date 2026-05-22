/* { dg-do compile } */
/* { dg-require-effective-target arcem } */
/* { dg-options "-Os -mno-code-density" } */

char
test_no_ldb_s (void)
{
  char arr[10];
  return arr[2];
}

short
test_no_ldh_s (void)
{
  short arr[10];
  return arr[2];
}

/* { dg-final { scan-assembler-not "ldb_s\\s+r\[0-9\]" } } */
/* { dg-final { scan-assembler-not "ldh_s\\s+r\[0-9\]" } } */
/* { dg-final { scan-assembler "ldb\\s+r\[0-9\]" } } */
/* { dg-final { scan-assembler "ldh(\\.x)?\\s+r\[0-9\]" } } */
