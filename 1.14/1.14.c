#include <stdio.h>

#define ASCII_TABLE_CAPACITY 256
#define HISTO_BRICK 219
#define HISTO_HALF_BRICK 220

int main()
{
	// chars_frequency[i] - Is frequency of character whose code is 'i'
	int chars_frequency[ASCII_TABLE_CAPACITY];

	// Array of char codes.
	// char_codes[n] - Is char code, whose frequency is char_requency[ char_codes[n] ]
	int char_codes[ASCII_TABLE_CAPACITY];

	// Arrays initialisation
	for (int idx = 0; idx < ASCII_TABLE_CAPACITY; ++ idx)
	{
		chars_frequency[idx] = 0;
		char_codes[idx]      = idx;
	}

	int current_char = 0;

	// Input
	while ((current_char = getchar()) != EOF)
	{
		chars_frequency[current_char] += 1;
	}

	// Sorting MAX to MIN
	for (int idx_position = 0; idx_position < ASCII_TABLE_CAPACITY - 1; ++ idx_position)
	{	
		int idx_max_frequency = 0;
		int max_frequency     = 0;

		for (int i = idx_position + 1; i < ASCII_TABLE_CAPACITY; ++ i)
		{
			int frequency = chars_frequency[char_codes[i]];

			if (frequency > max_frequency)
			{				
				idx_max_frequency = i;
				max_frequency = frequency;
			}
		}

		if (max_frequency > chars_frequency[char_codes[idx_position]])
		{
			int buf = char_codes[idx_position];

			char_codes[idx_position] = char_codes[idx_max_frequency];
			char_codes[idx_max_frequency] = buf;
		}
	}

	// Calculate width and height of histogram
	int histo_width  = 0;
	int histo_height = 0;

	for (int idx = 0; idx < ASCII_TABLE_CAPACITY; ++ idx)
	{
		int frequency = chars_frequency[idx];

		if (frequency > 0)
		{
			++ histo_width;
		}

		if (frequency > histo_height)
		{
			histo_height = frequency;
		}
	}

	// Histogram print
	for (int current_height = histo_height; current_height > 0; -- current_height)
	{
		int f = 0;

		for (int current_column = 0; current_column < histo_width; ++ current_column)
		{
			int frequrncy = chars_frequency[char_codes[current_column]];

			if (frequrncy == current_height && f == 0)
			{
				printf("%3d | ", frequrncy);
				f = 1;
			}
		}

		if (f == 0)
		{
			printf("    | ");
		}

		for (int current_column = 0; current_column < histo_width; ++ current_column)
		{
			int frequrncy = chars_frequency[char_codes[current_column]];
			
			if (frequrncy == current_height)
			{
				printf("%c ", HISTO_HALF_BRICK);
			}
			else if (frequrncy > current_height)
			{
				printf("%c ", HISTO_BRICK);
			}
			else
			{
				printf("  ");
			}
		}

		putchar('\n');
	}

	printf("    +-");

	for (int current_column = 0; current_column < histo_width; ++current_column)
	{
		printf("--");
	}

	printf("\n      ");

	for (int current_column = 0; current_column < histo_width; ++ current_column)
	{
		int current_char = char_codes[current_column];

		if (current_char == '\n')
		{
			printf("\\n");
		}
		else
		{
			printf("%c ", current_char);
		}
		
	}

	return 0;
}