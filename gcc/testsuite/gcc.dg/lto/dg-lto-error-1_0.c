/* { dg-lto-do link } */
/* { dg-lto-options { { -O2 -flto } } } */

extern void specific_function (void); /* { dg-lto-error "undefined reference to .?specific_function" } */

int
main (void)
{
  specific_function ();
  return 0;
}
