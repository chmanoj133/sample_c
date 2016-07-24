/*
5.Given three numbers n1,n2,and r. Merge the table of n1 and n2 and find the r th number. In merging it should eliminate duplicate values (tables consists the multiples of those numbers ,ie 3 contains 3,6,9,12..)
Ex , n1=3 ,n2=5 and r=5, The merged table is 3,5,9,10,12,15(One more 15 is removed as its duplicate ) 18,20,21,24,25........so on .
The rth num ie 5th number is 12 ,so OP is 12
Extension ,what if n3,n4 .. are also given ?
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int lcm_of_two_nums(int x, int y);
int lcm_of_arr(int *arr, int len);
int gcd_of(int x, int y);
int kth_index_of_merge(int *arr, int len, int k);
int find_index_of_lcm(int *arr, int len, int lcm);
void print_output();
int merge(int *arr, int len, int k);

struct testcases
{
	int arr[100];
	int len;
	int K;
	int output;
}testDB[10] = {
	{ { 3, 5 }, 2, 8, 20 }, 
	{ { 2}, 1, 4, 10 },
	{ {3, 4, 5}, 3, 2, 5 },
	{ { 1, 2, 3, 4, 5, 7, 8 }, 7, 15, 14}, 
	{ {3, 5, 7, 13}, 4, 15, 26 },
	{ NULL, 1, 1, 0 },
	{ {0, 0, 0}, 3, 5, 0 }
};

int kth_index_of_merge(int *arr, int len, int k)
{
	int i, j, no_of_checkpoints, checkpoint = 1, LCM, index_of_cp, after_cp, temp, sum = 0;
	int add;

	if (k < 0 || arr == NULL || len < 1)
		return 0;

	LCM = lcm_of_arr(arr, len);
	
	checkpoint = find_index_of_lcm(arr, len, LCM);
	no_of_checkpoints = k / checkpoint;
	after_cp = (k + 1) % checkpoint;
	index_of_cp = no_of_checkpoints*checkpoint - 1;
	add = merge(arr,len, after_cp);

	if (after_cp == 0)
		sum = (no_of_checkpoints + 1)*LCM;
	else
		sum = no_of_checkpoints*LCM + add;
	return sum;


}

int lcm_of_arr(int *arr, int len)
{
	int i, ans = 1, temp;

	for (i = 0; i < len; i++)
	{
		temp = gcd_of(arr[i], ans);
		if (temp != 0)
			ans = ans*arr[i] / temp;
		else
			ans = 0;
	}

	return ans;
}

int lcm_of_two_nums(int x, int y)
{
	int i, GCD, temp, ans = 1;

	GCD = gcd_of(x, y);
	if (GCD == 1)
		return ans*x*y;
	else if (GCD == 0)
		return 0;
	else
	{
		x = x / GCD;
		y = y / GCD;
		ans = GCD*lcm_of_two_nums(x, y);
	}

	return ans;
}


int gcd_of(int x, int y)
{
	int temp, flag = 1, div, diff;

	if (x == 0 || y == 0)
		return 0;
	while (flag)
	{
		if (x == 0)
		{
			return 0;
			break;
		}
		div = y / x;
		diff = y - (x*div);
		if (diff == 0)
		{
			flag = 0;
			return x;
		}
		y = x;
		x = diff;
	}

}

void main()
{
	print_output();
	_getch();
}


int find_index_of_lcm(int *arr, int len, int lcm)
{
	int count = 0, ans = 0, i, j, *table_arr = (int*)malloc((sizeof(int)*len));

	if (lcm == 0)
		return 1;
	for (i = 0; i < len; i++)
		table_arr[i] = arr[i];

	for (i = 0; ans != lcm; i++)
	{
		ans = table_arr[0];

		for (j = 0; j < len; j++)
		{
			if (table_arr[j] < ans)
				ans = table_arr[j];
		}

		for (j = 0; j < len; j++)
		{
			if (table_arr[j] == ans)
				table_arr[j] = table_arr[j] + arr[j];
		}

	}
	return i;
}
int merge(int *arr, int len, int k)
{
	int count = 0, ans = 0, i, j, *table_arr = (int*)malloc((sizeof(int)*len));

	for (i = 0; i < len; i++)
		table_arr[i] = arr[i];

	for (i = 0; i < k; i++)
	{
		ans = table_arr[0];
		for (j = 0; j < len; j++)
		{
			if (table_arr[j] < ans)
			{
				ans = table_arr[j];
			}
		}

		for (j = 0; j < len; j++)
		{
			if (table_arr[j] == ans)
				table_arr[j] = table_arr[j] + arr[j];
		}

	}
	return ans;
}

void print_output()
{
	int i, count = 7;

	for (i = 0; i < count; i++)
	{
		if (testDB[i].output == kth_index_of_merge(testDB[i].arr, testDB[i].len, testDB[i].K))
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
	}
}