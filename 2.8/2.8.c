#include <stdio.h>

int rightrot(int x, unsigned int n);

int main()
{
	int x = -1272023937;
	unsigned int int_width = sizeof(int) * 8;

	printf("x = %d\n", x);
	printf("int width = %u bits\n\n", int_width);

	char format_str[] = "n = %2u, result = %d\n";

	printf(format_str, 0, rightrot(x, 0));
	printf(format_str, 5, rightrot(x, 5));
	printf(format_str, int_width, rightrot(x, int_width));
	printf(format_str, int_width + 5, rightrot(x, int_width + 5));

	return 0;
}

int rightrot(int x, unsigned int n)
{
	int mask_LSB = 1;
	int mask_MSB = 1 << (sizeof(int) * 8 - 1);

	for (int i = 0; i < n; i++)
	{
		if ((x & mask_LSB) == 0)
		{
			x >>= 1;
			x &= ~mask_MSB;
		}
		else
		{
			x >>= 1;
			x |= mask_MSB;
		}
	}

	return x;
}