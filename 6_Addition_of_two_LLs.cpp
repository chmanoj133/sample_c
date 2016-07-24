/* 
6.Write a program to add two linked list 
(Each node is represented by a digit ) 
(Note: Unequal Lengths can also be given )

Ex: Input 1->2->3->4 and 1->2->3->4
Output 2->4->6->8
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

struct node
{
	int num;
	struct node *next;
};

struct test
{
	int a[100];
	int len_a;
	int b[100];
	int len_b;
	int ans[100];
	int len_ans;
}testDB[6] = {
	{ { 1, 2, 3, 4, 5 }, 5, { 1, 2, 3, 4, 5 }, 5, { 2, 4, 6, 9, 0 }, 5 },
	{ { 9, 9, 9 }, 3, { 1 }, 1, { 1, 0, 0, 0 }, 4 },
	{ { 9, 9, 9, 8, 9, 9, 9 }, 7, { 1 }, 1, { 9, 9, 9, 9, 0, 0, 0 }, 7 },
	{ { 1, 2, 3 }, 3, { 2, 4, 8, 1, 2, 3 }, 6, { 2, 4, 8, 2, 4, 6 }, 6 },
	{ { 9 }, 1, { 2 }, 1, { 1, 1 }, 2 },
	{NULL, 1, NULL, 1, NULL, 1}
};

struct node *reverse_SLL(struct node  *head, int *count);
struct node *Add_two_SLL(struct node *list1, struct node *list2);	//--> Method 1: Addition of two SLL's by reversing given nodes
void print_output();
int compare(int i, int function);
struct node *Array_to_SLL(int *arr, int len);
struct node *Add_two_equal_SLL_recursive(struct node *list1, struct node *list2);
struct node *Add_two_SLL_recursive(struct node *head1, struct node *head2);	//--> Method 2: Addition of two SLL's by recursion

void main()
{
	print_output();
	_getch();
}

struct node *Add_two_SLL(struct node *list1, struct node *list2) //method1
{
	struct node *temp, *i, *j;
	int count1 = 1, count2 = 1, carry = 0, j_num;

	if (list1 == NULL)
		return list2;
	else if (list2 == NULL)
		return list1;

	list1 = reverse_SLL(list1, &count1);
	list2 = reverse_SLL(list2, &count2);

	if (count1 < count2)
	{
		temp = list1;
		list1 = list2;
		list2 = temp;		
	}

	j_num = list2->num;
	j = list2;

	for (i = list1; i != NULL; i = i->next)
	{
		i->num = i->num + j_num + carry;

		if (i->num > 9)
		{
			i->num = i->num % 10;
			carry = 1;
		}
		else
			carry = 0;

		if (j->next != NULL)
		{
			j_num = j->next->num;
			j = j->next;
		}
		else
		{
			if (carry == 0)
				break;
			j_num = 0;
		}
	}

	list1 = reverse_SLL(list1, &count1);

	if (carry == 1)
	{
		list2 = (struct node*)malloc(sizeof(struct node));
		list2->num = 1;
		list2->next = list1;
		list1 = list2;
	}
	
	return list1;

}

struct node *Add_two_SLL_recursive(struct node *head1, struct node *head2)
{
	struct node *i, *temp;
	int count1, count2, j, diff;

	if (head1 == NULL)
		return head2;
	else if (head2 == NULL)
		return head1;
	
	for (i = head1, count1 = 0; i != NULL; i = i->next, count1++);
	for (i = head2, count2 = 0; i != NULL; i = i->next, count2++);

	diff = count1 - count2;
	if (count2 > count1)
	{
		i = head1;
		head1 = head2;
		head2 = i;
		diff = -diff;
	}

	for (j = 0; j < diff; j++)
	{
		temp = (struct node*)malloc(sizeof(struct node));
		temp->num = 0;
		temp->next = head2;
		head2 = temp;
	}
	head1 = Add_two_equal_SLL_recursive(head1, head2);

	if (head1->num > 9)
	{
		temp = (struct node*)malloc(sizeof(struct node));
		temp->num = 1;
		temp->next = head1;
		head1->num = head1->num % 10;
		head1 = temp;
	}

	return head1;
}

struct node *Add_two_equal_SLL_recursive(struct node *head1, struct node *head2)
{
	struct node *tail;

	if (head1->next == NULL && head2->next == NULL)
	{
		head1->num = (head1->num + head2->num) ;
		return head1;
	}
	tail = Add_two_equal_SLL_recursive(head1->next, head2->next);

	head1->num = head1->num + head2->num + (head1->next->num) / 10;
	head2->num = 0;
	head1->next->num = head1->next->num % 10;
	return head1;
}

struct node *reverse_SLL(struct node *head, int *count)
{
	struct node *tail;

	if (head == NULL)
		return NULL;
	else
	{
		if (head->next == NULL)
			return head;
		
		tail = reverse_SLL(head->next, count);
		(*count)++;
		head->next->next = head;
		head->next = NULL;
		return tail;
	}
}

int compare(int i, int function)		// Function comparing outputs
{
	int j, count = 2, flag = 1;
	struct node *head = NULL, *temp1, *temp2;
	temp1 = Array_to_SLL(testDB[i].a, testDB[i].len_a);
	temp2 = Array_to_SLL(testDB[i].b, testDB[i].len_b);

	if (function == 1)
		head = Add_two_SLL(temp1, temp2);
	else
		head = Add_two_SLL_recursive(temp1, temp2);

	for (j = 0, temp1 = head; j < testDB[i].len_ans; j++, temp1 = temp1->next)
	{
		if (testDB[i].ans[j] != temp1->num)
		{
			flag = 0;
			break;
		}
	}
	return flag;
}

void print_output()			// Function that prints on cmd
{
	int i, count = 6, function_select = 1;

	printf(" ---- Test results for Addition of two SLL's by reversing given nodes ----\n\n");
	for (i = 0; i < count; i++)
	{
		if (compare(i, function_select) == 1)
			printf("TESTCASE %d PASSED\n", i + 1);
		else
			printf("TESTCASE %d FAILED\n", i + 1);
		if (i == count - 1 && function_select == 1)
		{
			i = -1;
			function_select = 2;
			printf("\n\n ---- Test cases for Addition of two SLL's by using recursion method ----\n\n");
		}
		
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