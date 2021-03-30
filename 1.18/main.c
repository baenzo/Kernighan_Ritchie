#include <stdio.h>
#define STRING_BUFFER_SIZE 200

int get_line(char line[], int limit);

int main()
{
	char string_buffer[STRING_BUFFER_SIZE];

	while (get_line(string_buffer, STRING_BUFFER_SIZE) > 0)
	{
		int out_counter = 0;
		char c;

		for (int i = 0; (c = string_buffer[i]) != '\0'; ++i)
		{
			if (c == ' ' || c == '\t')
			{
				if (out_counter == 0)
				{
					putchar(' ');
					++out_counter;
				}
			}
			else
			{
				putchar(c);
				out_counter = 0;
			}
		}
	}
}

int get_line(char line[], int limit)
{
	// Проверка параметра на корректность.
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