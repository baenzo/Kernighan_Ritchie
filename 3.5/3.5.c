#include <stdio.h>
#include <stdlib.h>

void itob(int n, char s[], int b);

int main()
{
	char str[50];

	int n = 132754;
	int base = 5;

	printf("Num: %d\n\n", n);

	itob(n, str, base);
	printf("\n   itob(): %15s\n", str);
	_itoa_s(n, str, 50, base);
	printf("_itoa_s(): %15s\n", str);
	
	return 0;
}



void itob(int n, char s[], int b)
{
	//int sign = n;
	int i = 0;

	if (n < 0)
	{
		n = n + 1;

		int t, width;

		for (t = -n, width = 0; t > 0; width++)
		{
			t <<= 1;
		}

		printf("width = %d\n", width);
	}

	do
	{
		int mod_base = n % b;
		int digit = mod_base + b - 1;
		s[i++] = '0' + digit;

		//printf("%11d mod %d = %2d  |  %2d + %d - 1 = %d \n", n, b, mod_base, mod_base, b, digit);
		
		n /= b;
	} while (n != 0);

	s[i] = '\0';

	for (int tail = 0, head = i - 1; tail < head; tail++, head--)
	{
		char c = s[tail];
		s[tail] = s[head];
		s[head] = c;
	}
}