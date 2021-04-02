#include <stdio.h>
#include <stdbool.h>

#define READ_ELEMENT_SIZE 1
#define WRITE_ELEMENT_SIZE 1
#define ESCAPE_SIGN '\\'

int main(int argc, char* argv[])
{
	char* input_file_name = NULL;

	if (argc >= 2)
	{
		input_file_name = argv[1];
	}
	else
	{
		printf("Bad parameters!\n");
		return 0;
	}

	FILE* input_file;

	_set_errno(0);

	if (fopen_s(&input_file, input_file_name, "r") != 0 || input_file == NULL)
	{
		printf("Cannot open file %s\n", input_file_name);
		perror("Error");
		return _get_errno();
	}

	int current_char = '\0';
	int previous_char = '\0';

	bool in_string_literal = false;
	bool in_character_const = false;

	bool in_single_line_comment = false;
	bool in_multi_line_comment = false;
	
	unsigned int multi_line_comment_length = 0;

	int curly_brackets     = 0; // {}
	int round_brackets     = 0; // ()
	int square_brackets    = 0; // []
	int double_quotes      = 0; // ""
	int single_quotes      = 0; // ''
	int multiline_comments = 0; // /**/

	while ((current_char = fgetc(input_file)) != EOF)
	{
		if (in_single_line_comment == false && in_multi_line_comment == false)
		{
			if (in_string_literal == true)
			{
				if (current_char == '\"' && previous_char != ESCAPE_SIGN)
				{
					--double_quotes;
					in_string_literal = false;
				}
			}
			else if (in_character_const == true)
			{
				if (current_char == '\'' && previous_char != ESCAPE_SIGN)
				{
					--single_quotes;
					in_character_const = false;
				}
			}
			else
			{
				if (current_char == '\"')
				{
					++double_quotes;
					in_string_literal = true;
				}
				else if (current_char == '\'')
				{
					++single_quotes;
					in_character_const = true;
				}
				else if (current_char == '/')
				{
					if (previous_char == '/') in_single_line_comment = true;
				}
				else if (current_char == '*')
				{
					if (previous_char == '/')
					{
						in_multi_line_comment = true;
						++multiline_comments;
					}
				}
				else
				{
					switch (current_char)
					{
					case '{':
						++curly_brackets;
						break;
					case '}':
						--curly_brackets;
						break;
					case '(':
						++round_brackets;
						break;
					case ')':
						--round_brackets;
						break;
					case '[':
						++square_brackets;
						break;
					case ']':
						--square_brackets;
						break;
					default:
						break;
					}
				}
			}
		}
		else
		{
			// In the comment

			if (in_single_line_comment == true)
			{
				if (current_char == '\n') in_single_line_comment = false;
			}
			else if (in_multi_line_comment == true)
			{
				if (current_char == '/' && previous_char == '*' && multi_line_comment_length > 0)
				{
					in_multi_line_comment = false;
					multi_line_comment_length = 0;
					--multiline_comments;
					previous_char = '\0';
					continue;
				}
				else
				{
					++multi_line_comment_length;
				}
			}
		}

		previous_char = current_char;
	}

	if (ferror(input_file))
	{
		perror("Error");
	}

	fclose(input_file);

	if (double_quotes != 0)
	{
		printf("Double quotes disbalance!\n");
	}
	else if (single_quotes != 0)
	{
		printf("Single quotes disbalance!\n");
	}
	else if (multiline_comments != 0)
	{
		printf("Unclosed multiline comment!\n");
	}
	else
	{
		if (curly_brackets != 0)
		{
			printf("Curly brackets dispalance!\n");
		}

		if (round_brackets != 0)
		{
			printf("Round brackets dispalance!\n");
		}

		if (square_brackets != 0)
		{
			printf("Square brackets dispalance!\n");
		}
	}

	return 0;
}