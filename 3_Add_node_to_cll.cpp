/*  3.  Add a node to a sorted circular linked list  */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void swap(int *x, int *y);
void print_output();
int compare(int i, int function);
struct node *Array_to_CLL(int *arr, int len);

struct node *insert_node_loop_method(struct node* head, int N);								// Normal loop method
struct node *insert_node_Recursion_method(struct node *head, int N, struct node *ans);		// Recursion Method

struct node
{
	int num;
	struct node *next;
};

struct testcases
{
	int arr[100];
	int len;
	int N;
	int output[100];
	int op_len;
}testDB[10] = {
/*1*/	{ { 1, 2, 4, 5, 6 }, 5, 3, { 1, 2, 3, 4, 5, 6 }, 6 },
/*2*/	{ { 1, 2, 3, 4, 5 }, 5, 6, { 1, 2, 3, 4, 5, 6 }, 6 },
/*3*/	{ { 1, 1, 1, 1, 1 }, 5, 1, { 1, 1, 1, 1, 1, 1 }, 6 },
/*4*/	{ { 1, 1, 1, 1, 1 }, 5, -1, { -1, 1, 1, 1, 1, 1 }, 6 },
/*5*/	{ { 2, 3, 4 }, 3, 1, { 1, 2, 3, 4 }, 4 },
/*6*/	{ { 1, 2, 2, 3, 3, 3, 5, 5, 7 }, 9, 5, {1, 2, 2, 3, 3, 3, 5, 5, 5, 7}, 10 },
/*7*/	{ { 1, 2, 3 }, 3, NULL, {NULL, 1, 2, 3}, 4 },
/*8*/	{ NULL, 1, 5, { 5 }, 2 },
/*9*/	{ NULL, 1, NULL, NULL, 1 }
};

void main()
{
	print_output();
	_getch();
}

void print_output()			// Function that prints on cmd
{
	int i, count = 9, function_select = 1;

	printf(" --- Test Results for Normal loop Method ---\n\n");
	for (i = 0; i < count; i++)
	{
		if (compare(i, function_select) == 1)
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
		if (i == count - 1 && function_select == 1)
		{
			printf("\n\n --- Test Results for Recursion Method ---\n\n");
			function_select = 2;
			i = -1;
		}
	}
}

int compare(int i, int function)		// Function comparing outputs
{
	int j, count = 2, flag = 1;
	struct node *head, *temp;
	temp = Array_to_CLL(testDB[i].arr, testDB[i].len);

	if (function == 1)
		head = insert_node_loop_method(temp, testDB[i].N);
	else
		head = insert_node_Recursion_method(temp, testDB[i].N, temp);

	for (j = 0, temp = head; j < testDB[i].op_len; j++, temp = temp->next)
	{
		if (testDB[i].output[j] != temp->num)
		{
			flag = 0;
			break;
		}
	}
	return flag;
}


struct node *insert_node_loop_method(struct node* head, int N)
{
	struct node *i = head, *j = (struct node*)malloc(sizeof(struct node)), *temp1, *ans = head;
	int flag = 0;

	j->num = N;
	j->next = NULL;
	if (head == NULL)
		return j;
	else
	{
		while (1)
		{
			if (i->num >= N || (&i->num == &head->num && flag == 1))
			{
				swap(&i->num, &j->num);
				temp1 = i->next;
				i->next = j;
				j->next = temp1;
				if ((&i->num == &head->num) && flag == 1)
					ans = j;
				break;
			}
			i = i->next;
			flag = 1;
		}
		return ans;
	}
}

struct node *insert_node_Recursion_method(struct node *head, int N, struct node *ans)
{
	struct node *i = head, *temp, *add = NULL;

	if (ans == NULL)
		return add;
	else
	{
		if (i->next->num < N && &i->next->num != &ans->num)
			i = insert_node_Recursion_method(i->next, N, ans);
		else
		{
			add = (struct node*)malloc(sizeof(struct node));
			add->num = N;
			add->next = NULL;
			if (ans->num >= N)
				swap(&ans->num, &add->num);
			temp = i->next;
			i->next = add;
			add->next = temp;
		}

		return ans;
	}
}

void swap(int *x, int *y)
{
	int temp;

	temp = *x;
	*x = *y;
	*y = temp;	
}

struct node *Array_to_CLL(int *arr, int len)
{
	int j;
	struct node *temp = (struct node*)malloc(sizeof(struct node)), *head = NULL, *circle;

	if (arr == NULL || len == 0)
		return NULL;
	else
	{
		circle = temp;
		for (j = len - 1; j >= 0; j--)
		{
			temp->num = arr[j];
			head = (struct node*)malloc(sizeof(struct node));
			head->next = temp;
			temp = head;
		}

		circle->next = head->next;
		return head->next;
	}
}



