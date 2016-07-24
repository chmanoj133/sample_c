/* Given a fibonacci no. Write a function to return all the binary patterns whose one values sum is given number */


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int** fibonacci_pattern(int num, int *m, int *n);
void print_output();
int compare_outputs(int x);

struct test
{
	int input;
}testDB[5] = {5 , 34, 128, 1025, 1111};


void main()
{
	print_output();
	int first = 0, second = 1, next, num = 128, *fib_no, count = 0, i, **a, end1, end2, j, n;

	fib_no = (int*)malloc(sizeof(int));

	printf("Enter num: ");
	scanf_s("%d", &n);
	printf("\n\n\n");
	for (i = 0; second <= n; i++)
	{
		printf("   %d", second);
		fib_no[i] = second;
		next = first + second;
		first = second;
		second = next;
		count++;
		fib_no = (int*)realloc(fib_no, sizeof(int)*(count + 1));

	}

	a = fibonacci_pattern(n, &end1, &end2);
	printf("\n\n");
	for (i = 0; i < end1; i++)
	{
		for (j = 0; j < end2; j++)
		{
			printf("   %d", a[i][j]);
		}
		printf("\n\n");
	}

	_getch();
}

void print_output()
{
	int i;

	for (i = 0; i < 5; i++)
	{
		if (compare_outputs(i) == 1)
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
	}
}

int compare_outputs(int x)
{
	int i, j, end1, end2, **arr, sum, *fib_no, first = 0, second = 1, next, count = 0, flag = 1;

	arr = fibonacci_pattern(testDB[x].input, &end1, &end2);

	fib_no = (int*)malloc(sizeof(int));

	for (i = 0; second <= testDB[x].input; i++)
	{
		fib_no[i] = second;
		next = first + second;
		first = second;
		second = next;
		count++;
		fib_no = (int*)realloc(fib_no, sizeof(int)*(count + 1));

	}

	for (i = 0; i < end1; i++)
	{
		sum = 0;
		for (j = 0; j < end2; j++)
			sum = sum + (arr[i][j] * fib_no[j]);
		if (sum != testDB[x].input)
		{
			flag = 0;
			break;
		}
	}

	return flag;
}


int** fibonacci_pattern(int num, int *m, int *n)
{
	int i, *fib_no, first = 0, second = 1, next, count = 0, **bit_pattern, sum = 0, j = 0, k;

	
	if (num <= 0 || num == NULL)
		return 0;
	else
	{
		fib_no = (int*)malloc(sizeof(int));

		for (i = 0; second <= num; i++)
		{
			fib_no[i] = second;
			next = first + second;
			first = second;
			second = next;
			count++;
			fib_no = (int*)realloc(fib_no, sizeof(int)*(count + 1));

		}

		*n = count;
		bit_pattern = (int**)calloc(1, sizeof(int*));
		bit_pattern[0] = (int*)calloc(count, sizeof(int));

		for (i = count - 1; i >= 0; i--)
		{
			sum = sum + fib_no[i];
			if (sum < num)
				bit_pattern[0][i] = 1;
			else if (sum > num)
				sum = sum - fib_no[i];
			else
			{
				bit_pattern[0][i] = 1;
				break;
			}
		}

		for (i = count - 1; i >= 0; i--)
		{
			if (bit_pattern[j][i] == 1 && bit_pattern[j][i - 1] == 0 && bit_pattern[j][i - 2] == 0)
			{
				j++;
				bit_pattern = (int**)realloc(bit_pattern, sizeof(int)*(j + 1));
				bit_pattern[j] = (int*)calloc(count, sizeof(int));

				for (k = 0; k < count; k++)
					bit_pattern[j][k] = bit_pattern[j - 1][k];

				bit_pattern[j][i] = 0;
				bit_pattern[j][i - 1] = 1;
				bit_pattern[j][i - 2] = 1;
			}
		}

		if (bit_pattern[j][0] == 0 && bit_pattern[j][1] == 1)
		{
			j++;
			bit_pattern = (int**)realloc(bit_pattern, sizeof(int)*(j + 1));
			bit_pattern[j] = (int*)calloc(count, sizeof(int));

			for (k = 0; k < count; k++){
				bit_pattern[j][k] = bit_pattern[j - 1][k];
			}
			bit_pattern[j][0] = 1;
			bit_pattern[j][1] = 0;
		}

		*m = j + 1;
		return bit_pattern;
	}
}