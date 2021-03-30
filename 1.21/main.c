#include <stdio.h>
#include <errno.h>
#define TAB_WIDTH 8
#define INPUT_BUFFER_SIZE 5
#define READ_ELEMENT_SIZE 1
#define WRITE_ELEMENT_SIZE 1

int main()
{
	/*char error_message[100];

	if ((error_number = _set_errno(0)) != 0)
	{
		strerror_s(error_message, 100, error_number);
		printf("Error: %s", error_message);
		return -1;
	}*/

	char name_input_file[] = "in.txt";
	char name_output_file[] = "out.txt";

	FILE* finput;
	FILE* foutput;
	
	errno_t error_code = fopen_s(&finput, name_input_file, "r");

	if (error_code != 0 || finput == NULL)
	{
		printf("Cannot open file %s. Error code: %d", name_input_file, error_code);
		return 0;
	}

	error_code = fopen_s(&foutput, name_output_file, "w");
	
	if (error_code != 0 || foutput == NULL)
	{
		printf("Cannot open file %s. Error code: %d", name_output_file, error_code);
		return 0;
	}

	char input_buffer[INPUT_BUFFER_SIZE];

	int space_width = 0;

	while (feof(finput) == 0)
	{
		size_t count = fread_s(input_buffer, INPUT_BUFFER_SIZE, READ_ELEMENT_SIZE, INPUT_BUFFER_SIZE, finput);

		if (count != INPUT_BUFFER_SIZE && ferror(foutput) != 0)
		{
			_get_errno(&error_code);
			printf("Read error. Error code: %d", error_code);
			break;
		}

		for (int i = 0; i < count; ++i)
		{
			char c = input_buffer[i];

			if (c == ' ')
			{
				++space_width;
			}
			else if (c == '\t')
			{
				space_width += TAB_WIDTH;
			}
			else
			{
				int tab_count = space_width / TAB_WIDTH;
				int space_count = space_width - tab_count * TAB_WIDTH;
				
				space_width = 0;

				for (int i = 0; i < tab_count; ++i)
				{
					fputc('\t', foutput);
				}

				for (int i = 0; i < space_count; ++i)
				{
					fputc(' ', foutput);
				}

				fputc(c, foutput);
			}
		}
	}

	fclose(finput);
	fclose(foutput);

	return 0;
}