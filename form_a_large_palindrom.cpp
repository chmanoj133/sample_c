#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

struct node
{
	int num;
	struct node *next;
};

struct node *reverse_SLL(struct node* head, struct node* temp1, struct node* temp2, int *index, int *place1, int *place2, int *len)
{
	struct node *tail;

	if (head == NULL)
		return NULL;
	else
	{
		if (head->next == NULL)
			return head;

		(*index)++;
		(*len)++;

		if (head->next == temp1)
		{
			*place1 = *index;
			head->next = head->next->next;
		}

		if (head->next == temp2)
		{
			*place1 = *index;
			head->next = head->next->next;
		}


		tail = reverse_SLL(head->next, temp1, temp2, index, place1, place2, len);

		head->next->next = head;
		head->next = NULL;

		if (*len - *index - 1 == *place1)
		{
			head->next = temp1;
			temp1->next = NULL;
		}

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

void main()
{
	int arr[6] = { 1, 2, 3, 4, 5, 6 };

	struct node *head = Array_to_SLL(arr, 6);
	struct node *temp1 = head->next->next;
	struct node *temp2 = temp1->next->next;

	head = conditional_reverse(head, temp1, temp2);

	_getch();

}