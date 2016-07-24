#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

bool isClass_cancelled(int N, int K, int *arr);

int main()
{
	int N, K, i, j;
	int *arr, T;
	char c;
	bool *ans;
	scanf_s("%d", &T);
	ans = (bool*)malloc(sizeof(bool)*T);

	for (i = 0; i < T; i++)
	{
		scanf_s("%d %d", &N, &K);
		arr = (int*)calloc(N, sizeof(int));

		for (j = 0; j < N; j++)
		{
			arr[j] = getchar() - '0';
			c = getchar();
			if (c == '\n')
				break;
		}
		ans[i] = isClass_cancelled(N, K, arr);
	}

	for (i = 0; i < T; i++)
	{
		if (ans[i])
			printf("YES\n");
		else
			printf("NO\n");
	}

	_getch();
	return 0;
}

bool isClass_cancelled(int N, int K, int *arr)
{
	int count = 0, i;

	for (i = 0; i < N; i++)
	{
		if (arr[i] <= 0)
			count++;

		if (count == K)
			return false;
	}

	return true;
}

