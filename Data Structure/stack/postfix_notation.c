#include <stdio.h>
#include <string.h>
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

precedence stack[MAX_SIZE];
char expr[MAX_SIZE];
int top = 0;

static int isp[] = {0, 17, 12, 12, 13, 13, 13, 0};
static int icp[] = {18, 17, 12, 12, 13, 13, 13, 0};

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

void push(precedence token)
{ //삽입
    if (isfull())
    {
        return;
    }
    stack[++top] = token;
}

precedence pop()
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
    case '(':
        return lparen;
    case ')':
        return rparen;
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

void print_token(precedence token)
{
    switch (token)
    {
    case lparen:
        break;

    case rparen:
        break;

    case plus:
        printf("+");
        break;

    case minus:
        printf("-");
        break;

    case divide:
        printf("/");
        break;

    case times:
        printf("*");
        break;

    case mod:
        printf("%%");
        break;

    case eos:
        break;
    }
}

int main()
{
    gets(expr);
    stack[0]=eos;

    for (char *i = expr;i<expr+strlen(expr); i++)
    {
        precedence token = get_token(i);
        if (token == operand)
        {
            printf("%c", *i);
        }
        else if(token==rparen){
            while(isp[stack[top]]!=lparen){
                print_token(pop());
            }
            pop();
        }
        else
        {
            while (isp[stack[top]] >= icp[token])
            {
                if(stack[top]==eos){
                    break;
                }
                print_token(pop());
            }
            push(token);
        }
    }

    return 0;
}