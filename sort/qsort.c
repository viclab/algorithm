//快速排序，C实现
//2014年 07月 30日 星期三 23:59:52 CST
#include <stdio.h>
#include <assert.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *arr, int start, int end)
{
    int pivot, i, j;
    pivot = arr[end];
    i = start - 1;
    
    for (j = start; j < end; ++j)
    {
        if (arr[j] <= pivot)
        {
            ++i;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[end]);

    return i + 1;
}

void quick_sort_core(int *arr, int start, int end)
{
    if (start < end)
    {
        int pivot_num = partition(arr, start, end);
        quick_sort_core(arr, start, pivot_num - 1);
        quick_sort_core(arr, pivot_num + 1, end);
    }
}

void quick_sort(int *arr, int n)
{
    assert(arr != NULL && n > 0);
    quick_sort_core(arr, 0, n - 1);
}

void print_array(int *arr, int n)
{
    assert(arr != NULL && n > 0);
    int i;
    for (i = 0; i < n; ++i)
        printf("%d\t", *(arr + i));
    printf("\n");
}

    

int main()
{
    int aArray[] = { 6, 8, 3, 2, 7, 1, 5};
    int n = sizeof(aArray) / sizeof(int);

    printf("数组排序前所有元素为:\n");
    print_array(aArray, n);

    quick_sort(aArray, n);
    printf("数组快速排序后所有元素为:\n");
    print_array(aArray, n);
    
    return 0;
}
    
