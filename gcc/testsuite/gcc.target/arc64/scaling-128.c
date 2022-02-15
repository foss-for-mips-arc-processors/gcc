/* { dg-do compile } */
/* { dg-options "-mcpu=hs6x -m128 -O0" } */

/* Address scaling for double loads and stores must multiply
   the "offset" with the size of a single element and not
   the double of it.  For example:

   Wrong code generation:
     ldd     r2,[r1]
     std     r2,[r0]
     lddl.as r2,[r1,1]
     stdl.as r2,[r0,1]
     ...

   Correct code generation:
     lddl    r2,[r1]
     stdl    r2,[r0]
     lddl.as r2,[r1,2]
     stdl.as r2,[r0,2]
     ...
*/

/* Must generate:
     lddl    r0,[r3]
     stdl    r0,[r2]
     lddl.as r0,[r3,2]
     stdl.as r0,[r2,2]
*/
void func()
{
  char buf[32];
  __builtin_strcpy(buf, "ABCDEFGHIJKLMNOPQRSTUVWXYZ23456");
}

/* { dg-final { scan-assembler "lddl\\s+r.,\\\[r.\\\]"   } } */
/* { dg-final { scan-assembler "stdl\\s+r.,\\\[r.\\\]"   } } */
/* { dg-final { scan-assembler "lddl.as\\s+r.,\\\[r.,2\\\]" } } */
/* { dg-final { scan-assembler "stdl.as\\s+r.,\\\[r.,2\\\]" } } */
