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

	if (sign < 0) n = -n; //

	do
	{
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
//	} while ((n /= 10) != 0);

	if (sign < 0)
	{
		/*for (int j = 0; j < i; j++)
		{
			s[j] = 2 * '0' - s[j];
		}*/

		s[i++] = '-';
	}

	s[i] = '\0';

	for (int c, tail = 0, head = i - 1; tail < head; tail++, head--)
	{
		c = s[tail], s[tail] = s[head], s[head] = c;
	}
}
