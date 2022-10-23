#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef enum
{
    lparen,
    rparen,
    plus,
    minus,
    times,
    divide,
    mod,
    eos,
    operand
} precedence;

int stack[MAX_SIZE];
char expr[MAX_SIZE];
int top = -1;

int isempty()
{ //비어있는 지 검사
    if (top < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int isfull()
{ //가득 차 있는 지 검사
    if (top >= MAX_SIZE - 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void push(int op)
{ //삽입
    if (isfull())
    {
        return;
    }
    stack[++top] = op;
}

int pop()
{ //삭제
    if (top == -1)
    {
        return isempty();
    }
    return stack[top--];
}

precedence get_token(char *symbol)
{
    switch (*symbol)
    {
    case '+':
        return plus;
    case '-':
        return minus;
    case '/':
        return divide;
    case '*':
        return times;
    case '%':
        return mod;
    case ' ':
        return eos;
    default:
        return operand;
    }
}

void cal(precedence token)
{
    switch (token)
    {
    case plus:
        push(pop() + pop());
        break;

    case minus:
        push(pop() - pop());
        break;

    case divide:
        push(pop() / pop());
        break;

    case times:
        push(pop() * pop());
        break;

    case mod:
        push(pop() % pop());
        break;
    }
}

void print_stack(){
    printf("stack:");
    for(int i=0;i<=top;i++){
        printf("%d ",stack[i]);
    }
    printf("\n");
}

int main()
{
    gets(expr);

    for (char *i = expr; i < expr + strlen(expr); i++)
    {
        precedence token = get_token(i);
        if (token == eos)
        {
            break;
        }
        else if (token == operand)
        {
            push((*i-'0'));
            print_stack();
        }
        else
        {
            cal(token);
            print_stack();
        }
    }

    printf("%d",pop());

    return 0;
}