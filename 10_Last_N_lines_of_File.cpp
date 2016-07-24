/*
	10. Print last N lines of a file
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void print_last_k_lines_file_1(char *file_name, int k);
void print_last_k_lines_file_2(char *file_name, int k);

void main()
{
	print_last_k_lines_file_1("manoj.txt", 5);
	printf("\n\n");
	print_last_k_lines_file_2("manoj.txt", 5);
	_getch();
}

void print_last_k_lines_file_1(char *file_name, int k)			// Method 1	: n-k method
{
	FILE *p1, *p2;
	char ch;
	int count = 0, count2 = 0;

	p1 = fopen(file_name, "r");

	if (p1 == NULL)
		printf("Error: File not found");
	while (!feof(p1))
	{
		if (fgetc(p1) == '\n')
			count++;
	}

	p2 = fopen("manoj.txt", "r");

	while (!feof(p2))
	{
		ch = fgetc(p2);
		if (ch == '\n')
			count2++;
		if (count2 > count - k)
			putchar(ch);
	}
	fclose(p1);
	fclose(p2);
}

void print_last_k_lines_file_2(char *file_name, int k)		// Method 2: Two pointer method
{
	FILE *p1, *p2;
	char ch1,ch[1000], ch2[1000];
	int count = 0;
	

	p1 = fopen(file_name, "r");
	if (p1 == NULL)
		printf("Error: File not found");

	while (!feof(p1))
	{
		ch1 = fgetc(p1);
		if (ch1 == '\n')
			count++;
		if (count == k)
			break;
	}
	p2 = fopen(file_name, "r");
	while (fgets(ch, 1000, p1) != NULL)
		fgets(ch2, 1000, p2);

	while (!feof(p2))
	{
		fgets(ch2, 1000, p2);
		puts(ch2);
	}

	fclose(p1);
	fclose(p2);
}