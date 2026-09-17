/* PR target/124895 */
/* { dg-do compile } */
/* { dg-options "-Os -fpath-coverage -fno-tree-ccp -fprofile-generate -mnarrow-gp-writes" } */

void
foo (unsigned u)
{
  while (u)
    ;
}
