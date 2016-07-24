/*
9 . Largest Contiguous Sum Array .
Ex : 1,2,3,-5,-10,20,40 O/P : 20,40 Sum : 60
Ex: 1 2 3 4 5 -2 -3 -4 -20 10 2 O/:P:1 2 3 4 5 Sum:15
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int *Contigious_Sub_Array(int *arr, int len);
void print_output();
int compare(int i);

struct testcases
{
	int input[100];
	int len;
	int output[100];
	int op_len;
}testDB[10] = {
	{ { 1, -2, 4, 7, 6, -5, -13, 1, 8, 14 }, 10, { 1, 8 , 14} , 3},
	{ { 1, 2, 3, 4, 5 }, 5, { 1, 2, 3, 4, 5}, 5 },
	{ { 1, 2, -3, 5, -10, 20, 40 }, 7, {20, 40}, 2 }, 
	{ { 1, 2, 3, 4, 5, -2, -3, -4, -20, 10, 2 }, 11, { 1, 2, 3, 4, 5} , 5},
	{ { -1, -2, -3, 2, -5 }, 5, { 2 }, 1 }
};

void main()
{
	print_output();
	_getch();
}

int *Contigious_Sub_Array(int *arr, int len)
{
	int i = 0, j = 0, sum = 0, max = 0, index1, index2, flag = 0, size;
	int *ans;

	while (1)
	{
		sum = sum + arr[j];

		if (sum > max)
		{
			index1 = i;
			index2 = j;
			max = sum;
		}
		
		if (j < len)
		{
			if (j == len - 1)
			{
				j = i + 1;
				i++;
				sum = 0;
			}
			else
				j++;
		}
		if (i == len - 1 && j == len - 1)
			break;
	}

	size = index2 - index1 + 1;
	ans = (int*)malloc(sizeof(int)*size);
	
	for (i = 0, j = index1; i < size; i++, j++)
		ans[i] = arr[j];

	return ans;
}

int compare(int i)		// Function comparing outputs
{
	int j, flag = 1;
	int *a = Contigious_Sub_Array(testDB[i].input, testDB[i].len);


	for (j = 0; j < testDB[i].op_len; j++)
	{
		if (testDB[i].output[j] != a[j])
		{
			flag = 0;
			break;
		}
	}
	return flag;
}

void print_output()			
{
	int i, count = 5;

	for (i = 0; i < count; i++)
	{
		if (compare(i) == 1)
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
	}
}
