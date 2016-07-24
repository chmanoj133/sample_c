#include <stdio.h>
#include <conio.h>

int *fun();
void main()
{   
	static int a=20;
	int *p;
	p = fun();
	printf("%u\t%d\n", p, *p);
	_getch();

}

int *fun()
{
	static int  a = 25;
	return &a;
}