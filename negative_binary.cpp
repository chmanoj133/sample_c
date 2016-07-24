#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int* negative_binary(int num, int *length);
void print_output();
int compare_outputs(int x);

void main()
{
	print_output();
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

}

int* negative_binary(int num, int *length)
{
	int i, j, quotient, remainder, *ans = (int*)malloc(sizeof(int));


	quotient = num;
	for (i = 0; quotient != 0; i++)
	{
		remainder = quotient % (-2);
		quotient = quotient / (-2);
		if (remainder == -1)
		{
			remainder = 1;
			quotient = quotient + 1;
		}
		ans[i] = remainder;
		ans = (int*)realloc(ans, sizeof(int)*(i + 2));
	}

	*length = i;

	for (i = 0, j = *length - 1; i < j; i++, j--)
	{
		quotient = ans[i];
		ans[i] = ans[j];
		ans[j] = quotient;
	}

	if (num == 0)
	{
		ans[0] = 0;
		*length = 1;
	}

	return ans;
}

	
