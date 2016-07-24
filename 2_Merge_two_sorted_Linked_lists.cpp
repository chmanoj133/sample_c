/*   2.Merge two linked list which are in sorted order   */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node *merge(struct node *head1, struct node *head2);
struct node *Array_to_linked_list(int *arr, int len);
void print_output();
int compare(int i);

struct node{
	int num;
	struct node *next;
};

struct test
{
	int input1[100];
	int len1;
	int input2[100];
	int len2;
	int output[200];
	int len3;
}testDB[8] = {
/*1*/	{ { 1, 3, 5 }, 3, { 2, 4, 6 }, 3, { 1, 2, 3, 4, 5, 6 }, 6 },

/*2*/	{ { 1, 2, 3 }, 3, { 4, 5, 6, 7, 8 }, 5, { 1, 2, 3, 4, 5, 6, 7, 8 }, 8 },

/*3*/	{ { 4, 5, 6 }, 3, { 1, 2, 3 }, 3, { 1, 2, 3, 4, 5, 6 }, 6 },

/*4*/	{ { 2, 4, 6 }, 3, { 1, 7, 9 }, 3, { 1, 2, 4, 6, 7, 9 }, 6 },

/*5*/	{ { 1, 1, 1, 1, 1 }, 5, { 1, 1, 1 }, 3, { 1, 1, 1, 1, 1, 1, 1, 1 }, 8 },

/*6*/	{ NULL, 1, { 1 }, 1, { 1 }, 1 },

/*7*/	{ { 1 }, 1, NULL, 1, { 1 }, 1 },

/*8*/	{ NULL, 1, NULL, 1, NULL, 1 }
};

void main()
{
	print_output();
	_getch();
}

void print_output()
{
	int i, count = 8;

	for (i = 0; i < count; i++)
	{
		if (compare(i) == 1)
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
	}
}

int compare(int i)
{
	int j, count = 2, flag = 1;
	struct node *head, *temp;

	head = merge(Array_to_linked_list(testDB[i].input1, testDB[i].len1), Array_to_linked_list(testDB[i].input2, testDB[i].len2));

	for (j = 0, temp = head; j < testDB[i].len3; j++, temp = temp->next)
	{
		if (testDB[i].output[j] != temp->num)
		{
			flag = 0;
			break;
		}
	}
	return flag;
}

struct node *merge(struct node *head1, struct node *head2)
{
	struct node *i = head1, *j = head2, *temp, *first, *temp2;

	if (i == NULL)
		return j;
	else if (j == NULL)
		return i;
	else
	{
		if (i->num > j->num)
		{
			first = j;
			j = i;
			i = first;
		}

		else
			first = i;

		while (1)
		{
			if (i->next->num > j->num)
			{
				temp = i->next;
				i->next = j;
				temp2 = j->next;
				j->next = temp;
				i = j;
				j = temp2;
			}
			else
				i = i->next;

			if (i->next == NULL)
			{
				i->next = j;
				break;
			}

			if (j == NULL)
				break;
		}

		return first;
	}
}

struct node *Array_to_linked_list(int *arr, int len)
{
	int j;
	struct node *temp = (struct node*)malloc(sizeof(struct node)), *head = NULL;

	if (arr == NULL || len == 0)
		return NULL;
	else
	{
		temp->next = NULL;
		for (j = len - 1; j >= 0; j--)
		{
			temp->num = arr[j];
			head = (struct node*)malloc(sizeof(struct node));
			head->next = temp;
			temp = head;
		}
		return head->next;
	}
}
