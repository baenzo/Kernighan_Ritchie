#include <stdio.h>

double atof(char s[]);

int main()
{
	char str[] = "12548.27E";

	double dbl = atof(str);
	printf("%f\n", dbl);

	return 0;
}

double atof(char s[])
{
	double val, power;
	int i, sign;

	for (i = 0; s[i] == ' ' || s[i] == '\t' || s[i] == '\n'; i++)
		;

	sign = (s[i] == '-') ? -1 : 1;

	if (s[i] == '+' || s[i] == '-')
		i++;

	for (val = 0.0; s[i] >= '0' && s[i] <= '9'; i++)
		val = 10.0 * val + (s[i] - '0');

	if (s[i] == '.')
		i++;

	for (power = 1.0; s[i] >= '0' && s[i] <= '9'; i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	val = sign * val / power;

	if (s[i] == 'e' || s[i] == 'E')
	{
		i++;

		int exp_sign = (s[i] == '-') ? -1 : 1;

		if (s[i] == '-' || s[i] == '+')
			i++;

		int exp_val = 0;

		while (s[i] >= '0' && s[i] <= '9')
		{
			exp_val = 10 * exp_val + (s[i] - '0');
			i++;
		}

		power = 1.0;

		for (int j = 0; j < exp_val; j++)
			power *= 10.0;

		if (exp_sign > 0)
			val *= power;
		else
			val /= power;

	}

	return val;
}