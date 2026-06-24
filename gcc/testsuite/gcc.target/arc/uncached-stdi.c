/* { dg-do compile } */
/* { dg-options "-Os" } */

#ifndef __uncached
#define __uncached __attribute__((uncached))
#endif

volatile char *
_hl_pack_ptr(volatile char *p, const void *s, int len)
{
    volatile __uncached char *buf = p + 4;

    for (int i = 0; i < len; i++)
        buf[i] = ((const char *)s)[i];

    return p;
}


/* Singleregister uncached store byte should be present in the output.  */
/* { dg-final { scan-assembler "stb(_s)?\\.di" } } */

/* Ensure that stb.di and srt_s.di are not present.  */
/* { dg-final { scan-assembler-not {stb\.di\s+r[0-9]+,\s*\[r[0-9]+,\s*r[0-9]+\]} } } */
