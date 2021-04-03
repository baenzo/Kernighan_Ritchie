#include <stdio.h>

int any(char str1[], char str2[]);

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("Bad parameters.");
		return 0;
	}

	int pos = any(argv[1], argv[2]);
	printf("%d", pos);
	return 0;
}

int any(char str1[], char str2[])
{
	for (int i = 0; str1[i] != '\0'; i++)
	{
		for (int j = 0; str2[j] != '\0'; j++)
		{
			if (str1[i] == str2[j]) return i;
		}
	}

	return -1;
}