#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node *insert(struct node* head, int num);

struct node
{
	int num;
	struct node *next;
};

struct node *insert(struct node* head, int num)
{
	int count = 0; 
	struct node *i, *in, *temp1;

	
	for (i = head; ; i = i->next)
	{
		if (i->next->num > num && i->num <= num)
		{
			in = (struct node*)malloc(sizeof(struct node));
			in->num = num;
			temp1 = i->next;
			i->next = in;
			in->next = temp1;
			break;
		}
	}
	
}

void main()
{
	int 
}