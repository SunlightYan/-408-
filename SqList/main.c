/* ��Ŀ��˳����ʵ��
 *
 *
 *
 *
 * */
#include "stdio.h"

#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "string.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20          /* �洢�ռ��ʼ������ */
typedef int ElemType;       /* ElemType���͸���ʵ������������������Ϊint */
typedef struct
{
    ElemType data[MAXSIZE]; /* ���飬�洢����Ԫ�� */
    int length;             /* ���Ա�ǰ���� */
}SqList;

typedef int Status;         /* Status�Ǻ���������,��ֵ�Ǻ������״̬���룬��OK�� */


Status visit(ElemType c)
{
    printf("%d ",c);
    return OK;
}

/* ��ʼ��˳�����Ա� */
Status InitList(SqList *L)
{
    L->length=0;
    return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������LΪ�ձ��򷵻�TRUE�����򷵻�FALSE */
Status ListEmpty(SqList L)
{
    if(L.length==0)
        return TRUE;
    else
        return FALSE;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ������������L����Ϊ�ձ� */
Status ClearList(SqList *L)
{
    L->length=0;
    return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڡ��������������L������Ԫ�ظ��� */
int ListLength(SqList L)
{
    return L.length;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/* �����������e����L�е�i������Ԫ�ص�ֵ,ע��i��ָλ�ã���1��λ�õ������Ǵ�0��ʼ */
Status GetElem(SqList L,int i,ElemType *e)
{
    if(L.length==0 || i<1 || i>L.length)
        return ERROR;
    *e=L.data[i-1];

    return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* �������������L�е�1����e�����ϵ������Ԫ�ص�λ�� */
/* ������������Ԫ�ز����ڣ��򷵻�ֵΪ0 */
/* ʱ�临�Ӷ�: ���O(1)���O(n)��ƽ��O(n); */
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


/* ��ʼ������˳�����Ա�L�Ѵ���,1��i��ListLength(L)�� */
/*��������:
 * һ���ж�˳����Ƿ���
 * �����жϲ���λ���Ƿ���ȷ
 * ����������λ�ò��ڱ�β�����ƶ�����λ��i-1����֮���Ԫ��λ��
 * �ġ�����Ԫ�ز��� i-1 λ�� ������˳����ȼ�һ
 * �塢�����Ƿ����ɹ�״̬
 * */
/* �����������L�е�i��λ��֮ǰ�����µ�����Ԫ��e��L�ĳ��ȼ�1 */
/* ʱ�临�Ӷ�: ���O(1)���O(n)��ƽ��O(n); */
Status ListInsert(SqList *L,int i,ElemType e)
{
    int k;
    if (L->length == MAXSIZE)  /* ˳�����Ա��Ѿ��� */
        return ERROR;
    if (i<1 || i>L->length+1)/* ��i�ȵ�һλ��С���߱����һλ�ú�һλ�û�Ҫ��ʱ */
        return ERROR;

    if (i<=L->length)        /* ����������λ�ò��ڱ�β */
    {
        for(k=L->length-1;k>=i-1;k--)  /* ��Ҫ����λ��֮�������Ԫ������ƶ�һλ */
            L->data[k+1]=L->data[k];
    }
    L->data[i-1]=e;          /* ����Ԫ�ز��� */
    L->length++;

    return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��ڣ�1��i��ListLength(L) */
/*��������:
 * һ���ж�˳����Ƿ�Ϊ��
 * �����ж�ɾ��λ���Ƿ���ȷ
 * ������ɾ����Ԫ�ظ�ֵ����Ҫ���ص�Ԫ��e
 * �ġ�������λ�ò��ڱ�β�����±�Ϊi��Ԫ����ǰ�ƶ�һ��
 * �塢˳����ȼ�һ
 * ���������Ƿ�ɾ���ɹ�
 * */
/* ���������ɾ��L�ĵ�i������Ԫ�أ�����e������ֵ��L�ĳ��ȼ�1 */
/* ʱ�临�Ӷ�: ���O(1)���O(n)��ƽ��O(n); */
Status ListDelete(SqList *L,int i,ElemType *e)
{
    int k;
    if (L->length==0)               /* ���Ա�Ϊ�� */
        return ERROR;
    if (i<1 || i>L->length)         /* ɾ��λ�ò���ȷ */
        return ERROR;
    *e=L->data[i-1];
    if (i<L->length)                /* ���ɾ���������λ�� */
    {
        for(k=i;k<L->length;k++)/* ��ɾ��λ�ú��Ԫ��ǰ�� */
            L->data[k-1]=L->data[k];
    }
    L->length--;
    return OK;
}

/* ��ʼ������˳�����Ա�L�Ѵ��� */
/* ������������ζ�L��ÿ������Ԫ����� */
Status ListTraverse(SqList L)
{
    int i;
    for(i=0;i<L.length;i++)
        visit(L.data[i]);
    printf("\n");
    return OK;
}

/*�����е������Ա�Lb�е�����La�е�����Ԫ�ز��뵽La��*/
void unionL(SqList *La,SqList Lb)
{
    int La_len,Lb_len,i;
    ElemType e;                        /*������La��Lb��ͬ������Ԫ��e*/
    La_len=ListLength(*La);            /*�����Ա�ĳ��� */
    Lb_len=ListLength(Lb);
    for (i=1;i<=Lb_len;i++)
    {
        GetElem(Lb,i,&e);              /*ȡLb�е�i������Ԫ�ظ���e*/
        if (!LocateElem(*La,e))        /*La�в����ں�e��ͬ����Ԫ��*/
            ListInsert(La,++La_len,e); /*����*/
    }
}
         /* ------------  ���Ա��㷨��Ŀ����ʵ��   ------------------ */



/* ��һ������˳�����ɾ����СԪ�أ�������ɾ����ֵ
 * �������̣�
 * һ���ж�˳����Ƿ�Ϊ��
 * ����ѭ���ҵ���Сֵ����λ��
 * ���������Ƿ�ɾ���ɹ�
 * */

Status Del_Min(SqList *L, ElemType *min)
{
    int pos;                // ������Сֵλ�ñ��������ڱ���λ����Ϣ
    if(L->length == 0)      // �ж����Ա��Ƿ�Ϊ��
        return ERROR;
    *min = L->data[0];      // ����Сֵ������Ϊ˳���ı�ͷ
    for(int i = 1; i < L->length; i++)  // ѭ���ж��ҵ���Сֵ
    {
        if(L->data[i] < (*min))
        {
            *min = L->data[i];
            pos = i;
        }
    }
    ListDelete(L,pos,min);     // ɾ����Сֵ��������Сֵͨ��ָ�뷵��
    return OK;
}

/* �ڶ�������˳�������Ԫ������Ҫ��ռ临�Ӷ�ΪO(1)
 * �������̣�
 * һ���ж�˳����Ƿ�Ϊ��
 * ����ѭ������λ�ã�ѭ��һ��Ϳ�
 * ���������Ƿ񽻻��ɹ�
 * */
Status Reverse(SqList *L)
{
    ElemType temp;          // ��ʱ����˳������
    if(L->length == 0)
        return ERROR;
    for(int i = 0; i < (L->length/2); i++)          // ѭ������˳���ǰһ��ͺ�һ��
    {
        temp = L->data[i];
        L->data[i] = L->data[L->length-i-1];
        L->data[L->length-i-1] = temp;
    }
    return OK;
}

/* ��������ɾ������Ԫ��ֵΪx��Ԫ�أ�ʱ�临�Ӷ�ΪO(N)���ռ临�Ӷ�ΪO��1��
 * �������̣�
 * һ���ж�˳����Ƿ�Ϊ��
 * ����ѭ���ж��Ƿ�Ϊ����x���������򽫱�βԪ�������λ��
 * ���������Ƿ�ɹ�
 * */

Status Del_X(SqList *L, ElemType e)
{
    int k = 0;          // ��¼�ж��ٸ�ֵ������X��Ԫ�ظ���
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
    int k = 0;          // ��¼�ж��ٸ�����X��Ԫ��
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
/* ���ġ������ɾ������Ԫ��ֵ��s��t֮���Ԫ�أ���s��t�������˳���Ϊ�գ�����ʾ������Ϣ���˳�����
 * �������̣�
 * һ����˳���ͨ�����ű�������
 * ����ѭ���ж�s��t��λ�ã��������������Ԫ�ظ����������������е�Ԫ��ɾ��
 * ���������Ƿ�ɹ�
 * */
Status QuickSort(SqList *L, int left, int right)
{
    int i,j,position;  // ���������α�ͱ�־λ
    if(left > right)
        return ERROR;
    position = L->data[left]; // ������˵�Ԫ����Ϊ��ʼ��־λ
    i = left;
    j = right;
    if(i < j)   // �� i < j ʱѭ���ж�
    {
        while (i != j)
        {
            while ((L->data[j] >= position) && (i < j))j--;   // �ж����Ҷ˵�Ԫ�ؽ�С��position��Ԫ������˵ĵ�һ������position��Ԫ�ؽ���
            L->data[i] = L->data[j];
            while ((L->data[i] <= position) && (i < j))i++;   // ͬ������˴���position���Ҷ�С��position��Ԫ��
            L->data[j] = L->data[i];
        }

        L->data[i] = position;  // ��position�������м�
        QuickSort(L,left,i-1); // �ݹ���˵�����
        QuickSort(L,i+1,right); // �ݹ��Ҷ�����
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
/* �����������������ɾ������ֵ�ظ���Ԫ��
 * �������̣�
 * һ������һ��Ԫ����Ϊ���ظ���Ԫ��
 * ���������жϺ���Ԫ���Ƿ������ظ������ظ�ǰ��
 * ����˳�����Ϊi+1
 * �ġ������Ƿ�ɹ�
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

/* ���ߵ��������������ϲ�
 * �������̣�
 * һ���ж����������ϲ��󳤶��Ƿ����˳���������
 * ���������ж�La��Lb��Ԫ�ش�С
 * �������La��Lbδ����Lc�еķ���Lc�У���Lc��������Ϊk
 * �ġ������Ƿ�ɹ�
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

/* �ڰ˵�����������˳�������
 * �������̣�
 * һ������һ��Ԫ����Ϊ���ظ���Ԫ��
 * ���������жϺ���Ԫ���Ƿ������ظ������ظ�ǰ��
 * ����˳�����Ϊi+1
 * �ġ������Ƿ�ɹ�
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
    printf("�������ǰ�����飺");
    for(int i = 0; i < m+n; i++)
        printf("%d ", A[i]);
    Exchange(A,m,n,m+n);
    printf("������������飺");
    for(int i = 0; i < m+n; i++)
        printf("%d ", A[i]);
    printf("\n");
    return OK;
}

/* �ھŵ���������ʱ�����ҵ�ֵΪX��Ԫ�أ����ҵ���������Ԫ�ؽ���λ�ã����Ҳ�������������ʹ����Ȼ����
 * �������̣�
 * һ�����ֲ���
 * �����ҵ��ͽ���λ��
 * ����δ�ҵ��Ͳ���Ԫ��
 * �ġ������Ƿ�ɹ�
 * */

Status SearchExchangeInsert(ElemType A[], ElemType x, int n)
{
    int i;
    int left, right, mid;
    int temp;
    /* ���ֲ��� */
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
    /* ����ҵ�x����λ�ò������һ��λ�ã��͸����Ԫ�ؽ���λ�� */
    if(A[mid] == x && mid != n-1)
    {
        temp = A[mid];
        A[mid] = A[mid+1];
        A[mid+1] = temp;
    }
    /* ���û�ҵ�x���������right+1λ�� */
    if(left > right)
    {
        for(i = n-1; i > right; i--)
        {
            A[i+1] = A[i];
        }

        A[i+1] = x;
    }
    printf("�����");
    for(i = n; i >= 0; i--)
    {
        printf("%d ",A[i]);
    }
    return OK;
}

Status Test_SearchExchangeInsert()
{
    ElemType A[7] = {1,3,5,7,9,10};
    printf("�������ǰ�����飺");
    for(int i = 0; i < 6; i++)
        printf("%d ", A[i]);
    SearchExchangeInsert(A,4,6);
    printf("������������飺");
    for(int i = 0; i <= 6; i++)
        printf("%d ", A[i]);
    printf("\n");
    return OK;
}

/* ��ʮ����ѭ������Rλ  ʱ�临�Ӷ�λO(n)���ռ临�Ӷ�λO(1)
 * �������̣�
 * һ��������
 * ��������ǰrλ��λ�ã�Ȼ������ʣ��λ�ã�������������
 * ������ɷ��سɹ�
 * */
Status Reverse_1(ElemType A[], int left, int right)
{
    int temp;
    int i = left, j = right;
    int mid = (left + right) / 2;
    for(int i = 0; i <= mid - left; i++)
    {
        temp = A[left+i];
        A[left+i] = A[right-i];
        A[right-i] = temp;
    }
    return OK;
}

Status Reverse_Left(ElemType A[], int r, int arraySize)
{
    Reverse_1(A, 0, r-1);
    Reverse_1(A, r, arraySize-1);
    Reverse_1(A, 0, arraySize-1);

    return OK;
}

Status Test_Reverse_Left()
{
    int r = 4;
    ElemType A[] = {1,2,3,4,5,6,7,8,9,10};
    printf("����%dλǰ: ", r);
    for(int i = 0; i < 10; i++)
        printf("%d ", A[i]);
    int arraySize = sizeof (A) / sizeof (ElemType);
    Reverse_Left(A,r,arraySize);
    printf("����%dλ��: ", r);
    for(int i = 0; i < 10; i++)
        printf("%d ", A[i]);
    printf("\n");
    return OK;
}

/* ��ʮһ������λ��
 * �������̣�
 * һ���ж�A����λ����B����λ���Ƿ���ȣ��������ֱ�ӷ��ظ���λ��
 * �����������ȣ���A����λ������B����λ������ȥB����λ�����²��֣���ȥA����λ����Ĳ���
 *              ��A����λ��С��B����λ������ȥB����λ����Ĳ��֣���ȥA����λ��С�Ĳ���
 * ����ѭ���������̣�ֱ��A��Bֻ��һ������Ϊֹ������A��B�����С���Ǹ�������λ��
 * �ġ����سɹ�
 * */

ElemType Mid_Array(ElemType A[], ElemType B[], int n)
{
    int A_start = 0, A_mid, A_end = n-1, B_start = 0, B_mid, B_end = n-1;
    while((A_start != A_end) || (B_start != B_end))  //�ж�A��B�Ƿ�ֻ��һ��Ԫ��
    {
        A_mid = (A_start + A_end) / 2;
        B_mid = (B_start + B_end) / 2;
        if(A[A_mid] == B[B_mid])   // ��A��B��ȣ��򷵻���λ��
            return A[A_mid];
        if(A[A_mid] < B[B_mid])
        {
            if((A_start + A_end)%2 == 0)    // A��Ԫ�ظ���λ������
            {
                A_start = A_mid;
                B_end = B_mid;
            }
            else
            {
                A_start = A_mid+1;
                B_end = B_mid;
            }

        }
        else
        {
            if((B_start + B_end)%2 == 0)
            {
                B_start = B_mid;
                A_end = A_mid;
            }
            else
            {
                B_start = B_mid+1;
                A_end = A_mid;
            }

        }
    }

    return A[A_start] > B[B_start] ? A[A_start] : B[B_start];
}

Status Test_Mid_Array()
{
    int mid;
    ElemType A[] = {1,2,5,7,9,10};
    ElemType B[] = {3,7,9,15,16,18};

    mid = Mid_Array(A, B, 6);
    printf("��λ����%d \n", mid);
    return OK;
}
/* ��ʮ������Ѱ����Ԫ��
 * �������̣�
 * һ�����������㷨
 * ����������ͬԪ�صļ��
 * �����жϼ���Ƿ������Ԫ�ظ�����һ��
 * �ġ����سɹ�
 * */
/* ��һ�ַ��� �������� O(nlogn) O(1) */
Status QuickSort_1(ElemType A[], int left, int right)
{
    int i,j,position;  // ���������α�ͱ�־λ
    if(left > right)
        return ERROR;
    position = A[left]; // ������˵�Ԫ����Ϊ��ʼ��־λ
    i = left;
    j = right;
    if(i < j)   // �� i < j ʱѭ���ж�
    {
        while (i != j)
        {
            while ((A[j] >= position) && (i < j))j--;   // �ж����Ҷ˵�Ԫ�ؽ�С��position��Ԫ������˵ĵ�һ������position��Ԫ�ؽ���
            A[i] = A[j];
            while ((A[i] <= position) && (i < j))i++;   // ͬ������˴���position���Ҷ�С��position��Ԫ��
            A[j] = A[i];
        }

        A[i] = position;  // ��position�������м�
        QuickSort_1(A,left,i-1); // �ݹ���˵�����
        QuickSort_1(A,i+1,right); // �ݹ��Ҷ�����
    }
    return OK;
}
ElemType Find_Main_Num(ElemType A[],int n)
{
    int low = 0, high = 1, count = 0, main_num;
    QuickSort_1(A,0,n);
    while(high < n)
    {
        if(A[low] == A[high])
        {
            high++;
            if(high - low > count)
            {
                count = high - low + 1;
                main_num = A[low];
            }
        }
        else
        {
            low = high;
            high++;
        }
    }
    if(count > n/2)
        return main_num;
    else
        return -1;
}
/* ��Ϊ��Ԫ�ش���һ������count������ȥ����Ԫ�غ���Ȼ����0 O(n) O(1) */
ElemType Find_Main_Num_2(ElemType A[], int n)
{
    int cur, count = 1;
    cur = A[0];
    for(int i = 0; i < n; i++)
    {
        if(A[i] == cur)
            count++;
        else
        {
            if(count > 0)
                count--;
            else
            {
                cur = A[i];
                count = 1;
            }
        }
    }
    if(count > 0)
    {
        for(int i = count = 0; i < n; i++)
        {
            if(A[i] == cur)
                count++;
        }
    }
    if(count > n/2)
        return cur;
    else
        return -1;
}
Status Test_Find_Main_Num()
{
    ElemType A[] = {1,2,5,5,5,5,5,5,5,7,7};
    int n = sizeof (A) / sizeof (ElemType);
    int main_num;
    main_num = Find_Main_Num(A,n);
    printf("��һ�ַ����õ�����Ԫ��Ϊ %d ", main_num);

    main_num = Find_Main_Num_2(A,n);
    printf("�ڶ��ַ����õ�����Ԫ��Ϊ %d \n", main_num);
    return OK;
}
/* ��ʮ������δ���ֶ�����С������
 * �������̣�
 * һ������һ����־���鸨�������ڱ�ע���ֵ�������
 * ������ֵ��0-n��Ԫ���ڸ��������б�־
 * ����ѭ�����ҵ�һ����־λΪ0�ģ�Ȼ�󷵻�ֵ
 * O(n)  O(n)
 * */
ElemType Find_Min_PositionNum(ElemType A[], int n)
{
    int i;
    int *flag;
    flag = (int *) malloc(sizeof (int) * n);
    memset(flag, 0, sizeof (int) * n);

    for(i = 0; i < n; i++)
    {
        if(A[i] > 0 && A[i] < n)
            flag[A[i]-1] = 1;
    }
    for(i = 0; i < n; i++)
    {
        if(!flag[i])
            break;
    }
    return i+1;
}

Status Test_Find_Min_PositionNum()
{
    int min;
    int A[] = {-3,1,3,4,5,6,7,9};
    int n = sizeof (A) / sizeof (int );
    min = Find_Min_PositionNum(A, n);

    printf("δ���ֵ���С������Ϊ%d \n", min);
    return OK;
}

/* ��ʮ�ĵ�����Ԫ����С����
 * �������̣�
 * һ��������룬�õ�D����������С��D�Ƚ����С�����
 * �����ҵ���Ԫ���е���Сֵ�����������Сֵ��ͼ�ҵ���С�ľ��룬һֱ��
 * ����ѭ�����ҵ�һ����־λΪ0�ģ�Ȼ�󷵻�ֵ
 * O(n)  O(n)
 * */
ElemType abs_(ElemType a)
{
    return a<0 ? -a : a;
}

ElemType xls_min(ElemType a, ElemType b, ElemType c)
{
    if(a<b && a<c)
        return OK;
    return FALSE;
}
ElemType Find_Min_Three(ElemType A[],ElemType B[], ElemType C[],int al, int bl, int cl)
{
    int i = 0, j = 0, k = 0, D_Min = INT_MAX, D;
    while(i<al && j<bl && k<cl && D_Min > 0)
    {
        D = abs(A[i]-B[j]) + abs(B[j] - C[k]) + abs_(C[k] - A[i]);
        if(D < D_Min)
            D_Min = D;
        if(xls_min(A[i],B[j],C[k]))
            i++;
        else if(xls_min(B[j],A[i],C[k]))
            j++;
        else
            k++;
    }
    return D_Min;
}

Status Test_Find_Min_Three()
{
    int a[] = {-1,0,9};
    int b[] = {-25,-10,10,11};
    int c[] = {2,9,17,30,41};
    int min;
    min = Find_Min_Three(a,b,c,3,4,5);
    printf("��Ԫ������СֵΪ%d \n", min);

    return OK;
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
    printf("��ʼ��L��L.length=%d\n",L.length);
    for(j=1;j<=5;j++)
        i=ListInsert(&L,1,j);
    printf("��L�ı�ͷ���β���1��5��L.data=");
    ListTraverse(L);

    printf("L.length=%d \n",L.length);
    i=ListEmpty(L);
    printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n",i);

    i=ClearList(&L);
    printf("���L��L.length=%d\n",L.length);
    i=ListEmpty(L);
    printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n",i);

    for(j=1;j<=10;j++)
        ListInsert(&L,j,j);
    printf("��L�ı�β���β���1��10��L.data=");
    ListTraverse(L);

    printf("L.length=%d \n",L.length);

    ListInsert(&L,1,0);
    printf("��L�ı�ͷ����0��L.data=");
    ListTraverse(L);
    printf("L.length=%d \n",L.length);

    GetElem(L,5,&e);
    printf("��5��Ԫ�ص�ֵΪ��%d\n",e);
    for(j=3;j<=4;j++)
    {
        k=LocateElem(L,j);
        if(k)
            printf("��%d��Ԫ�ص�ֵΪ%d\n",k,j);
        else
            printf("û��ֵΪ%d��Ԫ��\n",j);
    }


    k=ListLength(L); /* kΪ�� */
    for(j=k+1;j>=k;j--)
    {
        i=ListDelete(&L,j,&e); /* ɾ����j������ */
        if(i==ERROR)
            printf("ɾ����%d������ʧ��\n",j);
        else
            printf("ɾ����%d����Ԫ��ֵΪ��%d\n",j,e);
    }
    printf("�������L��Ԫ�أ�");
    ListTraverse(L);

    j=5;
    ListDelete(&L,j,&e); /* ɾ����5������ */
    printf("ɾ����%d����Ԫ��ֵΪ��%d\n",j,e);

    printf("�������L��Ԫ�أ�");
    ListTraverse(L);

    //����һ����10������Lb
    i=InitList(&Lb);
    for(j=6;j<=15;j++)
        i=ListInsert(&Lb,1,j);

    unionL(&L,Lb);

    printf("��������ϲ���Lb��L��Ԫ�أ�");
    ListTraverse(L);

    Del_Min(&L,&min);
    printf("ɾ����Сֵ����СֵΪ: %d\n", min);
    Del_Min(&L,&min);
    printf("ɾ����Сֵ����СֵΪ: %d\n", min);

    printf("��������ϲ���Lb��L��Ԫ�أ�");
    ListTraverse(L);

    Reverse(&L);
    printf("��������ϲ���Lb��L��Ԫ�أ�");
    ListTraverse(L);

    e = 5;
    ListInsert(&L,6,e);
    ListInsert(&L,6,e);
    ListInsert(&L,6,e);
    printf("������������5��L��Ԫ�أ�");
    ListTraverse(L);
    Del_X(&L, e);
    printf("�������ɾ����5��L��Ԫ�أ�");
    ListTraverse(L);


    Del_sTOt(&L,3,6);
    printf("�������ɾ��3-6���Ԫ�أ�");
    ListTraverse(L);

    ListInsert(&L,4,5);
    ListInsert(&L,4,5);
    ListInsert(&L,4,5);
    printf("������������5��L��Ԫ�أ�");
    ListTraverse(L);

    Del_Same(&L);
    printf("�������ɾ����ͬԪ�غ��Ԫ�أ�");
    ListTraverse(L);

    Test_Exchange();

    Test_SearchExchangeInsert();

    Test_Reverse_Left();

    Test_Mid_Array();

    Test_Find_Main_Num();

    Test_Find_Min_PositionNum();

    Test_Find_Min_Three();
    return 0;
}

