/*  4.  Reverse given linked list using recursion (two approaches)  */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void print_output();
int compare(int i, int function);
struct node *Array_to_SLL(int *arr, int len);
struct node *reverse_SLL_tail_recursive(struct node* head, struct node*last);
struct node *reverse_SLL_recursive(struct node* head);

struct node
{
	int num;
	struct node *next;
};


struct testcases
{
	int input[100];
	int output[100];
	int len;
}testDB[10] = {
	{ { 1, 2, 3, 4, 5, 6 }, { 6, 5, 4, 3, 2, 1 }, 6 },
	{ { 1, 1, 1, 1, 1, 2 }, { 2, 1, 1, 1, 1, 1 }, 6 },
	{ { 1 }, { 1 }, 1 },
	{ { 1, 2 }, {2, 1}, 2 },
	{ NULL, NULL, 1 }, 
};

void main()
{
	print_output();
	_getch();
}

struct node *reverse_SLL_tail_recursive(struct node* head, struct node *last)
{
	struct node *temp;

	if (head == NULL && last == NULL)
		return NULL;
	else
	{
		if (last != NULL)
		{
			if (&head->num == &last->num)
			{
				last = head->next;
				head->next = NULL;
			}
			if (last == NULL)
				return head;
			else 
			{
				temp = last->next;
				last->next = head;
				head = last;
				last = temp;
				head = reverse_SLL_tail_recursive(head, last);
			}
		}
		return head;
	}
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



void print_output()			// Function that prints on cmd
{
	int i, count = 5, function_select = 1;

	printf(" ---- Test cases for reverse SLL tail recursive function ----\n\n");
	for (i = 0; i < count; i++)
	{
		if (compare(i, function_select) == 1)
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
		if (i == count - 1 && function_select == 1)
		{
			i = -1;
			function_select = 2;
			printf("\n\n ---- Test cases for reverse SLL general recursion function ----\n\n");
		}
	}
}

int compare(int i, int function)		// Function comparing outputs
{
	int j, count = 2, flag = 1;
	struct node *head, *temp;
	temp = Array_to_SLL(testDB[i].input, testDB[i].len);

	if (function == 1)
		head = reverse_SLL_tail_recursive(temp, temp);
	else
		head = reverse_SLL_recursive(temp);

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



