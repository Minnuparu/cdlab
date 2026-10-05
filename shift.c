#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char stack[100];
char input[100];
int top = 0;
int ip = 0;

/* Display stack */
void displayStack()
{
    int i;

    for (i = 0; i <= top; i++)
        printf("%c", stack[i]);
}

/* Display remaining input */
void displayInput()
{
    int i;

    for (i = ip; input[i] != '\0'; i++)
        printf("%c", input[i]);
}

/* Reduce the stack */
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
        top = top - 2;
        stack[top] = 'E';
        return 1;
    }

    /* E -> E * E */
    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '*' &&
        stack[top] == 'E')
    {
        top = top - 2;
        stack[top] = 'E';
        return 1;
    }

    /* E -> (E) */
    if (top >= 2 &&
        stack[top - 2] == '(' &&
        stack[top - 1] == 'E' &&
        stack[top] == ')')
    {
        top = top - 2;
        stack[top] = 'E';
        return 1;
    }

    return 0;
}

int main()
{
    printf("Enter expression (use i for identifier): ");
    scanf("%s", input);

    strcat(input, "$");

    /* Initialize stack */
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
            displayStack();
            printf("\t\t");
            displayInput();
            printf("\t\tAccept\n");
            break;
        }

        /* Shift */
        if (input[ip] != '$')
        {
            stack[++top] = input[ip];
            ip++;

            displayStack();
            printf("\t\t");
            displayInput();
            printf("\t\tShift\n");

            /* Try reduction after shift */
            while (reduce())
            {
                displayStack();
                printf("\t\t");
                displayInput();
                printf("\t\tReduce\n");
            }
        }
        else
        {
            /* Reduce when input reaches $ */
            if (reduce())
            {
                displayStack();
                printf("\t\t");
                displayInput();
                printf("\t\tReduce\n");
            }
            else
            {
                printf("Error: Invalid expression\n");
                break;
            }
        }
    }

    return 0;
}