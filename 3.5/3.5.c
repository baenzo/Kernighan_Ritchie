#include <stdio.h>
#include <stdlib.h>

void itob(int n, char s[], int b);

int main()
{
	int m = -1759584 + 1;
	int radix = 8;

	printf("Num: %d\n\n", m);

	do
	{
		int mod_radix = m % radix;
		printf("%11d mod %d = %d  |  %d + %d - 1 = %d \n", m, radix, mod_radix, mod_radix, radix, mod_radix + radix - 1);
		m /= radix;
	} while (m != 0);


	/*char str[20];
	int n = -2147483647;
	n = --n;
	
	_itoa_s(n, str, 20, 8);
	printf("%s\n", str);
	
	for (int i = 0; i < 20; i++)
		str[i] = 0;

	itob(n, str, 8);
	char c;

	for (int i = 19; i >= 0; i--)
	{
		printf(" %d ", str[i]);
	}*/
	
	return 0;
}



void itob(int n, char s[], int b)
{
	int sign = n;
	int i = 0;

	if (n < 0) n = -(n + 1);

	do
	{
		s[i++] = b - 1 - n % b;
	} while ((n /= b) != 0);

	s[i] = '\0';
}