/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-skip-if "" { *-*-* } { "-flto" "-Og" "-O0" "-O1" "-Os" "-Oz" } } */
/* { dg-options "-c -g -mtune=arc-v-rmx-500-series -march=rv32im -mabi=ilp32 -fdump-rtl-sched2" } */

void foo(int *a) {
    int bar = a[0] + a[1];
    a[0] = bar;
    a[1] = bar;
    return;
}

/* { dg-final { scan-rtl-dump ";;\[ \t\]*(\[0-9\]+)-->\[^\n\]*\\]=.*\n(?:\[^\n\]*\n)*?;;\[ \t\]*\\1-->\[^\n\]*\\]=" "sched2" } } */
