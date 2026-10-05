#include <stdio.h>

#define MAX 20
#define SYMBOLS 10

int n, m;

int epsilon[MAX][MAX];
int transition[SYMBOLS][MAX][MAX];

int eclosure[MAX][MAX];
int newTransition[SYMBOLS][MAX][MAX];

/* Find epsilon closure of a state */
void findClosure(int state)
{
    int stack[MAX];
    int top = -1;
    int current, i;

    eclosure[state][state] = 1;
    stack[++top] = state;

    while (top != -1)
    {
        current = stack[top--];

        for (i = 0; i < n; i++)
        {
            if (epsilon[current][i] == 1 &&
                eclosure[state][i] == 0)
            {
                eclosure[state][i] = 1;
                stack[++top] = i;
            }
        }
    }
}

/* Convert epsilon-NFA to NFA */
void convertNFA()
{
    int i, j, k, s;

    for (i = 0; i < n; i++)
    {
        for (s = 0; s < m; s++)
        {
            /*
             * For every state in epsilon closure of i,
             * check transition on symbol s.
             */
            for (j = 0; j < n; j++)
            {
                if (eclosure[i][j] == 1)
                {
                    for (k = 0; k < n; k++)
                    {
                        if (transition[s][j][k] == 1)
                        {
                            /*
                             * Add epsilon closure of
                             * the destination state.
                             */
                            int x;

                            for (x = 0; x < n; x++)
                            {
                                if (eclosure[k][x] == 1)
                                    newTransition[s][i][x] = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}

/* Display epsilon closures */
void displayClosures()
{
    int i, j;

    printf("\nEpsilon Closures:\n");

    for (i = 0; i < n; i++)
    {
        printf("E-closure(q%d) = { ", i);

        for (j = 0; j < n; j++)
        {
            if (eclosure[i][j] == 1)
                printf("q%d ", j);
        }

        printf("}\n");
    }
}

/* Display converted NFA */
void displayNFA()
{
    int i, j, k;

    printf("\nNFA without epsilon transitions:\n");

    for (i = 0; i < n; i++)
    {
        for (k = 0; k < m; k++)
        {
            printf("δ(q%d, %d) = { ", i, k);

            for (j = 0; j < n; j++)
            {
                if (newTransition[k][i][j] == 1)
                    printf("q%d ", j);
            }

            printf("}\n");
        }
    }
}

int main()
{
    int i, j, k;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("\nEnter epsilon transition matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &epsilon[i][j]);
        }
    }

    /*
     * Input transition matrix for each symbol.
     * Symbols are represented as 0, 1, 2, ...
     */
    for (k = 0; k < m; k++)
    {
        printf("\nEnter transition matrix for symbol %d:\n", k);

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                scanf("%d", &transition[k][i][j]);
            }
        }
    }

    /* Find epsilon closure of every state */
    for (i = 0; i < n; i++)
    {
        findClosure(i);
    }

    displayClosures();

    /* Convert epsilon-NFA to NFA */
    convertNFA();

    /* Display result */
    displayNFA();

    return 0;
}