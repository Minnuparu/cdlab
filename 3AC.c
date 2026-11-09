#include <stdio.h>
#include <string.h>

int main() {
    char result[10], op1[10], op2[10], operator;
    char code[50];

    printf("Enter three address code:\n");
    scanf("%s", code);

    sscanf(code, "%[^=]=%[^+-*/]%c%s",
           result, op1, &operator, op2);

    printf("\nEquivalent 8086 Assembly Code:\n");

    printf("MOV AX, %s\n", op1);

    switch (operator) {
        case '+':
            printf("ADD AX, %s\n", op2);
            break;

        case '-':
            printf("SUB AX, %s\n", op2);
            break;

        case '*':
            printf("MOV BX, %s\n", op2);
            printf("MUL BX\n");
            break;

        case '/':
            printf("MOV BX, %s\n", op2);
            printf("MOV DX, 0\n");
            printf("DIV BX\n");
            break;

        default:
            printf("Invalid operator\n");
            return 1;
    }

    printf("MOV %s, AX\n", result);

    return 0;
}
