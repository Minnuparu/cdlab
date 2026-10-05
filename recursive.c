#include <stdio.h>
#include <string.h>

char input[100];
int pos = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void error()
{
    printf("Error: Invalid expression\n");
    exit(0);
}

/* E -> T E' */
void E()
{
    T();
    Eprime();
}

/* E' -> + T E' | epsilon */
void Eprime()
{
    if (input[pos] == '+')
    {
        pos++;
        T();
        Eprime();
    }
}

/* T -> F T' */
void T()
{
    F();
    Tprime();
}

/* T' -> * F T' | epsilon */
void Tprime()
{
    if (input[pos] == '*')
    {
        pos++;
        F();
        Tprime();
    }
}

/* F -> (E) | i */
void F()
{
    if (input[pos] == 'i')
    {
        pos++;
    }
    else if (input[pos] == '(')
    {
        pos++;
        E();

        if (input[pos] == ')')
            pos++;
        else
            error();
    }
    else
    {
        error();
    }
}

int main()
{
    printf("Enter an expression (use i for identifier): ");
    scanf("%s", input);

    strcat(input, "$");

    E();

    if (input[pos] == '$')
        printf("Expression is Accepted\n");
    else
        printf("Expression is Rejected\n");

    return 0;
}