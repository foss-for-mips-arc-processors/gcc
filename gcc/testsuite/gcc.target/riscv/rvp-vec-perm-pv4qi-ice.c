/* { dg-do compile } */
/* { dg-options "-march=rv64gcp0p21 -mabi=lp64d -O3" } */

/* A byte-granularity zip {0,4,1,5} on a PV4QI vector is zip8p, not the
   halfword-granularity zip16p the vec_perm expander used to emit here, which
   had no recognizer and ICEd in the vregs pass.  */

void bar (unsigned char *q, unsigned short *data16s, int len)
{
  int i;

  for (i = 0; i < len; i++)
    {
      q[2 * i] =
	(((data16s[i] & 0xFF) << 8) | ((data16s[i] >> 8) & 0xFF)) & 0xFF;
      q[2 * i + 1] =
	((unsigned short)
	 (((data16s[i] & 0xFF) << 8) | ((data16s[i] >> 8) & 0xFF))) >> 8;
    }
}

/* { dg-final { scan-assembler {\mzip8p\M} } } */
