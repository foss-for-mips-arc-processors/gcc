#ifndef __uncached
#define __uncached __attribute__((uncached))
#endif

/*Test for QImode.  */
volatile char *
pack_byte_ptr(volatile char *p, const void *s, int len)
{
    volatile __uncached char *buf = p + 4;
    for (int i = 0; i < len; i++)
        buf[i] = ((const char *)s)[i];
    return p;
}

/*Test for HImode.  */
volatile short *
pack_halfword_ptr(volatile short *p, const void *s, int len)
{
    volatile __uncached short *buf = p + 4;
    for (int i = 0; i < len; i++)
        buf[i] = ((const short *)s)[i];
    return p;
}

/*Test for SImode.  */
volatile int *
pack_word_ptr(volatile int *p, const void *s, int len)
{
    volatile __uncached int *buf = p + 4;
    for (int i = 0; i < len; i++)
        buf[i] = ((const int *)s)[i];
    return p;
}

/*Test for DImode.  */
volatile long long *
pack_doubleword_ptr(volatile long long *p, const void *s, int len)
{
    volatile __uncached long long *buf = p + 4;
    for (int i = 0; i < len; i++)
        buf[i] = ((const long long *)s)[i];
    return p;
}
