 #include <stdio.h>
#include <string.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 10
#define MAX_DFA_STATES 100

int n, m;

int nfa[MAX_SYMBOLS][MAX_STATES][MAX_STATES];

int dfaStates[MAX_DFA_STATES][MAX_STATES];
int dfaTransition[MAX_DFA_STATES][MAX_SYMBOLS];

int dfaCount = 0;


/* Convert a state set into a string */
void stateToString(int state[], char str[])
{
    int i;
    int first = 1;

    strcpy(str, "{");

    for (i = 0; i < n; i++)
    {
        if (state[i] == 1)
        {
            char temp[10];

            if (!first)
                strcat(str, ",");

            sprintf(temp, "q%d", i);
            strcat(str, temp);

            first = 0;
        }
    }

    if (first)
        strcat(str, "-");

    strcat(str, "}");
}


/* Check whether DFA state already exists */
int findState(int state[])
{
    int i, j;

    for (i = 0; i < dfaCount; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (dfaStates[i][j] != state[j])
                break;
        }

        if (j == n)
            return i;
    }

    return -1;
}


/* Add a new DFA state */
int addState(int state[])
{
    int i;

    for (i = 0; i < n; i++)
        dfaStates[dfaCount][i] = state[i];

    dfaCount++;

    return dfaCount - 1;
}


/* Find the next state */
void getNextState(int current[], int symbol, int next[])
{
    int i, j;

    /* Initially empty */
    for (i = 0; i < n; i++)
        next[i] = 0;

    /*
       For every state present in the current DFA state,
       find its NFA transitions.
    */
    for (i = 0; i < n; i++)
    {
        if (current[i] == 1)
        {
            for (j = 0; j < n; j++)
            {
                if (nfa[symbol][i][j] == 1)
                    next[j] = 1;
            }
        }
    }
}


int main()
{
    int i, j, k;
    int next[MAX_STATES];
    int nextIndex;

    char currentString[100];
    char nextString[100];

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);


    /* Read NFA transition matrices */

    for (k = 0; k < m; k++)
    {
        printf("\nEnter transition matrix for input symbol %d:\n", k);

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                scanf("%d", &nfa[k][i][j]);
            }
        }
    }


    /* Initial DFA state = {q0} */

    int start[MAX_STATES] = {0};

    start[0] = 1;

    addState(start);


    /* Construct DFA */

    for (i = 0; i < dfaCount; i++)
    {
        for (k = 0; k < m; k++)
        {
            getNextState(dfaStates[i], k, next);

            nextIndex = findState(next);

            if (nextIndex == -1)
                nextIndex = addState(next);

            dfaTransition[i][k] = nextIndex;
        }
    }


    /* Display DFA */

    printf("\n\nDFA TRANSITION TABLE\n\n");

    printf("%-20s", "DFA State");

    for (k = 0; k < m; k++)
        printf("%-20d", k);

    printf("\n");

    printf("------------------------------------------------------------\n");


    for (i = 0; i < dfaCount; i++)
    {
        /* Current DFA state */
        stateToString(dfaStates[i], currentString);

        printf("%-20s", currentString);


        /* Transitions */
        for (k = 0; k < m; k++)
        {
            nextIndex = dfaTransition[i][k];

            stateToString(dfaStates[nextIndex], nextString);

            printf("%-20s", nextString);
        }

        printf("\n");
    }

    return 0;
}