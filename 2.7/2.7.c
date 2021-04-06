#include <stdio.h>

int invert(int x, unsigned int p, unsigned int n);

int main()
{
	int x = -1272023937;
	unsigned int int_width = sizeof(int) * 8;

	printf("x = %d\n", x);
	printf("int width = %u bits\n\n", int_width);

	char format_str[] = "p = %2u, n = %2u, result = %d\n";

	printf(format_str, int_width - 1, 0, invert(x, int_width - 1, 0));
	printf(format_str, int_width - 1, 5, invert(x, int_width - 1, 5));
	printf(format_str, int_width - 1, int_width, invert(x, int_width - 1, int_width));

	printf(format_str, 12, 0, invert(x, 12, 0));
	printf(format_str, 12, 5, invert(x, 12, 5));
	printf(format_str, 12, 13, invert(x, 12, 13));

	printf(format_str, 0, 0, invert(x, 0, 0));

	return 0;
}

int invert(int x, unsigned int p, unsigned int n)
{
	int a = ~x;
	int mask = ~0 << p << 1;

	if (n == 0)
	{
		mask |= ~(~0 << p << 1);
	}
	else
	{
		mask |= ~(~0 << (p + 1 - n));
	}

	x &= mask;
	mask = ~mask;
	a &= mask;

	return x | a;
}