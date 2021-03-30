#include <stdio.h>

#define IN  1
#define OUT 0

int main()
{
	int state = OUT;
	int first_word = 0;

	int current_char = 0;

	while ((current_char = getchar()) != EOF)
	{
		if (current_char == ' ' || current_char == '\t' || current_char == '\n')
		{
			if (state == IN && first_word == 0)
			{
				first_word = 1;
			}

			state = OUT;
		}
		else
		{
			if (state == OUT)
			{
				if (first_word == 1)
				{
					putchar('\n');
				}

				state = IN;
			}

			putchar(current_char);
		}
	}

	return 0;
}