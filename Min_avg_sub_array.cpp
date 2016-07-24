/*
	Link :	http://www.geeksforgeeks.org/find-subarray-least-average/
	
	Find the subarray with least average
	Given an array arr[] of size n and integer k such that k <= n.

	Input:  arr[] = {3, 7, 90, 20, 10, 50, 40}, k = 3
	Output: Subarray between indexes 3 and 5
	The subarray {20, 10, 50} has the least average 
	among all subarrays of size 3.

	Input:  arr[] = {3, 7, 5, 20, -10, 0, 12}, k = 2
	Output: Subarray between [4, 5] has minimum average
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
void sub_array_with_least_avg(int *arr, int len, int k, int *initial_index, int *final_index);
void print_output();

struct test
{
	int arr[100];
	int len;
	int k;
	int index1;
	int index2;
}testDB[10] = {
	{ { 1, 2, 3, 4, 5 }, 5, 2, 0, 1 },
	{ { 5, 4, 3, 2, 1 }, 5, 2, 3, 4 },
	{ { 3, 7, 5, 20, -10, 0, 12 }, 7, 1, 4, 4 },
	{ { 3, 7, 5, 20, -10, 0, 12 }, 7, 2, 4, 5 },
	{ { 3, 7, 5, 20, -10, 0, 12 }, 7, 0, -1, -1 },
};

void main()
{
	print_output();
	_getch();
}

void sub_array_with_least_avg(int *arr, int len, int k, int *initial_index, int *final_index)
{
	int i, j = 0, sum;
	int index1 = 0, index2 = k - 1, min_avg;

	if (k <= 0 || k > len || arr == NULL || len <= 0)
	{
		index1 = -1;
		index2 = -1;
	}
	else
	{
		for (sum = 0, i = 0; i < k; sum = sum + arr[i], i++);
		min_avg = sum;
		i = index1 = 0;
		j = index2 = k;
		while (j <= len)
		{
			if (sum < min_avg)
			{
				index1 = i;
				index2 = j;
				min_avg = sum;
			}
			if (j < len)
				sum = sum - arr[i] + arr[j];			
			i++;
			j++;
		}
	}

	*initial_index = index1;
	if (index2 < 0)
		index2++;
	*final_index = index2 - 1;
	
}


void print_output()
{
	int i, count = 5, index1, index2;

	for (i = 0; i < count; i++)
	{
		sub_array_with_least_avg(testDB[i].arr, testDB[i].len, testDB[i].k, &index1, &index2);

		if (index1 == testDB[i].index1 && index2 == testDB[i].index2)
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
	}
}
