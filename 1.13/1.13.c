#include <stdio.h>

#define IN  1
#define OUT 0
#define HISTO_BRICK 254

int main()
{
	int current_char = 0;
	int word_length  = 0;
	
	int state = OUT;

	while ((current_char = getchar()) != EOF)
	{
		if (current_char == ' ' || current_char == '\t' || current_char == '\n')
		{
			if (state == IN)
			{
				state = OUT;
				printf(" %d", word_length);
			}
		}
		else
		{
			if (state == IN)
			{
				++ word_length;
				putchar(HISTO_BRICK);
			}
			else
			{
				state = IN;
				putchar('\n');
				putchar(HISTO_BRICK);
				word_length = 1;
			}
		}
	}

	return 0;
}