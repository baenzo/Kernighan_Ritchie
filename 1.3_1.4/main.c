#include <stdio.h>

int main()
{
	float fahr  = 0;
	int celsius = 0;

	int upper = 100;
	int step  = 10;

	printf("\n\tCelsius to fahrenheit degrees conversion table.\n\n");

	while (celsius <= upper)
	{
		fahr = celsius * (9.0 / 5.0) + 32;
		printf("\t%3d\t%6.2f\n", celsius, fahr);

		celsius += step;
	}

	return 0;
}