#include <stdio.h>

int setbits(int x, unsigned int p, unsigned int n, int y);

int main()
{
	int x = -1272023937;
	int y = 1999443473;
	int result = setbits(x, 9, 3, y);
	printf("%d", result);
	return 0;
}

int setbits(int x, unsigned int p, unsigned int n, int y)
{
	int x_mask = 0;
	x_mask = (~x_mask << (p + 1)) | (~(~x_mask << (p + 1 - n)));
	x &= x_mask;

	int y_mask = 0;
	y_mask = ~(~y_mask << n);
	y &= y_mask;
	y <<= p + 1 - n;

	return x | y;
}