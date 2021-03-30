#include <stdio.h>

int main()
{
	int c = 0;

	while ((c = getchar()))
	{
		if (c == '\t')
		{
			printf("\\t");
		}
		else if (c == '\\')
		{
			printf("\\\\");
		}
		else if (c == '\n')
		{
			printf("\\n\n");
		}
		else
		{
			putchar(c);
		}
	}

	return 0;
}