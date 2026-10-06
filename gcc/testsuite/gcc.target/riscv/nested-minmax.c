/* { dg-do compile } */
/* { dg-options "-march=rv64gc_zba_zbb -mabi=lp64d -O1 -ftree-vrp" } */

short square(short *data, int flag2)
{
    short x = ((*data >> 3) & 0xf);
    short flag = *data & 0x7;
    if(flag2 > 5) {
        x |= x << 4;
        if(x > 34) {
            x = 34;
        }
    }
    return x;
}

/* { dg-final { scan-assembler-times "min\t" 1 } } */
