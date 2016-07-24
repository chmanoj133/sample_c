#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void file_print(char *file_name)
{
	FILE *fp = fopen(file_name, "r");

	int count = 0;
	char ch;

	while (!(feof(fp)))
	{
		ch = getc(fp);
		if (ch == '\n')
			count++;
		printf("%c", ch);
	}
	ch = ch + 1;

}

void main()
{
	file_print("manoj.txt");
	_getch();
}