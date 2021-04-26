#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define STR_BUFFER_LENGTH 50

/*
	For this exercise, I relied on how the _itob_s function works.
The key point is how the conversion of negative numbers is done.
If a negative number is converted to a decimal number system,
then the sign of the number is denoted by the symbol "-".
In other cases, the conversion of a negative number to the target
number system is performed as a conversion of an unsigned (positive)
number that has the same binary representation as a negative number.
For example:

	-1382 = -1382 (base 10)
	-1382 = 535a79065 (base 13)

If the int type (signed int) is 32-bit, then the number -1382 in the
binary system (in two's complement) looks like:

	11111111 11111111 11111010 10011010

The unsigned int 4294965914 has the same representation in the binary
system. Thus, to convert a negative number to a target base other
than 10, I use a positive unsigned number whose binary representation
is the same as the signed binary representation.

	And (importantly) I do not use variables with a bit width greater
than the bit width of an int variable. This can be useful if it becomes
necessary to modify the itob(n, s, b) function in such a way that the
type of the parameter "n" has the maximum bit width.
*/

void itob(int n, char s[], int b);

int main()
{
	char str1[STR_BUFFER_LENGTH];

	int n = -1382;
	int base = 13;
	int equal = 1;

	itob(n, str1, base);
	printf("\n   itob(): %15s\n", str1);

	_itoa_s(n, str1, STR_BUFFER_LENGTH, base);
	printf("_itoa_s(): %15s\n", str1);
	
	return 0;
}

void itob(int n, char s[], int b)
{
	int sign = n;
	int i = 0;

	if (n < 0)
	{
		if (b != 10)
		{
			/*
			Since at the moment the operation of type casting
			has not yet been considered, we will use bitwise operations.

			We know that:

				(a + b) mod c = (a mod c + b mod c) mod c
			
			Thus, the remainder of the division of the unsigned number
			11111111 in binary can be represented as follows:

				11111111 mod c = (10000000 mod c + 01111111 mod c) mod c

			So let's pretend that the variable n holds an unsigned integer
			and do the same with it :)
			*/

			n &= ~INT_MIN;

			int mod_1 = -(INT_MIN % b);
			int mod_2 = n % b;

			s[i++] = '0' + (mod_1 + mod_2) % b;
			n = -(INT_MIN / b) + n / b + (mod_1 + mod_2) / b;
		}
		else if (b == 10)
		{
			n = -n;
		}
	}

	do
	{
		int digit = n % b;
		s[i++] = '0' + digit;
		n /= b;
	} while (n != 0);


	if (sign < 0 && b == 10)
	{
		s[i++] = '-';
	}

	s[i] = '\0';

	for (int tail = 0, head = i - 1; tail < head; tail++, head--)
	{
		char c = s[tail];
		s[tail] = s[head];
		s[head] = c;
	}

	int c;

	for (int j = 0; (c = s[j]) != '\0'; j++)
	{
		if (c > '9')
		{
			s[j] = c - '0' - 10 + 'a';
		}
	}
}