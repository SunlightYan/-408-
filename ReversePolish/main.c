#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

/* 栈的封装 */
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

// 初始化栈，返回栈结构
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
// 压栈
Status Push(LinkStack *S, Elemtype e)
{
    Node *p ;
    p = (Node*) malloc(sizeof (Node));  // 压栈节点空间分配
    p->data = e;
    p->next = S->top;                // 将压栈节点的指针指向栈顶
    S->top = p;
    S->count++;

    return OK;
}

// 出栈
Node *Pop(LinkStack *S)
{
    if(!S->top)
        return NULL;
    Node *top = S->top;
    S->top = S->top->next;
    S->count--;
    return top;
}

// 获取栈顶元素指针
Node *GetTop(LinkStack *S)
{
    if(!S->top)
        return NULL;
    return S->top;
}

// 判断是否为空栈
Status EmptyStack(LinkStack *S)
{
    return S->count == 0 ? TRUE : FALSE;

}

/* 中缀转后缀函数封装 */

char buffer[256] = {0};
/* 结果存放 */
void char_put(char ch)
{
    static int index = 0;
    buffer[index++] = ch;
}

// 优先级判断
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

// 判断是否为数字
Status is_number(char ch)
{
    return ((ch >= '0') && (ch <= '9'));
}

// 判断是否为操作符
Status is_operator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// 判断是否为左括号
Status is_left(char ch)
{
    return (ch == '(');
}

// 判断是否为右括号
Status is_right(char ch)
{
    return (ch == ')');
}

// 中缀转后缀函数
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
                    printf("没有匹配到左括号\n");
                    return -1;
                }
            }

            Pop(isStack);
        }
        else
        {
            printf("又不能识别的字符\n");
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
                printf("有没有匹配到的（缺失）\n");
                return -1;
            }
            char_put(Pop(isStack)->data);
        }
    }
    else
    {
        printf("遍历没有完成\n");
    }
    return OK;
}

// 符号判断结果
int Express(int left, int right, char op)
{
    switch(op)
    {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            if(right == 0)
                return 999;
            return left / right;
        default:
            break;
    }
    return -1;
}
// 获取链栈长度
int GetSize(LinkStack *S)
{
    return S->count;
}

// 计算后缀表达式
int calculate(char str[])
{
    LinkStack *S = InitStack();
    int i = 0;
    while(str[i] != '\0')
    {
        char a[6] = {0};
        int index = 0;
        if(is_number(str[i]))
        {
            while(is_number(str[i]))
            {
                a[index] = str[i];
                index++;
                i++;
            }
            Push(S, atoi(a));
        }
        else if(is_operator(str[i]))
        {
            int right = Pop(S)->data;
            int left = Pop(S)->data;
            int ret = Express(left, right, str[i]);
            if(ret == 999)
            {
                printf("ILLEAGE\n");
                return 999;
            }
            Push(S,ret);
        }
        else if(str[i] == ' ')  // 多位数遍历 跳过即可
        {

        }
        else
        {
            printf("error");
            break;
        }
        i++;
    }
    if(str[i] == '\0' && GetSize(S))
    {
        return GetTop(S)->data;
    }
    return 0;
}
int main()
{
    char str[1024] = {0};
    printf("请输入四则运算表达式:\n");
    scanf("%s",str);
    int number = Transform(str);
    if(number == -1)
    {
        printf("表达式表达错误\n");
    }
    else if(number == 1)
    {
        printf("转化后的表达式：%s\n", buffer);
    }
    else
    {
        return 0;
    }

    int result = calculate(buffer);
    if(result == 999)
        return 0;
    printf("计算结果为：%d", result);
}
