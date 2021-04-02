#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
	// char
	// short
	// int
	// long

	char calc_min[] = "  calculated: min ";
	char lim_min[]  = "    limits.h: min ";
	char max[] = "   max ";

	signed char signed_char = 2;
	while (signed_char > 0) signed_char *= 2;
	printf("signed char\n\n");
	printf("%s%d", calc_min, signed_char);
	--signed_char;
	printf("%s%d\n", max, signed_char);
	printf("%s%d%s%d\n\n", lim_min, SCHAR_MIN, max, SCHAR_MAX);

	unsigned char unsigned_char = 0;
	printf("unsigned char\n\n");
	printf("%s%u", calc_min, unsigned_char);
	--unsigned_char;
	printf("%s%u\n", max, unsigned_char);
	printf("%s%u%s%u\n\n", lim_min, 0, max, UCHAR_MAX);
	
	//--------------------------------------------------------------------------------------------

	signed short signed_short = 2;
	while (signed_short > 0) signed_short *= 2;
	printf("signed short\n\n");
	printf("%s%d", calc_min, signed_short);
	--signed_short;
	printf("%s%d\n", max, signed_short);
	printf("%s%d%s%d\n\n", lim_min, SHRT_MIN, max, SHRT_MAX);

	unsigned short unsigned_short = 0;
	printf("unsigned short\n\n");
	printf("%s%u", calc_min, unsigned_short);
	--unsigned_short;
	printf("%s%u\n",max, unsigned_short);
	printf("%s%u%s%u\n\n", lim_min, 0, max, USHRT_MAX);

	//--------------------------------------------------------------------------------------------

	signed int signed_int = 2;
	while (signed_int > 0) signed_int *= 2;
	printf("signed int\n\n");
	printf("%s%d", calc_min, signed_int);
	--signed_int;
	printf("%s%d\n", max, signed_int);
	printf("%s%d%s%d\n\n", lim_min, INT_MIN, max, INT_MAX);

	unsigned int unsigned_int = 0;
	printf("unsigned int\n\n");
	printf("%s%u", calc_min, unsigned_int);
	--unsigned_int;
	printf("%s%u\n", max, unsigned_int);
	printf("%s%u%s%u\n\n", lim_min, 0, max, UINT_MAX);

	//--------------------------------------------------------------------------------------------

	signed long signed_long = 2;
	while (signed_long > 0) signed_long *= 2;
	printf("signed long\n\n");
	printf("%s%ld", calc_min, signed_long);
	--signed_long;
	printf("%s%ld\n", max, signed_long);
	printf("%s%ld%s%ld\n\n", lim_min, LONG_MIN, max, LONG_MAX);

	unsigned long unsigned_long = 0;
	printf("unsigned long\n\n");
	printf("%s%lu", calc_min, unsigned_long);
	--unsigned_long;
	printf("%s%lu\n", max, unsigned_long);
	printf("%s%lu%s%lu\n\n", lim_min, 0, max, ULONG_MAX);

	//--------------------------------------------------------------------------------------------

	float float_value = 0;
	printf("float\n\n");
	printf("%s ?", calc_min);
	printf("%s ?\n", max);
	printf("%s%f%s%f\n\n", lim_min, FLT_MIN, max, FLT_MAX);
	return 0;
}

