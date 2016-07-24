#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


struct node
{
	int num;
	struct node *next;
	int flag;
};

int find_link(struct node *head)
{
	int j;
	struct node *i;

	for (i = head; i)
}