/*	Given a fibonacci no. Write a function to return all possible binary patterns such that when one occurs,
	corresponding fib no. sum is given number */

// Pattern starts from 1, 1, 2, 3, 5, 8....

// example
//input : 12
//fib no:	1	1	2	3	5	8
//patterns:	0	1	0	1	0	1
//2nd pat.	1	0	1	1	0	1


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int** fibonacci_pattern(int num, int *m, int *n);


void main()
{
	int i, j, end1, end2, **arr, sum, *fib_no, first = 0, second = 1, next, count = 0, flag = 1;
	int input;

	printf("Enter num: ");
	scanf_s("%d", &input);
	printf("\n\n");
	arr = fibonacci_pattern(input, &end1, &end2);

	fib_no = (int*)malloc(sizeof(int));

	for (i = 0; second <= input; i++)
	{
		printf("   %d", second);
		fib_no[i] = second;
		next = first + second;
		first = second;
		second = next;
		count++;
		fib_no = (int*)realloc(fib_no, sizeof(int)*(count + 1));
	}
	printf("\n\n");

	for (i = 0; i < end1; i++)
	{
		for (j = 0; j < end2; j++)
			printf("   %d", arr[i][j]);
		printf("\n\n");
	}
	_getch();
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
		for (i = 0; i <= j; i++)
		{
			if (bit_pattern[i][0] == 0 && bit_pattern[i][1] == 1)
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
		}

		*m = j + 1;
		return bit_pattern;
	}
}