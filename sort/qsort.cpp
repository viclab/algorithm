//快速排序，C实现
//2014年 07月 30日 星期三 23:59:52 CST
#include <iostream>
#include <cassert>
using namespace std;

//交换两个变量的值
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

//快速排序划分算法
//思路：选取最后一个元素作为基准元素pivot，指定两个游标i,j
//  j指示所有处理过元素的边界, i指示所有小于pivot的边界
//  然后j从前之后扫描数组
//  如果比基准元素小,则递增i，同时交换i,j所知元素
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

int partition2(int *arr, int start, int end)
{
    int pivot = arr[start];
    int low, high;
    low = start;
    high = end;
    while(low < high)
    {
        while(low < high && arr[high] > pivot)
            --high;
        arr[low] = arr[high];
        
        while(low < high && arr[low] < pivot)
            ++low;
        arr[high] = arr[low];    
    }
    arr[low] = pivot;
    return low;
}

//注意调用quick_sort_core的实参+1/-1，遗漏可能导致死循环
void quick_sort_core(int *arr, int start, int end)
{
    if (start < end)
    {
        int pivot_num = partition2(arr, start, end);
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
    for (int i = 0; i < n; ++i)
        cout << *(arr + i) << "\t";
    cout << endl;
}

int main()
{
    int aArray[] = { 6, 8, 3, 2, 7, 1, 5};
    int n = sizeof(aArray) / sizeof(int);

    cout << "数组排序前所有元素为:" << endl;
    print_array(aArray, n);

    quick_sort(aArray, n);
    cout << "数组快速排序后所有元素为:" << endl;
    print_array(aArray, n);
    
    return 0;
}
    
