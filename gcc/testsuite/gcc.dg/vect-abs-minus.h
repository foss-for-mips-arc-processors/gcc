typedef __INT32_TYPE__ i32;
typedef __UINT32_TYPE__ u32;
typedef i32 v2si __attribute__ ((vector_size (8)));
typedef u32 v2su __attribute__ ((vector_size (8)));

static void __attribute__ ((noipa))
magnitude (const v2si *a, const v2si *b, v2si *out)
{
#ifdef WRAPPING_SIGNED_SUBTRACTION
  v2si difference = *a - *b;
#else
  v2si difference = (v2si) ((v2su) *a - (v2su) *b);
#endif
  v2si sign = difference >> 31;
  *out = (difference + sign) ^ sign;
}

static const v2si a[] =
{
  { 1073741824, 37 },
  { -2147483647 - 1, -5 },
  { 2147483647, 123 },
  { -2147483647 - 1, -456 }
};

static const v2si b[] =
{
  { -2147483647 - 1, -5 },
  { 1073741824, 37 },
  { -2147483647 - 1, -456 },
  { 2147483647, 123 }
};

static const v2si expected[] =
{
  { 1073741824, 42 },
  { 1073741824, 42 },
  { 1, 579 },
  { 1, 579 }
};

static struct
{
  v2si before;
  v2si value;
  v2si after;
} result = { { 17, 23 }, { 0, 0 }, { 29, 31 } };

int
main (void)
{
  for (unsigned int i = 0; i < sizeof (a) / sizeof (a[0]); ++i)
    {
      magnitude (&a[i], &b[i], &result.value);
      for (unsigned int j = 0; j < 2; ++j)
        if (result.value[j] != expected[i][j])
          __builtin_abort ();
      if (result.before[0] != 17 || result.before[1] != 23
          || result.after[0] != 29 || result.after[1] != 31)
        __builtin_abort ();
    }
  return 0;
}
