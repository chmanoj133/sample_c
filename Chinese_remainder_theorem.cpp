
/*
Link :  http://www.geeksforgeeks.org/chinese-remainder-theorem-set-1-introduction/

Chinese Remainder Theorem | Set 1 (Introduction)
We are given two arrays num[0..k-1] and rem[0..k-1]. In num[0..k-1], every pair is coprime (gcd for every pair is 1). 
We need to find minimum positive number x such that:

x % num[0]    =  rem[0],
x % num[1]    =  rem[1],
.......................
x % num[k-2]  =  rem[k-1]

Examples:

Input:  num[] = {5, 7}, rem[] = {1, 3}
Output: 31
Explanation:
31 is the smallest number such that:
(1) When we divide it by 5, we get remainder 1.
(2) When we divide it by 7, we get remainder 3.

Input:  num[] = {3, 4, 5}, rem[] = {2, 3, 1}
Output: 11
Explanation:
11 is the smallest number such that:
(1) When we divide it by 3, we get remainder 2.
(2) When we divide it by 4, we get remainder 3.
(3) When we divide it by 5, we get remainder 1.
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int chinese_remainder(int *arr, int *rem, int len);
void print_output();

struct test
{
	int arr[100];
	int rem[100];
	int len;
	int output;
}testDB[5] = {
	{ { 5, 7 }, { 1, 3 }, 2, 31 },
	{ { 3, 4, 5 }, { 2, 3, 1 }, 3, 11 },
	{ { 3, 4, 5, 7 }, { 2, 3, 1, 5 }, 4, 131 },
	{ { 3, 4, 5, 7 }, { 2, 3, 1, 6 }, 4, 251 },
	{ { 5 }, { 1 }, 1, 1 }
};

void main()
{
	print_output();
	_getch();
}

int chinese_remainder(int *arr, int *rem, int len)
{
	int i, j, index, max = 0, ans = 0;
	
	if (arr == NULL || rem == NULL || len <= 0)
		return -1;

	// Finding the maximum no. in arr
	for (i = 0; i < len; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			index = i;
		}
	}
	ans = rem[index];
	// the answer must be max*k + rem[index]
	// where k = 0,1,2....
	while (1)
	{
		for (j = 0; j < len; j++)
			if (ans % arr[j] != rem[j])
				break;

		if (j == len)
			return ans;

		ans += max;
	}
}

void print_output()
{
	int i, count = 5;

	for (i = 0; i < count; i++)
	{
		if (testDB[i].output == chinese_remainder(testDB[i].arr, testDB[i].rem, testDB[i].len))
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
	}
}
