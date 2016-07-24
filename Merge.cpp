#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node *merge(struct node *head1, struct node *head2);
struct node *merge2(struct node *head1, struct node *head2);
struct node * numberToLinkedList(int N);


struct node {
	int num;
	struct node *next;
};

void main()
{
	struct node *i = numberToLinkedList(34);
	struct node *j = numberToLinkedList(12);
	struct node *k = merge2(i, j);
	_getch();
}



struct node *merge(struct node *head1, struct node *head2)
{
	struct node *i, *j;
	int temp;

	for (i = head1; i != NULL; i = i->next);

	i = head2;

	for (i = head1; i != NULL; i = i->next)
	{
		for (j = i->next; j != NULL; j = j->next)
		{
			if (i->num > j->num)
			{
				temp = i->num;
				i->num = j->num;
				j->num = temp;
			}
		}
	}

	return head1;
}

struct node *merge2(struct node *head1, struct node *head2)
{
	struct node *i = head1, *j = head2, *temp, *first, *temp2;

	if (i->num > j->num){
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

struct node * numberToLinkedList(int N)
{
	int rem, flag = 0;
	struct node *temp = (struct node*)malloc(sizeof(struct node)), *head = NULL;

	if (N < 0)
		N = -N;
	if (N == 0)
		flag++;
	temp->next = NULL;
	while (N != 0 || flag == 1)
	{
		rem = N % 10;
		temp->num = rem;
		head = (struct node*)malloc(sizeof(struct node));
		head->next = temp;
		temp = head;
		N = N / 10;
		flag++;
	}
	return head->next;
}

