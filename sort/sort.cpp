#include <iostream>
#include <algorithm>
using namespace std;

void InsertSort(int arr[], int n)
{
    for(int i=0; i < n; ++i)
        for(int j=i; j > 0 && arr[j] < arr[j-1]; --j)
            swap<int>(arr[j], arr[j-1]);
}
            
int main()
{
    int a[] = { 5, 6, 3, 1, 2, 9 };
    InsertSort(a, 6);
    for(int i=0; i < 6; ++i)
        cout << a[i] << "\t";
    return 0;
}
