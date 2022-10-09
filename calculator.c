#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

bool shouldRepeatOperation = false;
const int NUM_OPERATORS = 10;
char displayOperator;

const char OPERATORS[] = {
    '+',
    'p',
    '-',
    '_',
    '*',
    'x',
    'X',
    '/',
    'd',
    '%'};

double calculate(double a, double b, char operation)
{
    switch (operation)
    {
    case '+':
    case 'p':
        displayOperator = '+';
        return a + b;
    case '-':
    case '_':
        displayOperator = '-';
        return a - b;
    case '*':
    case 'x':
    case 'X':
        displayOperator = '*';
        return a * b;
    case '/':
    case 'd':
        displayOperator = '/';
        return a / b;
    case '%':
        displayOperator = '%';
        return (int)round(a) % (int)round(b);
    default:
        break;
    }
}

bool isValidOperator(char operator)
{
    for (int i = 0; i < NUM_OPERATORS; i++)
        return operator== OPERATORS[i];
}

void calculatorUsecase(int time)
{
    double a;
    double b;
    char operation;
    system("cls");

    if (time == 1)
    {
        printf("\nYou enter number, operation, number, I display the result. Ready?\n\n\nPress Y any key to continue...");

        scanf(" %c", &operation);
    }

    system("cls");

    printf("\nEnter a number... \n\n\n   ");
    scanf("%lf", &a);

    system("cls");

    printf("\nEnter the operation... \n\n\n   %.2lf ", a);
    scanf(" %c", &operation);

    while (!isValidOperator(operation))
    {
        printf("\nInvalid operation!\n");
        printf("The operation  must be one of the folowing:\n");
        printf("( +, p ): Addition. Finds the Sum\n");
        printf("( -, _ ): Subtraction. Finds the difference\n");
        printf("( *, x, X ): Multiplication. Finds the product\n");
        printf("( /, d ): Division. Finds the quotient\n");
        printf("( % ): Modulus. Finds remainder for the integer division\n");
        printf("\n\n So, what operation will you choose? ");
        scanf(" %c", &operation);
    }

    system("cls");

    printf("\nEnter a number... \n\n\n   %.2lf %c ", a, operation);
    scanf("%lf", &b);

    system("cls");

    printf("\nThe result: \n\n\n   %.2lf %c %.2lf = %.3lf\n", a, displayOperator, b, calculate(a, b, operation));
}

bool willTerminate()
{
    int a;
    printf("\n\n\n\nWanna do it again? \n(1) for yes\n(0) for no\n ");
    scanf(" %d", &a);

    return !(a == 1);
}

int main()
{
    printf("You type the number, the operation the other number. I calculate.");

    int times = 0;
    while (1)
    {
        times++;
        calculatorUsecase(times);

        if (willTerminate())
        {
            system("cls");
            printf("Simple calculator, by Keisy Daniel rm93903...\n\n\n");
            break;
        }
    }

    return 0;
}
