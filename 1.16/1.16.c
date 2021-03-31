#include <stdio.h>
#define STRING_BUFFER_SIZE 200

int get_line(char line[], int limit);
void copy_line(char src[], char dest[]);
int str_length(char string[]);

int main()
{
	char longest_string[STRING_BUFFER_SIZE];
	char string_buffer[STRING_BUFFER_SIZE];

	int max_length = 0;

	while (get_line(string_buffer, STRING_BUFFER_SIZE) > 0)
	{
		int length = str_length(string_buffer);

		if (length > max_length)
		{
			copy_line(string_buffer, longest_string);
			max_length = length;
		}
	}

	if (max_length > 0)
	{
		printf("\nMax length: %d\n", max_length);
		printf("%s", longest_string);
	}

	return 0;
}

void copy_line(char src[], char dest[])
{
	int i;

	for (i = 0; src[i] != '\0'; ++i)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';
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