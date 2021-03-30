#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
	/*char
	short
	int
	long*/

	signed char signed_char = 2;
	while (signed_char > 0) signed_char *= 2;
	printf("signed char\n\n");
	printf("  Calculated: min: %d   ", signed_char);
	--signed_char;
	printf("max: %d\n", signed_char);
	printf("  <limits.h>: min: %d   max: %d\n\n", SCHAR_MIN, SCHAR_MAX);

	unsigned char unsigned_char = 0;
	printf("unsigned char\n\n");
	printf("  Calculated: min: %u   ", unsigned_char);
	--unsigned_char;
	printf("max: %u\n", unsigned_char);
	printf("  <limits.h>: min: %u   max: %u\n\n", 0, UCHAR_MAX);
	
	//--------------------------------------------------------------------------------------------

	signed short signed_short = 2;
	while (signed_short > 0) signed_short *= 2;
	printf("signed short\n");
	printf("\tmin: %d\n", signed_short);
	--signed_short;
	printf("\tmax:  %d\n", signed_short);

	unsigned short unsigned_short = 0;
	printf("unsigned short\n");
	printf("\tmin: %u\n", unsigned_short);
	--unsigned_short;
	printf("\tmax: %u\n", unsigned_short);
	//--------------------------------------------------------

	signed int signed_int = 2;
	while (signed_int > 0) signed_int *= 2;
	printf("signed int\n");
	printf("\tmin: %d\n", signed_int);
	--signed_int;
	printf("\tmax:  %d\n", signed_int);

	unsigned int unsigned_int = 0;
	printf("unsigned int\n");
	printf("\tmin: %u\n", unsigned_int);
	--unsigned_int;
	printf("\tmax: %u\n", unsigned_int);

	//--------------------------------------------------------

	signed long signed_long = 2;
	while (signed_long > 0) signed_long *= 2;
	printf("signed long\n");
	printf("\tmin: %ld\n", signed_long);
	--signed_long;
	printf("\tmax:  %ld\n", signed_long);

	unsigned long unsigned_long = 0;
	printf("unsigned long\n");
	printf("\tmin: %lu\n", unsigned_long);
	--unsigned_long;
	printf("\tmax: %lu\n", unsigned_long);

	//--------------------------------------------------------

	float float_value = 0;
	printf("float\n");
	printf("\tmin: %f\n", FLT_MIN);
	--float_value;
	printf("\tmax: %f\n", FLT_MAX);

	return 0;
}

