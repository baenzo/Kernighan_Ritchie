#include <stdio.h>

int strindex(char s[], char t[]);

int main()
{
	char str[] = "abc---abc------abc-----abc";

	int position = strindex(str, "abc");

	printf("position = %d\n", position);

	return 0;
}

int strindex(char s[], char t[])
{
	if (s[0] == '\0' || t[0] == '\0') return -1;

	int result = -1;

	for (int i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == t[0])
		{
			int j;

			for (j = 1; s[i + j] == t[j] && s[i + j] != '\0' && t[j] != '\0'; j++)
				;

			if (t[j] == '\0')
				result = i;
		}
	}

	return result;
}