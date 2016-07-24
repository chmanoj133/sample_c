/* Given a fibonacci no. Write a function to return all the binary patterns whose one values sum is given number */


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int compare_results(int i);
void print_output();
int* fibonacci_pattern(int num);


void print_output()
{
	int i;
	for (i = 0; i < 5; i++)
	{
		if (compare_results(i) == 1)
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
	}
}

int compare_results(int i)
{
	int *a = fibonacci_pattern(32);

	//	for (i = 0; )
	return 0;
}

void main()
{
	int i, j, *a;

	for (i = 1; i < 101; i++)
	{
		a = fibonacci_pattern(i);
		printf("%d -->  ", i);
		for (j = 0; a[j] == 0 || a[j] == 1; j++)
			printf("%d", a[j]);
		printf("\n");
	}
	_getch();
}

int* fibonacci_pattern(int num)
{
	int i, *fib_no, first = 0, second = 1, next, count = 0, *bit_pattern, sum = 0;

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

	bit_pattern = (int*)calloc(count, sizeof(int));


	for (i = count - 1; i >= 0; i--)
	{
		sum = sum + fib_no[i];
		if (sum < num)
			bit_pattern[i] = 1;
		else if (sum > num)
			sum = sum - fib_no[i];
		else
		{
			bit_pattern[i] = 1;
			break;
		}
	}

	for (i = count - 1; i >= 0; i--)
	{
		if (bit_pattern[i] == 1 && bit_pattern[i - 1] == 0 && bit_pattern[i - 2] == 0)
		{
			bit_pattern[i] = 0;
			bit_pattern[i - 1] = 1;
			bit_pattern[i - 2] = 1;
		}
	}

	sum = 0;
	for (i = 0; i < count; i++)
		sum = sum + (bit_pattern[i] * fib_no[i]);

	if (sum == num)
		return bit_pattern;
	else
		return NULL;
}