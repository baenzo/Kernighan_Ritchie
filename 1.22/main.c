#include <stdio.h>
#include <stdbool.h>

#define LINE_LENGTH 80
#define TAB_WIDTH 8
#define INPUT_BUFFER_SIZE 100
#define READ_ELEMENT_SIZE 1
#define WRITE_ELEMENT_SIZE 1

int next_word_length(const char buffer[], int buffer_size, int start_pos, bool* last_word_in_buffer);
void output(const char buffer[], int start_idx, int count, FILE* file);

int main(int argc, char* argv[])
{
	char* input_file_name = NULL;
	char* output_file_name = NULL;

	if (argc >= 3)
	{
		input_file_name = argv[1];
		output_file_name = argv[2];
	}
	else
	{
		printf("Bad parameters!\n");
		return 0;
	}

	FILE* input_file;
	FILE* output_file;

	_set_errno(0);

	if (fopen_s(&input_file, input_file_name, "r") != 0 || input_file == NULL)
	{
		printf("Cannot open file %s\n", input_file_name);
		perror("Error");
		return _get_errno();
	}

	_set_errno(0);

	if (fopen_s(&output_file, output_file_name, "w") != 0 || output_file == NULL)
	{
		printf("Cannot open file %s\n", output_file_name);
		perror("Error");
		return _get_errno();
	}

	// �������� �����
	char buffer[INPUT_BUFFER_SIZE];
	
	/* ����� �����.
	 * � ����� ����� ����������� ��������� ����� �� ��������� ������
	 * ��� ���������� ��������� �������:
	 *
	 *		1. ������ �� �����
	 *		2. � ������ ���� ��������� �����
	 *		3. ����� ����� ����� ����� ���������� ����� � ������
	 */
	char word_buffer[LINE_LENGTH];

	// ����� ����� � ������� �����
	char last_word_length = 0;

	// ����
	//		true  - ������� ����� �������� ������� �����������
	//		false - ������� ����� �� �������� ������� �����������
	bool word_tail = false;

	// ������ ������� ���������� ����� � ������
	int position_in_line = 0;

	// ������� ����
	while (feof(input_file) == 0)
	{
		int count = fread_s(buffer, INPUT_BUFFER_SIZE, READ_ELEMENT_SIZE, INPUT_BUFFER_SIZE, input_file);

		if (count != INPUT_BUFFER_SIZE && ferror(output_file) != 0)
		{
			perror("Error");
			break;
		}

		// ���� ��������� ��������� ������
		for (int IDX = 0; IDX < count; ++IDX)
		{
			const char c = buffer[IDX];

			if (IDX == 0 && last_word_length > 0)
			{
				// ������ �������� ����� ��������� ��������� ������. ����� ����� �������� �����.

				if (c != ' ' && c != '\t' && c != '\n')
				{
					// ������� ������ �� ���-�� ���������� => ������� ����� ���-�� �������
					// �����, ������������ � ������ ����� => ��������� ������� �� ����� ������
					fputc('\n', output_file);
					position_in_line = 0;
					word_tail = true;
				}

				// ������� ����� �� ������ �����.
				output(word_buffer, 0, last_word_length, output_file);
				position_in_line += last_word_length;
				last_word_length = 0;
			}

			if (c == ' ')
			{
				if (position_in_line < LINE_LENGTH)
				{
					fputc(c, output_file);
					++position_in_line;
				}
				else
				{
					fputc('\n', output_file);
					fputc(c, output_file);
					position_in_line = 1;
				}
			}
			else if (c == '\t')
			{
				int new_position_in_line = position_in_line + TAB_WIDTH - position_in_line % TAB_WIDTH;

				if (new_position_in_line >= LINE_LENGTH)
				{
					fputc('\n', output_file);
					position_in_line = 0;
				}

				fputc(c, output_file);
				position_in_line = position_in_line + TAB_WIDTH - position_in_line % TAB_WIDTH;
			}
			else if (c == '\n')
			{
				fputc(c, output_file);
				position_in_line = 0;
			}
			else
			{
				// ��������� �����

				bool last_word_in_buffer = false;

				int word_length = next_word_length(buffer, count, IDX, &last_word_in_buffer);
				int free_space_in_line = LINE_LENGTH - position_in_line;

				if (free_space_in_line == 0)
				{
					// ���������� ����� � ������ ���
					// ��������� ������� �� ����� ������. ���������� ������ ����� ���������
					// ��������� ������ �� ������� ����� � ������ �� ����. ��������.
					
					fputc('\n', output_file);
					position_in_line = 0;
					--IDX;
					continue;
				}
				else if (free_space_in_line < LINE_LENGTH)
				{
					// ������ �� �����, �� ��������� ����� ����

					if (word_length < free_space_in_line) 
					{
						// ���������� ����� � ������ ������ ��� ���������� ��� ������ �����
						
						output(buffer, IDX, word_length, output_file);
						position_in_line += word_length;
						IDX = IDX + word_length - 1;

						// ���� ����� ���� �������, �� ���������� ����
						if (word_tail == true) word_tail = false;
					}
					else if (word_length == free_space_in_line)
					{
						// ���������� ����� � ������ ����� ������� ������� ���� ��� ������ �����
						
						if (last_word_in_buffer == true && word_tail == false)
						{
							// ����� � ������ ��������� � �� �������� ������� ����������� �����
							
							last_word_length = word_length;

							for (int i = 0; i < word_length; ++i)
							{
								word_buffer[i] = buffer[IDX + i];
							}

							IDX = IDX + word_length - 1;
						}
						else
						{
							// ����� � ������ �� ��������� �/��� �������� ������� ����������� �����
							
							output(buffer, IDX, word_length, output_file);
							position_in_line += word_length;
							IDX = IDX + word_length - 1;

							// ���� ����� ���� �������, �� ���������� ����
							if (word_tail == true) word_tail = false;
						}
					}
					else if (word_length > free_space_in_line && word_tail == false)
					{
						// ���������� ����� � ������ ������������ ��� ������ �����
						
						if (word_tail == true)
						{
							// �����-�����. ������� ��� ����� ������ ����� ���������� ����� � ������.
							output(buffer, IDX, free_space_in_line, output_file);
							position_in_line += free_space_in_line;
							IDX = IDX + free_space_in_line - 1;
							word_tail = false;
						}
						else
						{
							// ��������� ������� �� ����� ������. ���������� ������ ����� ���������
							// ��������� ������ �� ������� ����� � ������ �� ����. ��������.

							fputc('\n', output_file);
							position_in_line = 0;
							--IDX;
							continue;
						}
					}
				}
				else if (free_space_in_line == LINE_LENGTH)
				{
					// ������ �����

					int count_to_write = 0;

					if (word_length >= free_space_in_line)
					{
						count_to_write = free_space_in_line;
					}
					else
					{
						count_to_write = word_length;
					}

					output(buffer, IDX, count_to_write, output_file);
					position_in_line += count_to_write;
					IDX = IDX + count_to_write - 1;
				}
			}
		}
	}

	if (last_word_length > 0)
	{
		// ������� ����� �� ������ �����.
		output(word_buffer, 0, last_word_length, output_file);
	}

	fclose(input_file);
	fclose(output_file);

	return 0;
}

int next_word_length(const char buffer[], int buffer_size, int start_pos, bool* last_word_in_buffer)
{
	if (last_word_in_buffer == NULL)
	{
		return 0;
	}

	int word_length = 0;

	int i;

	for (i = start_pos; i < buffer_size; ++i)
	{
		char c = buffer[i];

		if (c == ' ' || c == '\t' || c == '\n') break;

		++word_length;
	}

	if (i == buffer_size)
	{
		*last_word_in_buffer = true;
	}
	else
	{
		*last_word_in_buffer = false;
	}

	return word_length;
}

void output(const char buffer[], int start_idx, int count, FILE* file)
{
	for (int i = 0; i < count; ++i)
	{
		fputc(buffer[start_idx + i], file);
	}
}