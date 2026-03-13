/* { dg-lto-do link } */
/* { dg-lto-options { { -O2 -flto -fno-common } } } */

int global_var = 100; /* { dg-lto-error "multiple definition of .?global_var" } */

int
main (void)
{
  return global_var;
}
