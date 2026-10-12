/* { dg-do compile } */
/* { dg-options "-fsanitize=shadow-call-stack -fno-omit-frame-pointer -fno-optimize-sibling-calls" } */

/* In all the following cases, the return address
   should be loaded to the t0 register */

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

/* { dg-final { scan-assembler-times {addi\tgp,gp,4} 4 { target rv32 } } } */
/* { dg-final { scan-assembler-times {sw\tra,(-4|0)\(gp\)} 4 { target rv32 } } } */
/* { dg-final { scan-assembler-times {addi\tgp,gp,-4} 4 { target rv32 } } } */
/* { dg-final { scan-assembler-times {lw\tt0,(-4|0)\(gp\)} 4 { target rv32 } } } */

/* { dg-final { scan-assembler-times {addi\tgp,gp,8} 4 { target rv64 } } } */
/* { dg-final { scan-assembler-times {sd\tra,(-8|0)\(gp\)} 4 { target rv64 } } } */
/* { dg-final { scan-assembler-times {addi\tgp,gp,-8} 4 { target rv64 } } } */
/* { dg-final { scan-assembler-times {ld\tt0,(-8|0)\(gp\)} 4 { target rv64 } } } */
