#include <stdio.h>
#define MAX_STR_LENGTH 1000

void expand(char s1[], char s2[]);
int expand_available(char s[], int p);

int main()
{
	char str[MAX_STR_LENGTH];
	char dest[MAX_STR_LENGTH];

	char c;

	for (int idx = 0; (idx < MAX_STR_LENGTH - 1) && ((c = getchar()) != EOF); idx++)
	{
		str[idx] = c;

		if (c == '\n')
		{
			str[idx + 1] = '\0';
			expand(str, dest);
			printf("%s", dest);
			idx = -1;
		}
	}

	return 0;
}

void expand(char s1[], char s2[])
{
	char c;
	int idx_dest = 0;

	for (int i = 0; (c = s1[i]) != '\0'; i++)
	{
		if (c == '-' && expand_available(s1, i))
		{
			char e_begin = s1[i - 1];
			char e_end   = s1[i + 1];

			if (e_begin != e_end)
			{
				int way = (e_begin < e_end) ? 1 : -1;

				for (char j = e_begin + way; j != e_end; j += way, idx_dest++)
				{
					s2[idx_dest] = j;
				}
			}
		}
		else
		{
			s2[idx_dest] = c;
			idx_dest++;
		}
	}

	s2[idx_dest] = '\0';
}

int expand_available(char s[], int p)
{
	if (p == 0) return 0;

	char expand_begin = s[p - 1];
	char expand_end   = s[p + 1];

	if (('a' <= expand_begin && expand_begin <= 'z' && 'a' <= expand_end && expand_end <= 'z') ||
		('A' <= expand_begin && expand_begin <= 'Z' && 'A' <= expand_end && expand_end <= 'Z') ||
		('0' <= expand_begin && expand_begin <= '9' && '0' <= expand_end && expand_end <= '9'))
	{
		return 1;
	}
	
	return 0;
}