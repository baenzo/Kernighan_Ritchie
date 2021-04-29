/*
In a two's complement number representation, our version of itoa
does not handle the largest negative number, that is, the value
of N equal to -(2^(wordsize-1)) because two's complement code
allows to represent numbers from -(2 ^ (wordsize - 1)) to 2 ^ (wordsize - 1) - 1.
This indicates that the modulus of the largest negative number
is greater than the modulus of the maximum positive number.Therefore,
changing the sign on the line of code

		n = -n;

will not work correctly.
*/

#include <stdio.h>
#include <limits.h>
#include <stdint.h>

void itoa(int n, char s[]);

int main()
{
	char str[50];
	int a;

	printf("\n     Integer          String\n\n");

	a = INT_MIN;
	itoa(a, str);
	printf("%12d    %12s\n", a, str);

	a = INT_MIN / 2;
	itoa(a, str);
	printf("%12d    %12s\n", a, str);

	a = 0;
	itoa(a, str);
	printf("%12d    %12s\n", a, str);

	a = INT_MAX / 2;
	itoa(a, str);
	printf("%12d    %12s\n", a, str);

	a = INT_MAX;
	itoa(a, str);
	printf("%12d    %12s\n", a, str);

	return 0;
}

void itoa(int n, char s[])
{
	int i = 0;
	int sign = n;

	do
	{
		s[i++] = n % 10;
	} while ((n /= 10) != 0);

	for (int j = 0; j < i; j++)
	{
		if (sign < 0)
			s[j] = -s[j] + '0';
		else
			s[j] += '0';
	}

	if (sign < 0) s[i++] = '-';

	s[i] = '\0';

	for (int tail = 0, head = i - 1; tail < head; tail++, head--)
	{
		char c = s[tail];
		s[tail] = s[head];
		s[head] = c;
	}
}
