/*
7.Sorted a linked list which is in ascending order but two numbers are changed ,
i mean not in the usual order they need to be
Ex: 1->2->3->15->10->4->20; O/p:1-2-3-4-10-15-20
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node
{
	int num;
	struct node *next;
};

struct test {
	int arr[20];
	int len;
	int output[20];
}testDB[10] = {
/*1*/	{ { 1, 2, 3, 8, 5, 6, 7, 4, 9 }, 9, { 1, 2, 3, 4, 5, 6, 7, 8, 9 } }, 
/*2*/	{ { 0, 2, 4, 8, 6 }, 5, { 0, 2, 4, 6, 8 } },
/*3*/	{ { 1, 1, 1, 2, 1, 1, 1 }, 7, { 1, 1, 1, 1, 1, 1, 2 } }, 
/*4*/	{ { 0, 0, 0, 0 }, 4, { 0, 0, 0, 0 } }, 
/*5*/	{ { 2, 1 }, 2, { 1, 2 } }, 
/*6*/	{ { 3, 2, 4, 1 }, 4, NULL },		//NULL for more than 2 misplaced values
/*7*/	{ {3, 2, 4, 1, 5, 7, 9}, 7, NULL }
};

struct node *swap_misplaced_elements(struct node *head);
void print_output();
int compare(int i, int function);
struct node *Array_to_SLL(int *arr, int len);

struct node *swap_misplaced_elements(struct node *head)
{
	struct node *i, *j = NULL, *index_1 = head, *index_2 = head, *k = NULL, *m = NULL;
	int count = 0, temp, flag = 0;

	for (i = head; i->next != NULL; i = i->next)
	{
		if (flag == 1)
			j = head;
		if (i->num > i->next->num)
		{
			if (count == 0)
			{
				index_1 = i;
				count++;
				k = j;
			}
			else
			{
				m = i;
				index_2 = i->next;
				count++;
			}
		}
		if (flag != 0)
			j = j->next;
		flag++;
		
	}

	flag = 0;
	if (count == 1)
	{
		if (index_1->num > i->num && index_1->next->next != NULL)
		{
			k->next = index_1->next;
			i->next = index_1;
			index_1->next = NULL;
			flag = 1;
		}
		else
			index_2 = index_1->next;
	}

	if (count > 2)
		return NULL;
	if (count <= 2 && flag == 0)
	{
		temp = index_1->num;
		index_1->num = index_2->num;
		index_2->num = temp;

		if (count == 2)
		{
			if (m->num > index_2->num)
				return NULL;
		}

	}
	return head;
}

void main()
{
	print_output();
	_getch();
}

void print_output()		
{
	int i;
	for (i = 0; i < 7; i++)
	{
		if (compare(i, 1) == 1)
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
	}

}

int compare(int i, int function)		// Function comparing outputs
{
	int j, count = 2, flag = 1;
	struct node *head, *temp;
	temp = Array_to_SLL(testDB[i].arr, testDB[i].len);

	head = swap_misplaced_elements(temp);

	for (j = 0, temp = head; j < testDB[i].len; j++, temp = temp->next)
	{
		if (temp == NULL)
			return 1;
		else if (testDB[i].output[j] != temp->num)
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