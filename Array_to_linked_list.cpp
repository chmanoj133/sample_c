#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node *Array_to_linked_list(int *arr, int len);

struct node
{
	int num;
	struct node *next;
};

void main()
{
	struct node *a, *j;
	int *ar = (int*)malloc(sizeof(int) * 5), i;
	
	for (i = 0; i < 4; i++)
		ar[i] = i + 1;

	a = Array_to_linked_list(ar, 4);
	for (j = a, i = 0; i < 8; j = j->next, i++)
		printf("%d  ", j->num);
	_getch();
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

