/* 项目：顺序表的实现
 *
 *
 *
 *
 * */
#include "stdio.h"

#include "stdlib.h"
#include "math.h"
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20          /* 存储空间初始分配量 */
typedef int ElemType;       /* ElemType类型根据实际情况而定，这里假设为int */
typedef struct
{
    ElemType data[MAXSIZE]; /* 数组，存储数据元素 */
    int length;             /* 线性表当前长度 */
}SqList;

typedef int Status;         /* Status是函数的类型,其值是函数结果状态代码，如OK等 */


Status visit(ElemType c)
{
    printf("%d ",c);
    return OK;
}

/* 初始化顺序线性表 */
Status InitList(SqList *L)
{
    L->length=0;
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(SqList L)
{
    if(L.length==0)
        return TRUE;
    else
        return FALSE;
}

/* 初始条件：顺序线性表L已存在。操作结果：将L重置为空表 */
Status ClearList(SqList *L)
{
    L->length=0;
    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(SqList L)
{
    return L.length;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值,注意i是指位置，第1个位置的数组是从0开始 */
Status GetElem(SqList L,int i,ElemType *e)
{
    if(L.length==0 || i<1 || i>L.length)
        return ERROR;
    *e=L.data[i-1];

    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
/* 时间复杂度: 最好O(1)；最坏O(n)；平均O(n); */
int LocateElem(SqList L,ElemType e)
{
    int i;
    if (L.length==0)
        return 0;
    for(i=0;i<L.length;i++)
    {
        if (L.data[i]==e)
            break;
    }
    if(i>=L.length)
        return 0;

    return i+1;
}


/* 初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/*操作步骤:
 * 一、判断顺序表是否满
 * 二、判断插入位置是否正确
 * 三、若插入位置不在表尾，则移动插入位置i-1及其之后的元素位置
 * 四、将新元素插入 i-1 位置 ，并将顺序表长度加一
 * 五、返回是否插入成功状态
 * */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
/* 时间复杂度: 最好O(1)；最坏O(n)；平均O(n); */
Status ListInsert(SqList *L,int i,ElemType e)
{
    int k;
    if (L->length == MAXSIZE)  /* 顺序线性表已经满 */
        return ERROR;
    if (i<1 || i>L->length+1)/* 当i比第一位置小或者比最后一位置后一位置还要大时 */
        return ERROR;

    if (i<=L->length)        /* 若插入数据位置不在表尾 */
    {
        for(k=L->length-1;k>=i-1;k--)  /* 将要插入位置之后的数据元素向后移动一位 */
            L->data[k+1]=L->data[k];
    }
    L->data[i-1]=e;          /* 将新元素插入 */
    L->length++;

    return OK;
}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/*操作步骤:
 * 一、判断顺序表是否为空
 * 二、判断删除位置是否正确
 * 三、将删除的元素赋值给需要返回的元素e
 * 四、若插入位置不在表尾，则将下标为i的元素向前移动一格
 * 五、顺序表长度减一
 * 六、返回是否删除成功
 * */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
/* 时间复杂度: 最好O(1)；最坏O(n)；平均O(n); */
Status ListDelete(SqList *L,int i,ElemType *e)
{
    int k;
    if (L->length==0)               /* 线性表为空 */
        return ERROR;
    if (i<1 || i>L->length)         /* 删除位置不正确 */
        return ERROR;
    *e=L->data[i-1];
    if (i<L->length)                /* 如果删除不是最后位置 */
    {
        for(k=i;k<L->length;k++)/* 将删除位置后继元素前移 */
            L->data[k-1]=L->data[k];
    }
    L->length--;
    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(SqList L)
{
    int i;
    for(i=0;i<L.length;i++)
        visit(L.data[i]);
    printf("\n");
    return OK;
}

/*将所有的在线性表Lb中但不在La中的数据元素插入到La中*/
void unionL(SqList *La,SqList Lb)
{
    int La_len,Lb_len,i;
    ElemType e;                        /*声明与La和Lb相同的数据元素e*/
    La_len=ListLength(*La);            /*求线性表的长度 */
    Lb_len=ListLength(Lb);
    for (i=1;i<=Lb_len;i++)
    {
        GetElem(Lb,i,&e);              /*取Lb中第i个数据元素赋给e*/
        if (!LocateElem(*La,e))        /*La中不存在和e相同数据元素*/
            ListInsert(La,++La_len,e); /*插入*/
    }
}
         /* ------------  线性表算法题目代码实验   ------------------ */



/* 第一道：从顺序表中删除最小元素，并返回删除的值
 * 操作过程：
 * 一、判断顺序表是否为空
 * 二、循环找到最小值及其位置
 * 三、返回是否删除成功
 * */

Status Del_Min(SqList *L, ElemType *min)
{
    int pos;                // 定义最小值位置变量，用于保存位置信息
    if(L->length == 0)      // 判断线性表是否为空
        return ERROR;
    *min = L->data[0];      // 将最小值先设置为顺序表的表头
    for(int i = 1; i < L->length; i++)  // 循环判断找到最小值
    {
        if(L->data[i] < (*min))
        {
            *min = L->data[i];
            pos = i;
        }
    }
    ListDelete(L,pos,min);     // 删除最小值，并将最小值通过指针返回
    return OK;
}

/* 第二道：将顺序表所有元素逆序，要求空间复杂度为O(1)
 * 操作过程：
 * 一、判断顺序表是否为空
 * 二、循环交换位置，循环一半就可
 * 三、返回是否交换成功
 * */
Status Reverse(SqList *L)
{
    ElemType temp;          // 临时保存顺序表变量
    if(L->length == 0)
        return ERROR;
    for(int i = 0; i < (L->length/2); i++)          // 循环交换顺序表前一半和后一半
    {
        temp = L->data[i];
        L->data[i] = L->data[L->length-i-1];
        L->data[L->length-i-1] = temp;
    }
    return OK;
}

/* 第三道：删除所有元素值为x的元素，时间复杂度为O(N)，空间复杂度为O（1）
 * 操作过程：
 * 一、判断顺序表是否为空
 * 二、循环判断是否为等于x，若等于则将表尾元素填入该位置
 * 三、返回是否成功
 * */

Status Del_X(SqList *L, ElemType e)
{
    int k = 0;          // 记录有多少个值不等于X的元素个数
    for(int i = 0; i < L->length; i++)
    {
        if(L->data[i] != e)
        {
            L->data[k] = L->data[i];
            k++;
        }
    }
    L->length = k;
    return OK;
}


Status Del_X2(SqList *L, ElemType e)
{
    int k = 0;          // 记录有多少个等于X的元素
    for(int i = 0; i < L->length; i++)
    {
        if(L->data[i] == e)
            k++;
        else
            L->data[i-k] = L->data[i];
    }
    L->length = L->length - k;
    return OK;
}
/* 第四、五道：删除所有元素值在s和t之间的元素，若s、t不合理或顺序表为空，则显示出错信息并退出运行
 * 操作过程：
 * 一、将顺序表通过快排变成有序表
 * 二、循环判断s和t的位置，并计算出包含的元素个数，将包含在其中的元素删除
 * 三、返回是否成功
 * */
Status QuickSort(SqList *L, int left, int right)
{
    int i,j,position;  // 定义左右游标和标志位
    if(left > right)
        return ERROR;
    position = L->data[left]; // 将最左端的元素作为起始标志位
    i = left;
    j = right;
    if(i < j)   // 当 i < j 时循环判断
    {
        while (i != j)
        {
            while ((L->data[j] >= position) && (i < j))j--;   // 判断最右端的元素将小于position的元素与左端的第一个大于position的元素交换
            L->data[i] = L->data[j];
            while ((L->data[i] <= position) && (i < j))i++;   // 同理交换左端大于position和右端小于position的元素
            L->data[j] = L->data[i];
        }

        L->data[i] = position;  // 将position放置在中间
        QuickSort(L,left,i-1); // 递归左端的数列
        QuickSort(L,i+1,right); // 递归右端数列
    }
    return OK;
}


Status Del_sTOt(SqList *L,ElemType s, ElemType t)
{
    int left,right,k,cur;
    left = 0;
    cur = 0;
    right = L->length-1;
    if(L->length == 0 || (s > t))
        return ERROR;
    QuickSort(L,0,L->length-1);
    while(L->data[left] < s) left++;
    while(L->data[right] > t) right--;

    k = right - left + 1;
    for(int i = right; i < L->length; i++)
    {
        cur++;
        L->data[left + cur - 1] = L->data[right + cur];
    }
    L->length = L->length-k;

    return OK;
}

Status Del_sTOt2(SqList *L,ElemType s, ElemType t)
{
    int i,k=0;
    if(L->length == 0 || (s > t))
        return ERROR;

    for(i = 0; i < L->length; i++)
    {
        if(L->data[i] >= s && L->data[i] <= t)
            ++k;
        else
            L->data[i-k] = L->data[i];
    }
    L->length = L->length - k;
    return OK;

}
/* 第六道：从有序表中删除所有值重复的元素
 * 操作过程：
 * 一、将第一个元素视为非重复的元素
 * 二、依次判断后面元素是否与其重复，若重复前移
 * 三、顺序表长度为i+1
 * 四、返回是否成功
 * */

Status Del_Same(SqList *L)
{
    if(L->length == 0)
        return ERROR;
    int i,j;
    for(i = 0,j = 1; j < L->length; j++)
    {
        if(L->data[i] != L->data[j])
            L->data[++i] = L->data[j];
    }
    L->length = i+1;
    return OK;
}

/* 第七道：将两个有序表合并
 * 操作过程：
 * 一、判断两个有序表合并后长度是否大于顺序表允许长度
 * 二、依次判断La和Lb的元素大小
 * 三、最后将La或Lb未进入Lc中的放入Lc中，将Lc长度设置为k
 * 四、返回是否成功
 * */

Status Merge(SqList La, SqList Lb, SqList *Lc)
{
    if(La.length + Lb.length > Lc->length)
        return ERROR;
    int i=0,j=0,k=0;
    while(i < La.length && j < Lb.length)
    {
        if(La.data[i] < Lb.data[j])
            Lc->data[k++] = La.data[i++];
        else
            Lc->data[k++] = Lb.data[j++];
    }

    while(i < La.length)
        Lc->data[k++] = La.data[i++];
    while(i < Lb.length)
        Lc->data[k++] = Lb.data[j++];
    Lc->length = k;
    return OK;
}

/* 第八道：交换两个顺序表内容
 * 操作过程：
 * 一、将第一个元素视为非重复的元素
 * 二、依次判断后面元素是否与其重复，若重复前移
 * 三、顺序表长度为i+1
 * 四、返回是否成功
 * */

Status Reverse_Array(ElemType A[], int left, int right, int arraySize)
{
    int temp;
    if(left > right || right >= arraySize)
        return ERROR;
    int mid = (left + right) / 2;
    for(int i = 0; i <= mid - left; i++)
    {
        temp = A[left + i];
        A[left + i] = A[right - i];
        A[right - i] = temp;
    }
    return OK;
}

Status Exchange(ElemType A[], int m, int n, int arraySize)
{
    Reverse_Array(A,0,m+n-1,arraySize);
    Reverse_Array(A,0,n-1,arraySize);
    Reverse_Array(A,n,m+n-1,arraySize);

    return OK;
}

Status Test_Exchange()
{
    int m = 5, n = 6;
    ElemType A[m+n];
    for(int i = 0; i < m+n; i++)
    {
        A[i] = i;
    }
    printf("输出逆序前的数组：");
    for(int i = 0; i < m+n; i++)
        printf("%d ", A[i]);
    Exchange(A,m,n,m+n);
    printf("输出逆序后的数组：");
    for(int i = 0; i < m+n; i++)
        printf("%d ", A[i]);
    printf("\n");
    return OK;
}

/* 第九道：在最少时间内找到值为X的元素，若找到则将其与后继元素交换位置，若找不到则将其插入表中使其依然递增
 * 操作过程：
 * 一、二分查找
 * 二、找到就交换位置
 * 三、未找到就插入元素
 * 四、返回是否成功
 * */

Status SearchExchangeInsert(ElemType A[], ElemType x, int n)
{
    int i;
    int left, right, mid;
    int temp;
    /* 二分查找 */
    left = 0;
    right = n-1;
    while(left <= right)
    {
        mid = (left+right)/2;
        if(x == A[mid])
            break;
        else if(x < A[mid])
            right = mid-1;
        else if(x > A[mid])
            left = mid+1;
    }
    /* 如果找到x并且位置不在最后一个位置，就跟后继元素交换位置 */
    if(A[mid] == x && mid != n-1)
    {
        temp = A[mid];
        A[mid] = A[mid+1];
        A[mid+1] = temp;
    }
    /* 如果没找到x，则将其插入right+1位置 */
    if(left > right)
    {
        for(i = n-1; i > right; i--)
        {
            A[i+1] = A[i];
        }

        A[i+1] = x;
    }
    printf("插入后：");
    for(i = n; i >= 0; i--)
    {
        printf("%d ",A[i]);
    }
    return OK;
}

Status Test_SearchExchangeInsert()
{
    ElemType A[7] = {1,3,5,7,9,10};
    printf("输出逆序前的数组：");
    for(int i = 0; i < 6; i++)
        printf("%d ", A[i]);
    SearchExchangeInsert(A,4,6);
    printf("输出逆序后的数组：");
    for(int i = 0; i <= 6; i++)
        printf("%d ", A[i]);
    printf("\n");
    return OK;
}

/* 第十道：循环左移R位
 * 操作过程：
 * 一、二分查找
 * 二、找到就交换位置
 * 三、未找到就插入元素
 * 四、返回是否成功
 * */
Status Reverse_Left(ElemType A[], int r, int arraySize)
{

}
int main()
{

    SqList L;
    SqList Lb;

    ElemType e;
    Status i;
    int j,k;
    int min;
    i=InitList(&L);
    printf("初始化L后：L.length=%d\n",L.length);
    for(j=1;j<=5;j++)
        i=ListInsert(&L,1,j);
    printf("在L的表头依次插入1～5后：L.data=");
    ListTraverse(L);

    printf("L.length=%d \n",L.length);
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    i=ClearList(&L);
    printf("清空L后：L.length=%d\n",L.length);
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    for(j=1;j<=10;j++)
        ListInsert(&L,j,j);
    printf("在L的表尾依次插入1～10后：L.data=");
    ListTraverse(L);

    printf("L.length=%d \n",L.length);

    ListInsert(&L,1,0);
    printf("在L的表头插入0后：L.data=");
    ListTraverse(L);
    printf("L.length=%d \n",L.length);

    GetElem(L,5,&e);
    printf("第5个元素的值为：%d\n",e);
    for(j=3;j<=4;j++)
    {
        k=LocateElem(L,j);
        if(k)
            printf("第%d个元素的值为%d\n",k,j);
        else
            printf("没有值为%d的元素\n",j);
    }


    k=ListLength(L); /* k为表长 */
    for(j=k+1;j>=k;j--)
    {
        i=ListDelete(&L,j,&e); /* 删除第j个数据 */
        if(i==ERROR)
            printf("删除第%d个数据失败\n",j);
        else
            printf("删除第%d个的元素值为：%d\n",j,e);
    }
    printf("依次输出L的元素：");
    ListTraverse(L);

    j=5;
    ListDelete(&L,j,&e); /* 删除第5个数据 */
    printf("删除第%d个的元素值为：%d\n",j,e);

    printf("依次输出L的元素：");
    ListTraverse(L);

    //构造一个有10个数的Lb
    i=InitList(&Lb);
    for(j=6;j<=15;j++)
        i=ListInsert(&Lb,1,j);

    unionL(&L,Lb);

    printf("依次输出合并了Lb的L的元素：");
    ListTraverse(L);

    Del_Min(&L,&min);
    printf("删除最小值，最小值为: %d\n", min);
    Del_Min(&L,&min);
    printf("删除最小值，最小值为: %d\n", min);

    printf("依次输出合并了Lb的L的元素：");
    ListTraverse(L);

    Reverse(&L);
    printf("依次输出合并了Lb的L的元素：");
    ListTraverse(L);

    e = 5;
    ListInsert(&L,6,e);
    ListInsert(&L,6,e);
    ListInsert(&L,6,e);
    printf("依次输出添加了5的L的元素：");
    ListTraverse(L);
    Del_X(&L, e);
    printf("依次输出删除了5的L的元素：");
    ListTraverse(L);


    Del_sTOt(&L,3,6);
    printf("依次输出删除3-6后的元素：");
    ListTraverse(L);

    ListInsert(&L,4,5);
    ListInsert(&L,4,5);
    ListInsert(&L,4,5);
    printf("依次输出添加了5的L的元素：");
    ListTraverse(L);

    Del_Same(&L);
    printf("依次输出删除相同元素后的元素：");
    ListTraverse(L);

    Test_Exchange();

    Test_SearchExchangeInsert();
    return 0;
}

