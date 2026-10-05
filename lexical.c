#include <stdio.h>
#include <string.h>
#include <ctype.h>

char keywords[][20] = {
    "int", "float", "char", "double", "if",
    "else", "while", "for", "return", "void"
};

/* Check whether the given word is a keyword */
int isKeyword(char str[])
{
    int i;

    for (i = 0; i < 10; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

/* Identify identifier or keyword */
void identifier(FILE *fp, char first)
{
    char buffer[100];
    char ch;
    int i = 0;

    buffer[i++] = first;

    while ((ch = fgetc(fp)) != EOF &&
           (isalnum(ch) || ch == '_'))
    {
        buffer[i++] = ch;
    }

    buffer[i] = '\0';

    if (isKeyword(buffer))
        printf("%s\t\tKeyword\n", buffer);
    else
        printf("%s\t\tIdentifier\n", buffer);

    if (ch != EOF)
        ungetc(ch, fp);
}

/* Identify numbers */
void number(FILE *fp, char first)
{
    char buffer[100];
    char ch;
    int i = 0;

    buffer[i++] = first;

    while ((ch = fgetc(fp)) != EOF && isdigit(ch))
    {
        buffer[i++] = ch;
    }

    buffer[i] = '\0';

    printf("%s\t\tNumber\n", buffer);

    if (ch != EOF)
        ungetc(ch, fp);
}

/* Identify operators */
void operatorToken(FILE *fp, char first)
{
    char next;

    next = fgetc(fp);

    if ((first == '=' && next == '=') ||
        (first == '<' && next == '=') ||
        (first == '>' && next == '=') ||
        (first == '!' && next == '='))
    {
        printf("%c%c\t\tOperator\n", first, next);
    }
    else
    {
        printf("%c\t\tOperator\n", first);

        if (next != EOF)
            ungetc(next, fp);
    }
}

/* Identify special symbols */
void specialSymbol(char ch)
{
    printf("%c\t\tSpecial Symbol\n", ch);
}

/* Main lexical analyser */
void lexicalAnalysis(FILE *fp)
{
    char ch;

    while ((ch = fgetc(fp)) != EOF)
    {
        /* Ignore spaces, tabs, newlines and carriage return */
        if (ch == ' ' || ch == '\t' ||
            ch == '\n' || ch == '\r')
        {
            continue;
        }

        /* Identifier or keyword */
        if (isalpha(ch) || ch == '_')
        {
            identifier(fp, ch);
        }

        /* Number */
        else if (isdigit(ch))
        {
            number(fp, ch);
        }

        /* Operator */
        else if (ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/' ||
                 ch == '=' || ch == '<' ||
                 ch == '>' || ch == '!')
        {
            operatorToken(fp, ch);
        }

        /* Special symbol */
        else if (ch == '(' || ch == ')' ||
                 ch == '{' || ch == '}' ||
                 ch == '[' || ch == ']' ||
                 ch == ';' || ch == ',')
        {
            specialSymbol(ch);
        }

        /* Unknown symbol */
        else
        {
            printf("%c\t\tUnknown Symbol\n", ch);
        }
    }
}

int main()
{
    FILE *fp;

    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    printf("Tokens:\n");

    lexicalAnalysis(fp);

    fclose(fp);

    return 0;
}