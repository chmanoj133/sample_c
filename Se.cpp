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