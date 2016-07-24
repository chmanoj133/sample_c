/*		1.Find median of a given linked list (Sorted Linked List)		*/	

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

float median_1(struct node *head);							// Count Method
float median_2(struct node* head);							// Two pointer Method
struct node *Array_to_linked_list(int *arr, int len);		// Array to Linked list converter
void print_output();

struct node
{
	int num;
	struct node *next;
};

struct test
{
	int a[1000];
	int len;
	float output;
}testDB[7] = {
	{ { 1, 2, 3, 4 }, 4, 2.5 },
	{ { 1, 2, 3, 4, 5 }, 5, 3 },
	{ { 1, 1, 1, 1, 2}, 5, 1 },
	{ NULL, 1, 0 },
	{ {-1, 1}, 2, 0 },
	{ { -1, -2, -3, -4, -5, -6}, 6, -3.5},
	{ { 1111111, 222222222, 333333333 }, 3, 222222222 }
};

void main()
{
	print_output();
	_getch();
}


void print_output()
{
	int i, count = 7;

	printf("Test Details -- Finding median by count Method\n\n");
	for (i = 0; i < count; i++)
	{
		if (testDB[i].output == median_1(Array_to_linked_list(testDB[i].a, testDB[i].len)))
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
	}

	printf("\n\nTest Details -- Finding median by Two pointer Method\n\n");
	for (i = 0; i < count; i++)
	{
		if (testDB[i].output == median_2(Array_to_linked_list(testDB[i].a, testDB[i].len)))
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
	}
}

float median_1(struct node *head)		// Count method
{
	int count = 0, j;
	float ans = 0.0;
	struct node *i;

	for (i = head; i != NULL; i = i->next)
		count++;

	for (i = head, j = 1; i != NULL; i = i->next, j++)
	{
		if (count % 2 == 0 && (j == count / 2 || j == (count/2 + 1)))
			ans = i->num + ans;
		if (count % 2 == 1 && j == (count / 2) + 1)
			ans = i->num;
	}

	if (count % 2 == 0)
		ans = ans / 2;

	return ans;	
}

float median_2(struct node* head)		// Two Pointers method
{
	float ans = 0;
	struct node *i = head, *j = head;
	
	if (i == NULL)
		return NULL;
	else if (i->next == NULL)
		return i->num;
	else
	{
		while (j != NULL)
		{
			if (j->next == NULL)
			{
				ans = i->num;
				break;
			}
			else if (j->next->next == NULL)
			{
				ans = i->num + i->next->num;
				ans = ans / 2;
				break;
			}
			j = j->next->next;
			i = i->next;
		}
		return ans;
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

