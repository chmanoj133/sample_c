/*
	Geeks for Geeks : http://www.geeksforgeeks.org/print-a-pattern-without-using-any-loop/

	Question :	Given a number n, print following pattern without using any loop.

				Input: n = 16
				Output: 16, 11, 6, 1, -4, 1, 6, 11, 16

				Input: n = 10
				Output: 10, 5, 0, 5, 10
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void print_pattern(int N, int diff, int present)
{
	printf("%d  ", present);
	if (diff > 0)
	{
		if (present <= N && present > 0)
			print_pattern(N, diff, present - diff);
		if (present + diff <= N)
			printf("%d  ", present + diff);
	}
}

void main()
{
	int N, diff;

	printf("Enter the starting No. : ");
	scanf_s("%d", &N);
	printf("Enter the difference value :");
	scanf_s("%d", &diff);
	print_pattern(N, diff, N);
	_getch();
}