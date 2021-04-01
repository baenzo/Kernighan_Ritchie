#include <stdio.h>
#include <errno.h>
#define TAB_WIDTH 8
#define INPUT_BUFFER_SIZE 1000
#define READ_ELEMENT_SIZE 1
#define WRITE_ELEMENT_SIZE 1

void space_output(int length, FILE* file);

int main(int argc, char* argv[])
{

	char* name_input_file  = NULL;
	char* name_output_file = NULL;

	if (argc >= 3)
	{
		name_input_file  = argv[1];
		name_output_file = argv[2];
	}
	else
	{
		printf("Bad parameters!\n");
		return 0;
	}

	FILE* finput  = NULL;
	FILE* foutput = NULL;
	
	int error_code = 0;

	if (fopen_s(&finput, name_input_file, "r") != 0 || finput == NULL)
	{
		_get_errno(&error_code);
		printf("Cannot open file \'%s\'\n", name_input_file);
		perror("");
		return error_code;
	}
	
	if (fopen_s(&foutput, name_output_file, "w") != 0 || foutput == NULL)
	{
		_get_errno(&error_code);
		printf("Cannot open file \'%s\'\n", name_output_file);
		perror("");
		return error_code;
	}

	error_code = 0;

	char input_buffer[INPUT_BUFFER_SIZE];

	int space_length = 0;

	while (feof(finput) == 0)
	{
		size_t count = fread_s(input_buffer, INPUT_BUFFER_SIZE, READ_ELEMENT_SIZE, INPUT_BUFFER_SIZE, finput);

		if (ferror(finput) != 0)
		{
			_get_errno(&error_code);
			perror("File read error");
			break;
		}

		for (int i = 0; i < count; ++i)
		{
			char c = input_buffer[i];

			if (c == ' ')
			{
				++space_length;
			}
			else if (c == '\t')
			{
				space_length += TAB_WIDTH;
			}
			else
			{
				space_output(space_length, foutput);
				space_length = 0;
				fputc(c, foutput);
			}
		}
	}

	if (space_length > 0 && feof(finput) != 0 && ferror(finput) == 0)
	{
		space_output(space_length, foutput);
	}

	fclose(finput);
	fclose(foutput);

	return error_code;
}

void space_output(int length, FILE* file)
{
	if (file == NULL) return;

	int tab_count = length / TAB_WIDTH;
	int space_count = length - tab_count * TAB_WIDTH;

	for (int i = 0; i < tab_count; ++i)
	{
		fputc('\t', file);
	}

	for (int i = 0; i < space_count; ++i)
	{
		fputc(' ', file);
	}
}