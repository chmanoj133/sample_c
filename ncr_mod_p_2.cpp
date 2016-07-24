
// Geeks for Geeks link: http://www.geeksforgeeks.org/compute-ncr-p-set-1-introduction-and-dynamic-programming-solution/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int ncr_mod_p(int n, int r, int p);
int min(int a, int b);

void main()
{
	int a = ncr_mod_p(1000, 900, 13);
	_getch();
}

int ncr_mod_p(int n, int r, int p)
{
	int i, j, temp;
	int *c = (int*)calloc(r + 1, sizeof(int));

	c[0] = 1;
	for (i = 1; i <= n; i++)
		for (j = min(i,r); j > 0; j--)
			c[j] = (c[j - 1] + c[j]) % p;

	return c[r];
}

int min(int a, int b)
{
	if (a > b)
		return b;
	else
		return a;
}