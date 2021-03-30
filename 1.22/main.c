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

	// Основной буфер
	char buffer[INPUT_BUFFER_SIZE];
	
	/* Буфер слова.
	 * В буфер слова сохраняется последнее слово из основного буфера
	 * при выполнении следующих условий:
	 *
	 *		1. строка не пуста
	 *		2. в строке есть свободное место
	 *		3. длина слова равна длине свободного места в строке
	 */
	char word_buffer[LINE_LENGTH];

	// Длина слова в буффере слова
	char last_word_length = 0;

	// Флаг
	//		true  - текущее слово является хвостом предыдущего
	//		false - текущее слово НЕ является хвостом предыдущего
	bool word_tail = false;

	// Индекс первого свободного места в строке
	int position_in_line = 0;

	// Главный цикл
	while (feof(input_file) == 0)
	{
		int count = fread_s(buffer, INPUT_BUFFER_SIZE, READ_ELEMENT_SIZE, INPUT_BUFFER_SIZE, input_file);

		if (count != INPUT_BUFFER_SIZE && ferror(output_file) != 0)
		{
			perror("Error");
			break;
		}

		// Цикл обработки основного буфера
		for (int IDX = 0; IDX < count; ++IDX)
		{
			const char c = buffer[IDX];

			if (IDX == 0 && last_word_length > 0)
			{
				// Первая итерация цикла обработки основного буфера. Буфер слова содержит слово.

				if (c != ' ' && c != '\t' && c != '\n')
				{
					// Текущий символ не явл-ся пробельным => текущее слово явл-ся хвостом
					// слова, сохраненного в буфере слова => выполняем перенос на новую строку
					fputc('\n', output_file);
					position_in_line = 0;
					word_tail = true;
				}

				// Выводим слово из буфера слова.
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
				// Встретили слово

				bool last_word_in_buffer = false;

				int word_length = next_word_length(buffer, count, IDX, &last_word_in_buffer);
				int free_space_in_line = LINE_LENGTH - position_in_line;

				if (free_space_in_line == 0)
				{
					// Свободного места в строке НЕТ
					// Выполняем перенос на новую строку. Откатываем индекс цикла обработки
					// основного буфера на единицу назад и уходим на след. итерацию.
					
					fputc('\n', output_file);
					position_in_line = 0;
					--IDX;
					continue;
				}
				else if (free_space_in_line < LINE_LENGTH)
				{
					// Строка не пуста, но свободное место есть

					if (word_length < free_space_in_line) 
					{
						// Свободного места в строке больше чем необходимо для вывода слова
						
						output(buffer, IDX, word_length, output_file);
						position_in_line += word_length;
						IDX = IDX + word_length - 1;

						// Если слово было хвостом, то сбрасываем флаг
						if (word_tail == true) word_tail = false;
					}
					else if (word_length == free_space_in_line)
					{
						// Свободного места в строке ровно столько сколько надо для вывода слова
						
						if (last_word_in_buffer == true && word_tail == false)
						{
							// Слово в буфере последнее и не является хвостом предыдущего слова
							
							last_word_length = word_length;

							for (int i = 0; i < word_length; ++i)
							{
								word_buffer[i] = buffer[IDX + i];
							}

							IDX = IDX + word_length - 1;
						}
						else
						{
							// Слово в буфере НЕ последнее И/ИЛИ является хвостом предыдущего слова
							
							output(buffer, IDX, word_length, output_file);
							position_in_line += word_length;
							IDX = IDX + word_length - 1;

							// Если слово было хвостом, то сбрасываем флаг
							if (word_tail == true) word_tail = false;
						}
					}
					else if (word_length > free_space_in_line && word_tail == false)
					{
						// Свободного места в строке недостаточно для вывода слова
						
						if (word_tail == true)
						{
							// Слово-хвост. Выводим его часть равную длине свободного места в строке.
							output(buffer, IDX, free_space_in_line, output_file);
							position_in_line += free_space_in_line;
							IDX = IDX + free_space_in_line - 1;
							word_tail = false;
						}
						else
						{
							// Выполняем перенос на новую строку. Откатываем индекс цикла обработки
							// основного буфера на единицу назад и уходим на след. итерацию.

							fputc('\n', output_file);
							position_in_line = 0;
							--IDX;
							continue;
						}
					}
				}
				else if (free_space_in_line == LINE_LENGTH)
				{
					// Строка пуста

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
		// Выводим слово из буфера слова.
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