/* { dg-do compile } */
/* { dg-options "-Os" } */


/* Check if MACH is removing the last accumulator to R0 move.  */
int bug()
{
        int bcnt;
        int cur_size = 0;
        int i, j;

        for (i = 10; i > 0; i -= 1) {
                bcnt = i;

                if (i > 5) {
                        cur_size += i * i;
                        continue;
                }

                for (j = 10; j > 0; j -= 1) {
                         bcnt += j;
                }

                cur_size += bcnt * i;
        }

        return cur_size;
}

/* { dg-final { scan-assembler "mov\\s+r0,r58" } } */
/* { dg-final { scan-assembler "vmac2h\\s+0," } } */
/* { dg-final { scan-assembler "mac\\s+0," } } */
