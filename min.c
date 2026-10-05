#include <stdio.h>

#define MAX 20

int main()
{
    int n, m;
    int trans[MAX][MAX];
    int final[MAX];
    int reachable[MAX] = {0};
    int group[MAX], newGroup[MAX];

    int i, j, k;
    int changed, count;

    /* Input */
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    printf("\nEnter transition table:\n");

    for (i = 0; i < n; i++)
    {
        printf("For q%d: ", i);

        for (j = 0; j < m; j++)
            scanf("%d", &trans[i][j]);
    }

    printf("\nEnter final states (1 = Final, 0 = Non-Final):\n");

    for (i = 0; i < n; i++)
        scanf("%d", &final[i]);


    /* Find reachable states */
    reachable[0] = 1;

    for (i = 0; i < n; i++)
    {
        if (reachable[i])
        {
            for (j = 0; j < m; j++)
            {
                reachable[trans[i][j]] = 1;
            }
        }
    }


    /* Initial grouping */
    /* 0 = Non-final, 1 = Final */

    for (i = 0; i < n; i++)
    {
        if (!reachable[i])
            group[i] = -1;
        else if (final[i])
            group[i] = 1;
        else
            group[i] = 0;
    }


    /* Refine groups until no change */
    do
    {
        changed = 0;

        for (i = 0; i < n; i++)
            newGroup[i] = -1;

        count = 0;

        for (i = 0; i < n; i++)
        {
            if (group[i] == -1)
                continue;

            if (newGroup[i] == -1)
            {
                newGroup[i] = count;

                for (j = i + 1; j < n; j++)
                {
                    if (group[j] == group[i])
                    {
                        int same = 1;

                        for (k = 0; k < m; k++)
                        {
                            if (group[trans[i][k]] !=
                                group[trans[j][k]])
                            {
                                same = 0;
                                break;
                            }
                        }

                        if (same)
                            newGroup[j] = count;
                    }
                }

                count++;
            }
        }


        /* Check whether grouping changed */

        for (i = 0; i < n; i++)
        {
            if (group[i] != newGroup[i])
            {
                changed = 1;
                break;
            }
        }


        /* Copy new groups */

        for (i = 0; i < n; i++)
            group[i] = newGroup[i];

    } while (changed);


    /* Display equivalence classes */

    printf("\nEquivalence Classes:\n");

    for (i = 0; i < count; i++)
    {
        printf("A%d = { ", i);

        for (j = 0; j < n; j++)
        {
            if (group[j] == i)
                printf("q%d ", j);
        }

        printf("}\n");
    }


    /* Display minimized DFA */

    printf("\nMINIMIZED DFA TRANSITION TABLE\n\n");

    printf("%-20s", "State");

    for (i = 0; i < m; i++)
        printf("%-20d", i);

    printf("\n");

    printf("------------------------------------------------------------\n");


    for (i = 0; i < count; i++)
    {
        /* Print current state */

        printf("A%-19d", i);


        /* Find representative state */

        for (j = 0; j < n; j++)
        {
            if (group[j] == i)
                break;
        }


        /* Print transitions */

        for (k = 0; k < m; k++)
        {
            printf("A%-19d", group[trans[j][k]]);
        }

        printf("\n");
    }


    /* Initial state */

    printf("\nInitial State: A%d", group[0]);


    /* Final states */

    printf("\nFinal States: ");

    for (i = 0; i < count; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (group[j] == i && final[j])
            {
                printf("A%d ", i);
                break;
            }
        }
    }

    printf("\n");

    return 0;
}