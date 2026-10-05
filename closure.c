#include <stdio.h>

#define MAX 20

int n;
int epsilon[MAX][MAX];
int closure[MAX][MAX];

/* Find epsilon closure of a state */
void findClosure(int state)
{
    int stack[MAX];
    int top = -1;
    int current, i;

    /* Initially, the state itself is included */
    closure[state][state] = 1;
    stack[++top] = state;

    while (top != -1)
    {
        current = stack[top--];

        for (i = 0; i < n; i++)
        {
            if (epsilon[current][i] == 1 &&
                closure[state][i] == 0)
            {
                closure[state][i] = 1;
                stack[++top] = i;
            }
        }
    }
}

int main()
{
    int i, j;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter epsilon transition matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &epsilon[i][j]);
        }
    }

    /* Find epsilon closure of every state */
    for (i = 0; i < n; i++)
    {
        findClosure(i);
    }

    /* Display epsilon closures */
    printf("\nEpsilon Closures:\n");

    for (i = 0; i < n; i++)
    {
        printf("E-closure(q%d) = { ", i);

        for (j = 0; j < n; j++)
        {
            if (closure[i][j] == 1)
                printf("q%d ", j);
        }

        printf("}\n");
    }

    return 0;
}