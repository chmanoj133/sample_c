/*
Geeks for Geeks:  http://www.geeksforgeeks.org/fibonacci-coding/

Fibonacci coding encodes an integer into binary number using Fibonacci Representation of the number. 
The idea is based on Zeckendorf’s Theorem which states that states that every positive Every positive integer 
can be written uniquely as a sum of distinct non-neighbouring Fibonacci numbers (0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 141, ……).

The Fibonacci code word for a particular integer is exactly the integer’s Zeckendorf representation with the order of its digits reversed 
and an additional “1” appended to the end. 
The extra 1 is appended to indicate end of code (Note that the code never contain two consecutive 1s as per Zeckendorf’s Theorem. 
The representation uses Fibonacci numbers starting from 1 (2’nd Fibonacci Number). 
So the Fibonacci Numbers used are 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 141, …….

Given a number n, print its Fibonacci code.

Examples:

Input: n = 1
Output: 11
1 is first Fibonacci number in this representation
and an extra 1 is appended at the end.

Input:  n = 11
Output: 001011
11 is sum of 8 and 3.  The last 1 represents extra 1
that is always added. A 1 before it represents 8. 
The third 1 (from beginning) represents 3.

*/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int* fibonacci_pattern(int num, int *end);

void main()
{
	int i, j, end, *arr, sum, *fib_no, first = 0, second = 1, next = 1, count = 0, flag = 1;
	int input;

	printf("Enter num: ");
	scanf_s("%d", &input);
	printf("\n\n");
	arr = fibonacci_pattern(input, &end);

	// FOR REFERENCE
	for (i = 0; next <= input; i++)
	{
		printf("   %d", next);
		
		first = second;
		second = next;
		next = first + second;
	}

	printf("\n\n");

	for (i = 0; i < end; i++)
		printf("   %d", arr[i]);
	_getch();
}


int* fibonacci_pattern(int num, int *end)
{
	int i, *fib_no, first = 0, second = 1, next = 1, count = 0, *bit_pattern, sum = 0, j = 0, k;


	if (num <= 0 || num == NULL)
		return 0;
	
	fib_no = (int*)malloc(sizeof(int));

	for (i = 0; next <= num; i++)
	{
		fib_no[i] = next;
		first = second;
		second = next;
		next = first + second;		
		count++;
		fib_no = (int*)realloc(fib_no, sizeof(int)*(count + 1));
	}

	*end = count + 1;
	bit_pattern = (int*)calloc(count + 1, sizeof(int));	
	bit_pattern[count] = 1;

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

	for (i = count - 1; i > 1; i--)
	{
		if (bit_pattern[i] == 1 && bit_pattern[i - 1] == 1)
		{
			if (bit_pattern[i - 2] == 0 && bit_pattern[i - 3] == 0)
			{
				bit_pattern[i - 1] = 0;
				bit_pattern[i - 2] = 1;
				bit_pattern[i - 3] = 1;
			}
		}
	}

	return bit_pattern;
	
}