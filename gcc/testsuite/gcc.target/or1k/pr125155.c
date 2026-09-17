/* { dg-do compile } */
/* { dg-options "-O2" } */

int __pthread_keys_0_0;
int
___pthread_key_delete (void)
{
  int result = 22;
  int __atg3_old = 0;
  if (__atomic_compare_exchange_n (&__pthread_keys_0_0, &__atg3_old,
				   0, 0, 2, 0))
    result = 0;
  return result;
}
