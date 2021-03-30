#include <stdio.h>

#define IN  1 /* внутри слова */
#define OUT 0 /* вне слова    */

int main()
{
	int current_char = 0;
	
	int lines_counter = 0;
	int word_counter  = 0;
	int char_counter  = 0;

	int state = OUT;

	while ((current_char = getchar()) != EOF)
	{
		++ char_counter;

		if (current_char == '\n')
		{
			++ lines_counter;
		}

		if (current_char == ' ' || current_char == '\n' || current_char == '\t')
		{
			state = OUT;
		}
		else if (state == OUT)
		{
			state = IN;
			++ word_counter;
		}
	}

	printf("\n\nLines: %d\n", lines_counter);
	printf("Words: %d\n", word_counter);
	printf("Chars: %d\n", char_counter);

	return 0;
}