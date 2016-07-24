#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int isBalanced(char *str)
{
	char *stack = (char*)calloc(1000, sizeof(char));
	int top = -1, i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
		{
			top++;
			stack[top] = str[i];
		}
		else
		{
			if (str[i] == ')')
			{
				if (stack[top] == '(')
				{
					stack[top] = '\0';
					top--;
				}
				else
					return 0;
			}
			if (str[i] == '}')
			{
				if (stack[top] == '{')
				{
					stack[top] = '\0';
					top--;
				}
				else
					return 0;
			}
			if (str[i] == ']')
			{
				if (stack[top] == '[')
				{
					stack[top] = '\0';
					top--;
				}
				else
					return 0;
			}
		}
	}

	if (top == -1)
		return 1;
	else
		return 0;
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    
    int i, T;
    char str[1000];
    scanf("%d", &T);
    
    for (i = 0; i < T; i++)
    {
        scanf("%s", &str);
        if (isBalanced(str))
            printf("YES");
        else
            printf("NO");
    }
    return 0;
}
