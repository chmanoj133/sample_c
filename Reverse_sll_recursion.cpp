#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node
{
	int num;
	struct node *next;
};

struct node * numberToLinkedList(int N);
struct node *reverse_sll_recursion(struct node *head);

void main()
{
	struct node *a = reverse_sll_recursion(numberToLinkedList(123456));
}

struct node *reverse_sll_recursion(struct node *head)
{
	struct node*i, *j, *temp;

	if (head->next == NULL)
		head = head->next;
	else
		temp = reverse_sll_recursion(head->next);

	return head;
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