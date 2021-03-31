#include <stdio.h>

int main()
{
	int c;
	int spaces    = 0;
	int tabs      = 0;
	int new_lines = 0;

	while ((c = getchar()) != EOF)
	{
		if (c == ' ')
		{
			++ spaces;
		}
		else if (c == '\t')
		{
			++ tabs;
		}
		else if (c == '\n')
		{
			++ new_lines;
		}
	}

	printf("\nSpaces: %d\n", spaces);
	printf("Tabs: %d\n", tabs);
	printf("New lines: %d\n", new_lines);

	return 0;
}