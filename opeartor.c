#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 100

int values[MAX], operators[MAX];
int vtop = -1, otop = -1;

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

void evaluate()
{
    int b = values[vtop--];
    int a = values[vtop--];
    char op = operators[otop--];

    switch (op)
    {
        case '+': values[++vtop] = a + b; break;
        case '-': values[++vtop] = a - b; break;
        case '*': values[++vtop] = a * b; break;
        case '/':
            if (b == 0)
            {
                printf("Division by zero error");
                exit(1);
            }
            values[++vtop] = a / b;
            break;
    }
}

int main()
{
    char exp[MAX];
    int i = 0, num;

    printf("Enter arithmetic expression: ");
    scanf("%99s", exp);

    while (exp[i] != '\0')
    {
        if (isdigit(exp[i]))
        {
            num = 0;

            while (isdigit(exp[i]))
            {
                num = num * 10 + (exp[i] - '0');
                i++;
            }

            values[++vtop] = num;
            continue;
        }
        else if (exp[i] == '(')
        {
            operators[++otop] = exp[i];
        }
        else if (exp[i] == ')')
        {
            while (otop != -1 && operators[otop] != '(')
                evaluate();

            if (otop != -1)
                otop--;
        }
        else
        {
            while (otop != -1 &&
                   operators[otop] != '(' &&
                   precedence(operators[otop]) >= precedence(exp[i]))
            {
                evaluate();
            }

            operators[++otop] = exp[i];
        }

        i++;
    }

    while (otop != -1)
        evaluate();

    printf("Result = %d\n", values[vtop]);

    return 0;
}
