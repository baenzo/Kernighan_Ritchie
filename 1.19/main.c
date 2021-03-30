#include <stdio.h>
#define STRING_BUFFER_SIZE 200

int get_line(char line[], int limit);
int str_length(char string[]);
void reverse(char str[]);

int main()
{
	char string_buffer[STRING_BUFFER_SIZE];
	string_buffer[0] = '\0';

	while (get_line(string_buffer, STRING_BUFFER_SIZE) > 0)
	{
		reverse(string_buffer);

		if (str_length(string_buffer) > 0)
		{
			printf("%s\n", string_buffer);
		}
	}

	return 0;
}

int get_line(char line[], int limit)
{
	// Проверка параметра на корректность.
	if (limit <= 0) return -1;

	int counter = 0;
	int current_char = 0;

	int result = 1;

	while (counter < limit - 1 && (current_char = getchar()) != '\n')
	{
		if (current_char == EOF)
		{
			result = 0;
			break;
		}

		line[counter] = current_char;
		++counter;
	}

	line[counter] = '\0';

	return result;
}

int str_length(char string[])
{
	int i;
	for (i = 0; string[i] != '\0'; ++i);
	return i;
}

void reverse(char str[])
{
	int length = str_length(str);

	if (length <= 0) return;

	int tail = 0;
	int head = length - 1;

	while (tail < head)
	{
		char c = str[tail];
		str[tail] = str[head];
		str[head] = c;

		++tail;
		--head;
	}
}