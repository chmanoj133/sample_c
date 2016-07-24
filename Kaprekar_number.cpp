#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include "manoj.h"

bool isKaprekar_num(int N);

void main()
{
	int i;

	for (i = 1; i < 10000000; i++)
	{
		if (isKaprekar_num(i))
			printf("%d --> %d\n", i, i*i);

	}
	_getch(); 
}

bool isKaprekar_num(int N)
{
	int len = 0;
	int sq = N*N, temp;

	temp = sq;

	for (len = 0; temp != 0; len++, temp = temp / 10);

	if (len % 2 != 0)
		return false;

	else if (len / 2 != 0)
	{
		if (sq / exp(10, len / 2) + sq % exp(10, len / 2) == N)
			return true;
		else
			return false;
	}
	else
		return false;
}