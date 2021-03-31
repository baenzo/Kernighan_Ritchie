#include <stdio.h>
#define STRING_BUFFER_SIZE 200
#define MAX_LENGTH 10

int get_line(char line[], int limit);
int str_length(char string[]);

int main()
{
	char string_buffer[STRING_BUFFER_SIZE];

	while (get_line(string_buffer, STRING_BUFFER_SIZE) > 0)
	{
		if (str_length(string_buffer) > MAX_LENGTH)
		{
			printf("%s\n", string_buffer);
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

int str_length(char string[])
{
	int length = 0;

	for (int i = 0; string[i] != '\0'; ++i)
	{
		++length;
	}

	return length;
}