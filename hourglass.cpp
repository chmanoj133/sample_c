#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include "manoj.h"

void main()
{
	int arr[6][6], ans[16] ;
	int i, j, sum = 0, k = 0;
	int max = 0;
	char c;

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			scanf_s("%d\t", &arr[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			ans[k] = arr[i][j] + arr[i][j + 1] + arr[i][j + 2] + arr[i + 1][j + 1] + arr[i + 2][j] + arr[i + 2][j + 1] + arr[i + 2][j + 2];
			k++;
		}
	}

	for (i = 0; i < 16; i++)
	{
		if (max < ans[i])
			max = ans[i];
	}

	printf("%d", max);

	_getch();
}