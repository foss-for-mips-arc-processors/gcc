/* { dg-do run } */
/* { dg-require-effective-target tls_runtime } */
/* { dg-add-options tls } */

/* The compiler emits for all TLS variables LE accesses.  Tests if the linker
   is correctly resolves the R_ARC_TLS_LE_32 relocation, namely correctly
   allignig the TLS Control Block.  */

extern void abort (void);

/* TLS data ends into .tdata  */
__thread int data_var = 12;
__attribute__((__aligned__(128))) __thread int data_var_128 = 128;

/* TLS data ends into .tbss  */
__thread int bss_var;
__attribute__((__aligned__(256))) __thread int bss_var_256;

int main (void)
{
  int val;
  val =  data_var + data_var_128 + bss_var + bss_var_256;
  if (val != 140)
    abort ();

  return 0;
}
