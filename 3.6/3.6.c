#include <stdio.h>
#include <limits.h>

void itoa(int n, char s[], int min_length);

int main()
{
	char str[50];
	int a;

	printf("\n     Integer          String\n\n");

	a = INT_MIN;
	itoa(a, str, 12);
	printf("%12d    [%s]\n", a, str);

	return 0;
}

void itoa(int n, char s[], int min_length)
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

	if (i < min_length)
	{
		int space_length = min_length - i;

		for (int j = i; j >= 0; j--)
		{
			s[j + space_length] = s[j];
		}

		for (int j = 0; j < space_length; j++)
		{
			s[j] = ' ';
		}
	}
}