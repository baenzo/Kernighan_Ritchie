/*
In a two's complement number system , X &= (X-1) deletes the rightmost 1-bit
in X because when adding X to -1, the sum of the rightmost 1-bit of X with
the corresponding bit of -1 is zero, always. (This will always be so because,
according to the problem statement, we consider the rightmost 1-bit of X.
Therefore, carry from the least significant bits is impossible.) As a result
of the bitwise operation "&" between the X and (X - 1) bit 1 of X and bit 0
from (X - 1) will give 0.
*/

#include <stdio.h>

int bitcount(int x);

int main()
{
	printf("int width = %u bits\n\n", sizeof(int) * 8);
	
	printf("1-bits in %4d = %d\n",    0, bitcount(0));
	printf("1-bits in %4d = %d\n", -112, bitcount(-112));
	printf("1-bits in %4d = %d\n",   94, bitcount(94));
	printf("1-bits in %4d = %d\n",   -1, bitcount(-1));

	return 0;
}

int bitcount(int x)
{
	int count = 0;

	while (x != 0)
	{
		x &= (x - 1);
		count++;
	}

	return count;
}