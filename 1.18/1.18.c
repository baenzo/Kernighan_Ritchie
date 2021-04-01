#include <stdio.h>
#define STRING_BUFFER_SIZE 200
#define STATE_IN 1
#define STATE_OUT 0

int get_line(char line[], int limit);

int main()
{
	char string_buffer[STRING_BUFFER_SIZE];

	while (get_line(string_buffer, STRING_BUFFER_SIZE) > 0)
	{
		unsigned int current_length = 0;
		int state = STATE_IN;
		char c;

		for (int i = 0; (c = string_buffer[i]) != '\0'; ++i)
		{
			if (c == '\n' && current_length == 0)
			{
				continue;
			}
			else if (c == ' ' || c == '\t')
			{
				if (state == STATE_IN)
				{
					putchar(' ');
					state = STATE_OUT;
					++current_length;
				}
			}
			else
			{
				putchar(c);
				state = STATE_IN;
				++current_length;
			}
		}
	}
}

int get_line(char line[], int limit)
{
	if (limit <= 0) return -1;

	int counter = 0;
	int current_char = 0;

	int result = 1;

	while (counter < limit - 1)
	{
		current_char = getchar();

		if (current_char == EOF)
		{
			result = 0;
			break;
		}

		line[counter] = current_char;
		++counter;

		if (current_char == '\n') break;
	}

	line[counter] = '\0';

	return result;
}