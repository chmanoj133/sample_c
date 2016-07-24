#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

bool is_palindrome(int *arr, int start, int end)
{
	int i, j;
	bool ans;

	for (i = start, j = end; i < j; i++, j--)
	{
		if (arr[i] != arr[j])
			return false;
	}
	return true;
}


int palindrome_number(int N)
{
	int *arr, len = 1;
	int rem, i = 0, j;
	int first, last, end;

	while (N != 0)
	{
		arr = (int*)realloc(arr, sizeof(int)*len);
		len++;
		arr[i] = N % 10;
		N = N / 10;
		i++;
	}

	j = i - 1;
	i = 0;

	first = i;
	last = j;
	end = j;

	while (i < j)
	{
		while (arr[first] != arr[last])
		{
			last--;
		}
		if (is_palindrome(arr, first, last))
			break;

		first++;
		last = end;
	}

	N = 0;

	for (i = first; i <= last; i++)
	{
		N = arr[i] + N * 10;
	}

	return N;
}

void main()
{

}

