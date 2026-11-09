%{
#include <stdio.h>

int yylex();
int yyerror();
%}

%token NUMBER

%%

input : expression '\n'   { printf("Result = %d\n", $1); }
      ;

expression : expression '+' term   { $$ = $1 + $3; }
           | expression '-' term   { $$ = $1 - $3; }
           | term                  { $$ = $1; }
           ;

term : term '*' factor             { $$ = $1 * $3; }
     | term '/' factor             { $$ = $1 / $3; }
     | factor                      { $$ = $1; }
     ;

factor : '(' expression ')'        { $$ = $2; }
       | NUMBER                    { $$ = $1; }
       ;

%%

int yyerror()
{
    printf("Invalid expression\n");
    return 0;
}

int main()
{
    printf("Enter an expression: ");
    yyparse();
    return 0;
}