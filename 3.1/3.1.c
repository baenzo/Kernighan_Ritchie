#include <stdio.h>

int binsearch(int x, int v[], int n);

int main()
{
	int a[10000];

	for (int i = 0; i < 10000; i++)
	{
		a[i] = i;
	}

	int idx = binsearch(2, a, 10000);

	printf("%d", idx);

	return 0;
}

int binsearch(int x, int v[], int n)
{
	int begin = 0;
	int end = n;
	int mid;

	while (begin < end)
	{
		mid = begin + (end - begin) / 2;

		if (x <= v[mid])
			end = mid;
		else
			begin = mid + 1;
	}

	if (end < n && v[end] == x) return end;

	return -1;
}