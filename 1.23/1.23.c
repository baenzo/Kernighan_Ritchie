#include <stdio.h>
#include <stdbool.h>

#define READ_ELEMENT_SIZE 1
#define WRITE_ELEMENT_SIZE 1

#define STRING_LITERAL_START '\"'
#define STRING_LITERAL_END   '\"'

#define CHARACTER_CONST_START '\''
#define CHARACTER_CONST_END   '\''

#define ESCAPE_SIGN '\\'

int main(int argc, char* argv[])
{
	char* input_file_name  = NULL;
	char* output_file_name = NULL;

	if (argc >= 3)
	{
		input_file_name  = argv[1];
		output_file_name = argv[2];
	}
	else
	{
		printf("Bad parameters!\n");
		return 0;
	}

	FILE* input_file;
	FILE* output_file;

	int error_code = 0;

	if (fopen_s(&input_file, input_file_name, "r") != 0 || input_file == NULL)
	{
		_get_errno(&error_code);
		printf("Cannot open file \'%s\'\n", input_file_name);
		perror("");
		return error_code;
	}

	if (fopen_s(&output_file, output_file_name, "w") != 0 || output_file == NULL)
	{
		_get_errno(&error_code);
		printf("Cannot open file \'%s\'\n", output_file_name);
		perror("");
		return error_code;
	}

	int current_char = '\0';
	int previous_char = '\0';

	bool in_string_literal = false;
	bool in_character_const = false;

	bool in_single_line_comment = false;
	bool in_multi_line_comment = false;
	unsigned int multi_line_comment_length = 0;

	while ((current_char = fgetc(input_file)) != EOF)
	{
		if (in_single_line_comment == false && in_multi_line_comment == false)
		{
			if (in_string_literal == true)
			{
				fputc(current_char, output_file);

				if (current_char == STRING_LITERAL_END && previous_char != ESCAPE_SIGN)
				{
					in_string_literal = false;
				}
			}
			else if (in_character_const == true)
			{
				fputc(current_char, output_file);

				if (current_char == CHARACTER_CONST_END && previous_char != ESCAPE_SIGN)
				{
					in_character_const = false;
				}
			}
			else
			{
				if (current_char == STRING_LITERAL_START)
				{
					in_string_literal = true;

					if (previous_char == '/' || previous_char == '*')
					{
						fputc(previous_char, output_file);
					}

					fputc(current_char, output_file);
				}
				else if (current_char == CHARACTER_CONST_START)
				{
					in_character_const = true;

					if (previous_char == '/' || previous_char == '*')
					{
						fputc(previous_char, output_file);
					}

					fputc(current_char, output_file);
				}
				else if (current_char == '/')
				{
					if (previous_char == '/') in_single_line_comment = true;
				}
				else if (current_char == '*')
				{
					if (previous_char == '/') in_multi_line_comment = true;
				}
				else
				{
					if (previous_char == '/' || previous_char == '*')
					{
						fputc(previous_char, output_file);
					}

					fputc(current_char, output_file);
				}
			}
		}
		else
		{
			// In the comment

			if (in_single_line_comment == true)
			{
				if (current_char == '\n')
				{
					in_single_line_comment = false;
					fputc(current_char, output_file);
				}
			}
			else if (in_multi_line_comment == true)
			{
				if (current_char == '/' && previous_char == '*' && multi_line_comment_length > 0)
				{
					in_multi_line_comment = false;
					multi_line_comment_length = 0;
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
	fclose(output_file);

	return error_code;
}