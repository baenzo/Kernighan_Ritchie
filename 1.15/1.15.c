#include <stdio.h>

float celsius_to_fahr(int celsius);

int main()
{
	float fahr = 0;
	int celsius = 0;

	int upper = 100;
	int step = 10;

	printf("Celsius to fahrenheit degrees conversion table.\n\n");

	while (celsius <= upper)
	{
		printf("\t%3d\t%6.2f\n", celsius, celsius_to_fahr(celsius));
		celsius += step;
	}

	return 0;
}

float celsius_to_fahr(int celsius)
{
	return celsius * (9.0 / 5.0) + 32;
}