#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

/* ջ�ķ�װ */
typedef int Status;
typedef char Elemtype;

typedef struct Node{
    Elemtype data;
    struct Node *next;
}Node, *LinkStackPtr;

typedef struct
{
    Node *top;
    int count;
}LinkStack;

LinkStack *InitStack()
{
    LinkStack *isStack = (LinkStack*) malloc(sizeof (LinkStack));
    if(isStack != NULL)
    {
        isStack->top = NULL;
        isStack->count = 0;
    }
    return isStack;
}

Status Push(LinkStack *S, Elemtype e)
{
    Node *p ;
    p = (Node*) malloc(sizeof (Node));
    p->data = e;
    p->next = S->top;
    S->top = p;
    S->count++;

    return OK;
}

Node *Pop(LinkStack *S)
{
    if(!S->top)
        return NULL;
    Node *top = S->top;
    S->top = S->top->next;
    S->count--;
    return top;
}

Node *GetTop(LinkStack *S)
{
    if(!S->top)
        return NULL;
    return S->top;
}

Status EmptyStack(LinkStack *S)
{
    return S->count == 0 ? TRUE : FALSE;

}

/* ��׺ת��׺������װ */

char buffer[256] = {0};
/* ������ */
void char_put(char ch)
{
    static int index = 0;
    buffer[index++] = ch;
}

int Priority(char ch)
{
    int ret = 0;
    switch (ch)
    {
        case '+':
        case '-':
            ret = 1;
            break;
        case '*':
        case '/':
            ret = 2;
            break;
        default:
            break;
    }
    return ret;
}

Status is_number(char ch)
{
    return ((ch >= '0') && (ch <= '9'));
}

Status is_operator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

Status is_left(char ch)
{
    return (ch == '(');
}

Status is_right(char ch)
{
    return (ch == ')');
}

Status Transform(char str[])
{
    LinkStack *isStack = InitStack();
    int i = 0;
    char Top;

    while(str[i] != '\0')
    {
        if(is_number(str[i]) == TRUE)
        {
            if(is_number(str[i+1]) == TRUE)
                char_put(str[i]);
            else
            {
                char_put(str[i]);
                char_put(' ');
            }
        }
        else if(is_operator(str[i]) == TRUE)
        {
            if(str[i+1] == '0' && str[i] == '/')
            {
                printf("ILLEAGE\n");
                return FALSE;
            }
            if(EmptyStack(isStack) == 0)
            {
                while(EmptyStack(isStack) == 0 && Priority(str[i]) <= Priority(GetTop(isStack)->data))
                {
                    char_put(Pop(isStack)->data);
                    char_put(' ');
                }
            }
            Push(isStack,str[i]);
        }
        else if(is_left(str[i]))
        {
            Push(isStack, str[i]);
        }
        else if(is_right(str[i]))
        {
            while(is_left(GetTop(isStack)->data) != TRUE)
            {
                char_put(Pop(isStack)->data);
                if(EmptyStack(isStack) == TRUE)
                {
                    printf("û��ƥ�䵽������\n");
                    return -1;
                }
            }

            Pop(isStack);
        }
        else
        {
            printf("�ֲ���ʶ����ַ�\n");
            return -1;
        }

        i++;
    }
    if(str[i] == '\0')
    {
        while(EmptyStack(isStack) == 0)
        {
            if(GetTop(isStack)->data == '(')
            {
                printf("��û��ƥ�䵽�ģ�ȱʧ��\n");
                return -1;
            }
            char_put(Pop(isStack)->data);
        }
    }
    else
    {
        printf("����û�����\n");
    }
    return OK;
}
int main()
{
    char str[1024] = {0};
    printf("����������������ʽ:\n");
    scanf("%s",str);
    int number = Transform(str);
    if(number == -1)
    {
        printf("���ʽ������\n");
    }
    else if(number == 1)
    {
        printf("ת����ı��ʽ��%s\n", buffer);
    }
    else
    {
        return 0;
    }
}
