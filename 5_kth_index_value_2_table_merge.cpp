#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int lcm_of(int x, int y);
int gcd_of(int x, int y);
int kth_index_of_merge(int x, int y, int k);
int merge(int x, int y, int k);
void print_output();

struct testcases
{
	int n1;
	int n2;
	int K;
	int output;
}testDB[10] = {
	{3 , 5, 6, 15},
	{0, 1, 7, 8}, 
	{0, 0, 45, 0}, 
	{25, 5, 14, 75},
	{7, 13, 52, 252},
	{1, 2, -5, 0}
};


int kth_index_of_merge(int x, int y, int k)
{
	int i, j, no_of_checkpoints, checkpoint, LCM, index_of_cp, after_cp, temp, sum = 0;
	int add;

	if (k < 0)
		return 0;

	if (x > y)
	{
		temp = x;
		x = y;
		y = temp;
	}

	if (x == 0 && y != 0)
		x = y;
	else if (x != 0 && y == 0)
		y = x;
	else if (x == 0 && y == 0)
		return 0;

	LCM = lcm_of(x, y);

	checkpoint = (LCM / x) + (LCM / y) - 1;

	no_of_checkpoints = k / checkpoint;
	after_cp = (k + 1) % checkpoint;
	index_of_cp = no_of_checkpoints*checkpoint - 1;
	add = merge(x, y, after_cp);

	if (after_cp == 0)
		sum = (no_of_checkpoints + 1)*LCM;
	else
		sum = no_of_checkpoints*LCM + add;
	return sum;
	

}

int lcm_of(int x, int y)
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
		ans = GCD*lcm_of(x, y);
	}


	return ans;
}


int gcd_of(int x, int y)
{
	int temp, flag = 1, div, diff;

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

int merge(int x, int y, int k)
{
	int count = 0, temp, i, mul_x = x, mul_y = y, mul = x;

	for (i = 0; i < k; i++)
	{
		if (mul_x < mul_y)
		{
			mul = mul_x;
			mul_x = mul_x + x;
		}
		else if (mul_x > mul_y)
		{
			mul = mul_y;
			mul_y = mul_y + y;
		}
		else
		{
			mul = mul_x;
			mul_x = mul_x + x;
			mul_y = mul_y + y;
		}

	}
	return mul;
}


void print_output()
{
	int i, count = 6;

	for (i = 0; i < count; i++)
	{
		if (kth_index_of_merge(testDB[i].n1, testDB[i].n2, testDB[i].K) == testDB[i].output)
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
	}
}





