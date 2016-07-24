#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int string_length(char* str)
{
	int i;
	if (str == NULL)
		return 0;
	for (i = 0; str[i] != '\0'; i++);
	return i;
}

bool string_compare(char *str1, char *str2)
{
	int i;
	int len = string_length(str1);
	if (len != string_length(str2))
		return false;

	for (i = 0; i < len; i++)
	{
		if (str1[i] != str2[i])
			return false;
	}
	return true;
}

int exp(int base, int pow)
{
	int i, ans = 1;
	for (i = 0; i < pow; i++)
		ans = ans*base;
	return ans;
}

int sqrt(int N)
{
	int i;
	for (i = 0; i*i <= N; i++);
	return i - 1;
}

char *toLower(char *str)
{
	int i;
	char *ans = (char*)calloc(string_length(str), sizeof(char));
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			ans[i] = str[i] - 'A' + 'a';
		else
			ans[i] = str[i];
	}
	ans[i] = '\0';
	return ans;
}

char *captilize(char *str)
{
	int i;

	if (str[0] >= 'a' && str[0] <= 'z')
		str[0] = str[0] - 'a' + 'A';

	for (i = 1; str[i + 1] != '\0'; i++)
	{
		if (str[i] == ' ' && str[i + 1] >= 'a' && str[i + 1] <= 'z')
			str[i + 1] = str[i + 1] - 'a' + 'A';
	}

	return str;
}

char *num_to_str(int num, int len)
{
	char *str = (char*)calloc(len, sizeof(char));
	int i, rem;

	for (i = len - 1; i >= 0; i--)
	{
		rem = num % 10;
		str[i] = rem + '0';
		num = num / 10;
	}
	str[len] = '\0';
	return str;
}

bool is_there(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	if (c >= 'a' && c <= 'z')
		return true;
	return false;
}

char base36(int num)
{
	if (num >= 0 && num <= 9)
		return num + '0';
	else
		return 'a' + num - 10;
}

int base10(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	else
		return c - 'a' + 10;
}

int str_to_num(char *str)
{
	int i;
	long int ans = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			ans = ans * 10 + str[i] - '0';
	}
	return ans;
}

int val(char c)
{
	if (c >= '0' && c <= '9')
		return (int)c - '0';
	else
		return (int)c - 'A' + 10;
}

int toDecimal(char *str, int base)
{
	int len = string_length(str);
	int power = 1; 
	int num = 0; 
	int i;

	
	for (i = len - 1; i >= 0; i--)
	{
		if (val(str[i]) >= base)
		{
			printf("Invalid Number");
			return -1;
		}

		num += val(str[i]) * power;
		power = power * base;
	}

	return num;
}

char reVal(int num)
{
	if (num >= 0 && num <= 9)
		return (char)(num + '0');
	else
		return (char)(num - 10 + 'A');
}


void strev(char *str)
{
	int len = string_length(str);
	int i;
	for (i = 0; i < len / 2; i++)
	{
		char temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
	}
}

char* fromDecimal(int base, int inputNum, int len)
{
	int index = len - 1; 
	int i = len;
	char *res = (char*)calloc(len, sizeof(char));
	while (i > 0)
	{
		res[index] = reVal(inputNum % base);
		index--;
		inputNum /= base;
		i--;
	}
	res[len] = '\0';

	return res;
}

char *only_nums(char *str)
{
	int i, count = 0;
	char *ans = (char*)calloc(string_length(str), sizeof(char));
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9'){
			ans[count] = str[i];
			count++;
		}
	}
	ans[count] = '\0';
	return ans;
}



struct stack
{
	int element;
	struct stack *next;
};


char *error_msg(int error_code)
{
	if (error_code == 0)
		return "Math Error: Integer division by zero error";

	return "Syntax Error: Expression is invalid or not recognisable";

}

void create_node(struct stack **top, int num)
{
	struct stack *new_node = (struct stack*)malloc(sizeof(struct stack));

	new_node->next = *top;
	new_node->element = num;
	*top = new_node;
}

int perform_arithematic(int left, int right, int op, int *any_error)
{
	int i = 0, ans = 1;

	if (op == 0)
		return left - right;
	if (op == 1)
		return left + right;
	if (op == 2)
		return left * right;
	if (op == 3)
	{
		if (right == 0)
			*any_error = 0;
		else
			return left / right;
	}
	if (op == 4)
	{
		for (i = 0; i < right; i++)
			ans = ans * left;
		return ans;
	}
	return NULL;
}


int solve_expression(struct stack *top, int *any_error)
{
	struct stack *ref_top = top, *i, *j;
	int left, right, op, just_stop = 0;

	if (top == NULL)
		return 0;

	if (top->next == NULL)
		return top->element;

	i = top->next;
	j = top->next;
	while (i->next != NULL)
	{
		// e.g: 8/4/2/1 : first 8/4 must be calculated, top is at 1,
		// this loop moves top  to 8/4 
		if (i->next->next != NULL)
		{
			if (i->next->next->element == i->element)
			{
				i = i->next->next;
				if (just_stop)
					j = j->next->next;
			}
			else
				break;
		}
		else
			break;
		just_stop = 1;
	}

	if (i == j)
	{
		left = i->next->element;
		right = top->element;
		op = i->element;
		top = i->next->next;
		create_node(&top, perform_arithematic(left, right, op, any_error));
	}
	else
	{
		left = i->next->element;
		right = j->next->element;
		op = i->element;
		i = i->next->next;
		create_node(&i, perform_arithematic(left, right, op, any_error));
		j->next = i;
	}

	return solve_expression(top, any_error);
}


int assigned_operator_num(char c)
{
	if (c == '+')
		return 1;

	if (c == '-')
		return 0;

	if (c == '*')
		return 2;

	if (c == '/')
		return 3;

	return -1;
}

int is_allowable_char(char c)
{
	if (c >= '0' && c <= '9')
		return 1;

	if (c == '+' || c == '-' || c == '*' || c == '/')
		return 2;
	return 0;
}

int solve_file(char *file_name)
{
	FILE *p1 = fopen(file_name, "r");
	FILE *p2 = fopen("temp.txt", "w");
	FILE *p3 = fopen("op.txt", "w");
	char c;
	int num = 0, isNum = 0, last_op = -1, any_error = -1, temp_ans = 0, entry = 0;
	int op = -1, special_start = 0;
	struct stack *top = NULL, *temp = NULL;

	if (p1 == NULL)
		return 0;

	while (!feof(p1))
	{
		c = fgetc(p1);
		entry = is_allowable_char(c);

		if (c != '\n' && c != EOF && any_error == -1)
		{
			if (entry == 1)		// if c is a num
			{
				fseek(p1, -1, SEEK_CUR);
				fscanf(p1, "%d", &num);
				fprintf(p2, "%d", num);
				if (special_start == 1)
					// if starting num is negative
					num = -num;
				special_start = 0;
				create_node(&top, num);
			}
			else if (entry == 2)	// if c is a operator
			{
				isNum = 0;
				// we use this variable since if c is a num,
				// we should not do fputc 
				// as fprintf is going to print the integer in next loop 
				fputc(c, p2);
				op = assigned_operator_num(c);
				if (top == NULL)
				{
					// this is a special case : if expression starts with + or -
					// e.g: -5+1 = -4 , not an error 
					//		+5+5 = 10
					if (op == 0 || op == 1)
					{
						if (op == 0)
							special_start = 1;
						else
							special_start = 2;
					}
					else
						any_error = 1;
					// invalid expression: starting itself an operator is used 
					// e.g : /5+2 : starting / shouldn't be occured
				}
				if (!special_start)
				{
					create_node(&top, op);
					if (top->element == 0)
					{
						special_start = 1;
						top->element = 1;
					}
					if (top->element == 2)
					{
						c = fgetc(p1);
						// check for power operator **
						if (c >= '0' && c <= '9')
						{
							fseek(p1, -1, SEEK_CUR);
							isNum = 1;
						}
						else if (c == '*')
						{
							fputc(c, p2);
							top->element = 4;
							c = fgetc(p1);
							// check for error : after **, whether any other operator is occured 
							// e.g: 5**+2 is an error !
							if (c >= '0' && c <= '9')
							{
								fseek(p1, -1, SEEK_CUR);
								isNum = 1;
							}
							else if (c != ' ') // e.g: 5  **  2 = 25 --> spacing is allowable
								any_error = 2;

							if (isNum != 1 && c != '\n' && c != EOF)
								fputc(c, p2);
							isNum = 0;
						}
						else
						{
							if (isNum != 1 && c != '\n' && c != EOF)
								fputc(c, p2);
							if (c != ' ')
								// after * something unusal char is used
								// e.g: 5*h2 : h is recognised as error here
								any_error = 2;
						}
					}
					else
					{
						c = fgetc(p1);
						// check whether , after a opertor, any unsual char is there or not
						// e.g: 5+-9 : two operators are not allowed at a time
						if (c >= '0' && c <= '9')
						{
							fseek(p1, -1, SEEK_CUR);
							isNum = 1;
						}
						else if (c != ' ')
							// e.g: 5+&4
							any_error = 2;
						if (isNum != 1 && c != '\n' && c != EOF)
							fputc(c, p2);
					}

					if (last_op > top->element)
					{
						// This is a operator precedence check
						// e.g: if the stack cotains:  5 + 2 * 2 / 1 + : top->element is at +
						// In the expression, until, from start to 2/1 is calculated 
						// since '/' > '+' 
						// Now the stack will be --> 9 + 
						temp = top;
						top = NULL;
						create_node(&top, solve_expression(temp->next, &any_error));
						temp->next = top;
						top = temp;
					}
					last_op = top->element;
				}
			}
			else
			{
				// Here error check is done
				// e.g: hjh : wrong expression
				if (c != '\n' && c != EOF)
					fputc(c, p2);
				if (c != ' ')
					any_error = 3;
			}
		}
		else
		{
			if (c != '\n' && c != EOF)
				fputc(c, p2);
		}

		if (c == '\n' || c == EOF)
		{
			// when expression comes to end,
			// final answer is appended here
			if (any_error == -1 && c != -1 && top != NULL)
			{
				temp_ans = solve_expression(top, &any_error);
				if (any_error == -1)
					fprintf(p3, "%d", temp_ans);
				else
					fprintf(p2, " :\t%s", error_msg(any_error));
			}
			else if (c != -1 && top != NULL)
				fprintf(p2, " :  %s", error_msg(any_error));
			else if (any_error == 3)
				fprintf(p2, " :  %s", error_msg(any_error));
			if (c != -1)
				fputc(c, p2);

			break;

		}
	}

	fclose(p1);
	fclose(p2);
	fclose(p3);

	remove(file_name);
	rename("temp.txt", file_name);
	return any_error;

}

int in(char *str, char c)
{
	int i;
	for (i = 0; str[i] != c && str[i] != '\0'; i++);
	if (str[i] == '\0')
		return -1;
	else
		return i;
}

bool isAlpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return true;
	if (c >= 'A' && c <= 'Z')
		return true;
	return false;
}

bool isNum(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

char *remove_spaces(char *str)
{
	char *ans = (char*)calloc(string_length(str), sizeof(char));
	int j = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ')
		{
			ans[j] = str[i];
			j++;
		}
	}
	ans[j] = '\0';

	return ans;
}
