/*
	Geeks for Geeks: http://www.geeksforgeeks.org/find-the-smallest-twin-numbers-in-given-range/

	Find the smallest twins in given range
	Given a range [low..high], print the smallest twin numbers in given range (low and high inclusive). 
	Two numbers are twins if they are primes and there difference is 2.

	Input:  low = 10,  high = 100
	Output: Smallest twins in given range: (11, 13)
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void smallest_twins(int min, int max, int *twin1, int *twin2);
int isPrime(int N);

void smallest_twins(int min, int max, int *twin1, int *twin2)
{
	int i, j;

	if (min % 2 == 0)
		min = min + 1;

	for (i = min, j = min + 2; j <= max; i = i + 2, j = j + 2)
	{
		if (isPrime(i) == 1 && isPrime(j) == 1)
		{
			*twin1 = i;
			*twin2 = j;
			break;
		}
	}
}

void main()
{
	int min, max, twin1 = 0, twin2 = 0;

	printf("Enter min, max:\n");
	scanf_s("%d%d", &min, &max);
	smallest_twins(min, max, &twin1, &twin2);
	printf("%d\t%d", twin1, twin2);
	_getch();
}

int isPrime(int N)
{
	int i, flag = 1;

	for (i = 2; i <= N / 2; i++)
	{
		if (N % i == 0)
		{
			flag = 0;
			break;
		}
	}

	return flag;
}