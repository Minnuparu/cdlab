#include <stdio.h>
#include <string.h>

char stack[100];
char input[100];
int top = 0;
int ip = 0;

/* Return the precedence relation between two terminals */
char precedence(char a, char b)
{
    if (a == '+' && b == '+') return '>';
    if (a == '+' && b == '*') return '<';
    if (a == '+' && b == '(') return '<';
    if (a == '+' && b == ')') return '>';
    if (a == '+' && b == 'i') return '<';
    if (a == '+' && b == '$') return '>';

    if (a == '*' && b == '+') return '>';
    if (a == '*' && b == '*') return '>';
    if (a == '*' && b == '(') return '<';
    if (a == '*' && b == ')') return '>';
    if (a == '*' && b == 'i') return '<';
    if (a == '*' && b == '$') return '>';

    if (a == '(' && b == '+') return '<';
    if (a == '(' && b == '*') return '<';
    if (a == '(' && b == '(') return '<';
    if (a == '(' && b == ')') return '=';
    if (a == '(' && b == 'i') return '<';

    if (a == ')' && b == '+') return '>';
    if (a == ')' && b == '*') return '>';
    if (a == ')' && b == ')') return '>';
    if (a == ')' && b == '$') return '>';

    if (a == 'i' && b == '+') return '>';
    if (a == 'i' && b == '*') return '>';
    if (a == 'i' && b == ')') return '>';
    if (a == 'i' && b == '$') return '>';

    if (a == '$' && b == '+') return '<';
    if (a == '$' && b == '*') return '<';
    if (a == '$' && b == '(') return '<';
    if (a == '$' && b == 'i') return '<';
    if (a == '$' && b == '$') return '=';

    return ' ';
}

/* Find the topmost terminal in the stack */
int topTerminal()
{
    int i;

    for (i = top; i >= 0; i--)
    {
        if (stack[i] == '+' ||
            stack[i] == '*' ||
            stack[i] == '(' ||
            stack[i] == ')' ||
            stack[i] == 'i' ||
            stack[i] == '$')
        {
            return i;
        }
    }

    return -1;
}

/* Print stack */
void printStack()
{
    int i;

    for (i = 0; i <= top; i++)
        printf("%c", stack[i]);
}

/* Print remaining input */
void printInput()
{
    int i;

    for (i = ip; i < strlen(input); i++)
        printf("%c", input[i]);
}

/* Reduce the handle */
int reduce()
{
    /* E -> i */
    if (stack[top] == 'i')
    {
        stack[top] = 'E';
        return 1;
    }

    /* E -> E + E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '+' &&
        stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }

    /* E -> E * E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '*' &&
        stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }

    /* E -> ( E ) */
    if (top >= 2 &&
        stack[top - 2] == '(' &&
        stack[top - 1] == 'E' &&
        stack[top] == ')')
    {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }

    return 0;
}

int main()
{
    char relation;
    int t;

    printf("Enter expression (use i for identifier): ");
    scanf("%s", input);

    strcat(input, "$");

    stack[0] = '$';
    top = 0;
    ip = 0;

    printf("\nStack\t\tInput\t\tAction\n");
    printf("---------------------------------------------\n");

    while (1)
    {
        /* Accept */
        if (top == 1 &&
            stack[0] == '$' &&
            stack[1] == 'E' &&
            input[ip] == '$')
        {
            printStack();
            printf("\t\t");
            printInput();
            printf("\t\tAccept\n");
            break;
        }

        t = topTerminal();

        if (t == -1)
        {
            printf("Error\n");
            break;
        }

        relation = precedence(stack[t], input[ip]);

        /* SHIFT */
        if (relation == '<' || relation == '=')
        {
            stack[++top] = input[ip];
            ip++;

            printStack();
            printf("\t\t");
            printInput();
            printf("\t\tShift\n");
        }

        /* REDUCE */
        else if (relation == '>')
        {
            if (reduce())
            {
                printStack();
                printf("\t\t");
                printInput();
                printf("\t\tReduce\n");
            }
            else
            {
                printf("Error\n");
                break;
            }
        }

        /* ERROR */
        else
        {
            printf("Error\n");
            break;
        }
    }

    return 0;
}