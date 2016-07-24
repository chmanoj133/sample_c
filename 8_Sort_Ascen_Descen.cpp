/*
8.Given a linked list which is in pattern like combination of ascending and descending. Sort it.
(First all ascending numbers occur ,next all descending nums )
Note : min of descending part is greater than max of ascending
Ex: Input 1->2->7->20->15->10
Output 1->2->7->10->15->20
*/

/* ---- Here output doesnt come if input contains duplicates ------*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node
{
	int num;
	struct node *next;
};

struct test

{
	int arr[100];
	int output[100];
	int len;
}testDB[9] = {
	{ { 1, 2, 3, 4, 9, 8, 6, 10, 11, 12, 16, 15, 14, 13 }, { 1, 2, 3, 4, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16 }, 14 },
	{ { 1, 2, 3, 4, 9, 8, 7, 6, 5 }, { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, 9 },
	{ { 1, 3, 2 }, { 1, 2, 3}, 3 },
	{ { 1, 6, 5, 7 }, {1, 5, 6, 7}, 4},
	{ { 1, 2, 3, 4, 5 }, {1, 2, 3, 4, 5}, 5 }, 
	{ { 1 }, {1}, 1 },
	{ NULL, NULL, 1}
};


struct node *reverse_SLL(struct node *head, struct node **nul_previous);
struct node *sort(struct node *head);
struct node *Array_to_SLL(int *arr, int len);
void print_output();
int compare(int i, int function);


void main()
{
	print_output();
	_getch();
}

struct node *sort(struct node *head)
{
	struct node *i = head, *j = head,*temp, *index_1 = NULL, *index_2 = NULL, *index1_previous = NULL, *index2_previous = NULL;
	int flag = 0, flag2 = 0, just_action = 0, check = 0;

	while (i != NULL)
	{
		if (flag == 1)
			j = head;
		if (i->next != NULL)
		{
			if (i->num > i->next->num && flag2 == 0)
			{
				index1_previous = j;
				index_1 = i;
				flag2 = 1;
			}
		}
		if ((flag2 && i->num > index_1->num && j->num > index1_previous->num) || (i->next == NULL) && flag2)
		{
			index_2 = i;
			index2_previous = j;

			if (i->next == NULL && i->num <= j->num)
			{
				index_2 = NULL;
				index2_previous = i;
				i = i->next;
				check = 1;
			}
			if (check != 1)
				if (i->next == NULL && i->num > j->num)
				{
					i = i->next;
					check = 0;
				}
			index2_previous->next = NULL;
			index_1 = reverse_SLL(index_1, &temp);
			
			index1_previous->next = index_1;
			temp->next = index_2;
			flag2 = 0;
			just_action = 1;
			j = temp;
		}
		
		if (just_action != 1)
		{
			i = i->next;
			j = j->next;
			flag++;			
		}
		just_action = 0;
	}
	return head;
}



struct node *reverse_SLL(struct node *head, struct node **nul_previous)
{
	struct node *tail;

	if (head == NULL)
		return NULL;
	else
	{
		if (head->next == NULL)
			return head;

		tail = reverse_SLL(head->next, nul_previous);
		head->next->next = head;
		*nul_previous = head;
		head->next = NULL;
		return tail;
	}
}

struct node *Array_to_SLL(int *arr, int len)
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

void print_output()			// Function that prints on cmd
{
	int i, count = 7, function_select = 1;

	for (i = 0; i < count; i++)
	{
		if (compare(i, function_select) == 1)
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);		
	}
}

int compare(int i, int function)		// Function comparing outputs
{
	int j, flag = 1;
	struct node *head = NULL, *temp;
	
	temp = Array_to_SLL(testDB[i].arr, testDB[i].len);
	
	head = sort(temp);

	for (j = 0, temp = head; j < testDB[i].len; j++, temp = temp->next)
	{
		if (testDB[i].output[j] != temp->num)
		{
			flag = 0;
			break;
		}
	}
	return flag;
}
