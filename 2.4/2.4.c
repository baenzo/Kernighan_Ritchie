#include <stdio.h>

void squeeze(char str1[], char str2[]);

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("Bad parameters.");
		return 0;
	}

	squeeze(argv[1], argv[2]);
	printf("%s", argv[1]);
	return 0;
}

void squeeze(char str1[], char str2[])
{
	int i, j;

	for (i = j = 0; str1[i] != '\0'; i++)
	{
		str1[j++] = str1[i];

		for (int k = 0; str2[k] != '\0'; k++)
		{
			if (str1[j-1] == str2[k])
			{
				j--;
				break;
			}
		}
	}

	str1[j] = '\0';
}
