#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int count_remainders(int N);

int main()
{
	int N, i;
	int T;
	char c;
	int *ans;
	scanf_s("%d", &T);
	ans = (int*)malloc(sizeof(int)*T);

	for (i = 0; i < T; i++)
	{
		scanf_s("%d", &N);		
		ans[i] = count_remainders(N);
	}

	for (i = 0; i < T; i++)
	{
		printf("%d\n", ans[i]);
	}

	_getch();
	return 0;
}

int count_remainders(int N)
{
	int i, count = 0;
	int temp = N;
	int k;

	while (temp != 0)
	{
		k = temp % 10;
		if (k != 0)
			if ((N % k == 0) && (k != 0))
				count++;
		temp = temp / 10;
	}
	return count;
}
