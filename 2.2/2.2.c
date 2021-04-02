#include <stdio.h>
#define STR_LIMIT 21

int main()
{
	char data[STR_LIMIT];
	int c = 0;
	int i;

	for (i = 0; (c = getchar()) != EOF; ++i)
	{
		if (i == STR_LIMIT - 1)
			break;
		else if (c == '\n')
			break;
		else
			data[i] = c;
	}

	data[i] = '\0';
	printf("%s", data);

	return 0;
}