#include <stdio.h>

int main()
{
	for (int fahr = 300; fahr >= 0; fahr -= 20)
	{
		printf("%3d\t%6.2f\n", fahr, 5.0 / 9.0 * (fahr - 32));
	}

	return 0;
}