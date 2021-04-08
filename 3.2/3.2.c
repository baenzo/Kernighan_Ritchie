#include <stdio.h>

#define STR_LENGTH 1000

void escape(char dest[], char src[]);
void descape(char dest[], char src[]);

int main()
{
	char src[STR_LENGTH];
	char dst[STR_LENGTH];

	int c;
	int i;

	for (i = 0; i < (STR_LENGTH - 1) && (c = getchar()) != EOF; i++)
	{
		src[i] = c;
	}

	src[i] = '\0';

	escape(dst, src);
	printf("%s\n", dst);

	for (int j = 0; j < STR_LENGTH; j++)
	{
		src[j] = '\0';
	}

	descape(src, dst);
	printf("%s\n", src);

	return 0;
}

void escape(char dest[], char src[])
{
	char c;
	int dest_idx = 0;

	for (int i = 0; (c = src[i]) != '\0'; i++)
	{
		switch (c)
		{
		case '\n':
			dest[dest_idx] = '\\';
			dest[dest_idx + 1] = 'n';
			dest_idx += 2;
			break;
		case '\t':
			dest[dest_idx] = '\\';
			dest[dest_idx + 1] = 't';
			dest_idx += 2;
			break;
		default:
			dest[dest_idx] = c;
			dest_idx ++;
			break;
		}
	}

	dest[dest_idx] = '\0';
}

void descape(char dest[], char src[])
{
	char previous_char = '\0';
	int dest_idx = 0;
	char c;

	for (int i = 0; (c = src[i]) != '\0'; i++)
	{
		if (c == '\\')
		{
			char next_char = src[i + 1];

			switch (next_char)
			{
			case '\0':
				break;
			case 'n':
				dest[dest_idx] = '\n';
				i++;
				break;
			case 't':
				dest[dest_idx] = '\t';
				i++;
				break;
			default:
				dest[dest_idx] = c;
				break;
			}
		}
		else
		{
			dest[dest_idx] = c;
		}

		dest_idx++;
	}

	dest[dest_idx] = '\0';
}