
// 11. Find the loop in SLL

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node
{
	int num;
	struct node *next;
	int flag;
};

int find_loop_in_SLL_1(struct node* head);
int find_loop_in_SLL_2(struct node *head);
struct node *Array_to_SLL(int *arr, int len);

int find_loop_in_SLL_1(struct node* head)				// Method 1: Flag method;
{
	struct node *i;

	for (i = head; i != NULL; i = i->next)
	{
		if (i->flag == 1)
			return i->num;
		i->flag = 1;
	}
	return NULL;
}

int find_loop_in_SLL_2(struct node *head)
{
	struct node *i = head, *j = head;

	while (1)
	{
		i = i->next->next;
		j = j->next;
		if (i == j)
		{
			i = head;
			break;
		}
	}
	while (1)
	{
		if (i == j)
			return i->num;
		i = i->next;
		j = j->next;
	}
}

void main()
{
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, ans1, ans2;
	struct node *head = Array_to_SLL(arr, 10), *i;

	for (i = head; i->next != NULL; i = i->next);
	i->next = head->next->next;

	ans1 = find_loop_in_SLL_2(head);
	ans2 = find_loop_in_SLL_1(head);

	printf("%d\t%d", ans1, ans2);
	_getch();
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