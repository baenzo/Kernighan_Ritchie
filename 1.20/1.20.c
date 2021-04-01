#include <stdio.h>
#define TAB_WIDTH 8

int main()
{
	int c;
	int pos_in_tab_field = 0;

	while ((c = getchar()) != '\n' && c != EOF)
	{
		if (c == '\t')
		{
			int spaces_count = TAB_WIDTH - pos_in_tab_field;

			while (spaces_count > 0)
			{
				putchar(' ');
				--spaces_count;
			}

			pos_in_tab_field = 0;
		}
		else
		{
			putchar(c);
			++pos_in_tab_field;
			if (pos_in_tab_field == TAB_WIDTH) pos_in_tab_field = 0;
		}
	}
}