#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int ncr_mod_p(int n, int r, int p);

void main()
{
	printf("%d", ncr_mod_p(70,6, 13));
	_getch();
}

int ncr_mod_p(int n, int r, int p)
{
	if (n == r || r == 0)
		return 1;
	return ((ncr_mod_p(n - 1, r - 1, p) % p + ncr_mod_p(n - 1, r, p) % p) % p);
}

