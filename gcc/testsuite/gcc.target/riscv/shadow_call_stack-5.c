/* { dg-do compile } */
/* { dg-options "-fsanitize=shadow-call-stack -fno-omit-frame-pointer -fno-optimize-sibling-calls" } */
/* { dg-additional-options "-march=rv32g_zicfiss -fcf-protection=return" { target rv32 } }*/
/* { dg-additional-options "-march=rv64g_zicfiss -fcf-protection=return" { target rv64 } }*/

__attribute__((noipa))
int f3() {
    return 1;
}

__attribute__((noipa))
int f2() {
    return f3();
}

__attribute__((noipa))
int f1() {
    return f2();
}

__attribute__((noipa))
int main() {
    int temp = f1();
    return temp;
}

/* { dg-final { scan-assembler-not {addi\tgp,gp,4} { target rv32 } } } */
/* { dg-final { scan-assembler-not {sw\tra,(-4|0)\(gp\)} { target rv32 } } } */
/* { dg-final { scan-assembler-not {addi\tgp,gp,-4} { target rv32 } } } */
/* { dg-final { scan-assembler-not {lw\tt0,(-4|0)\(gp\)} { target rv32 } } } */

/* { dg-final { scan-assembler-not {addi\tgp,gp,8} { target rv64 } } } */
/* { dg-final { scan-assembler-not {sd\tra,(-8|0)\(gp\)} { target rv64 } } } */
/* { dg-final { scan-assembler-not {addi\tgp,gp,-8} { target rv64 } } } */
/* { dg-final { scan-assembler-not {ld\tt0,(-8|0)\(gp\)} { target rv64 } } } */

/* { dg-final { scan-assembler-times {sspush\tra} 4 } } */
/* { dg-final { scan-assembler-times {sspopchk\tt0} 4 } } */
