/* { dg-do run } */
/* { dg-options "-O2" } */

typedef short v4hi __attribute__((vector_size(8)));

__attribute__((noinline)) void foo3(short a)
{
    if (a != 520)
    {
        __builtin_abort();
    }
}

__attribute__((noinline)) void foo2(v4hi v)
{
    foo3(v[0]);
}

__attribute__((noinline)) void foo(v4hi *v)
{
    foo2(*v);
}

int main (void)
{
    v4hi v;
    v[0] = 520;
    v[1] = -1;
    v[2] = 42;
    v[3] = -42;
    foo(&v);
    foo2(v);
    return 0;
}
