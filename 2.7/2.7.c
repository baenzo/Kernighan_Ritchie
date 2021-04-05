#include <stdio.h>

int invert(int x, unsigned int p, unsigned int n);

int main()
{
	int x = 1903483230;
	int result = invert(x, 31, 32);
	printf("%d", result);
	return 0;
}

int invert(int x, unsigned int p, unsigned int n)
{
	int a = ~x;
	int mask = ((~0 << p) << 1) | (~(~0 << (p + 1 - n)));
	//                 ^^^^^^^ do not replace with (p + 1) !!!
	x &= mask;
	mask = ~mask;
	a &= mask;

	return x | a;
}