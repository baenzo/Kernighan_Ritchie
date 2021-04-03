#include <stdio.h>
#include <limits.h>

int htoi(char str[]);

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Bad parameters.");
	}
	else
	{
		printf("%d", htoi(argv[1]));
	}

	return 0;
}

int htoi(char str[])
{
	int result = 0;

	char c;

	int idx = 0;

	for (idx = 0; (c = str[idx]) != '\0'; ++idx)
	{
		if (c == '0' && (str[idx + 1] == 'x' || str[idx + 1] == 'X'))
		{
			idx += 2;
			break;
		}
	}

	int digit = 0;

	for (int n = 0; n < sizeof(int) * 2 && (c = str[idx]) != '\0'; ++n, ++idx)
	{
		if (c >= '0' && c <= '9')
		{
			digit = c - '0';
		}
		else if (c >= 'a' && c <= 'f')
		{
			digit = c - 'a' + 10;
		}
		else if (c >= 'A' && c <= 'F')
		{
			digit = c - 'A' + 10;
		}
		else
		{
			break;
		}

		result = result * 16 + digit;
	}

	return result;
}