#include <stdio.h>

int main()
{
	int c = 0;

	int spaces_counter = 0;

	while ((c = getchar()) != EOF)
	{
		if (c == ' ')
		{
			if (spaces_counter == 0)
			{
				++spaces_counter;
				putchar(c);
			}
		}
		else
		{
			putchar(c);
			spaces_counter = 0;
		}
	}

	return 0;
}