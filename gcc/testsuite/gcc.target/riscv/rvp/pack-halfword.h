unsigned int
pack_halfwords (unsigned int a, unsigned int b)
{
  return (unsigned short) a | ((unsigned int) (unsigned short) b << 16);
}

void
store_halfwords (unsigned int *out, unsigned int a, unsigned int b)
{
  *out = (unsigned short) a | ((unsigned int) (unsigned short) b << 16);
}

unsigned int
halfword_sign (unsigned int a, unsigned int b)
{
  return (int) ((unsigned short) a
		| ((unsigned int) (unsigned short) b << 16)) < 0;
}
