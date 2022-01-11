/* { dg-options "-O" } */
extern void will_trig_exception(void);

__attribute__ ((interrupt))
void isr_0 (void)
{
  will_trig_exception();
}

/* { dg-final { scan-assembler-times "\\sblink" 2 } } */
/* { dg-final { scan-assembler-times "\\sr58" 2 } } */
/* { dg-final { scan-assembler-times "\\sr30" 2 } } */
/* { dg-final { scan-assembler-times "\\sr12" 2 } } */
/* { dg-final { scan-assembler-times "\\sr12" 2 } } */
/* { dg-final { scan-assembler-times "\\sr11" 2 } } */
/* { dg-final { scan-assembler-times "\\sr10" 2 } } */
/* { dg-final { scan-assembler-times "\\sr9" 2 } } */
/* { dg-final { scan-assembler-times "\\sr8" 2 } } */
/* { dg-final { scan-assembler-times "\\sr7" 2 } } */
/* { dg-final { scan-assembler-times "\\sr6" 2 } } */
/* { dg-final { scan-assembler-times "\\sr5\\n" 2 } } */
/* { dg-final { scan-assembler-times "\\sr4\\n" 2 } } */
/* { dg-final { scan-assembler-times "\\sr3\\n" 2 } } */
/* { dg-final { scan-assembler-times "\\sr2\\n" 2 } } */
/* { dg-final { scan-assembler-times "\\sr1\\n" 2 } } */
/* { dg-final { scan-assembler-times "\\sr0" 2 } } */
