#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char production[MAX][MAX];
char first[26][MAX];
char follow[26][MAX];

int n;

/* Add a symbol if it is not already present */
void addToSet(char set[], char symbol)
{
    int i;

    if (symbol == '\0')
        return;

    for (i = 0; set[i] != '\0'; i++)
    {
        if (set[i] == symbol)
            return;
    }

    set[i] = symbol;
    set[i + 1] = '\0';
}

/* Find FIRST of a symbol */
void findFirst(char symbol, char result[])
{
    int i, j;
    char rhs[MAX];

    /* Terminal */
    if (!isupper(symbol) && symbol != '#')
    {
        addToSet(result, symbol);
        return;
    }

    /* Epsilon */
    if (symbol == '#')
    {
        addToSet(result, '#');
        return;
    }

    /* Non-terminal */
    for (i = 0; i < n; i++)
    {
        if (production[i][0] == symbol)
        {
            strcpy(rhs, production[i] + 2);

            /* A -> # */
            if (rhs[0] == '#')
            {
                addToSet(result, '#');
                continue;
            }

            for (j = 0; rhs[j] != '\0'; j++)
            {
                char temp[MAX] = "";
                int k;
                int epsilon = 0;

                findFirst(rhs[j], temp);

                for (k = 0; temp[k] != '\0'; k++)
                {
                    if (temp[k] == '#')
                        epsilon = 1;
                    else
                        addToSet(result, temp[k]);
                }

                if (!epsilon)
                    break;

                /* All symbols produced epsilon */
                if (rhs[j + 1] == '\0')
                    addToSet(result, '#');
            }
        }
    }
}

/* Find FOLLOW sets */
void findFollow()
{
    int changed = 1;
    int i, j, k;

    /* $ belongs to FOLLOW of start symbol */
    addToSet(follow[production[0][0] - 'A'], '$');

    while (changed)
    {
        changed = 0;

        for (i = 0; i < n; i++)
        {
            char lhs = production[i][0];
            char *rhs = production[i] + 2;

            for (j = 0; rhs[j] != '\0'; j++)
            {
                char B = rhs[j];

                if (!isupper(B))
                    continue;

                /* Check symbols after B */
                int nullable = 1;

                for (k = j + 1; rhs[k] != '\0'; k++)
                {
                    char temp[MAX] = "";
                    int hasEpsilon = 0;

                    findFirst(rhs[k], temp);

                    int x;
                    for (x = 0; temp[x] != '\0'; x++)
                    {
                        if (temp[x] == '#')
                            hasEpsilon = 1;
                        else
                        {
                            int oldLen = strlen(follow[B - 'A']);
                            addToSet(follow[B - 'A'], temp[x]);

                            if (strlen(follow[B - 'A']) != oldLen)
                                changed = 1;
                        }
                    }

                    if (!hasEpsilon)
                    {
                        nullable = 0;
                        break;
                    }
                }

                /* If B is at the end or remaining part derives epsilon */
                if (nullable)
                {
                    char *lhsFollow = follow[lhs - 'A'];

                    for (k = 0; lhsFollow[k] != '\0'; k++)
                    {
                        int oldLen = strlen(follow[B - 'A']);

                        addToSet(follow[B - 'A'], lhsFollow[k]);

                        if (strlen(follow[B - 'A']) != oldLen)
                            changed = 1;
                    }
                }
            }
        }
    }
}

int main()
{
    int i;
    char temp[MAX];

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("\nEnter productions (use # for epsilon):\n");

    for (i = 0; i < n; i++)
    {
        printf("Production %d: ", i + 1);
        scanf("%s", production[i]);
    }

    /* Calculate FIRST */
    for (i = 0; i < n; i++)
    {
        int index = production[i][0] - 'A';

        findFirst(production[i][0], first[index]);
    }

    /* Calculate FOLLOW */
    findFollow();

    printf("\nFIRST sets:\n");

    for (i = 0; i < 26; i++)
    {
        if (first[i][0] != '\0')
        {
            printf("FIRST(%c) = { ", 'A' + i);

            int j;
            for (j = 0; first[i][j] != '\0'; j++)
                printf("%c ", first[i][j]);

            printf("}\n");
        }
    }

    printf("\nFOLLOW sets:\n");

    for (i = 0; i < 26; i++)
    {
        if (follow[i][0] != '\0')
        {
            printf("FOLLOW(%c) = { ", 'A' + i);

            int j;
            for (j = 0; follow[i][j] != '\0'; j++)
                printf("%c ", follow[i][j]);

            printf("}\n");
        }
    }

    return 0;
}