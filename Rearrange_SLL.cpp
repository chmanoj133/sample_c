/*
	Geeks for Geeks : http://www.geeksforgeeks.org/rearrange-a-given-linked-list-in-place/

	Rearrange a given linked list in-place.
	Given a singly linked list L0 -> L1 -> … -> Ln-1 -> Ln. 
	Rearrange the nodes in the list so that the new formed list is : L0 -> Ln -> L1 -> Ln-1 -> L2 -> Ln-2 …

	You are required do this in-place without altering the nodes’ values.

	Examples:
	Input:  1 -> 2 -> 3 -> 4
	Output: 1 -> 4 -> 2 -> 3

	Input:  1 -> 2 -> 3 -> 4 -> 5
	Output: 1 -> 5 -> 2 -> 4 -> 3 
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

struct node *Rearrange(struct node *head);
struct node *reverse_SLL_recursive(struct node *head);
struct node *Array_to_SLL(int *arr, int len);
void print_output();
int compare(int i);

struct node
{
	int num;
	struct node *next;
};

struct test
{
	int arr[100];
	int len;
	int output[100];
}testDB[7] = {
	{ { 1, 2, 3, 4, 5, 6, 7 }, 7, { 1, 7, 2, 6, 3, 5, 4} },
	{ { 1, 2, 3, 4, 5, 6, 7, 8 }, 8, { 1, 8, 2, 7, 3, 6, 4, 5} },
	{ { 1, 2, 3 }, 3, {1, 3, 2} }
};

struct node *Rearrange(struct node *head)
{
	struct node *i = head, *j = head->next, *temp1, *temp2;

	while (j != NULL)
	{
		if (j->next != NULL)
		{
			j = j->next->next;
			i = i->next;
		}
		else
			j = j->next;
	}
	
	j = reverse_SLL_recursive(i->next);
	i->next = NULL;
	i = head;

	while (1)
	{
		temp1 = i->next;
		i->next = j;
		temp2 = j->next;
		j->next = temp1;
		i = temp1;
		j = temp2;

		if (j == NULL)
			break;
	}
	
	return head;
}

void main()
{
	print_output();
	_getch();
}

struct node *reverse_SLL_recursive(struct node *head)
{
	struct node *tail;

	if (head == NULL)
		return NULL;
	else
	{
		if (head->next == NULL)
			return head;

		tail = reverse_SLL_recursive(head->next);

		head->next->next = head;
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
	int i, count = 3;

	for (i = 0; i < count; i++)
	{
		if (compare(i) == 1)
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
	}
}

int compare(int i)		// Function comparing outputs
{
	int j, flag = 1;
	struct node *head = NULL, *temp;

	temp = Array_to_SLL(testDB[i].arr, testDB[i].len);

	head = Rearrange(temp);

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
