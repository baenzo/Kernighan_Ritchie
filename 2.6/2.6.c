#include <stdio.h>

int setbits(int x, unsigned int p, unsigned int n, int y);

int main()
{
	int x = -1272023937;
	int y = 1999443473;
	unsigned int int_width = sizeof(int) * 8;

	printf("x = %d\n", x);
	printf("y = %d\n", y);
	printf("int width = %u bits\n\n", int_width);

	char format_str[] = "p = %2u, n = %2u, result = %d\n";

	printf(format_str, int_width - 1, 0, setbits(x, int_width - 1, 0, y));
	printf(format_str, int_width - 1, 5, setbits(x, int_width - 1, 5, y));
	printf(format_str, int_width - 1, int_width, setbits(x, int_width - 1, int_width, y));
	
	printf(format_str, 12, 0, setbits(x, 12, 0, y));
	printf(format_str, 12, 5, setbits(x, 12, 5, y));
	printf(format_str, 12, 13, setbits(x, 12, 13, y));

	printf(format_str, 0, 0, setbits(x, 0, 0, y));

	return 0;
}

int setbits(int x, unsigned int p, unsigned int n, int y)
{
	int x_mask = ~0 << p << 1;
	int y_mask = 0;

	if (n == 0)
	{
		x_mask |= ~(~0 << p << 1);
	}
	else
	{
		x_mask |= ~(~0 << (p + 1 - n));
		y_mask = ~(~0 << (n - 1) << 1);
	}

	x &= x_mask;
	y &= y_mask;

	if (n == 0)
	{
		y = y << p << 1;
	}
	else
	{
		y <<= p + 1 - n;
	}
	
	return x | y;
}