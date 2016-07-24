#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
bool isPrime(int N);
int sqrt(int N);

void main()
{
	if (isPrime(57))
		printf("True\t");
	else
		printf("False\t");	
	_getch();
}

bool isPrime(int N)
{
	int i;

	if (N <= 1)
		return false;
	if (N <= 3)
		return true;
	
	for (i = 5; i <= sqrt(N); i = i + 6)
	{
		if (N % i == 0 || N % (i + 2) == 0)
			return false;
	}

	return true;
}

int sqrt(int N)
{
	int k;

	for (k = 0; k*k <= N; k++);
	k--;

	return k;
}